#include "PlayerFactory.hpp"

#include <QHostAddress>

namespace GUI
{

/**
 * Creates a new player factory with the given board widget.
 *
 * @param board Board widget to use for the human player.
 */
PlayerFactory::PlayerFactory(Widgets::Board* board)
	: board(board)
{

}

/**
 * Frees all used resources.
 */
PlayerFactory::~PlayerFactory()
{

}

/**
 * Creates a new human player.
 *
 * @param playerId Player id for the game engine.
 * @param name Player name.
 * @param controls Which controls are used by this player.
 * @return A new human player.
 */
QSharedPointer<HumanPlayer>
PlayerFactory::createHumanPlayer(PlayerType playerId, QString name, HumanPlayer::Controls controls) const
{
	QSharedPointer<HumanPlayer> player;

	player.reset(new HumanPlayer(playerId, controls, this->board, name));

	return player;
}

/**
 * Creates a new artificial intelligence player.
 *
 * @param playerId Player id.
 * @param name Player name.
 * @param levelOfDifficulty How difficult it should be to beat the AI.
 * @return A new artificial intelligence player.
 */
QSharedPointer<PlayerFactory::AIPlayer>
PlayerFactory::createArtificialIntelligencePlayer(PlayerType playerId, QString name,
												  PlayerFactory::LOD levelOfDifficulty) const
{
	QSharedPointer<ArtificialIntelligencePlayer> player;

	player.reset(new ArtificialIntelligencePlayer(playerId, levelOfDifficulty, name));

	return player;
}

/**
 * Creates a new network player.
 *
 * @param playerId Player id.
 * @param name Player name.
 * @return A new network player.
 */
QSharedPointer<NetworkPlayer> PlayerFactory::createNetworkPlayer(PlayerType playerId, QString name) const
{
	QSharedPointer<NetworkPlayer> player;

	player.reset(new NetworkPlayer(playerId, QHostAddress(), name));

	return player;
}

}
