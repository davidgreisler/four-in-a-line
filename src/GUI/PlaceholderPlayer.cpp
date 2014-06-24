#include "PlaceholderPlayer.hpp"

#include <stdexcept>

namespace GUI
{

/**
 * Creates a new placeholder player.
 *
 * @param player Player id for the game engine.
 * @param name Player name.
 * @param parent Parent object.
 */
PlaceholderPlayer::PlaceholderPlayer(::Game::FourInALine::Game::PlayerType player, QString name, QObject *parent) :
	AbstractPlayer(player, name, parent)
{

}

/**
 * Frees all used resources.
 */
PlaceholderPlayer::~PlaceholderPlayer()
{

}

/**
 * Throws an exception, a placeholder player can't play a game.
 *
 * @param game The current game state.
 */
void PlaceholderPlayer::requestMove(const QSharedPointer<const Game>& game)
{
	Q_UNUSED(game)

	throw std::runtime_error("Requested move from placeholder player.");
}

/**
 * Throws an exception, a placeholder player can't play a game.
 */
void PlaceholderPlayer::abortMove()
{
	throw std::runtime_error("Tried to abort move of placeholder player.");
}

}
