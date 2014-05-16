#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "MainMenuBar.hpp"
#include "Actions/Game.hpp"
#include "Actions/Settings.hpp"
#include "Actions/View.hpp"

#include <QMainWindow>

namespace GUI
{

/**
 * Main window of the game.
 */
class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		MainWindow(QWidget* parent = 0);
		~MainWindow();

		void setFullscreen(bool fullscreen);

	private:
		Q_DISABLE_COPY(MainWindow)

		void closeEvent(QCloseEvent* event);

		/**
		 * Main window version, increase when new toolbars/docks/etc. are added
		 * (used for saving/restoring state).
		 */
		static const int version = 1;

		/**
		 * The menu bar.
		 */
		MainMenuBar* menuBar;

		/**
		 * Contains game actions.
		 */
		Actions::Game* gameActions;

		/**
		 * Contains settings actions.
		 */
		Actions::Settings* settingsActions;

		/**
		 * Contains view actions.
		 */
		Actions::View* viewActions;
};

}

#endif // MAINWINDOW_HPP
