#ifndef GAME_FOUR_IN_A_LINE_GAME_HPP
#define GAME_FOUR_IN_A_LINE_GAME_HPP

#include "Board.hpp"

#include <memory>
#include <vector>
#include <utility>

namespace Game
{
namespace FourInALine
{

/**
 * Contains four in a line game logic.
 *
 * The game class contains the logic for the four in a line game. It provides methods for making moves
 * and checking whether the game is over/who won it.
 *
 * When a new game is created, the number of rows and columns for the game board must be specified.
 * It is also possible to define which player makes the first move.
 *
 * It is then possible to retrieve the current player with getCurrentPlayer(), check whether the
 * desired move is possible with isMovePossible(column) and then to make that move with
 * makeMove(column).
 *
 * Previous moves can be undone with undoLastMove(), this is only possible if there were any moves
 * of course. Check whether undoing the last move is possible using isUndoPossible().
 *
 * After a move has been made with makeMove(column) or undone with undoLastMove(), the game object
 * will check whether the winning condition is (still) met. If it is met, isOver() returns true and
 * getWinner() returns the winning player.
 *
 * The number of moves so far can be retrieved with getNumberOfMoves() and a replay of the game
 * (vector containing all moves) is returned by getReplay().
 *
 * The game board can be accessed through getBoard().
 */
class Game
{
	public:
		typedef ::Game::Board::TokenType PlayerType;

		Game(unsigned int nRows, unsigned int nColumns, PlayerType firstMove = 1);
		Game(const Game&) = delete;
		virtual ~Game();

		Game& operator=(const Game&) = delete;

		unsigned int getCurrentPlayer() const;

		bool isMovePossible(unsigned int column) const;
		void makeMove(unsigned int column);

		bool isUndoPossible() const;
		void undoLastMove();

		bool isOver() const;
		bool isDraw() const;
		unsigned int getWinner() const;

		const std::vector<std::pair<unsigned int, unsigned int> >& getReplay() const;
		unsigned int getNumberOfMoves() const;

		std::shared_ptr<const Board> getBoard() const;

        /**
         * First player.
         */
        static const PlayerType PLAYER_ONE;

        /**
         * Second player.
         */
        static const PlayerType PLAYER_TWO;

	private:
		void checkWinningCondition();

		/**
		 * The game board.
		 */
		std::shared_ptr<Board> board;

		/**
		 * List of moves already done.
		 *
		 * The first element of the pair is the player number, the second element the column where
		 * the token was inserted.
		 */
		std::vector<std::pair<PlayerType, unsigned int> > moves;

		/**
		 * Stores the player number of the winning player, if there is one, otherwise 0.
		 */
		PlayerType winner;

		/**
		 * Stores the player number of the player that makes the next move.
		 */
		PlayerType currentPlayer;
};

}
}

#endif // GAME_FOUR_IN_A_LINE_GAME_HPP
