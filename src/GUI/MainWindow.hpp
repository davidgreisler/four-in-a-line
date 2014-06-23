#ifndef GUI_MAINWINDOW_HPP
#define GUI_MAINWINDOW_HPP

#include "Actions/Game.hpp"
#include "Actions/Settings.hpp"
#include "Actions/View.hpp"
#include "Actions/Help.hpp"
#include "Actions/Replay.hpp"
#include "Actions/Move.hpp"
#include "ControllerManager.hpp"

#include <QMainWindow>

namespace GUI
{

/**
 * Main window of the game.
 *
 * The main window creates actions for every activity in the program and then creates a menu bar
 * and tool bars for accessing those actions. The actions are stored in action containers which
 * are responsible for creating the menus, keeping the enabled state of the actions updated, etc.
 *
 * The main window has 2 central widgets, the game widget controlled by the game controller and the
 * replay widget controlled by the replay controller. The controller manager makes sure only one
 * controller is active at the same time and sets the corresponding widget as central widget of the
 * main window.
 */
class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		MainWindow(QWidget* parent = 0);
		~MainWindow();

		void setFullscreen(bool fullscreen);

	private slots:
		void updateFullscreen();

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

		/**
		 * Manages controllers and central widget.
		 */
		ControllerManager* controllerManager;
};

}

#endif // GUI_MAINWINDOW_HPP
