#ifndef GUI_PLAYERFACTORY_HPP
#define GUI_PLAYERFACTORY_HPP

#include "HumanPlayer.hpp"
#include "ArtificialIntelligencePlayer.hpp"
#include "NetworkPlayer.hpp"
#include "Widgets/Board.hpp"

#include <QSharedPointer>

namespace GUI
{

/**
 * Creates players.
 *
 * The player factory is used to create players. It contains a pointer to the current board widget,
 * which is needed for the human player to request a move from the user/player.
 */
class PlayerFactory
{
	public:
		using LOD = ArtificialIntelligencePlayer::LevelOfDifficulty;
		using AIPlayer = ArtificialIntelligencePlayer;
		using PlayerType = ::Game::FourInALine::Game::PlayerType;

		PlayerFactory(Widgets::Board* board);
		virtual ~PlayerFactory();

		QSharedPointer<HumanPlayer> createHumanPlayer(PlayerType playerId, QString name,
													  HumanPlayer::Controls controls) const;

		QSharedPointer<AIPlayer> createArtificialIntelligencePlayer(PlayerType playerId, QString name,
																	LOD levelOfDifficulty) const;

		QSharedPointer<NetworkPlayer> createNetworkPlayer(PlayerType playerId, QString name) const;

	private:
		/**
		 * Game board widget, used by the human player.
		 */
		Widgets::Board* board;
};

}

#endif // GUI_PLAYERFACTORY_HPP
