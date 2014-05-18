#include "MainMenuBar.hpp"

#include <QEvent>

namespace GUI
{

/**
 * Creates a new menu bar for the main window, using the given actions.
 *
 * @param gameActions Game action container.
 * @param settingsActions Settings action container.
 * @param parent Parent widget.
 */
MainMenuBar::MainMenuBar(Actions::Game* gameActions, Actions::Settings* settingsActions,
						 Actions::View* viewActions, Actions::Move* moveActions,
						 Actions::Help* helpActions, QWidget *parent) :
	QMenuBar(parent), gameActions(gameActions), settingsActions(settingsActions),
	viewActions(viewActions), moveActions(moveActions), helpActions(helpActions)
{
	this->setupLanguageMenu();

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

	this->viewMenu = this->addMenu("");
	this->viewMenu->addAction(this->viewActions->getFullscreenCheckboxAction());

	this->moveMenu = this->addMenu("");
	this->moveMenu->addAction(this->moveActions->getUndoAction());
	this->moveMenu->addAction(this->moveActions->getHintAction());

	this->settingsMenu = this->addMenu("");
	this->settingsMenu->addMenu(this->languageMenu);
	this->settingsMenu->addSeparator();
	this->settingsMenu->addAction(this->settingsActions->getOpenSettingsAction());

	this->helpMenu = this->addMenu("");
	this->helpMenu->addAction(this->helpActions->getAboutAction());
	this->helpMenu->addAction(this->helpActions->getAboutQtAction());

	this->retranslateUI();
}

/**
 * Frees all used resources.
 */
MainMenuBar::~MainMenuBar()
{

}

/**
 * Retranslates all strings.
 */
void MainMenuBar::retranslateUI()
{
	this->gameMenu->setTitle(tr("&Game"));

	this->viewMenu->setTitle(tr("&View"));

	this->moveMenu->setTitle(tr("&Move"));

	this->settingsMenu->setTitle(tr("&Settings"));

	this->languageMenu->setTitle(tr("&Languages"));

	this->helpMenu->setTitle(tr("&Help"));
}

/**
* Creates the language menu.
*/
void MainMenuBar::setupLanguageMenu()
{
	this->languageMenu = new QMenu(this);
	this->languageGroup = this->settingsActions->getLanguages();

	QList<QAction*> languageActions = this->languageGroup->actions();

	int nLanguageActions = languageActions.count();
	for (int i = 0; i < nLanguageActions; ++i)
	{
		this->languageMenu->addAction(languageActions[i]);
	}
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
void MainMenuBar::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	QMenuBar::changeEvent(event);
}

}
