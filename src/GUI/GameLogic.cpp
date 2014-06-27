#include "GameLogic.hpp"
#include "Game.hpp"
#include "../Game/FourInALine/AsynchronousArtificialIntelligence.hpp"

#include <QDebug>
#include <QTimer>

namespace GUI
{

/**
 * Creates a new game logic.
 *
 * @param parent Parent object.
 */
GameLogic::GameLogic(QObject *parent) :
    QObject(parent), moveRequested(false)
{
	this->timeLimitTimer = new QTimer(this);
	this->timeLimitTimer->setInterval(1000);

	this->connect(this->timeLimitTimer, &QTimer::timeout, this, &GameLogic::updateRemainingTime);
}

/**
 * Frees all used resources.
 */
GameLogic::~GameLogic()
{
	this->endGame();
}

/**
 * Starts a new game.
 *
 * @param game The game to start.
 */
void GameLogic::startGame(QSharedPointer<Game> game)
{
	this->game = game;
	this->moveRequested = false;

	qDebug() << "[" << this << "::startGame ] " << "Started new game.";
	qDebug() << "[" << this << "::startGame ] " << "Player 1:" << game->getFirstPlayer()->getName();
	qDebug() << "[" << this << "::startGame ] " << "Player 2:" << game->getSecondPlayer()->getName();

	this->connect(this->game->getFirstPlayer().data(), &AbstractPlayer::moveReady, this,
	              &GameLogic::makeMove);
	this->connect(this->game->getSecondPlayer().data(), &AbstractPlayer::moveReady, this,
	              &GameLogic::makeMove);

	emit this->gameStarted(game->getGameEngine()->getBoard()->getNumberOfColumns(),
	                       game->getGameEngine()->getBoard()->getNumberOfRows(),
	                       game->getFirstPlayer(),
	                       game->getSecondPlayer());

	this->requestNextMove();
}

/**
 * Ends the current game.
 */
void GameLogic::endGame()
{
	qDebug() << "[" << this << "::endGame ] " << "Ended game.";

	this->abortRequest();
	this->game.reset();

	emit this->gameEnded();
}

/**
 * Shows a hint for the next move a player could make.
 */
void GameLogic::showHint()
{
	qDebug() << "[" << this << "::showHint ] " << "Show hint";

	// @todo Implement.
}

/**
 * Undoes the last move.
 */
void GameLogic::undoLastMove()
{
	qDebug() << "[" << this << "::undoLastMove ] " << "Undo last move";

	bool gameWasOverBefore = this->game->getGameEngine()->isOver();

	this->abortRequest();

	auto nMoves = this->game->getGameEngine()->getNumberOfMoves();

	auto position = this->game->getGameEngine()->computeMovePosition(nMoves - 1);
	this->game->getGameEngine()->undoLastMove();

	emit this->removeCell(position.first, position.second);

	position = this->game->getGameEngine()->computeMovePosition(nMoves - 2);
	this->game->getGameEngine()->undoLastMove();

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
void GameLogic::makeMove(unsigned int x)
{
	qDebug() << "[" << this << "::makeMove ] " << "Player " << game->getCurrentPlayer()->getName()
	         << " made a move, token dropped in column " << x;

	this->moveRequested = false;
	this->timeLimitTimer->stop();
	this->game->getGameEngine()->makeMove(x);

	auto moveNo = this->game->getGameEngine()->getNumberOfMoves() - 1;
	auto position = this->game->getGameEngine()->computeMovePosition(moveNo);

	emit this->endPlayerTurn();
	emit this->setCell(position.first, position.second, this->game->getCurrentPlayer());

	if (!this->checkGameOver())
	{
		this->requestNextMove();
	}
}

/**
 * Decrements remaining seconds by one and makes a timeout move when the player's time is up.
 */
void GameLogic::updateRemainingTime()
{
	this->remainingSeconds--;

	emit this->remainingTimeChanged(this->game->getGameEngine()->getTimeLimit(), this->remainingSeconds);

	if (0 == this->remainingSeconds)
	{
		qDebug() << "[" << this << "::updateRemainingTime ] " << "Player " << game->getCurrentPlayer()->getName()
		         << " timed out.";

		this->timeLimitTimer->stop();
		this->game->getGameEngine()->makeTimeoutMove();
		this->checkGameOver();
	}
}

/**
 * Checks whether the game is over and if yes stops timer and emits gameOver().
 *
 * @return When it is over true, otherwise false.
 */
bool GameLogic::checkGameOver()
{
	QSharedPointer< ::Game::FourInALine::Game> game = this->game->getGameEngine();

	if (game->isOver())
	{
		qDebug() << "[" << this << "::checkGameOver ] " << "Game is over.";

		this->abortRequest();

		if (this->game->getGameEngine()->hasTimeLimit())
		{
			this->remainingSeconds = 0;
			this->timeLimitTimer->stop();
		}

		emit this->gameOver();

		return true;
	}

	return false;
}

/**
 * Aborts current request for the next move if there is one.
 */
void GameLogic::abortRequest()
{
	if (!this->moveRequested)
	{
		return;
	}

	qDebug() << "[" << this << "::abortRequest ] " << "Aborting request for next move by "
	         << game->getCurrentPlayer()->getName() << ".";

	if (this->game->getGameEngine()->hasTimeLimit())
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
void GameLogic::requestNextMove()
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

	if (this->game->getGameEngine()->hasTimeLimit())
	{
		this->remainingSeconds = this->game->getGameEngine()->getTimeLimit();
		this->timeLimitTimer->start();
	}
}

}
