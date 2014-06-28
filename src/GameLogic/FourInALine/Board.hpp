#ifndef GAMELOGIC_FOUR_IN_A_LINE_BOARD_HPP
#define GAMELOGIC_FOUR_IN_A_LINE_BOARD_HPP

#include "../CellSet.hpp"
#include "../Board.hpp"

#include <vector>

namespace GameLogic
{

namespace FourInALine
{

/**
 * Represents a four in a line game board.
 *
 * The game board is used to store the current state of the game. It consists of a grid/matrix which
 * stores the positions of the tokens dropped by the players. The number of rows/columns in the
 * grid is given during construction of the board. Every cell in the grid is either empty
 * (Board::CELL_EMPTY), or contains a player token (unsigned integer).
 *
 * The class provides methods for inserting tokens into the board. Use canDropToken(column) to check
 * whether a token can be dropped into a column and dropToken(column, token) to insert the
 * token at the correct position. A token can be removed from the board using removeToken(), tokens
 * above the removed token will fall down, this can be used to implement special game modes or for
 * an undo functionality.
 *
 * The content of a cell can be retrieved with getCell(row, column). To determine if the game was
 * won, or to evaluate moves for an artificial intelligence, it is often necessary to iterate over
 * all horizontal/vertical/diagonal rows. This is easily possible with the getRow()/getColumn()
 * methods for horizontal/vertical rows and the getMajorDiagonal()/getMinorDiagonal() methods for
 * diagonal rows. Use getAllRows() to retrieve all horizontal/vertical/diagonal rows in a vector.
 *
 * This class is reentrant but not thread-safe.
 */
class Board : public ::GameLogic::Board
{
	public:
		/**
		 * Represents an empty cell in the grid.
		 */
		static const ::GameLogic::Board::TokenType CELL_EMPTY;

		Board(unsigned int nColumns, unsigned int nRows);
		Board(const Board& board);
		virtual ~Board();

		bool canDropToken(unsigned int x) const;
		void dropToken(unsigned int x, ::GameLogic::Board::TokenType token);
		void removeToken(unsigned int x);
		void removeToken(unsigned int x, unsigned int y);

		virtual bool isColumnFull(unsigned int x) const override;
		virtual bool isColumnEmpty(unsigned int x) const override;

		std::vector<unsigned int> getAvailableColumns() const;

		CellSet findWinningCells() const;

	protected:
		using ::GameLogic::Board::setCell;
		using ::GameLogic::Board::swapCells;
};

}
}

#endif // GAMELOGIC_FOUR_IN_A_LINE_BOARD_HPP
