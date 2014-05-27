#include "Game.hpp"
#include "../../FourInALine.hpp"

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
 * @param parentWindow Parent window, used for dialogs.
 * @param parent Parent object.
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
	::FourInALine::getInstance()->quit();
}

/**
 * Create all actions and connect them.
 */
void Game::createActions()
{
	QIcon newGameIcon;
	newGameIcon.addFile(":/icons/16x16/page_add.png", QSize(16, 16));
	newGameIcon.addFile(":/icons/32x32/page_add.png", QSize(32, 32));
	this->newGameAction = new QAction(newGameIcon, "", this);

	QIcon endGameIcon;
	endGameIcon.addFile(":/icons/16x16/cancel.png", QSize(16, 16));
	endGameIcon.addFile(":/icons/32x32/cancel.png", QSize(32, 32));
	this->endGameAction = new QAction(endGameIcon, "", this);

	QIcon loadGameIcon;
	loadGameIcon.addFile(":/icons/16x16/page_add.png", QSize(16, 16));
	loadGameIcon.addFile(":/icons/32x32/page_add.png", QSize(32, 32));
	this->loadGameAction = new QAction(loadGameIcon, "", this);

	QIcon saveGameIcon;
	saveGameIcon.addFile(":/icons/16x16/page_save.png", QSize(16, 16));
	saveGameIcon.addFile(":/icons/32x32/page_save.png", QSize(32, 32));
	this->saveGameAction = new QAction(saveGameIcon, "", this);

	QIcon saveGameAsIcon;
	saveGameAsIcon.addFile(":/icons/16x16/save_as.png", QSize(16, 16));
	saveGameAsIcon.addFile(":/icons/32x32/save_as.png", QSize(32, 32));
	this->saveGameAsAction = new QAction(saveGameAsIcon, "", this);

	QIcon showHighscoresIcon;
	showHighscoresIcon.addFile(":/icons/16x16/cup_gold.png", QSize(16, 16));
	showHighscoresIcon.addFile(":/icons/32x32/cup_gold.png", QSize(32, 32));
	this->showHighscoresAction = new QAction(showHighscoresIcon, "", this);

	QIcon exitIcon;
	exitIcon.addFile(":/icons/16x16/cross.png", QSize(16, 16));
	exitIcon.addFile(":/icons/32x32/cross.png", QSize(32, 32));
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
