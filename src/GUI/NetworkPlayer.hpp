#ifndef GUI_NETWORKPLAYER_HPP
#define GUI_NETWORKPLAYER_HPP

#include "AbstractPlayer.hpp"

#include <QHostAddress>

namespace GUI
{

/**
 * A remote player playing over the network.
 *
 * @todo Implement.
 */
class NetworkPlayer : public AbstractPlayer
{
		Q_OBJECT
	public:
		explicit NetworkPlayer(::Game::FourInALine::Game::PlayerType player, QHostAddress address,
		                       QString name = QString(""), QObject *parent = 0);
		virtual ~NetworkPlayer();

		virtual void requestMove(const QSharedPointer<const ::GUI::Game>& game);

		virtual void abortMove();

		const QHostAddress& getAddress() const;

	signals:

	public slots:

	private:
		/**
		 * Network address of the player.
		 */
		QHostAddress address;
};

}

#endif // GUI_NETWORKPLAYER_HPP
