#include "Network.hpp"

namespace Game
{

namespace Players
{

/**
 * Creates a new network player.
 *
 * @param player Player id.
 * @param address Host address.
 * @param name Player name.
 * @param parent Parent object.
 */
Network::Network(::GameLogic::FourInALine::Game::PlayerType player, QHostAddress address,
                             QString name, QObject *parent) :
    AbstractPlayer(player, name, parent), address(address)
{

}

/**
 * Frees all used resources.
 */
Network::~Network()
{

}

/**
 * Invoked by the game logic when it's the player's turn.
 *
 * @param game Current game state.
 */
void Network::requestMove(const QSharedPointer<const ::Game::Game>& game)
{
	Q_UNUSED(game);
}

/**
 * Invoked by the game logic when the move should be aborted, e.g. when the player exceeded the
 * time limit.
 */
void Network::abortMove()
{

}

/**
 * Returns the network address of this player.
 *
 * @return Network address of the player.
 */
const QHostAddress& Network::getAddress() const
{
	return this->address;
}

}
}
