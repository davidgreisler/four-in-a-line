#ifndef GAME_PLAYERS_FACTORY_HPP
#define GAME_PLAYERS_FACTORY_HPP

#include "Human.hpp"
#include "ArtificialIntelligence.hpp"
#include "Placeholder.hpp"
#include "Network.hpp"
#include "../../GUI/Widgets/Board.hpp"

#include <QSharedPointer>

namespace Game
{

namespace Players
{

/**
 * Creates players.
 *
 * The player factory is used to create players. It contains a pointer to the current board widget,
 * which is needed for the human player to request a move from the user/player.
 */
class Factory
{
	public:
		/**
		 * Level of difficulty for the artificial intelligence.
		 */
		using LOD = ArtificialIntelligence::LevelOfDifficulty;

		/**
		 * Artificial intelligence player.
		 */
		using AIPlayer = ArtificialIntelligence;

		/**
		 * Player id type.
		 */
		using PlayerType = ::GameLogic::FourInALine::Game::PlayerType;

		Factory(::GUI::Widgets::Board* board);
		virtual ~Factory();

		QSharedPointer<Human> createHumanPlayer(PlayerType playerId, QString name,
		                                              Human::Controls controls) const;

		QSharedPointer<AIPlayer> createArtificialIntelligencePlayer(PlayerType playerId, QString name,
		                                                            LOD levelOfDifficulty) const;

		QSharedPointer<Network> createNetworkPlayer(PlayerType playerId, QString name) const;

		QSharedPointer<AbstractPlayer> createCopy(const QSharedPointer<const AbstractPlayer>& original);

		QSharedPointer<Placeholder> createPlaceholder(PlayerType playerId, QString name) const;
		QSharedPointer<Placeholder> createPlaceholder(const QSharedPointer<const AbstractPlayer>& player) const;

	private:
		/**
		 * Game board widget, used by the human player.
		 */
		::GUI::Widgets::Board* board;
};

}
}

#endif // GAME_PLAYERS_FACTORY_HPP
