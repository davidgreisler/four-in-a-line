#include "AbstractPlayer.hpp"

namespace GUI
{

/**
 * Creates a new abstract player.
 *
 * @param name Player name.
 * @param parent Parent object.
 */
AbstractPlayer::AbstractPlayer(::Game::FourInALine::Game::PlayerType player, QString name, QObject* parent)
	: QObject(parent), player(player), name(name)
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
