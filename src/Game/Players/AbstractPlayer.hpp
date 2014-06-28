#ifndef GAME_PLAYERS_ABSTRACTPLAYER_HPP
#define GAME_PLAYERS_ABSTRACTPLAYER_HPP

#include "../../GameLogic/FourInALine/Game.hpp"

#include <QSharedPointer>
#include <QObject>
#include <QString>

namespace Game
{

class Game;

namespace Players
{

/**
 * Abstract base class for players.
 *
 * Stores a player name and provides methods to retrieve/set the player name and a method to
 * retrieve the player id.
 *
 * The methods requestMove() and abortMove() are invoked by the game logic and must be
 * reimplemented. When it is the player's turn, the game logic calls requestMove(), and when the
 * player times out or the requested move isn't needed anymore abortMove() is called. Emit
 * moveReady() as soon as the requested move is ready/computed to inform the game logic about
 * the move.
 */
class AbstractPlayer : public QObject
{
		Q_OBJECT
	public:
		AbstractPlayer(::GameLogic::FourInALine::Game::PlayerType playerId, QString name = QString(""),
		               QObject *parent = 0);
		virtual ~AbstractPlayer();

		/**
		 * Used by the game logic to request a move.
		 */
		virtual void requestMove(const QSharedPointer<const ::Game::Game>& game) = 0;

		/**
		 * Invoked by the game logic to abort the request for a move.
		 */
		virtual void abortMove() = 0;

		QString getName() const;
		void setName(QString name);

		::GameLogic::FourInALine::Game::PlayerType getPlayer() const;

	signals:
		/**
		 * Emitted when a requested move is ready.
		 *
		 * @param x Index of the column where the token should be dropped.
		 */
		void moveReady(unsigned int x);

	private:
		Q_DISABLE_COPY(AbstractPlayer)

		/**
		 * Token/id of the player used by the game logic.
		 */
		::GameLogic::FourInALine::Game::PlayerType player;

		/**
		 * Player name.
		 */
		QString name;
};

}
}

#endif // GAME_PLAYERS_ABSTRACTPLAYER_HPP
