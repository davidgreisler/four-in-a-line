#include "Board.hpp"
#include "CellSet.hpp"

#include <QDebug>
#include <stdexcept>

namespace GameLogic
{

/**
 * Creates a new empty board with the given dimensions using the given value as empty token.
 *
 * @param nColumns Number of columns. Minimum 1.
 * @param nRows Number of rows. Minimum 1.
 * @param emptyToken Value to use as empty token.
 */
Board::Board(unsigned int nColumns, unsigned int nRows, TokenType emptyToken)
    : nRows(nRows), nColumns(nColumns), emptyToken(emptyToken)
{
	if (nRows < 1 || nColumns < 1)
	{
		throw std::domain_error("Number of columns/rows must be greater or equal 1.");
	}

	this->cells = std::vector<Board::TokenType>(nRows * nColumns, this->emptyToken);
}

/**
 * Copy constructor.
 *
 * @param board Board to copy.
 */
Board::Board(const Board& board)
    : nRows(board.nRows), nColumns(board.nColumns), emptyToken(board.emptyToken)
{
	this->cells = std::vector<Board::TokenType>(board.cells);
}

/**
 * Frees all used resources.
 */
Board::~Board()
{

}

/**
 * Clears the board (makes all cells empty).
 */
void Board::clear()
{
	std::fill(this->cells.begin(), this->cells.end(), this->emptyToken);
}

/**
 * Returns the number of rows on the board.
 *
 * @return Number of rows.
 */
unsigned int Board::getNumberOfRows() const
{
	return this->nRows;
}

/**
 * Returns the number of columns on the board.
 *
 * @return Number of columns.
 */
unsigned int Board::getNumberOfColumns() const
{
	return this->nColumns;
}

/**
 * Returns whether the specified row is full or not.
 *
 * @param y Position of the row on the y axis.
 * @return When the row is full true, otherwise false.
 */
bool Board::isRowFull(unsigned int y) const
{
	this->checkPosition(0, y);

	for (unsigned int i = 0; i < this->nColumns; ++i)
	{
		if (this->getCell(i, y) == this->emptyToken)
		{
			return false;
		}
	}

	return true;
}

/**
 * Returns whether the specified row is empty or not.
 *
 * @param y Position of the row on the y axis.
 * @return When the row is empty true, otherwise false.
 */
bool Board::isRowEmpty(unsigned int y) const
{
	this->checkPosition(0, y);

	for (unsigned int i = 0; i < this->nColumns; ++i)
	{
		if (this->getCell(i, y) != this->emptyToken)
		{
			return false;
		}
	}

	return true;
}

/**
 * Returns whether the given column is full or not.
 *
 * @param x Position of the column on the x axis.
 * @return When the column is full true, when it is not full false.
 */
bool Board::isColumnFull(unsigned int x) const
{
	this->checkPosition(x, 0);

	for (unsigned int i = 0; i < this->nRows; ++i)
	{
		if (this->getCell(x, i) == this->emptyToken)
		{
			return false;
		}
	}

	return true;
}

/**
 * Returns whether the given column is empty or not.
 *
 * @param x Position of the column on the x axis.
 * @return When the column is empty true, otherwise false.
 */
bool Board::isColumnEmpty(unsigned int x) const
{
	this->checkPosition(x, 0);

	for (unsigned int i = 0; i < this->nColumns; ++i)
	{
		if (this->getCell(x, i) != this->emptyToken)
		{
			return false;
		}
	}

	return true;
}

/**
 * Returns whether the board is full, i.e. all cells are occupied.
 *
 * @return When it is full true, otherwise false.
 */
bool Board::isFull() const
{
	for (auto i = this->cells.cbegin(); i != this->cells.cend(); ++i)
	{
		if (*i == this->emptyToken)
		{
			return false;
		}
	}

	return true;
}

/**
 * Returns whether the board contains only empty tokens.
 *
 * @return When the board contains only empty tokens true, otherwise false.
 */
bool Board::isEmpty() const
{
	for (auto i = this->cells.cbegin(); i != this->cells.cend(); ++i)
	{
		if (*i != this->emptyToken)
		{
			return false;
		}
	}

	return true;
}

/**
 * Returns the value that is used to represent an empty cell.
 *
 * @return Value used to represent an empty cell.
 */
Board::TokenType Board::getEmptyToken() const
{
	return this->emptyToken;
}

/**
 * Returns whether the cell at the given position is empty or not.
 *
 * @param x Position of the cell on the x axis.
 * @param y Position of the cell on the y axis.
 * @return When the cell is empty true, otherwise false.
 */
bool Board::isCellEmpty(unsigned int x, unsigned int y) const
{
	this->checkPosition(x, y);

	return this->getCell(x, y) == this->emptyToken;
}

/**
 * Returns whether the cell at the given position is occupied (not empty) or not.
 *
 * @param x Position of the cell on the x axis.
 * @param y Position of the cell on the y axis.
 * @return When the cell is occupied true, otherwise false.
 */
bool Board::isCellOccupied(unsigned int x, unsigned int y) const
{
	this->checkPosition(x, y);

	return !this->isCellEmpty(x, y);
}

/**
 * Returns content of cell at the given position.
 *
 * @param x Position of the cell on the x axis.
 * @param y Position of the cell on the y axis.
 * @return The token at the given position (can be an empty token).
 */
Board::TokenType Board::getCell(unsigned int x, unsigned int y) const
{
	this->checkPosition(x, y);

	return this->cells[y * this->nColumns + x];
}

/**
 * Sets the content of the cell at the given coordinates to the given token.
 *
 * @param x Position of the cell on the x axis.
 * @param y Position of the cell on the y axis.
 * @param token The token.
 */
void Board::setCell(unsigned int x, unsigned int y, Board::TokenType token)
{
	this->checkPosition(x, y);

	this->cells[y * this->nColumns + x] = token;
}

/**
 * Swaps the content of the given 2 cells.
 *
 * @param x1 Position of the first cell on the x axis.
 * @param y1 Position of the first cell on the y axis.
 * @param x2 Position of the second cell on the x axis.
 * @param y2 Position of the second cell on the y axis.
 */
void Board::swapCells(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
	this->checkPosition(x1, y1);
	this->checkPosition(x2, y2);

	unsigned int tempToken = this->getCell(x1, y1);
	this->setCell(x1, y1, this->getCell(x2, y2));
	this->setCell(x2, y2, tempToken);
}

/**
 * Returns a cell set referencing all cells in the given column.
 *
 * @param x Position of the column on the x axis.
 * @return Cell set referencing all cells in the column from first to last row.
 */
CellSet Board::getColumn(unsigned int x) const
{
	this->checkPosition(x, 0);

	CellSet result(this, x, 0, 0, 1, this->nRows);

	return result;
}

/**
 * Returns a cell set referencing all cells in the given row.
 *
 * @param y Position of the column on the y axis.
 * @return Cell set referencing all cells in the row from first to last column.
 */
CellSet Board::getRow(unsigned int y) const
{
	this->checkPosition(0, y);

	CellSet result(this, 0, y, 1, 0, this->nColumns);

	return result;
}

/**
 * Returns a cell set referencing all cells in the major diagonal that intersects the cell with the
 * given position.
 *
 * A major diagonal runs from the top left corner to the right bottom corner.
 *
 * @param x Position of the cell on the x axis.
 * @param y Position of the cell on the y axis.
 * @return Cell set referencing all cells in the major diagonal from the first to the last row.
 */
CellSet Board::getMajorDiagonal(unsigned int x, unsigned int y) const
{
	this->checkPosition(x, y);

	// Start at the first possible cell.

	unsigned int nCellsToFirstCell = std::min(x, y);
	x -= nCellsToFirstCell;
	y -= nCellsToFirstCell;

	// On the left bottom/top right edges, there will be less than nRows cells in the result.

	unsigned int nRemainingRows = std::min(this->nRows - y, this->nColumns - x);

	CellSet result(this, x, y, 1, 1, nRemainingRows);

	return result;
}

/**
 * Returns a cell set referencing all cells in the minor diagonal that intersects the cell with the
 * given position.
 *
 * A minor diagonal runs from the top right corner to the bottom left corner.
 *
 * @param x Position of the cell on the x axis.
 * @param y Position of the cell on the y axis.
 * @return Cell set referencing all cells in the minor diagonal from the first to the last row.
 */
CellSet Board::getMinorDiagonal(unsigned int x, unsigned int y) const
{
	this->checkPosition(x, y);

	// Start at the first possible cell.

	unsigned int nCellsToFirstCell = std::min(this->nColumns - x - 1, y);
	x += nCellsToFirstCell;
	y -= nCellsToFirstCell;

	// On the left top/bottom right edges, there will be less than nRows cells in the result.

	unsigned int nRemainingRows = std::min(x + 1, this->nRows - y);

	CellSet result(this, x, y, -1, 1, nRemainingRows);

	return result;
}

/**
 * Returns cell sets referencing all possible horizontal/vertical and diagonal rows.
 *
 * @return A vector containing a cell set for every possible row.
 */
std::vector<CellSet> Board::getAllRows() const
{
	std::vector<CellSet> result;

	// Horizontal rows.

	for(unsigned int i = 0; i < this->nRows; ++i)
	{
		result.push_back(this->getRow(i));
	}

	// Vertical rows (columns).

	for(unsigned int i = 0; i < this->nColumns; ++i)
	{
		result.push_back(this->getColumn(i));
	}

	// Minor diagonal rows.

	for(unsigned int i = 0; i < this->nColumns; ++i)
	{
		result.push_back(this->getMinorDiagonal(i, 0));
	}

	for(unsigned int i = 1; i < this->nRows; ++i)
	{
		result.push_back(this->getMinorDiagonal(this->nColumns - 1, i));
	}

	// Major diagonal rows.

	for(unsigned int i = 0; i < this->nColumns; ++i)
	{
		result.push_back(this->getMajorDiagonal(i, 0));
	}

	for(unsigned int i = 1; i < this->nRows; ++i)
	{
		result.push_back(this->getMajorDiagonal(0, i));
	}

	return result;
}

/**
 * Checks whether the given x and y positions are inside the board and throws an exception if not.
 *
 * @param x Position of the cell on the x axis.
 * @param y Position of the cell on the y axis.
 */
void Board::checkPosition(unsigned int x, unsigned int y) const
{
	if (x >= this->nColumns)
	{
		throw std::out_of_range("Position on the x-axis is greater or equal the number of columns.");
	}

	if (y >= this->nRows)
	{
		throw std::out_of_range("Position on the x-axis is greater or equal the number of rows.");
	}
}

}
