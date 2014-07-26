#include "Game.hpp"

#include <stdexcept>
#include <random>
#include <chrono>

namespace GameLogic
{
namespace FourInALine
{

const Game::PlayerType Game::PLAYER_ONE = 1;
const Game::PlayerType Game::PLAYER_TWO = 2;

/**
 * Creates a new game on a board with the given number of rows/columns.
 *
 * @param nRows Number of rows.
 * @param nColumns Number of columns.
 * @param firstMove Which player makes the first move. PLAYER_ONE or PLAYER_TWO. (Default:
 *        PLAYER_ONE).
 */
Game::Game(unsigned int nRows, unsigned int nColumns, Game::PlayerType firstMove)
    : winner(0), currentPlayer(firstMove), timedOutPlayer(0), timeoutAction(TimeoutAction::DRAW_GAME),
      isGameOver(false), timeLimit(0)
{
	if (firstMove != Game::PLAYER_ONE && firstMove != Game::PLAYER_TWO)
	{
		throw std::runtime_error("First move argument must be either PLAYER_ONE or PLAYER_TWO.");
	}

	/// @todo Use the same order for all classes (first nColumns then nRows or the other way around).

	this->board = std::make_shared<Board>(nColumns, nRows);
}

/**
 * Copy constructor.
 *
 * @param orig Game to copy.
 */
Game::Game(const Game& orig)
    : board(new Board(*(orig.board))), moves(orig.moves), winner(orig.winner),
      currentPlayer(orig.currentPlayer), timedOutPlayer(orig.timedOutPlayer),
      timeoutAction(orig.timeoutAction), isGameOver(orig.isGameOver), timeLimit(orig.timeLimit)
{

}

/**
 * Frees all used resources.
 */
Game::~Game()
{

}

/**
 * Returns the player who makes the next move.
 *
 * @return Current player.
 */
Game::PlayerType Game::getCurrentPlayer() const
{
	return this->currentPlayer;
}

/**
 * Returns the player who timed out.
 *
 * @return The player who timed out or 0 if no player timed out.
 */
Game::PlayerType Game::getPlayerWhoTimedOut() const
{
	return this->timedOutPlayer;
}

/**
 * Returns the player who makes the first move.
 *
 * @return Player id.
 */
Game::PlayerType Game::getPlayerWhoMakesFirstMove() const
{
	if (0 == (this->moves.size() % 2))
	{
		return this->currentPlayer;
	}
	else
	{
		return (this->currentPlayer == Game::PLAYER_ONE) ? Game::PLAYER_TWO : Game::PLAYER_ONE;
	}
}

/**
 * Returns whether a move is possible or not.
 *
 * @param column The column where a token should be dropped.
 * @return When it is possible to drop a token in the given column true, otherwise false.
 */
bool Game::isMovePossible(unsigned int column) const
{
	// No moves are possible after the game has ended.

	if (this->isOver())
	{
		return false;
	}

	// Check if it is possible to drop a token in the given column.

	if (!this->board->canDropToken(column))
	{
		return false;
	}

	return true;
}

/**
 * Makes a move, i.e. drops a token of the current player in the given column.
 *
 * @param column Column where the token is dropped.
 */
void Game::makeMove(unsigned int column)
{
	if (!this->isMovePossible(column))
	{
		throw std::runtime_error("Not possible to make move.");
	}

	this->board->dropToken(column, this->currentPlayer);
	this->moves.push_back(std::make_pair(this->currentPlayer, column));

	this->currentPlayer = (this->currentPlayer == Game::PLAYER_ONE) ? Game::PLAYER_TWO : Game::PLAYER_ONE;

	this->checkWinningCondition();
}

/**
 * Informs the game that the current player did not make a move within the time limit.
 *
 * This method will perform the configured timeout action. When the timeout action is RANDOM_MOVE,
 * this method will make a random move. When it is DRAW_GAME or LOSE_GAME, the game ends with a
 * draw/lose for the player who timed out.
 */
void Game::makeTimeoutMove()
{
	if (!this->hasTimeLimit())
	{
		throw std::runtime_error("This game has no time limit.");
	}

	if (this->timeoutAction == TimeoutAction::RANDOM_MOVE)
	{
		this->makeRandomMove();
	}
	else
	{
		this->timedOutPlayer = this->currentPlayer;

		this->checkWinningCondition();
	}
}

/**
 * Makes a random move, i.e. drops a token of the current player in a free column.
 *
 * Do not call this method when the game is over/no more moves are possible.
 */
void Game::makeRandomMove()
{
	if (this->isOver())
	{
		throw std::runtime_error("Not possible to make random move, game is over.");
	}

	auto availableColumns = this->board->getAvailableColumns();
	auto millisecondsSinceEpoch = std::chrono::system_clock::now().time_since_epoch() /
	                              std::chrono::milliseconds(1);

	static std::mt19937 randomNumberGenerator(millisecondsSinceEpoch);
	std::uniform_int_distribution<unsigned int> distribution(0, availableColumns.size() - 1);

	auto columnNo = distribution(randomNumberGenerator);

	this->makeMove(availableColumns.at(columnNo));
}

/**
 * Returns whether it is possible to undo the last move.
 *
 * @return When it is possible true, otherwise false.
 */
bool Game::isUndoPossible() const
{
	if (0 == this->moves.size() && !this->isTimeout())
	{
		return false;
	}

	return true;
}

/**
 * Undoes the last move.
 *
 * When the game is over because the player timed out, this will undo that and the player can make
 * a move again.
 *
 * This method will also check for the winning condition, so it is possible that a game that was
 * over before this method was called is not over anymore after it was called!
 */
void Game::undoLastMove()
{
	if (this->isUndoPossible())
	{
		if (this->isOver() && this->isTimeout())
		{
			// Game is over because the player timed out. Undo that and let him try again.

			this->timedOutPlayer = 0;
		}
		else
		{
			// Just undo the last move.

			std::pair<Game::PlayerType, unsigned int> lastMove = this->moves.back();
			this->moves.pop_back();

			this->board->removeToken(lastMove.second);
			this->currentPlayer = (this->currentPlayer == Game::PLAYER_ONE) ? Game::PLAYER_TWO : Game::PLAYER_ONE;
		}

		this->checkWinningCondition();
	}
	else
	{
		throw std::runtime_error("Not possible to undo last move.");
	}
}

/**
 * Returns whether the game is over or not.
 *
 * @return When it is over true, otherwise false.
 */
bool Game::isOver() const
{
	return this->isGameOver;
}

/**
 * Returns whether the game is a draw or not.
 *
 * @return When it is a draw true, otherwise false.
 */
bool Game::isDraw() const
{
	return (0 == this->winner) && this->isGameOver;
}

/**
 * Returns whether this game is over because a player timed out.
 *
 * @return When it is over because a player timed out true, otherwise false.
 */
bool Game::isTimeout() const
{
	return this->timedOutPlayer != 0;
}

/**
 * Returns the winner of the game.
 *
 * Do not call this method when the game is not over yet.
 *
 * @see Game::isOver() To check whether the game is over.
 * @return Player number.
 */
Game::PlayerType Game::getWinner() const
{
	if (0 == this->winner)
	{
		throw std::runtime_error("There is no winner.");
	}

	return this->winner;
}

/**
 * Returns whether there is a time limit set for this game or not.
 *
 * @return When there is a time limit true, otherwise false.
 */
bool Game::hasTimeLimit() const
{
	return this->timeLimit > 0;
}

/**
 * Returns the time limit for a move.
 *
 * @return The time limit, in seconds.
 */
unsigned int Game::getTimeLimit() const
{
	return this->timeLimit;
}

/**
 * Sets the time limit for a move.
 *
 * @param timeLimit The time limit, in seconds.
 */
void Game::setTimeLimit(unsigned int timeLimit)
{
	this->timeLimit = timeLimit;
}

/**
 * Returns the action for when a player times out.
 *
 * @return Timeout action.
 */
Game::TimeoutAction Game::getTimeoutAction() const
{
	return this->timeoutAction;
}

/**
 * Sets the action for when a player times out.
 *
 * @param action Timeout action.
 */
void Game::setTimeoutAction(Game::TimeoutAction action)
{
	this->timeoutAction = action;
}

/**
 * Computes and returns the x/y coordinates of the token dropped in the given move.
 *
 * @param moveNo Number of the move.
 * @return X/Y coordinates of the token.
 */
std::pair<unsigned int, unsigned int> Game::computeMovePosition(unsigned int moveNo) const
{
	if (moveNo >= this->getNumberOfMoves())
	{
		throw std::out_of_range("Move number must be smaller or equal to the number of moves.");
	}

	unsigned int x;
	unsigned int y;
	auto replay = this->getReplay();

	x = replay.at(moveNo).second;
	y = this->board->getNumberOfRows() - 1;

	for (unsigned int i = 0; i < moveNo; ++i)
	{
		if (replay.at(i).second == x)
		{
			y--;
		}
	}

	return std::make_pair(x, y);
}

/**
 * Returns a replay of the game.
 *
 * @return Vector containing pairs, first element is the player number, second element is the column
 *         where the token was inserted.
 */
const std::vector<std::pair<Game::PlayerType, unsigned int> >& Game::getReplay() const
{
	return this->moves;
}

/**
 * Returns the number of moves made yet.
 *
 * @return Number of moves.
 */
unsigned int Game::getNumberOfMoves() const
{
	return this->moves.size();
}

/**
 * Returns the game board.
 *
 * @return The game board.
 */
std::shared_ptr<const Board> Game::getBoard() const
{
	return this->board;
}

/**
 * Checks if the winning condition is met or the game is over and if yes, ends the game.
 */
void Game::checkWinningCondition()
{
	this->isGameOver = false;
	this->winner = 0;
	CellSet winningCells = this->board->findWinningCells();

	// Check if there is a winner.

	if (!winningCells.isEmpty())
	{
		this->isGameOver = true;
		this->winner = winningCells.getContent(0);
	}

	// Check whether a player timed out.

	else if (this->timedOutPlayer != 0)
	{
		if (this->timeoutAction == TimeoutAction::DRAW_GAME)
		{
			this->isGameOver = true;
		}
		else if (this->timeoutAction == TimeoutAction::LOSE_GAME)
		{
			this->isGameOver = true;
			this->winner = (this->currentPlayer == Game::PLAYER_ONE) ? Game::PLAYER_TWO : Game::PLAYER_ONE;
		}
	}

	// Check whether the board is full.

	else if (this->board->isFull())
	{
		this->isGameOver = true;
	}
}

}
}
