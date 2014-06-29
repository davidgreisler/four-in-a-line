#include "GameWriter.hpp"

#include <stdexcept>

namespace Game
{

/**
 * Creates a new game writer.
 */
GameWriter::GameWriter()
{
	this->xmlStream.setAutoFormatting(true);
	this->xmlStream.setCodec("UTF-8");
}

/**
 * Frees all used resources.
 */
GameWriter::~GameWriter()
{

}

/**
 * Writes an XML representation of the state of the given game to the given device.
 *
 * @param device Device to write the XML representation to.
 * @param game Game state that should be stored in XML.
 * @param withConfiguration Whether the game configuration should be included or not.
 */
void GameWriter::writeXML(QIODevice* device, QSharedPointer<const Game> game, bool withConfiguration)
{
	this->xmlStream.setDevice(device);
	this->xmlStream.writeStartDocument();

	this->xmlStream.writeDTD("<!DOCTYPE fourinaline>");

	this->xmlStream.writeStartElement("game");

	// Players.

	this->xmlStream.writeStartElement("players");

	this->writePlayer(game->getFirstPlayer());
	this->writePlayer(game->getSecondPlayer());

	this->xmlStream.writeEndElement();

	// Board.

	this->writeBoard(game->getGameLogic()->getBoard());

	// Moves.

	this->writeMoves(game->getGameLogic()->getReplay());

	// Configuration.

	if (withConfiguration)
	{
		this->writeConfiguration(game);
	}

	this->xmlStream.writeEndElement();

	this->xmlStream.writeEndDocument();
}

/**
 * Writes a <player> element containing information about the given player to the stream.
 *
 * @param player Player to extract id/name from.
 */
void GameWriter::writePlayer(QSharedPointer<const::Game::Players::AbstractPlayer> player)
{
	this->xmlStream.writeStartElement("player");
	this->xmlStream.writeAttribute("playerId", QString::number(player->getPlayer()));
	this->xmlStream.writeAttribute("name", player->getName());
	this->xmlStream.writeEndElement();
}

/**
 * Writes a <board> element containing information about the given board to the stream.
 *
 * @param board Board to extract information.
 */
void GameWriter::writeBoard(std::shared_ptr<const GameLogic::FourInALine::Board> board)
{
	this->xmlStream.writeStartElement("board");
	this->xmlStream.writeAttribute("columns", QString::number(board->getNumberOfColumns()));
	this->xmlStream.writeAttribute("rows", QString::number(board->getNumberOfRows()));
	this->xmlStream.writeEndElement();
}

/**
 * Writes a <configuration> element containing information about the given game to the stream.
 *
 * @param game Game to extract configuration information.
 */
void GameWriter::writeConfiguration(QSharedPointer<const Game> game)
{
	this->xmlStream.writeStartElement("configuration");

	this->xmlStream.writeStartElement("timeLimit");
	this->xmlStream.writeAttribute("duration",
			QString::number(game->getGameLogic()->getTimeLimit()));
	this->xmlStream.writeAttribute("action",
	        QString::number(static_cast<int>(game->getGameLogic()->getTimeoutAction())));
	this->xmlStream.writeEndElement();

	this->xmlStream.writeStartElement("generalSettings");
	this->xmlStream.writeAttribute("firstMove",
	        QString::number(game->getGameLogic()->getPlayerWhoMakesFirstMove()));
	this->xmlStream.writeAttribute("saveHighscore", QString::number(game->isSavingHighscore()));
	this->xmlStream.writeAttribute("undoAllowed", QString::number(game->isUndoAllowed()));
	this->xmlStream.writeAttribute("hintAllowed", QString::number(game->isHintAllowed()));
	this->xmlStream.writeEndElement();

	this->xmlStream.writeEndElement();
}

/**
 * Writes a <moves> element containing information about the moves in the given replay to the
 * stream.
 *
 * @param replay Vector containing pairs of player id and column.
 */
void GameWriter::writeMoves(const std::vector<std::pair<unsigned int, unsigned int> >& replay)
{
	this->xmlStream.writeStartElement("moves");

	for (auto i = replay.cbegin(); i != replay.cend(); ++i)
	{
		this->xmlStream.writeStartElement("move");
		this->xmlStream.writeAttribute("playerId", QString::number(i->first));
		this->xmlStream.writeAttribute("column", QString::number(i->second));
		this->xmlStream.writeEndElement();
	}

	this->xmlStream.writeEndElement();
}

}
