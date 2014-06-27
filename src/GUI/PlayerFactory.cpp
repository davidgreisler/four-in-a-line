#include "PlayerFactory.hpp"

#include <QHostAddress>
#include <QDebug>

#include <stdexcept>

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

	player.reset(new HumanPlayer(playerId, controls, this->board, name), &QObject::deleteLater);

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

	player.reset(new ArtificialIntelligencePlayer(playerId, levelOfDifficulty, name), &QObject::deleteLater);

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

	player.reset(new NetworkPlayer(playerId, QHostAddress(), name), &QObject::deleteLater);

	return player;
}

/**
 * Creates a copy of the given player.
 *
 * @param original The original player.
 * @return A copy of the original player.
 */
QSharedPointer<AbstractPlayer> PlayerFactory::createCopy(const QSharedPointer<const AbstractPlayer>& original)
{
	QSharedPointer<AbstractPlayer> player;
	auto humanOriginal = qSharedPointerDynamicCast<const HumanPlayer>(original);
	auto aiOriginal = qSharedPointerDynamicCast<const ArtificialIntelligencePlayer>(original);

	if (humanOriginal != nullptr)
	{
		player = PlayerFactory::createHumanPlayer(original->getPlayer(), original->getName(),
		                                          humanOriginal->getControls());
	}
	else if (aiOriginal != nullptr)
	{
		player = PlayerFactory::createArtificialIntelligencePlayer(original->getPlayer(),
		                                                           original->getName(),
		                                                           aiOriginal->getLevelOfDifficulty());
	}
	else if (qSharedPointerCast<const NetworkPlayer>(original) != nullptr)
	{
		player = PlayerFactory::createNetworkPlayer(original->getPlayer(), original->getName());
	}
	else
	{
		throw std::runtime_error("Unknown player type.");
	}

	return player;
}

/**
 * Creates a placeholder player with the given id and name.
 *
 * @param playerId Player id used by the game engine.
 * @param name Player name.
 * @return Placeholder player.
 */
QSharedPointer<PlaceholderPlayer> PlayerFactory::createPlaceholder(PlayerFactory::PlayerType playerId, QString name) const
{
	QSharedPointer<PlaceholderPlayer> placeholderPlayer;

	placeholderPlayer.reset(new PlaceholderPlayer(playerId, name), &QObject::deleteLater);

	return placeholderPlayer;
}

/**
 * Creates a placeholder player from the given player.
 *
 * @param player The player to copy the player id and name from.
 * @return Placeholder player.
 */
QSharedPointer<PlaceholderPlayer> PlayerFactory::createPlaceholder(const QSharedPointer<const AbstractPlayer>& player) const
{
	QSharedPointer<PlaceholderPlayer> placeholderPlayer;

	placeholderPlayer.reset(new PlaceholderPlayer(player->getPlayer(), player->getName()),
	                        &QObject::deleteLater);

	return placeholderPlayer;
}

}
