#include "Game.hpp"
#include "../Dialogs/Highscores.hpp"
#include "../../../app/FourInALine.hpp"
#include "../GameController.hpp"
#include "../ControllerManager.hpp"
#include "../Icon.hpp"

#include <QAction>
#include <QMenu>
#include <QWidget>
#include <QIcon>

namespace GUI
{
namespace Actions
{

/**
 * Creates a new game action container.
 *
 * @param controllerManager Controller manager, used to deactivate active controller on exit.
 * @param gameController Game controller used to invoke game actions.
 * @param parentWindow Parent window, used for dialogs.
 * @param parent Parent object.
 */
Game::Game(::GUI::ControllerManager* controllerManager, ::GUI::GameController* gameController,
		   QWidget* parentWindow, QObject* parent) :
	QObject(parent), controllerManager(controllerManager), gameController(gameController),
	parentWindow(parentWindow)
{
	this->createActions();
	this->createMenu();
	this->retranslateUI();
	this->updateActions();

	this->connect(this->gameController, &::GUI::GameController::stateChanged,
				  this, &Game::updateActions);
}

/**
 * Frees all used resources.
 */
Game::~Game()
{

}

/**
 * Returns the new game action.
 *
 * @return Action for starting a new game.
 */
QAction* Game::getNewGameAction() const
{
	return this->newGameAction;
}

/**
 * Returns the end game action.
 *
 * @return Action for ending the current game.
 */
QAction* Game::getEndGameAction() const
{
	return this->endGameAction;
}

/**
 * Returns the load game action.
 *
 * @return Action for loading a game.
 */
QAction* Game::getLoadGameAction() const
{
	return this->loadGameAction;
}

/**
 * Returns the save game action.
 *
 * @return Action for saving the game.
 */
QAction* Game::getSaveGameAction() const
{
	return this->saveGameAction;
}

/**
 * Returns the save game as action.
 *
 * @return Action for saving the game under a new path.
 */
QAction* Game::getSaveGameAsAction() const
{
	return this->saveGameAsAction;
}

/**
 * Returns the show highscores action.
 *
 * @return Action for showing the highscore list.
 */
QAction* Game::getShowHighscoresAction() const
{
	return this->showHighscoresAction;
}

/**
 * Returns the exit action.
 *
 * @return Action for exiting the game.
 */
QAction* Game::getExitAction() const
{
	return this->exitAction;
}

/**
 * Returns the game menu.
 *
 * The game menu contains all game actions.
 *
 * @return The game menu.
 */
QMenu* Game::getMenu() const
{
	return this->menu.data();
}

/**
 * Requests currently active controller to deactivate and if that worked ends program execution.
 *
 * The controller is requested to deactivate so that the controller-specific confirmation dialog
 * can be displayed (e.g. "do you want to abort the current game?").
 */
void Game::exit()
{
	if (this->controllerManager->requestController(nullptr))
	{
		::FourInALine::getInstance()->quit();
	}
}

/**
 * Updates actions, i.e. checks whether they have to be disabled/enabled.
 */
void Game::updateActions()
{
	// New game, load game, exit and show highscores are always possible.

	this->newGameAction->setEnabled(true);
	this->loadGameAction->setEnabled(true);
	this->exitAction->setEnabled(true);
	this->showHighscoresAction->setEnabled(true);

	// Disable all other actions.

	this->endGameAction->setEnabled(false);

	this->saveGameAction->setEnabled(false);
	this->saveGameAsAction->setEnabled(false);

	// Check which actions should be enabled.

	if (this->gameController->isActive())
	{
		if (this->gameController->hasGame())
		{
			this->endGameAction->setEnabled(true);
			this->saveGameAction->setEnabled(true);
			this->saveGameAsAction->setEnabled(true);
		}
	}
}

/**
 * Shows the highscores dialog.
 */
void Game::showHighscoresDialog()
{
	Dialogs::Highscores dialog(this->parentWindow);

	dialog.exec();
}

/**
 * Create all actions and connect them.
 */
void Game::createActions()
{
	// Create application icon and bullets for combining them.

	QIcon applicationIcon;
	applicationIcon.addFile(":/icons/fourinaline/16x16/application_icon.png", QSize(16, 16));
	applicationIcon.addFile(":/icons/fourinaline/32x32/application_icon.png", QSize(32, 32));
	applicationIcon.addFile(":/icons/fourinaline/128x128/application_icon.png", QSize(128, 128));

	QIcon newBullet;
	newBullet.addFile(":/icons/fatcow/16x16/bullet_add.png", QSize(16, 16));
	newBullet.addFile(":/icons/fatcow/32x32/bullet_add.png", QSize(32, 32));

	QIcon endBullet;
	endBullet.addFile(":/icons/fatcow/16x16/bullet_delete.png", QSize(16, 16));
	endBullet.addFile(":/icons/fatcow/32x32/bullet_delete.png", QSize(32, 32));

	QIcon saveBullet;
	saveBullet.addFile(":/icons/fatcow/16x16/bullet_disk.png", QSize(16, 16));
	saveBullet.addFile(":/icons/fatcow/32x32/bullet_disk.png", QSize(32, 32));

	QIcon loadBullet;
	loadBullet.addFile(":/icons/fatcow/16x16/bullet_down.png", QSize(16, 16));
	loadBullet.addFile(":/icons/fatcow/32x32/bullet_down.png", QSize(32, 32));

	// Create actions.

	QIcon newGameIcon = ::GUI::Icon::combineIcons(applicationIcon, newBullet);
	this->newGameAction = new QAction(newGameIcon, "", this);
	this->connect(this->newGameAction, &QAction::triggered,
				  this->gameController, &::GUI::GameController::newGame);

	QIcon endGameIcon = ::GUI::Icon::combineIcons(applicationIcon, endBullet);
	this->endGameAction = new QAction(endGameIcon, "", this);
	this->connect(this->endGameAction, &QAction::triggered,
				  this->gameController, &::GUI::GameController::endGame);

	QIcon loadGameIcon = ::GUI::Icon::combineIcons(applicationIcon, loadBullet);
	this->loadGameAction = new QAction(loadGameIcon, "", this);
	this->connect(this->loadGameAction, &QAction::triggered,
				  this->gameController, &::GUI::GameController::loadGame);

	QIcon saveGameIcon = ::GUI::Icon::combineIcons(applicationIcon, saveBullet);
	this->saveGameAction = new QAction(saveGameIcon, "", this);
	this->connect(this->saveGameAction, &QAction::triggered,
				  this->gameController, &::GUI::GameController::saveGame);

	QIcon saveGameAsIcon;
	saveGameAsIcon.addFile(":/icons/fatcow/16x16/save_as.png", QSize(16, 16));
	saveGameAsIcon.addFile(":/icons/fatcow/32x32/save_as.png", QSize(32, 32));
	this->saveGameAsAction = new QAction(saveGameAsIcon, "", this);
	this->connect(this->saveGameAsAction, &QAction::triggered,
				  this->gameController, &::GUI::GameController::saveGameAs);

	QIcon showHighscoresIcon;
	showHighscoresIcon.addFile(":/icons/fatcow/16x16/cup_gold.png", QSize(16, 16));
	showHighscoresIcon.addFile(":/icons/fatcow/32x32/cup_gold.png", QSize(32, 32));
	this->showHighscoresAction = new QAction(showHighscoresIcon, "", this);
	this->connect(this->showHighscoresAction, &QAction::triggered,
				  this, &Game::showHighscoresDialog);

	QIcon exitIcon;
	exitIcon.addFile(":/icons/fatcow/16x16/cross.png", QSize(16, 16));
	exitIcon.addFile(":/icons/fatcow/32x32/cross.png", QSize(32, 32));
	this->exitAction = new QAction(exitIcon, "", this);
	this->connect(this->exitAction, &QAction::triggered, this, &Game::exit);
}

/**
 * Creates the game menu.
 */
void Game::createMenu()
{
	this->menu.reset(new QMenu(0));
	this->menu->addAction(this->newGameAction);
	this->menu->addAction(this->endGameAction);
	this->menu->addSeparator();
	this->menu->addAction(this->loadGameAction);
	this->menu->addAction(this->saveGameAction);
	this->menu->addAction(this->saveGameAsAction);
	this->menu->addSeparator();
	this->menu->addAction(this->showHighscoresAction);
	this->menu->addSeparator();
	this->menu->addAction(this->exitAction);
}

/**
 * Retranslates all strings.
 */
void Game::retranslateUI()
{
	this->newGameAction->setText(tr("&New game"));
	this->newGameAction->setStatusTip(tr("Start a new game."));

	this->endGameAction->setText(tr("&End game"));
	this->endGameAction->setStatusTip(tr("End the current game."));

	this->loadGameAction->setText(tr("&Load game ..."));
	this->loadGameAction->setStatusTip(tr("Load a saved game."));

	this->saveGameAction->setText(tr("&Save game"));
	this->saveGameAction->setStatusTip(tr("Save the current game."));

	this->saveGameAsAction->setText(tr("&Save game as ..."));
	this->saveGameAsAction->setStatusTip(tr("Save the current game."));

	this->showHighscoresAction->setText(tr("Show &Highscores"));
	this->showHighscoresAction->setStatusTip(tr("Show highscore list."));

	this->exitAction->setText(tr("E&xit"));
	this->exitAction->setStatusTip(tr("Exit game."));

	this->menu->setTitle(tr("&Game"));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
bool Game::event(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	return QObject::event(event);
}

}
}
