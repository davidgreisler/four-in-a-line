#include "Board.hpp"

#include <QDebug>
#include <stdexcept>

namespace GameLogic
{
namespace FourInALine
{

const ::GameLogic::Board::TokenType Board::CELL_EMPTY = 0;

/**
 * Creates a new empty four in a line board with the given dimensions.
 *
 * @param nColumns Number of columns. Minimum 1.
 * @param nRows Number of rows. Minimum 1.
 */
Board::Board(unsigned int nColumns, unsigned int nRows)
    : ::GameLogic::Board(nColumns, nRows, Board::CELL_EMPTY)
{

}

/**
 * Copy constructor.
 *
 * @param board Board to copy.
 */
Board::Board(const Board& board)
    : ::GameLogic::Board(board)
{

}

/**
 * Frees all used resources.
 */
Board::~Board()
{

}

/**
 * Returns whether it is possible to drop a token in the specified column.
 *
 * @param x Which column to check.
 * @return When it is possible true, otherwise false.
 */
bool Board::canDropToken(unsigned int x) const
{
	return !this->isColumnFull(x);
}

/**
 * Drops the given token into the given column.
 *
 * The token will fall straight through and occupy the lowest empty cell. Make sure to check whether
 * a token can be dropped in the column before with canDropToken().
 *
 * @param x Position of the token on the x axis (column).
 * @param token The token.
 * @see Board::canDropToken() To check whether a token can be dropped in this column.
 */
void Board::dropToken(unsigned int x, TokenType token)
{
	if (this->canDropToken(x))
	{
		for (unsigned int i = this->nRows; i-- != 0;)
		{
			if (this->isCellEmpty(x, i))
			{
				// Lowest empty cell found, drop token here.

				this->setCell(x, i, token);
				return;
			}
		}
	}

	throw std::runtime_error("Can't drop token in given column.");
}

/**
 * Removes a token from the top of the column, replacing it with an empty cell.
 *
 * @param x Position of the cell on the x axis.
 */
void Board::removeToken(unsigned int x)
{
	if (this->isColumnEmpty(x))
	{
		throw std::runtime_error("Cannot remove token, column is already empty.");
	}

	for (unsigned int i = 0; i < this->nRows; ++i)
	{
		if (this->isCellOccupied(x, i))
		{
			this->setCell(x, i, Board::CELL_EMPTY);
			break;
		}
	}
}

/**
 * Removes a token, replacing it with an empty cell.
 *
 * Tokens above the removed token will fall down one cell.
 *
 * @param x Position of the cell on the x axis.
 * @param y Position of the cell on the y axis.
 */
void Board::removeToken(unsigned int x, unsigned int y)
{
	if (this->isCellEmpty(x, y))
	{
		throw std::runtime_error("Cannot remove token, cell is already empty.");
	}

	this->setCell(x, y, Board::CELL_EMPTY);

	while (y > 0 && this->isCellOccupied(x, y - 1))
	{
		this->swapCells(x, y - 1, x, y);
		y--;
	}
}

/**
 * @copydoc ::Game::Board::isColumnFull()
 *
 * This method is optimized for four in a line, because in this game it is only necessary to check
 * the top cell to see whether a column is full.
 */
bool Board::isColumnFull(unsigned int x) const
{
	bool result = true;

	if (this->isCellEmpty(x, 0))
	{
		result = false;
	}

	return result;
}

/**
 * @copydoc ::Game::Board::isColumnEmpty()
 *
 * This method is optimized for four in a line, because in this game it is only necessary to check
 * the bottom cell to see whether a column is full.
 */
bool Board::isColumnEmpty(unsigned int x) const
{
	bool result = false;

	if (this->isCellEmpty(x, this->nRows - 1))
	{
		result = true;
	}

	return result;
}

/**
 * Returns a vector containing positions on the x-axis of all columns in which a token can be dropped.
 *
 * @return Vector containing columns in which a token can be dropped.
 */
std::vector<unsigned int> Board::getAvailableColumns() const
{
	std::vector<unsigned int> columns;

	for(unsigned int i = 0; i < this->nColumns; ++i)
	{
		if (this->canDropToken(i))
		{
			columns.push_back(i);
		}
	}

	return columns;
}

/**
 * Finds and returns the cells that won the game.
 *
 * @return Cell set referencing the winning cells or empty cell set if game isn't won yet.
 */
CellSet Board::findWinningCells() const
{
	CellSet result;
	auto sets = this->getAllRows();
	std::vector<CellSet>::const_iterator i;
	unsigned int nConsecutive = 1;
	::GameLogic::Board::TokenType lastToken;
	auto emptyToken = this->getEmptyToken();

	for (i = sets.begin(); i != sets.end() && nConsecutive != 4; i++)
	{
		nConsecutive = 1;
		lastToken = emptyToken;

		for(CellSetIterator j = i->begin(); j != i->end(); j++)
		{
			if (lastToken == *j && emptyToken != *j)
			{
				nConsecutive++;
			}
			else
			{
				lastToken = *j;
				nConsecutive = 1;
			}

			if (nConsecutive == 4)
			{
				unsigned int startX = i->getCellXPosition(j.getIndex() - 3);
				unsigned int startY = i->getCellYPosition(j.getIndex() - 3);

				result = CellSet(this, startX, startY, i->getDeltaX(), i->getDeltaY(), 4);
				break;
			}
		}
	}

	return result;
}

}
}
