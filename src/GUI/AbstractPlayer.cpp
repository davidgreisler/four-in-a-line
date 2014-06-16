#include "AbstractPlayer.hpp"

namespace GUI
{

/**
 * Creates a new abstract player.
 *
 * @parem name Player name.
 */
AbstractPlayer::AbstractPlayer(QString name)
	: name(name)
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

}
