#ifndef GAME_GAMEWRITER_HPP
#define GAME_GAMEWRITER_HPP

#include "Game.hpp"
#include "Players/AbstractPlayer.hpp"

#include <QXmlStreamWriter>

#include <vector>
#include <utility>
#include <memory>

namespace Game
{

/**
 * Writes an XML representation of a game (savegame/replay) to an io device.
 *
 * This class creates an XML representation of a given game and then writes it to a given io device
 * with writeXML(). It is possible to specify whether the game configuration should be included in
 * the XML (savegame) or not (replay).
 */
class GameWriter
{
	public:
		GameWriter();
		virtual ~GameWriter();

		void writeXML(QIODevice* device, QSharedPointer<const ::Game::Game> game, bool withConfiguration);

	private:
		void writePlayer(QSharedPointer<const ::Game::Players::AbstractPlayer> player);
		void writeBoard(std::shared_ptr<const ::GameLogic::FourInALine::Board> board);
		void writeConfiguration(QSharedPointer<const ::Game::Game> game);
		void writeMoves(const std::vector<std::pair<unsigned int, unsigned int> >& replay);

		/**
		 * XML stream used to create XML representation of the game.
		 */
		QXmlStreamWriter xmlStream;
};

}

#endif // GAME_GAMEWRITER_HPP
