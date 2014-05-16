#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "MainMenuBar.hpp"
#include "Actions/Game.hpp"

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

	private:
		Q_DISABLE_COPY(MainWindow)

		/**
		 * The menu bar.
		 */
		MainMenuBar* menuBar;

		/**
		 * Contains game actions.
		 */
		Actions::Game* gameActions;
};

}

#endif // MAINWINDOW_HPP
