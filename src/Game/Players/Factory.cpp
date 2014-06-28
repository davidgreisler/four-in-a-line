#include "Factory.hpp"

#include <QHostAddress>
#include <QDebug>

#include <stdexcept>

namespace Game
{

namespace Players
{

/**
 * Creates a new player factory with the given board widget.
 *
 * @param board Board widget to use for the human player.
 */
Factory::Factory(::GUI::Widgets::Board* board)
    : board(board)
{

}

/**
 * Frees all used resources.
 */
Factory::~Factory()
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
QSharedPointer<Human>
Factory::createHumanPlayer(PlayerType playerId, QString name, Human::Controls controls) const
{
	QSharedPointer<Human> player;

	player.reset(new Human(playerId, controls, this->board, name), &QObject::deleteLater);

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
QSharedPointer<Factory::AIPlayer>
Factory::createArtificialIntelligencePlayer(PlayerType playerId, QString name,
                                                  Factory::LOD levelOfDifficulty) const
{
	QSharedPointer<ArtificialIntelligence> player;

	player.reset(new ArtificialIntelligence(playerId, levelOfDifficulty, name), &QObject::deleteLater);

	return player;
}

/**
 * Creates a new network player.
 *
 * @param playerId Player id.
 * @param name Player name.
 * @return A new network player.
 */
QSharedPointer<Network> Factory::createNetworkPlayer(PlayerType playerId, QString name) const
{
	QSharedPointer<Network> player;

	player.reset(new Network(playerId, QHostAddress(), name), &QObject::deleteLater);

	return player;
}

/**
 * Creates a copy of the given player.
 *
 * @param original The original player.
 * @return A copy of the original player.
 */
QSharedPointer<AbstractPlayer> Factory::createCopy(const QSharedPointer<const AbstractPlayer>& original)
{
	QSharedPointer<AbstractPlayer> player;
	auto humanOriginal = qSharedPointerDynamicCast<const Human>(original);
	auto aiOriginal = qSharedPointerDynamicCast<const ArtificialIntelligence>(original);

	if (humanOriginal != nullptr)
	{
		player = Factory::createHumanPlayer(original->getPlayer(), original->getName(),
		                                          humanOriginal->getControls());
	}
	else if (aiOriginal != nullptr)
	{
		player = Factory::createArtificialIntelligencePlayer(original->getPlayer(),
		                                                           original->getName(),
		                                                           aiOriginal->getLevelOfDifficulty());
	}
	else if (qSharedPointerCast<const Network>(original) != nullptr)
	{
		player = Factory::createNetworkPlayer(original->getPlayer(), original->getName());
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
QSharedPointer<Placeholder> Factory::createPlaceholder(Factory::PlayerType playerId, QString name) const
{
	QSharedPointer<Placeholder> placeholderPlayer;

	placeholderPlayer.reset(new Placeholder(playerId, name), &QObject::deleteLater);

	return placeholderPlayer;
}

/**
 * Creates a placeholder player from the given player.
 *
 * @param player The player to copy the player id and name from.
 * @return Placeholder player.
 */
QSharedPointer<Placeholder> Factory::createPlaceholder(const QSharedPointer<const AbstractPlayer>& player) const
{
	QSharedPointer<Placeholder> placeholderPlayer;

	placeholderPlayer.reset(new Placeholder(player->getPlayer(), player->getName()),
	                        &QObject::deleteLater);

	return placeholderPlayer;
}

}
}
