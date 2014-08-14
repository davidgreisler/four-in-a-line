#include "GameController.hpp"
#include "Game.hpp"
#include "../GameLogic/FourInALine/Game.hpp"
#include "../GameLogic/FourInALine/AAI.hpp"
#include "../Highscore/database.h"
#include "../../app/FourInALine.hpp"

#include <QDebug>
#include <QTimer>

namespace Game
{

/**
 * Creates a new game controller.
 *
 * @param parent Parent object.
 */
GameController::GameController(QObject *parent) :
    QObject(parent), moveRequested(false), artificialIntelligence(4)
{
	this->timeLimitTimer = new QTimer(this);
	this->timeLimitTimer->setInterval(1000);

	this->artificialIntelligenceTimer = new QTimer(this);
	this->artificialIntelligenceTimer->setInterval(100);

	this->connect(this->timeLimitTimer, &QTimer::timeout, this, &GameController::updateRemainingTime);
	this->connect(this->artificialIntelligenceTimer, &QTimer::timeout, this, &GameController::checkHintReady);
}

/**
 * Frees all used resources.
 */
GameController::~GameController()
{
	this->endGame();
}

/**
 * Starts a new game.
 *
 * @param game The game to start.
 */
void GameController::startGame(QSharedPointer<Game> game)
{
	this->game = game;
	this->moveRequested = false;

	qDebug() << "[" << this << "::startGame ] " << "Started new game.";
	qDebug() << "[" << this << "::startGame ] " << "Player 1:" << game->getFirstPlayer()->getName();
	qDebug() << "[" << this << "::startGame ] " << "Player 2:" << game->getSecondPlayer()->getName();

	this->connect(this->game->getFirstPlayer().data(), &::Game::Players::AbstractPlayer::moveReady, this,
	              &::Game::GameController::makeMove);
	this->connect(this->game->getSecondPlayer().data(), &::Game::Players::AbstractPlayer::moveReady, this,
	              &::Game::GameController::makeMove);

	emit this->gameStarted(game->getGameLogic()->getBoard()->getNumberOfColumns(),
	                       game->getGameLogic()->getBoard()->getNumberOfRows(),
	                       game->getFirstPlayer(),
	                       game->getSecondPlayer(),
	                       game->getGameLogic()->hasTimeLimit());

	// Replay moves already made in case this game was loaded from a savegame.

	auto replay = game->getGameLogic()->getReplay();
	for (unsigned int i = 0; i < replay.size(); ++i)
	{
		auto player = game->playerIdToPlayer(replay[i].first);
		auto movePosition = game->getGameLogic()->computeMovePosition(i);

		emit this->startPlayerTurn(player);
		emit this->setCell(movePosition.first, movePosition.second, player);
		emit this->endPlayerTurn();
	}

	this->requestNextMove();
}

/**
 * Ends the current game.
 */
void GameController::endGame()
{
	qDebug() << "[" << this << "::endGame ] " << "Ended game.";

	this->abortRequest();
	this->game.reset();

	emit this->gameEnded();
}

/**
 * Shows a hint for the next move a player could make.
 */
void GameController::showHint()
{
	qDebug() << "[" << this << "::showHint ] " << "Show hint";

	if (!this->artificialIntelligence.isComputing())
	{
		this->artificialIntelligence.computeNextMoveAsynchronously(*this->game->getGameLogic());
		this->artificialIntelligenceTimer->start();
	}
}

/**
 * Undoes the last move.
 */
void GameController::undoLastMove()
{
	qDebug() << "[" << this << "::undoLastMove ] " << "Undo last move";

	bool gameWasOverBefore = this->game->getGameLogic()->isOver();

	this->abortRequest();

	if (gameWasOverBefore)
	{
		auto winningCells = this->game->getGameLogic()->getBoard()->findWinningCells();

		for (auto it = winningCells.begin(); it != winningCells.end(); it++)
		{
			emit this->setCellHighlighted(it.getXPosition(), it.getYPosition(), false);
		}
	}

	auto nMoves = this->game->getGameLogic()->getNumberOfMoves();

	auto position = this->game->getGameLogic()->computeMovePosition(nMoves - 1);
	this->game->getGameLogic()->undoLastMove();

	emit this->removeCell(position.first, position.second);

	position = this->game->getGameLogic()->computeMovePosition(nMoves - 2);
	this->game->getGameLogic()->undoLastMove();

	emit this->removeCell(position.first, position.second);

	if (gameWasOverBefore)
	{
		emit this->gameNotOverAnymore();
	}

	this->requestNextMove();
}

/**
 * Makes a move at the given position.
 *
 * @param x X position of the column in which the token should be dropped.
 */
void GameController::makeMove(unsigned int x)
{
	qDebug() << "[" << this << "::makeMove ] " << "Player " << game->getCurrentPlayer()->getName()
	         << " made a move, token dropped in column " << x;

	auto currentPlayer = game->getCurrentPlayer();

	this->moveRequested = false;
	this->timeLimitTimer->stop();
	this->game->getGameLogic()->makeMove(x);

	auto moveNo = this->game->getGameLogic()->getNumberOfMoves() - 1;
	auto position = this->game->getGameLogic()->computeMovePosition(moveNo);

	emit this->setCell(position.first, position.second, currentPlayer);
	emit this->endPlayerTurn();

	if (!this->checkGameOver())
	{
		this->requestNextMove();
	}
}

/**
 * Decrements remaining seconds by one and makes a timeout move when the player's time is up.
 */
void GameController::updateRemainingTime()
{
	auto RANDOM_MOVE = ::GameLogic::FourInALine::Game::TimeoutAction::RANDOM_MOVE;

	this->remainingSeconds--;

	emit this->remainingTimeChanged(this->game->getGameLogic()->getTimeLimit(), this->remainingSeconds);

	if (0 == this->remainingSeconds)
	{
		qDebug() << "[" << this << "::updateRemainingTime ] " << "Player "
		         << game->getCurrentPlayer()->getName() << " timed out.";

		this->game->getGameLogic()->makeTimeoutMove();

		if (this->game->getGameLogic()->getTimeoutAction() == RANDOM_MOVE)
		{
			this->moveRequested = false;
			this->timeLimitTimer->stop();

			auto moveNo = this->game->getGameLogic()->getNumberOfMoves() - 1;
			auto position = this->game->getGameLogic()->computeMovePosition(moveNo);

			emit this->endPlayerTurn();
			emit this->setCell(position.first, position.second, this->game->getCurrentPlayer());
		}
		else
		{
			this->abortRequest();
		}

		// When the timeout action is RANDOM_MOVE, the game is probably not over after a timeout.

		if (!this->checkGameOver())
		{
			this->requestNextMove();
		}
	}
}

/**
 * Checks whether the game is over and if yes stops timer and emits gameOver().
 *
 * @return When it is over true, otherwise false.
 */
bool GameController::checkGameOver()
{
	QSharedPointer< ::GameLogic::FourInALine::Game> game = this->game->getGameLogic();

	if (game->isOver())
	{
		auto board = game->getBoard();
		auto winningCells = board->findWinningCells();

		qDebug() << "[" << this << "::checkGameOver ] " << "Game is over.";

		this->abortRequest();

		if (this->game->getGameLogic()->hasTimeLimit())
		{
			this->remainingSeconds = 0;
			this->timeLimitTimer->stop();
		}

		for (auto it = winningCells.begin(); it != winningCells.end(); it++)
		{
			emit this->setCellHighlighted(it.getXPosition(), it.getYPosition(), true);
		}

        if (this->game->isSavingHighscore())
        {
            Database* database = ::FourInALine::getInstance()->getDatabase();
            int result = 0;
            if (game->isDraw())
                result = 2;
            else if (this->game->getWinningPlayer() == this->game->getFirstPlayer())
                result = 1;
            database->insertHighscore(this->game->getFirstPlayer()->getName(), this->game->getSecondPlayer()->getName(), result);
        }

		emit this->gameOver(game->isDraw());

		// this->game could be a new game after gameOver has been emitted!

		return true;
	}

	return false;
}

/**
 * Aborts current request for the next move if there is one.
 */
void GameController::abortRequest()
{
	if (!this->moveRequested)
	{
		return;
	}

	qDebug() << "[" << this << "::abortRequest ] " << "Aborting request for next move by "
	         << game->getCurrentPlayer()->getName() << ".";

	if (this->game->getGameLogic()->hasTimeLimit())
	{
		this->remainingSeconds = 0;
		this->timeLimitTimer->stop();
	}

	emit this->endPlayerTurn();

	this->game->getCurrentPlayer()->abortMove();

	this->moveRequested = false;
}

/**
 * Requests next move from the current player and starts timer if there is a time limit.
 */
void GameController::requestNextMove()
{
	qDebug() << "[" << this << "::requestNextMove ] " << "Requesting next move from player "
	         << this->game->getCurrentPlayer()->getName() << ".";

	if (this->moveRequested)
	{
		qDebug() << "[" << this << "::requestNextMove ] " << "ERROR: There is already a move request.";

		this->abortRequest();
	}

	emit this->startPlayerTurn(this->game->getCurrentPlayer());

	this->game->getCurrentPlayer()->requestMove(this->game);
	this->moveRequested = true;

	if (this->game->getGameLogic()->hasTimeLimit())
	{
		this->remainingSeconds = this->game->getGameLogic()->getTimeLimit();
		this->timeLimitTimer->start();
	}
}

/**
 * Checks whether the AI has finished computing the hint and emits the according signal if so.
 */
void GameController::checkHintReady()
{
	if (this->artificialIntelligence.isNextMoveReady())
	{
		unsigned int nColumns = this->game->getGameLogic()->getBoard()->getNumberOfColumns();

		std::vector<int> columnScores(nColumns);
		for (unsigned int i = 0; i < nColumns; ++i)
		{
			columnScores[i] = -1;
		}

		unsigned int nextMove = this->artificialIntelligence.getNextMove();
		columnScores[nextMove] = 100;

		emit this->showColumnHints(columnScores);

		this->artificialIntelligenceTimer->stop();
	}
}

}
