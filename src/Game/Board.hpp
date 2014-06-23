#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include <vector>

namespace Game
{

class CellSet;

/**
 * Provides a basic game board (grid) and methods to add/remove tokens on the board.
 *
 * When creating a board it is necessary to specify the dimensions and a value which represents an
 * empty cell. A grid with rows * column cells is then created and filled with empty tokens.
 *
 * The individual cells can be addressed using their x/y position in the grid.
 *
 * Example of a 3x3 grid with 0 as empty token:
 *
 *                     x
 *   +---+---+---+---+---->
 *   |   | 0 | 1 | 2 |
 *   +---+---+---+---+
 *   | 0 | 0 | 0 | 0 |
 *   +---+---+---+---+
 *   | 1 | 0 | 0 | 0 |
 *   +---+---+---+---+
 *   | 2 | 0 | 0 | 0 |
 *   +---+---+---+---+
 *   |
 * y |
 *   v
 *
 *
 * It is then possible to insert tokens with setCell(x, y) and retrieve them with getCell(x, y).
 * Two cells can be swapped with swapCells(x1, y1, x2, y2).
 *
 * The dimensions of the board can be retrieved with getNumberOfRows() and getNumberOfColumns().
 *
 * Use isRowFull(y) or isColumnFull(x) to check whether a row/column contains no empty cells and
 * isRowEmpty(y) or isColumnEmpty(x) to check whether a row/column contains only empty cells. An
 * individual cell can be checked with isCellEmpty(x, y) or isCellOccupied(x, y).
 *
 * The getRow(y)/getColumn(x) and getMajorDiagonal(x, y)/getMinorDiagonal(x, y) methods can be used
 * to retrieve a cell set referencing all cells in the specified row. The cell set can be used to
 * easily query/manipulate cells in a horizontal/vertical/diagonal row without having to worry about
 * their exact position.
 *
 * This class is reentrant but not thread-safe.
 */
class Board
{
	public:
		typedef unsigned int TokenType;

		Board(unsigned int nColumns, unsigned int nRows, TokenType emptyToken = 0);
		Board(const Board& board);
		virtual ~Board();

		virtual void clear();

		unsigned int getNumberOfRows() const;
		unsigned int getNumberOfColumns() const;

		virtual bool isRowFull(unsigned int y) const;
		virtual bool isRowEmpty(unsigned int y) const;

		virtual bool isColumnFull(unsigned int x) const;
		virtual bool isColumnEmpty(unsigned int x) const;

		virtual bool isFull() const;
		virtual bool isEmpty() const;

		virtual TokenType getEmptyToken() const;
		virtual bool isCellEmpty(unsigned int x, unsigned int y) const;
		virtual bool isCellOccupied(unsigned int x, unsigned int y) const;

		virtual void setCell(unsigned int x, unsigned int y, TokenType token);
		virtual TokenType getCell(unsigned int x, unsigned int y) const;

		virtual void swapCells(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

		CellSet getRow(unsigned int y) const;
		CellSet getColumn(unsigned int x) const;
		CellSet getMajorDiagonal(unsigned int x, unsigned int y) const;
		CellSet getMinorDiagonal(unsigned int x, unsigned int y) const;

		std::vector<CellSet> getAllRows() const;

	protected:
		void checkPosition(unsigned int x, unsigned int y) const;

		/**
		 * Contains the cells of the grid.
		 */
		std::vector<TokenType> cells;

		/**
		 * Number of rows.
		 */
		unsigned int nRows;

		/**
		 * Number of columns.
		 */
		unsigned int nColumns;

		/**
		 * Contains the value that represents an empty token.
		 */
		const TokenType emptyToken;
};

}

#endif // GAME_BOARD_HPP
