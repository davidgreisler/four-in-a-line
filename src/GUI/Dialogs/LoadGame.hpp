#ifndef GUI_DIALOGS_LOADGAME_HPP
#define GUI_DIALOGS_LOADGAME_HPP

#include "../../Game/Players/Factory.hpp"
#include "../Widgets/BoardConfiguration.hpp"
#include "../Widgets/TimeLimitConfiguration.hpp"
#include "../Widgets/PlayerConfiguration.hpp"
#include "../Widgets/GameConfiguration.hpp"
#include "../Widgets/GameSetup.hpp"

#include <QDialog>
#include <QSharedPointer>

class QDialogButtonBox;
class QVBoxLayout;

namespace GUI
{

class Game;

namespace Dialogs
{

/**
 * Dialog showing the loaded game settings and allowing the user to configure players and then
 * start the game.
 *
 * This dialog shows the game settings like the number of rows/columns, etc. like the new game
 * dialog but they are read-only. The dialog allows the user to configure the 2 players though.
 *
 * After they have been configured and the player clicks the load game button, the placeholder
 * players in the game are replaced by players created according to the settings defined by the
 * user and the dialog is closed.
 */
class LoadGame : public QDialog
{
		Q_OBJECT
	public:
		explicit LoadGame(QSharedPointer< ::Game::Game> game, QWidget *parent = 0);
		virtual ~LoadGame();

		void replacePlayers(::Game::Players::Factory& playerFactory);

	private slots:
		void updateLoadGameButton();

	private:
		Q_DISABLE_COPY(LoadGame)

		void changeEvent(QEvent* event);
		void retranslateUI();

		/**
		 * Layout of the dialog.
		 */
		QVBoxLayout* layout;

		/**
		 * Contains game configuration widgets.
		 */
		Widgets::GameSetup* gameSetupWidget;

		/**
		 * Contains dialog buttons.
		 */
		QDialogButtonBox* buttonBox;

		/**
		 * Button to start the game.
		 */
		QPushButton* loadGameButton;

		/**
		 * The loaded game with placeholder players to replace.
		 */
		QSharedPointer< ::Game::Game> game;
};

}
}

#endif // GUI_DIALOGS_LOADGAME_HPP
