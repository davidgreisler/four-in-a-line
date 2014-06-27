#include "AbstractPlayer.hpp"

namespace GUI
{

/**
 * Creates a new abstract player.
 *
 * @param name Player name.
 * @param playerId Player id as used by the game engine.
 * @param parent Parent object.
 */
AbstractPlayer::AbstractPlayer(::Game::FourInALine::Game::PlayerType playerId, QString name, QObject* parent)
    : QObject(parent), player(playerId), name(name)
{

}

/**
 * Frees all used resources.
 */
AbstractPlayer::~AbstractPlayer()
{

}

/**
 * Returns the name of the player.
 *
 * @return Player name.
 */
QString AbstractPlayer::getName() const
{
	return this->name;
}

/**
 * Sets the name of the player.
 *
 * @param name Player name.
 */
void AbstractPlayer::setName(QString name)
{
	this->name = name;
}

/**
 * Returns the player token/id used by the game logic.
 *
 * @return Token used by the game logic.
 */
::Game::FourInALine::Game::PlayerType AbstractPlayer::getPlayer() const
{
	return this->player;
}

}
