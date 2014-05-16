#include "MainWindow.hpp"
#include "../ConnectFour.hpp"
#include "../ConnectFourSettings.hpp"

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
	::ConnectFourSettings* settings = ::ConnectFour::getInstance()->getSettings();

	this->gameActions = new Actions::Game(this);
	this->settingsActions = new Actions::Settings(this);

	this->menuBar = new MainMenuBar(this->gameActions, this->settingsActions, this);
	this->setMenuBar(this->menuBar);

	// Restore geometry/state. Toolbars, docks, etc. must already have been created.

	this->restoreGeometry(settings->getViewSettings()->getWindowGeometry("MainWindow"));
	this->restoreState(settings->getViewSettings()->getWindowState("MainWindow"));
}

/**
 * Frees all used resources.
 */
MainWindow::~MainWindow()
{

}

/**
 * Saves window geometry/state and other view settings.
 *
 * @param event Close event.
 */
void MainWindow::closeEvent(QCloseEvent* event)
{
	Q_UNUSED(event);

	::ConnectFourSettings* settings = ::ConnectFour::getInstance()->getSettings();

	settings->getViewSettings()->setWindowGeometry("MainWindow", this->saveGeometry());
	settings->getViewSettings()->setWindowState("MainWindow", this->saveState(MainWindow::version));
	settings->getViewSettings()->save();
}

}
