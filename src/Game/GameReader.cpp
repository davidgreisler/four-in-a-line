#include "GameReader.hpp"
#include "Game.hpp"
#include "Replay.hpp"
#include "ParseError.hpp"
#include "../GameLogic/FourInALine/Game.hpp"

#include <QDebug>

namespace Game
{

/**
 * Creates a new game reader.
 */
GameReader::GameReader()
{
	this->reset();
}

/**
 * Frees all used resources.
 */
GameReader::~GameReader()
{

}

/**
 * Reads a game in XML representation from the given device and creates a game object for it.
 *
 * @param device Device to read the game from.
 * @return A game representing the state of the XML.
 */
QSharedPointer<Game> GameReader::readGame(QIODevice* device)
{
	this->xmlStream.setDevice(device);

	this->readXML(true);

	auto gameLogic = QSharedPointer< ::GameLogic::FourInALine::Game>::create(this->nRows,
	                                                                         this->nColumns,
	                                                                         this->firstMovePlayerId);
	gameLogic->setTimeLimit(this->timeLimit);
	gameLogic->setTimeoutAction(this->timeoutAction);

	auto game = QSharedPointer<Game>::create(gameLogic, this->firstPlayer, this->secondPlayer);
	game->setSaveHighscore(this->saveHighscore);
	game->setAllowUndo(this->allowUndo);
	game->setAllowHint(this->allowHint);

	for (auto i = this->moves.cbegin(); i != this->moves.cend(); ++i)
	{
		if (game->getCurrentPlayer()->getPlayer() != i->first)
		{
			throw ParseError("Expected other player in current move.");
		}

		game->getGameLogic()->makeMove(i->second);
	}

	return game;
}

/**
 * Reads a replay in XML form from the given device and creates a replay object for it.
 *
 * @param device Device to read the replay from.
 * @return Replay created from the XML.
 */
QSharedPointer<Replay> GameReader::readReplay(QIODevice* device)
{
	this->xmlStream.setDevice(device);

	this->readXML(false);

	auto replay = QSharedPointer<Replay>::create(this->moves, this->nColumns, this->nRows,
	                                             this->firstPlayer, this->secondPlayer);

	return replay;
}

/**
 * Resets the internal state of the game reader.
 */
void GameReader::reset()
{
	this->allowHint = false;
	this->allowUndo = false;
	this->saveHighscore = false;
	this->timeLimit = 0;
	this->timeoutAction = ::GameLogic::FourInALine::Game::TimeoutAction::DRAW_GAME;
	this->nColumns = 0;
	this->nRows = 0;
	this->firstMovePlayerId = 0;
	this->firstPlayer.reset();
	this->secondPlayer.reset();
	this->moves.clear();
}

/**
 * Reads the XML with the stream reader and stores the information in the attributes.
 *
 * This method will read a complete <game> element with the XML stream reader. It will parse the
 * player/board/moves/configuration information from the elements in the <game> element and store
 * them in the according game reader attributes.
 *
 * An exception is thrown when there was a parsing error or information is missing (e.g. no
 * player information). It is possible to switch this check off for the configuration, making it
 * possible to also read replays with this method (replays do not contain configuration
 * information).
 *
 * @param withConfiguration Whether the configuration should/must be read or not.
 * @throws ParseError When the XML is invalid/there was a parser error.
 */
void GameReader::readXML(bool withConfiguration)
{
	this->reset();

	bool hasPlayers = false;
	bool hasBoard = false;
	bool hasMoves = false;
	bool hasConfiguration = false;

	if (!this->xmlStream.readNextStartElement() ||
	    this->xmlStream.name() != "game")
	{
		throw ParseError("Not a valid savegame/replay.");
	}

	while (this->xmlStream.readNextStartElement())
	{
		QStringRef name = this->xmlStream.name();

		if (name == "players")
		{
			this->readPlayers();
			hasPlayers = true;
		}
		else if (name == "board")
		{
			this->readBoard();
			hasBoard = true;
		}
		else if (name == "moves")
		{
			this->readMoves();
			hasMoves = true;
		}
		else if (name == "configuration" && withConfiguration)
		{
			this->readConfiguration();
			hasConfiguration = true;
		}
		else
		{
			this->xmlStream.skipCurrentElement();
		}
	}

	if (!hasPlayers)
	{
		throw ParseError("Game must contain players.");
	}

	if (!hasMoves)
	{
		throw ParseError("Game must contain moves.");
	}

	if (!hasBoard)
	{
		throw ParseError("Game must contain board.");
	}

	if (withConfiguration && !hasConfiguration)
	{
		throw ParseError("Game must contain configuration.");
	}

	if (this->xmlStream.hasError())
	{
		throw ParseError(this->xmlStream.errorString());
	}
}

/**
 * Reads next start element and tries to parse a <player> element.
 *
 * @return Placeholder player for the <player> element.
 * @throws ParseError Invalid player id or no <player> element.
 */
QSharedPointer<Players::Placeholder> GameReader::readPlayer()
{
	auto PLAYER_ONE = ::GameLogic::FourInALine::Game::PLAYER_ONE;
	auto PLAYER_TWO = ::GameLogic::FourInALine::Game::PLAYER_TWO;

	::GameLogic::FourInALine::Game::PlayerType playerId;
	QString playerName;

	if (!this->xmlStream.readNextStartElement())
	{
		throw ParseError("Failed to read next player element.");
	}

	this->checkStartElement("player");

	playerId = this->readUnsignedIntegerAttribute("playerId");

	if (playerId != PLAYER_ONE && playerId != PLAYER_TWO)
	{
		throw ParseError("Invalid player id.");
	}

	playerName = this->xmlStream.attributes().value("name").toString();

	this->xmlStream.readElementText();

	return QSharedPointer<Players::Placeholder>::create(playerId, playerName);
}

/**
 * Parses a <players> element and stores the information.
 */
void GameReader::readPlayers()
{
	auto PLAYER_ONE = ::GameLogic::FourInALine::Game::PLAYER_ONE;
	auto PLAYER_TWO = ::GameLogic::FourInALine::Game::PLAYER_TWO;

	this->checkStartElement("players");

	auto firstPlayer = this->readPlayer();
	auto secondPlayer = this->readPlayer();

	this->xmlStream.skipCurrentElement();

	if (firstPlayer->getPlayer() == PLAYER_ONE && secondPlayer->getPlayer() == PLAYER_TWO)
	{
		this->firstPlayer = firstPlayer;
		this->secondPlayer = secondPlayer;
	}
	else if (firstPlayer->getPlayer() == PLAYER_TWO && secondPlayer->getPlayer() == PLAYER_ONE)
	{
		this->firstPlayer = secondPlayer;
		this->secondPlayer = firstPlayer;
	}
	else
	{
		throw ParseError("There must be exactly one first player and one second player.");
	}
}

/**
 * Parses a <board> element and stores the information.
 */
void GameReader::readBoard()
{
	this->checkStartElement("board");

	this->nColumns = this->readUnsignedIntegerAttribute("columns");
	this->nRows = this->readUnsignedIntegerAttribute("rows");

	this->xmlStream.skipCurrentElement();
}

/**
 * Parses a <moves> element and stores the information.
 */
void GameReader::readMoves()
{
	this->checkStartElement("moves");

	this->moves.clear();

	while (this->xmlStream.readNextStartElement())
	{
		unsigned int playerId = this->readUnsignedIntegerAttribute("playerId");
		unsigned int columnNo = this->readUnsignedIntegerAttribute("column");

		this->moves.push_back(std::pair<unsigned int, unsigned int>(playerId, columnNo));

		this->xmlStream.skipCurrentElement();
	}
}

/**
 * Parses a <configuration> element and stores the information.
 */
void GameReader::readConfiguration()
{
	using TimeoutAction = ::GameLogic::FourInALine::Game::TimeoutAction;

	bool hasTimeLimit = false;
	bool hasGeneralSettings = false;

	this->checkStartElement("configuration");

	while (this->xmlStream.readNextStartElement())
	{
		auto name = this->xmlStream.name();

		if (name == "timeLimit")
		{
			this->timeLimit = this->readUnsignedIntegerAttribute("duration");
			auto timeoutActionNo = this->readUnsignedIntegerAttribute("action");
			this->timeoutAction = static_cast<TimeoutAction>(timeoutActionNo);

			hasTimeLimit = true;
		}
		else if (name == "generalSettings")
		{
			this->firstMovePlayerId = this->readUnsignedIntegerAttribute("firstMove");
			this->saveHighscore = this->readUnsignedIntegerAttribute("saveHighscore");
			this->allowUndo = this->readUnsignedIntegerAttribute("undoAllowed");
			this->allowHint = this->readUnsignedIntegerAttribute("hintAllowed");

			hasGeneralSettings = true;
		}

		this->xmlStream.skipCurrentElement();
	}

	if (!hasTimeLimit || !hasGeneralSettings)
	{
		throw ParseError("Configuration must at least contain time limit and general settings.");
	}
}

/**
 * Reads the attribute with the given name, converts it to an unsigned integer and then returns it.
 *
 * @param attributeName The attribute to read.
 * @return Value of the attribute converted to unsigned integer.
 * @throws ParseError When converting the value to an unsigned integer fails.
 */
unsigned int GameReader::readUnsignedIntegerAttribute(const char* attributeName)
{
	bool isIntegerOk;

	auto value = this->xmlStream.attributes().value(attributeName);
	unsigned int result = value.toInt(&isIntegerOk);

	if (!isIntegerOk)
	{
		throw ParseError(QString("Failed to convert '%1' to unsigned integer.").arg(value.toString()));
	}

	return result;
}

/**
 * Checks whether the current element is a start element with the given name and throws an exception
 * when not.
 *
 * @param elementName The element name.
 * @throws ParseError When the current element is not a start element or has a different name.
 */
void GameReader::checkStartElement(const char* elementName)
{
	if (!this->xmlStream.isStartElement())
	{
		throw ParseError("Expected start element.");
	}

	if (this->xmlStream.name() != elementName)
	{
		auto message = QString("Expected %1 element, read '%2' instead.")
		               .arg(elementName).arg(this->xmlStream.name().toString());
		throw ParseError(message);
	}
}

}
