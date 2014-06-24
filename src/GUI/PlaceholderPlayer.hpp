#ifndef GUI_PLACEHOLDERPLAYER_HPP
#define GUI_PLACEHOLDERPLAYER_HPP

#include "AbstractPlayer.hpp"
#include "../Game/FourInALine/Game.hpp"

#include <QString>

namespace GUI
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
class PlaceholderPlayer : public AbstractPlayer
{
		Q_OBJECT
	public:
		explicit PlaceholderPlayer(::Game::FourInALine::Game::PlayerType player,
								   QString name = QString(""), QObject *parent = 0);
		virtual ~PlaceholderPlayer();

		virtual void requestMove(const QSharedPointer<const ::GUI::Game>& game);
		virtual void abortMove();

	private:
		Q_DISABLE_COPY(PlaceholderPlayer)

};

}

#endif // GUI_PLACEHOLDERPLAYER_HPP
