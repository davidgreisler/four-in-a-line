#include "Game.hpp"
#include "../../ConnectFour.hpp"

#include <QAction>
#include <QMenu>
#include <QWidget>

namespace GUI
{
namespace Actions
{

/**
 * Creates a new game action container.
 *
 * @param parent Parent window, used for dialogs.
 */
Game::Game(QWidget* parentWindow, QObject* parent) :
	QObject(parent), parentWindow(parentWindow)
{
	this->createActions();
	this->createMenu();
	this->retranslateUI();
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
 * Ends program execution.
 */
void Game::exit()
{
	::ConnectFour::getInstance()->quit();
}

/**
 * Create all actions and connect them.
 */
void Game::createActions()
{
	this->newGameAction = new QAction("", this);

	this->endGameAction = new QAction("", this);

	this->loadGameAction = new QAction("", this);

	this->saveGameAction = new QAction("", this);

	this->saveGameAsAction = new QAction("", this);

	this->showHighscoresAction = new QAction("", this);

	this->exitAction = new QAction("", this);

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
