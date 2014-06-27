#include "NetworkPlayer.hpp"

namespace GUI
{

/**
 * Creates a new network player.
 *
 * @param player Player id.
 * @param address Host address.
 * @param name Player name.
 * @param parent Parent object.
 */
NetworkPlayer::NetworkPlayer(::Game::FourInALine::Game::PlayerType player, QHostAddress address,
                             QString name, QObject *parent) :
    AbstractPlayer(player, name, parent), address(address)
{

}

/**
 * Frees all used resources.
 */
NetworkPlayer::~NetworkPlayer()
{

}

/**
 * Invoked by the game logic when it's the player's turn.
 *
 * @param game Current game state.
 */
void NetworkPlayer::requestMove(const QSharedPointer<const::GUI::Game>& game)
{
	Q_UNUSED(game);
}

/**
 * Invoked by the game logic when the move should be aborted, e.g. when the player exceeded the
 * time limit.
 */
void NetworkPlayer::abortMove()
{

}

/**
 * Returns the network address of this player.
 *
 * @return Network address of the player.
 */
const QHostAddress& NetworkPlayer::getAddress() const
{
	return this->address;
}

}
