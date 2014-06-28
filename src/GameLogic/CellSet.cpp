#include "CellSet.hpp"
#include "Board.hpp"

#include <QDebug>
#include <stdexcept>

namespace GameLogic
{

/**
 * Creates an empty cell set.
 */
CellSet::CellSet()
    : board(0), startX(0), startY(0), deltaX(0), deltaY(0), length(0)
{

}

/**
 * Creates a new cell set referencing cells on the given board.
 *
 * The first cell is the one with the given startX/startY position. The cell set contains as many
 * cells as defined with length, using deltaX/deltaY to compute the positions of the other cells.
 *
 * @param board The board on which the cells are located.
 * @param startX X position of the first cell.
 * @param startY Y position of the first cell.
 * @param deltaX Added to the x position to get the next cell.
 * @param deltaY Added to the y position to get the next cell.
 * @param length Length of the cell set.
 */
CellSet::CellSet(const Board* board, unsigned int startX, unsigned int startY, int deltaX,
                 int deltaY, unsigned int length)
    : board(board), startX(startX), startY(startY), deltaX(deltaX), deltaY(deltaY), length(length)
{

}

/**
 * Copy constructor.
 *
 * @param orig Original object.
 */
CellSet::CellSet(const CellSet& orig)
    : board(orig.board), startX(orig.startX), startY(orig.startY), deltaX(orig.deltaX),
      deltaY(orig.deltaY), length(orig.length)
{

}

/**
 * Frees all used resources.
 */
CellSet::~CellSet()
{

}

/**
 * Copy the state of the given cell set to this cell set.
 *
 * @param rhs The other cell set.
 * @return This cell set.
 */
CellSet&CellSet::operator=(const CellSet& rhs)
{
	if (this != &rhs)
	{
		this->board = rhs.board;
		this->startX = rhs.startX;
		this->startY = rhs.startY;
		this->deltaX = rhs.deltaX;
		this->deltaY = rhs.deltaY;
		this->length = rhs.length;
	}

	return *this;
}

/**
 * Returns the content of the cell at the given index.
 *
 * @param index Index of the cell.
 * @return The content of the cell.
 */
Board::TokenType CellSet::getContent(unsigned int index) const
{
	std::pair<unsigned int, unsigned int> position = this->getCellPosition(index);

	return this->board->getCell(position.first, position.second);
}

/**
 * Returns a vector containing the contents of all cells in this set.
 *
 * @return Vector containing contents of all cells in this set.
 */
std::vector<Board::TokenType> CellSet::getContents() const
{
	std::vector<unsigned int> contents(this->length);

	CellSetIterator it;

	for (it = this->begin(); it != this->end(); it++)
	{
		contents[it.getIndex()] = it.getContent();
	}

	return contents;
}

/**
 * Returns an iterator pointing to the first cell in the set.
 *
 * @return Iterator.
 */
CellSetIterator CellSet::begin() const
{
	return CellSetIterator(this, 0);
}

/**
 * Returns an iterator positioned one cell after the last cell in the set.
 *
 * @return Iterator.
 */
CellSetIterator CellSet::end() const
{
	return CellSetIterator(this, this->length);
}

/**
 * Returns the X/Y coordinates of the cell at the given index.
 *
 * @param index Index of the cell.
 * @return Pair with X coordinate as first element and Y coordinate as second element.
 */
std::pair<unsigned int, unsigned int> CellSet::getCellPosition(unsigned int index) const
{
	return std::make_pair(this->getCellXPosition(index), this->getCellYPosition(index));
}

/**
 * Returns the X position of the cell at the given index.
 *
 * @param index Index of the cell.
 * @return X position.
 */
unsigned int CellSet::getCellXPosition(unsigned int index) const
{
	this->checkIndex(index);

	unsigned int x = this->startX + (this->deltaX * index);

	return x;
}

/**
 * Returns the Y position of the cell at the given index.
 *
 * @param index Index of the cell.
 * @return Y position.
 */
unsigned int CellSet::getCellYPosition(unsigned int index) const
{
	this->checkIndex(index);

	unsigned int y = this->startY + (this->deltaY * index);

	return y;
}

/**
 * Returns a vector containing the coordinates of all cells in this set.
 *
 * @return Vector containing pairs with the first element being the X position and the second
 *         element being the Y position.
 */
std::vector<std::pair<unsigned int, unsigned int> > CellSet::getCellPositions() const
{
	std::vector<std::pair<unsigned int, unsigned int> > result;

	for (unsigned int i = 0; i < this->length; ++i)
	{
		result.push_back(this->getCellPosition(i));
	}

	return result;
}

/**
 * Returns the length of the cell set.
 *
 * @return Length of the cell set.
 */
unsigned int CellSet::getLength() const
{
	return this->length;
}

/**
 * Returns delta X.
 *
 * The delta X value is used to determine the position of cells in the set. When a cell is retrieved
 * from the set, the cell index is multiplied by the delta X value, and then the result is added to
 * the X position of the first cell in the set.
 *
 * @return Delta X.
 */
int CellSet::getDeltaX() const
{
	return this->deltaX;
}

/**
 * Returns delta Y.
 *
 * @return Delta Y.
 */
int CellSet::getDeltaY() const
{
	return this->deltaY;
}

/**
 * Returns whether the cell set is empty.
 *
 * @return When it is empty true, otherwise false.
 */
bool CellSet::isEmpty() const
{
	return this->length == 0;
}

/**
 * Checks whether the given index is valid and throws an exception if not.
 *
 * @param index The index to check.
 */
void CellSet::checkIndex(unsigned int index) const
{
	if (index >= this->length)
	{
		throw std::out_of_range("Index is out of range.");
	}
}

}
