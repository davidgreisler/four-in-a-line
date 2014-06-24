#ifndef GUI_DIALOGS_NEWGAME_HPP
#define GUI_DIALOGS_NEWGAME_HPP

#include "../AbstractPlayer.hpp"
#include "../PlayerFactory.hpp"
#include "../Widgets/GameSetup.hpp"

#include <QDialog>
#include <QSharedPointer>

class QVBoxLayout;
class QDialogButtonBox;

namespace GUI
{

class Game;

namespace Dialogs
{

/**
 * Dialog for starting a new game.
 *
 * This dialog allows the user to configure and start a new game. It is possible to configure
 * various game settings like the board size, player types/names, etc.
 *
 * Use createFirstPlayer()/createSecondPlayer() to create the players according to the settings
 * chosen by the user and createGame() to create a game according to the configured settings.
 */
class NewGame : public QDialog
{
		Q_OBJECT
	public:
		explicit NewGame(QWidget *parent = 0);
		virtual ~NewGame();

		QSharedPointer<AbstractPlayer> createFirstPlayer(PlayerFactory& factory) const;
		QSharedPointer<AbstractPlayer> createSecondPlayer(PlayerFactory& factory) const;

		QSharedPointer< ::GUI::Game> createGame(PlayerFactory& factory) const;

	public slots:
		void updateNewGameButton();

	private:
		Q_DISABLE_COPY(NewGame)

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
};

}
}

#endif // GUI_DIALOGS_NEWGAME_HPP
