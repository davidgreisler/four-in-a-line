#include "Game.hpp"

#include <QDebug>
#include <stdexcept>

namespace Game
{
namespace FourInALine
{

/**
 * Creates a new game on a board with the given number of rows/columns.
 *
 * @param nRows Number of rows.
 * @param nColumns Number of columns.
 * @param firstMove Which player makes the first move. PLAYER_ONE or PLAYER_TWO. (Default:
 *        PLAYER_ONE).
 */
Game::Game(unsigned int nRows, unsigned int nColumns, Game::PlayerType firstMove)
	: winner(0), currentPlayer(firstMove)
{
	if (firstMove != Game::PLAYER_ONE && firstMove != Game::PLAYER_TWO)
	{
		throw std::runtime_error("First move argument must be either PLAYER_ONE or PLAYER_TWO.");
	}

	this->board = std::make_shared<Board>(nRows, nColumns);
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
 * Returns whether it is possible to undo the last move.
 *
 * @return When it is possible true, otherwise false.
 */
bool Game::isUndoPossible() const
{
	if (0 == this->moves.size())
	{
		return false;
	}

	return true;
}

/**
 * Undoes the last move.
 *
 * This method will also check for the winning condition, so it is possible that a game that was
 * over before this method was called is not over anymore after it was called!
 */
void Game::undoLastMove()
{
	if (!this->isUndoPossible())
	{
		throw std::runtime_error("Not possible to undo last move.");
	}

	std::pair<Game::PlayerType, unsigned int> lastMove = this->moves.back();
	this->moves.pop_back();

	this->board->removeToken(lastMove.second);
	this->currentPlayer = (this->currentPlayer == Game::PLAYER_ONE) ? Game::PLAYER_TWO : Game::PLAYER_ONE;

	this->checkWinningCondition();
}

/**
 * Returns whether the game is over or not.
 *
 * @return When it is over true, otherwise false.
 */
bool Game::isOver() const
{
	return (0 != this->winner) || this->board->isFull();
}

/**
 * Returns whether the game is a draw or not.
 *
 * @return When it is a draw true, otherwise false.
 */
bool Game::isDraw() const
{
	return (0 == this->winner) && this->board->isFull();
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
 * Checks if the winning condition is met, and if it is met, ends the game.
 */
void Game::checkWinningCondition()
{
	CellSet winningCells = this->board->findWinningCells();

	if (winningCells.isEmpty())
	{
		this->winner = 0;
	}
	else
	{
		this->winner = winningCells.getContent(0);
	}
}

}
}
