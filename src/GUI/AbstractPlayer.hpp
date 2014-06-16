#ifndef GUI_ABSTRACTPLAYER_HPP
#define GUI_ABSTRACTPLAYER_HPP

#include <QString>

namespace GUI
{

/**
 * Abstract base class for players.
 *
 * Stores a player name and provides methods to retrieve/set the player name.
 */
class AbstractPlayer
{
	public:
		AbstractPlayer(QString name = QString(""));
		virtual ~AbstractPlayer();

		QString getName() const;
		void setName(QString name);

	private:
		/**
		 * Player name.
		 */
		QString name;
};

}

#endif // GUI_ABSTRACTPLAYER_HPP
