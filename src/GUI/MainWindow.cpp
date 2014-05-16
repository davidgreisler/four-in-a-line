#include "MainWindow.hpp"
#include "../ConnectFour.hpp"
#include "../ConnectFourSettings.hpp"

#include <QStatusBar>
#include <QDebug>

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
	this->viewActions = new Actions::View(this, this);

	this->menuBar = new MainMenuBar(this->gameActions, this->settingsActions, this->viewActions,
									this);
	this->setMenuBar(this->menuBar);

	// Restore geometry/state. Toolbars, docks, etc. must already have been created.

	this->restoreGeometry(settings->getViewSettings()->getWindowGeometry("MainWindow"));
	this->restoreState(settings->getViewSettings()->getWindowState("MainWindow"));
	this->setFullscreen(settings->getViewSettings()->isFullscreen());

	this->setWindowTitle(tr("Connect four"));
	this->statusBar()->showMessage(tr("Ready."), 2000);

	// Geometry/state/view settings are saved when the window is closed, make sure it will is closed
	// on exit.

	this->connect(::ConnectFour::getInstance(), &QApplication::aboutToQuit, this, &QMainWindow::close);
}

/**
 * Frees all used resources.
 */
MainWindow::~MainWindow()
{

}

/**
 * Activates or deactivates fullscreen mode.
 *
 * @param fullscreen When true, the window is displayed in full screen mode, when false the
 *        window is displayed in normal mode.
 */
void MainWindow::setFullscreen(bool fullscreen)
{
	if (fullscreen)
	{
		this->showFullScreen();
	}
	else
	{
		this->showNormal();
	}
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
