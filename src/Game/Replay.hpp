#ifndef GAME_REPLAY_HPP
#define GAME_REPLAY_HPP

#include "Players/Factory.hpp"
#include "Players/Placeholder.hpp"
#include "Game.hpp"
#include "../GameLogic/FourInALine/Board.hpp"

#include <QSharedPointer>
#include <vector>
#include <utility>

namespace Game
{

/**
 * Represents a replay of a game and provides methods for retrieving moves and player information.
 *
 * Create the replay through the CreateFromString() and CreateFromGame() methods. The first method
 * is for loading saved replays and the second method is for creating a replay from a game.
 *
 * It is then possible to get the number of moves with getNumberOfMoves() and to get individial
 * moves with getMove() and compute the position of the dropped token with computeMovePosition().
 *
 * The number of columns/rows in the game board can be queried with getNumberOfRows() and
 * getNumberOfColumns().
 *
 * The replay can be converted to a string with toString().
 *
 * The first player can be retrieved with getFirstPlayer() and the second player can be retrieved
 * with getSecondPlayer(). The players are placeholders which only have a name and a player id
 * for the game engine.
 */
class Replay
{
	public:
		/**
		 * Vector of pairs of player id and column index.
		 */
		using MovesVector = std::vector<std::pair<unsigned int, unsigned int> >;

		/**
		 * Shared pointer to a placeholder player.
		 */
		using PlayerPointer = QSharedPointer<Players::Placeholder>;

		Replay(MovesVector moves, unsigned int nColumns, unsigned int nRows,
		       PlayerPointer firstPlayer, PlayerPointer secondPlayer);
		virtual ~Replay();

		std::pair<unsigned int, unsigned int> getMove(unsigned int moveNo) const;
		std::pair<unsigned int, unsigned int> computeMovePosition(unsigned int moveNo) const;

		::GameLogic::FourInALine::Board computeBoard(unsigned int moveNo) const;

		unsigned int getNumberOfMoves() const;

		QString toString();

		PlayerPointer getFirstPlayer() const;
		PlayerPointer getSecondPlayer() const;

		unsigned int getNumberOfRows() const;
		unsigned int getNumberOfColumns() const;

		static QSharedPointer<Replay> CreateFromString(const QString& string,
		                                               Players::Factory& playerFactory);
		static QSharedPointer<Replay> CreateFromGame(QSharedPointer<const Game> game,
		                                             Players::Factory& playerFactory);

	private:
		/**
		 * Vector containing all moves.
		 */
		MovesVector moves;

		/**
		 * Number of columns of the board.
		 */
		unsigned int nColumns;

		/**
		 * Number of rows of the board.
		 */
		unsigned int nRows;

		/**
		 * First player (placeholder, has only player id and name).
		 */
		PlayerPointer firstPlayer;

		/**
		 * Second player (placeholder, has only player id and name).
		 */
		PlayerPointer secondPlayer;
};

}

#endif // GAME_REPLAY_HPP
