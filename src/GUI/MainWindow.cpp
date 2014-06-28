#include "MainWindow.hpp"
#include "../../app/FourInALine.hpp"
#include "../Settings/FourInALine.hpp"
#include "GameView.hpp"
#include "ReplayView.hpp"

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
	auto settings = ::FourInALine::getInstance()->getSettings();

	// Create views and manager.

	this->viewManager = new ViewManager(this);

	GameView* gameView = new GameView(this->viewManager);
	ReplayView* replayView = new ReplayView(this->viewManager);

	this->viewManager->setView(gameView);

	// Create action containers.

	this->gameActions = new Actions::Game(this->viewManager, gameView, this, this);
	this->settingsActions = new Actions::Settings(this, this);
	this->viewActions = new Actions::View(this, this);
	this->moveActions = new Actions::Move(gameView, this, this);
	this->replayActions = new Actions::Replay(gameView, replayView, this, this);
	this->helpActions = new Actions::Help(this, this);

	this->setupMenuBar();
	this->setupToolbars();

	// Restore geometry/state. Toolbars, docks, etc. must already have been created.

	this->restoreGeometry(settings->getViewSettings()->getWindowGeometry("MainWindow"));
	this->restoreState(settings->getViewSettings()->getWindowState("MainWindow"), MainWindow::version);
	this->setFullscreen(settings->getViewSettings()->isFullscreen());

	this->setWindowTitle(tr("Four in a line"));
	this->statusBar()->showMessage(tr("Ready."), 2000);

	// Geometry/state/view settings are saved when the window is closed, make sure it will is closed
	// on exit.

	this->connect(::FourInALine::getInstance(), &QApplication::aboutToQuit,
	              this, &QMainWindow::close);
	this->connect(settings->getViewSettings(), &Settings::View::changed,
	              this, &MainWindow::updateFullscreen);
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
 * Asks settings whether the window should be in fullscreen mode and then sets it up accordingly.
 */
void MainWindow::updateFullscreen()
{
	auto settings = ::FourInALine::getInstance()->getSettings();

	this->setFullscreen(settings->getViewSettings()->isFullscreen());
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

	auto settings = ::FourInALine::getInstance()->getSettings();

	settings->getViewSettings()->setWindowGeometry("MainWindow", this->saveGeometry());
	settings->getViewSettings()->setWindowState("MainWindow", this->saveState(MainWindow::version));
	settings->getViewSettings()->save();

	QMainWindow::closeEvent(event);
}

}
