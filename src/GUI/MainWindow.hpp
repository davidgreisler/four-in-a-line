#ifndef GUI_MAINWINDOW_HPP
#define GUI_MAINWINDOW_HPP

#include "Actions/Game.hpp"
#include "Actions/Settings.hpp"
#include "Actions/View.hpp"
#include "Actions/Help.hpp"
#include "Actions/Replay.hpp"
#include "Actions/Move.hpp"

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

		void setupMenuBar();
		void setupToolbars();
		void setupToolbar(QMenu* menu, QString title, const char* objectName);

		void closeEvent(QCloseEvent* event);

		/**
		 * Main window version, increase when new toolbars/docks/etc. are added
		 * (used for saving/restoring state).
		 */
		static const int version = 2;

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

		/**
		 * Contains help actions.
		 */
		Actions::Help* helpActions;

		/**
		 * Contains move actions.
		 */
		Actions::Move* moveActions;

		/**
		 * Contains replay actions.
		 */
		Actions::Replay* replayActions;
};

}

#endif // GUI_MAINWINDOW_HPP
