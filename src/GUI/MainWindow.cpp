#include "MainWindow.hpp"

namespace GUI
{

/**
 * Creates a new main window using the given parent.
 *
 * @param parent Parent window.
 */
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
	this->gameActions = new Actions::Game(this);
	this->settingsActions = new Actions::Settings(this);

	this->menuBar = new MainMenuBar(this->gameActions, this->settingsActions, this);
	this->setMenuBar(this->menuBar);
}

/**
 * Frees all used resources.
 */
MainWindow::~MainWindow()
{

}

}
