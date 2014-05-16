#include "MainMenuBar.hpp"

namespace GUI
{

/**
 * Creates a new menu bar for the main window, using the given actions.
 *
 * @param gameActions Game action container.
 * @param parent Parent widget.
 */
MainMenuBar::MainMenuBar(Actions::Game* gameActions, QWidget *parent) :
	QMenuBar(parent), gameActions(gameActions)
{
	this->gameMenu = this->addMenu("");
	this->gameMenu->addAction(this->gameActions->getNewGameAction());
	this->gameMenu->addAction(this->gameActions->getEndGameAction());
	this->gameMenu->addSeparator();
	this->gameMenu->addAction(this->gameActions->getLoadGameAction());
	this->gameMenu->addAction(this->gameActions->getSaveGameAction());
	this->gameMenu->addSeparator();
	this->gameMenu->addAction(this->gameActions->getShowHighscoresAction());
	this->gameMenu->addSeparator();
	this->gameMenu->addAction(this->gameActions->getExitAction());

	this->retranslateUI();
}

/**
 * Retranslates all strings.
 */
void MainMenuBar::retranslateUI()
{
	this->gameMenu->setTitle(tr("&Game"));
}

/**
 * Frees all used resources.
 */
MainMenuBar::~MainMenuBar()
{

}

}
