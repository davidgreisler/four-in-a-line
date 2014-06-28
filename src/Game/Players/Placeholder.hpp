#ifndef GAME_PLAYERS_PLACEHOLDER_HPP
#define GAME_PLAYERS_PLACEHOLDER_HPP

#include "AbstractPlayer.hpp"
#include "../../GameLogic/FourInALine/Game.hpp"

#include <QString>

namespace Game
{

namespace Players
{

/**
 * Placeholder for a real player.
 *
 * This player is a placeholder for a real player. It has a name and a player id for the game engine.
 * It is used by replays and savegames which do not need/can't save more information. When a game is
 * loaded it first contains placeholder players which then get replaced by real players before
 * the game starts. This allows the player to setup the players differently when loading a game than
 * how they were configured when the game was started.
 *
 * When a move is requested from this player or a move request is aborted, an exception is thrown.
 * A placeholder player can't play a game, it must be replaced by a real player before.
 */
class Placeholder : public AbstractPlayer
{
		Q_OBJECT
	public:
		explicit Placeholder(::GameLogic::FourInALine::Game::PlayerType player,
		                     QString name = QString(""), QObject *parent = 0);
		virtual ~Placeholder();

		virtual void requestMove(const QSharedPointer<const ::Game::Game>& game) override;
		virtual void abortMove() override;

	private:
		Q_DISABLE_COPY(Placeholder)

};

}
}

#endif // GAME_PLAYERS_PLACEHOLDER_HPP
