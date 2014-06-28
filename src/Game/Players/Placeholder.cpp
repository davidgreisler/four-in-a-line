#include "Placeholder.hpp"

#include <stdexcept>

namespace Game
{

namespace Players
{

/**
 * Creates a new placeholder player.
 *
 * @param player Player id for the game engine.
 * @param name Player name.
 * @param parent Parent object.
 */
Placeholder::Placeholder(::GameLogic::FourInALine::Game::PlayerType player, QString name, QObject *parent) :
    AbstractPlayer(player, name, parent)
{

}

/**
 * Frees all used resources.
 */
Placeholder::~Placeholder()
{

}

/**
 * Throws an exception, a placeholder player can't play a game.
 *
 * @param game The current game state.
 */
void Placeholder::requestMove(const QSharedPointer<const ::Game::Game>& game)
{
	Q_UNUSED(game)

	throw std::runtime_error("Requested move from placeholder player.");
}

/**
 * Throws an exception, a placeholder player can't play a game.
 */
void Placeholder::abortMove()
{
	throw std::runtime_error("Tried to abort move of placeholder player.");
}

}
}
