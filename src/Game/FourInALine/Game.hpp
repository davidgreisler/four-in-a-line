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
 * getWinner() returns the winning player, except for when the game is a draw (check with isDraw()).
 *
 * It is possible to specify a time limit for a move with setTimeLimit() and to define what happens
 * when a player exceeds the time limit using setTimeoutAction(). There are two timeout actions:
 * LOSE_GAME which makes the player who exceeded the time limit lose the game and DRAW_GAME which
 * draws the game when a player exceeds the limit. The game logic can't check for how long the
 * player is able to make a move, therefore it can't measure whether the timeout was exceeded
 * or not. This is the responsibility of the user of this class. Use makeTimeoutMove() when a player
 * exceeds the timeout and the game will end correctly.
 *
 * Use isTimeout() to check whether the game ended because a player exceeded the time limit and
 * getPlayerWhoTimedOut() to retrieve the player who timed out.
 *
 * The number of moves so far can be retrieved with getNumberOfMoves() and a replay of the game
 * (vector containing all moves) is returned by getReplay().
 *
 * The game board can be accessed through getBoard().
 */
class Game
{
	public:
		/**
		 * Type used to identify players.
		 */
		using PlayerType = ::Game::Board::TokenType;

		/**
		 * Used to specify what happens when a player exceeds the time limit.
		 */
		enum class TimeoutAction {
			LOSE_GAME,  ///< When a player exceeds the time limit, he loses the game.
			DRAW_GAME   ///< When a player exceeds the time limit, the game is a draw.
		};

		Game(unsigned int nRows, unsigned int nColumns, PlayerType firstMove = 1);
		Game(const Game& orig);
		virtual ~Game();

		Game& operator=(const Game&) = delete;

		PlayerType getCurrentPlayer() const;
		PlayerType getPlayerWhoTimedOut() const;
		PlayerType getPlayerWhoMakesFirstMove() const;

		bool isMovePossible(unsigned int column) const;
		void makeMove(unsigned int column);
		void makeTimeoutMove();

		bool isUndoPossible() const;
		void undoLastMove();

		bool isOver() const;
		bool isDraw() const;
		bool isTimeout() const;
		unsigned int getWinner() const;

		bool hasTimeLimit() const;
		unsigned int getTimeLimit() const;
		void setTimeLimit(unsigned int timeLimit);

		TimeoutAction getTimeoutAction() const;
		void setTimeoutAction(TimeoutAction action);

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

		/**
		 * Stores the player number of the player who timed out if there is one, otherwise 0.
		 */
		PlayerType timedOutPlayer;

		/**
		 * What will happen when a player times out?
		 */
		TimeoutAction timeoutAction;

		/**
		 * Whether the game is over or not.
		 */
		bool isGameOver;

		/**
		 * Time limit in seconds. 0 means no limit.
		 */
		unsigned int timeLimit;
};

}
}

#endif // GAME_FOUR_IN_A_LINE_GAME_HPP
