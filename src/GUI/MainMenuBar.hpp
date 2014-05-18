#ifndef MAINMENUBAR_HPP
#define MAINMENUBAR_HPP

#include "Actions/Game.hpp"
#include "Actions/Settings.hpp"
#include "Actions/View.hpp"
#include "Actions/Help.hpp"
#include "Actions/Move.hpp"

#include <QMenuBar>

namespace GUI
{

/**
 * Menu bar for the main window.
 */
class MainMenuBar : public QMenuBar
{
		Q_OBJECT
	public:
		explicit MainMenuBar(Actions::Game* gameActions, Actions::Settings* settingsActions,
							 Actions::View* viewActions, Actions::Move* moveActions,
							 Actions::Help* helpActions, QWidget *parent = 0);
		virtual ~MainMenuBar();

	signals:

	public slots:

	private:
		Q_DISABLE_COPY(MainMenuBar)

		void setupLanguageMenu();
		void retranslateUI();
		void changeEvent(QEvent* event);

		/**
		 * Game menu containing start new game, load/save game, exit, etc.
		 */
		QMenu* gameMenu;

		/**
		 * Contains game actions.
		 */
		Actions::Game* gameActions;

		/**
		 * Settings menu.
		 */
		QMenu* settingsMenu;

		/**
		 * Contains settings actions like changing language or showing settings dialog.
		 */
		Actions::Settings* settingsActions;

		/**
		 * Contains the languages the user can select.
		 */
		QMenu* languageMenu;

		/**
		 * Action group containing the languages.
		 */
		QSharedPointer<QActionGroup> languageGroup;

		/**
		 * View actions.
		 */
		Actions::View* viewActions;

		/**
		 * Menu for view options, like toggle fullscreen.
		 */
		QMenu* viewMenu;

		/**
		 * Move actions.
		 */
		Actions::Move* moveActions;

		/**
		 * Menu for game moves, undo last move, get hint, etc.
		 */
		QMenu* moveMenu;

		/**
		 * Help actions.
		 */
		Actions::Help* helpActions;

		/**
		 * Menu for showing about dialogs.
		 */
		QMenu* helpMenu;
};

}

#endif // MAINMENUBAR_HPP
