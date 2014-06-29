#ifndef GAME_GAMEREADER_HPP
#define GAME_GAMEREADER_HPP

#include "Players/Placeholder.hpp"

#include <QXmlStreamReader>
#include <QSharedPointer>

namespace Game
{

class Game;
class Replay;

/**
 * Reads XML representation of a game (savegame/replay) and creates a corresponding game/replay.
 *
 * This class can read an XML representation of a game and create a game/replay with the same state.
 * Use readGame() to read a game and readReplay() to read a replay. The difference is that a
 * savegame (game) contains the game configuration and a replay only contains players/board/move
 * information.
 */
class GameReader
{
	public:
		GameReader();
		virtual ~GameReader();

		QSharedPointer<Game> readGame(QIODevice* device);
		QSharedPointer<Replay> readReplay(QIODevice* device);

	private:
		void reset();
		void readXML(bool withConfiguration);

		QSharedPointer<Players::Placeholder> readPlayer();
		void readPlayers();
		void readBoard();
		void readMoves();
		void readConfiguration();

		unsigned int readUnsignedIntegerAttribute(const char* attributeName);

		void checkStartElement(const char* elementName);

		/**
		 * XML stream used to parse XML representation of the game.
		 */
		QXmlStreamReader xmlStream;

		/**
		 * Number of columns in the board.
		 */
		unsigned int nColumns;

		/**
		 * Number of rows in the board.
		 */
		unsigned int nRows;

		/**
		 * Player id of the player who makes the first move.
		 */
		unsigned int firstMovePlayerId;

		/**
		 * Whether to save the game result to the highscore list.
		 */
		bool saveHighscore;

		/**
		 * Whether hints should be allowed.
		 */
		bool allowHint;

		/**
		 * Whether undo should be allowed.
		 */
		bool allowUndo;

		/**
		 * Time limit in seconds.
		 */
		unsigned int timeLimit;

		/**
		 * Action to perform when a player exceeds the time limit.
		 */
		::GameLogic::FourInALine::Game::TimeoutAction timeoutAction;

		/**
		 * The first player (placeholder).
		 */
		QSharedPointer<Players::Placeholder> firstPlayer;

		/**
		 * The second player (placeholder).
		 */
		QSharedPointer<Players::Placeholder> secondPlayer;

		/**
		 * Vector containing game moves.
		 */
		std::vector<std::pair<unsigned int, unsigned int> > moves;
};

}

#endif // GAME_GAMEREADER_HPP
