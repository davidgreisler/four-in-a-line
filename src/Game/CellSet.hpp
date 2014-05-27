#ifndef GAME_CELLSET_HPP
#define GAME_CELLSET_HPP

#include "CellSetIterator.hpp"
#include "Board.hpp"

#include <vector>
#include <utility>

namespace Game
{

/**
 * A set of cells on the game board.
 *
 * This class represents a set of cells on the board. It allows you to work with a set of cells
 * without having to concern about their position. It provides methods to retrieve the contents
 * and positions of the cells, and to iterate over the cells.
 *
 * A cell set is defined through the position of the first cell (startX/startY), the length of the
 * set and the deltaX/deltaY values, which are added to the first cell's coordinates to get the
 * coordinates of the next cell.
 *
 * The getContent(index) method can be used to retrieve the content of the cell with the given index.
 * Use getContents() to retrieve a vector with all cell contents.
 *
 * The class also provides an iterator: CellSetIterator. Use begin() to get an iterator pointing at
 * the first cell, and end() to get an iterator positioned after the last cell.
 *
 * The position/coordinates of a cell can be retrieved with getCellPosition(index). The
 * getCellXPosition(index)/getCellYPosition(index) methods return only the X/Y position of the cell
 * and getCellPositions() returns a vector containing all positions.
 *
 * It is possible to check whether a cell set is empty using isEmpty().
 *
 * This class is reentrant but not thread-safe.
 */
class CellSet
{
	public:
		CellSet();
		CellSet(const Board* board, unsigned int startX, unsigned int startY,
				int deltaX, int deltaY, unsigned int length);
		CellSet(const CellSet& orig);
		virtual ~CellSet();

		CellSet& operator=(const CellSet& rhs);

		Board::TokenType getContent(unsigned int index) const;
		std::vector<Board::TokenType> getContents() const;

		CellSetIterator begin() const;
		CellSetIterator end() const;

		std::pair<unsigned int, unsigned int> getCellPosition(unsigned int index) const;
		unsigned int getCellXPosition(unsigned int index) const;
		unsigned int getCellYPosition(unsigned int index) const;
		std::vector<std::pair<unsigned int, unsigned int> > getCellPositions() const;

		unsigned int getLength() const;

		int getDeltaX() const;
		int getDeltaY() const;

		bool isEmpty() const;

	private:
		void checkIndex(unsigned int index) const;

		/**
		 * Pointer to the game board.
		 */
		const Board* board;

		/**
		 * X position of the first cell.
		 */
		unsigned int startX;

		/**
		 * Y position of the first cell.
		 */
		unsigned int startY;

		/**
		 * Difference on the x axis to the next cell.
		 */
		int deltaX;

		/**
		 * Difference on the y axis to the next cell.
		 */
		int deltaY;

		/**
		 * Length of the cell set.
		 */
		unsigned int length;
};

}

#endif // GAME_CELLSET_HPP
