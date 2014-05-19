#include "MainWindow.hpp"
#include "../ConnectFour.hpp"
#include "../ConnectFourSettings.hpp"

#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>
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

	this->gameActions = new Actions::Game(this, this);
	this->settingsActions = new Actions::Settings(this, this);
	this->viewActions = new Actions::View(this, this);
	this->moveActions = new Actions::Move(this, this);
	this->replayActions = new Actions::Replay(this, this);
	this->helpActions = new Actions::Help(this, this);

	this->setupMenuBar();
	this->setupToolbars();

	// Restore geometry/state. Toolbars, docks, etc. must already have been created.

	this->restoreGeometry(settings->getViewSettings()->getWindowGeometry("MainWindow"));
	this->restoreState(settings->getViewSettings()->getWindowState("MainWindow"), MainWindow::version);
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
 * Sets up the menu bar.
 */
void MainWindow::setupMenuBar()
{
	QMenuBar* menuBar = this->menuBar();
	menuBar->addMenu(this->gameActions->getMenu());
	menuBar->addMenu(this->viewActions->getMenu());
	menuBar->addMenu(this->moveActions->getMenu());
	menuBar->addMenu(this->replayActions->getMenu());
	menuBar->addMenu(this->settingsActions->getMenu());
	menuBar->addMenu(this->helpActions->getMenu());
}

/**
 * Sets up toolbars and updates toolbar menu.
 */
void MainWindow::setupToolbars()
{
	this->setupToolbar(this->gameActions->getMenu(), tr("Game"), "GameToolBar");
	this->setupToolbar(this->moveActions->getMenu(), tr("Move"), "MoveToolBar");
	this->setupToolbar(this->viewActions->getMenu(), tr("View"), "ViewToolBar");
	this->setupToolbar(this->replayActions->getMenu(), tr("Replay"), "ReplayToolBar");

	QMenu* toolbarMenu = this->createPopupMenu();
	this->viewActions->updateToolbars(toolbarMenu->actions());
}

/**
 * Retrieves all actions from the given menu and creates and adds a toolbar for these actions.
 *
 * @param menu The source menu, from where the actions are retrieved.
 * @param title Title of the toolbar.
 * @param objectName Object name of the toolbar.
 */
void MainWindow::setupToolbar(QMenu* menu, QString title, const char* objectName)
{
	QList<QAction*> actions;
	QList<QAction*>::ConstIterator actionsIt;

	QToolBar* toolbar = new QToolBar(title, this);
	toolbar->setObjectName(objectName);
	toolbar->setIconSize(QSize(32, 32));

	actions = menu->actions();
	for(actionsIt = actions.constBegin(); actionsIt != actions.constEnd(); ++actionsIt)
	{
		toolbar->addAction(*actionsIt);
	}

	this->addToolBar(Qt::TopToolBarArea, toolbar);
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

	QMainWindow::closeEvent(event);
}

}
