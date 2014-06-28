#ifndef GAME_PLAYERS_NETWORK_HPP
#define GAME_PLAYERS_NETWORK_HPP

#include "AbstractPlayer.hpp"

#include <QHostAddress>

namespace Game
{

namespace Players
{

/**
 * A remote player playing over the network.
 *
 * @todo Implement.
 */
class Network : public AbstractPlayer
{
		Q_OBJECT
	public:
		explicit Network(::GameLogic::FourInALine::Game::PlayerType player, QHostAddress address,
		                       QString name = QString(""), QObject *parent = 0);
		virtual ~Network();

		virtual void requestMove(const QSharedPointer<const ::Game::Game>& game) override;

		virtual void abortMove() override;

		const QHostAddress& getAddress() const;

	private:
		Q_DISABLE_COPY(Network)

		/**
		 * Network address of the player.
		 */
		QHostAddress address;
};

}
}

#endif // GAME_PLAYERS_NETWORK_HPP
