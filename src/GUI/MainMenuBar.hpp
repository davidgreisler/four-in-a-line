#ifndef MAINMENUBAR_HPP
#define MAINMENUBAR_HPP

#include "Actions/Game.hpp"
#include "Actions/Settings.hpp"

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
							 QWidget *parent = 0);
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
};

}

#endif // MAINMENUBAR_HPP
