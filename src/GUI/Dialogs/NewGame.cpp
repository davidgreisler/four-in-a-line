#include "NewGame.hpp"
#include "../Game.hpp"
#include "../Widgets/PlayerConfiguration.hpp"
#include "../Widgets/TimeLimitConfiguration.hpp"
#include "../Widgets/GameConfiguration.hpp"
#include "../Widgets/BoardConfiguration.hpp"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QEvent>
#include <QDebug>

namespace GUI
{
namespace Dialogs
{

/**
 * Creates a new new game dialog.
 *
 * @param parent Parent widget.
 */
NewGame::NewGame(QWidget *parent) :
    QDialog(parent)
{
	this->layout = new QVBoxLayout;
	this->setLayout(this->layout);

	this->gameSetupWidget = new Widgets::GameSetup(this);
	this->layout->addWidget(this->gameSetupWidget);

	this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
	this->layout->addWidget(this->buttonBox);

	this->connect(this->buttonBox, &QDialogButtonBox::accepted, this, &NewGame::accept);
	this->connect(this->buttonBox, &QDialogButtonBox::rejected, this, &NewGame::reject);

	this->connect(this->gameSetupWidget,
	              &Widgets::GameSetup::configurationChanged,
	              this, &NewGame::updateNewGameButton);

	this->connect(this->gameSetupWidget,
	              &Widgets::GameSetup::configurationChanged,
	              this, &NewGame::updateNewGameButton);

	this->retranslateUI();
	this->updateNewGameButton();
}

/**
 * Frees all used resources.
 */
NewGame::~NewGame()
{

}

/**
 * Creates and returns the first player.
 *
 * @param factory Player factory to use to create the player.
 * @return First player.
 */
QSharedPointer<AbstractPlayer> NewGame::createFirstPlayer(PlayerFactory& factory) const
{
	return this->gameSetupWidget->getFirstPlayerConfigurationWidget()->createPlayer(factory);
}

/**
 * Creates and returns the second player.
 *
 * @param factory Player factory to use to create the player.
 * @return Second player.
 */
QSharedPointer<AbstractPlayer> NewGame::createSecondPlayer(PlayerFactory& factory) const
{
	return this->gameSetupWidget->getSecondPlayerConfigurationWidget()->createPlayer(factory);
}

/**
 * Creates a new game according to the settings the user made.
 *
 * @param factory Player factory to use to create the players.
 * @return New game.
 */
QSharedPointer<GUI::Game> NewGame::createGame(PlayerFactory& factory) const
{
	QSharedPointer< ::Game::FourInALine::Game> fourInALine;
	QSharedPointer<GUI::Game> game;
	QSharedPointer<AbstractPlayer> firstPlayer = this->createFirstPlayer(factory);
	QSharedPointer<AbstractPlayer> secondPlayer = this->createSecondPlayer(factory);
	auto boardConfigurationWidget = this->gameSetupWidget->getBoardConfigurationWidget();
	auto timeLimitConfigurationWidget = this->gameSetupWidget->getTimeLimitConfigurationWidget();
	auto gameConfigurationWidget = this->gameSetupWidget->getGameConfigurationWidget();

	unsigned int nRows = boardConfigurationWidget->getNumberOfRows();
	unsigned int nColumns = boardConfigurationWidget->getNumberOfColumns();
	unsigned int firstMove = gameConfigurationWidget->getFirstMove();

	fourInALine.reset(new ::Game::FourInALine::Game(nRows, nColumns, firstMove));

	if (timeLimitConfigurationWidget->hasTimeLimit())
	{
		fourInALine->setTimeLimit(timeLimitConfigurationWidget->getTimeLimit());
		fourInALine->setTimeoutAction(timeLimitConfigurationWidget->getTimeoutAction());
	}

	game = QSharedPointer<GUI::Game>(new GUI::Game(fourInALine, firstPlayer, secondPlayer));
	game->setAllowHint(gameConfigurationWidget->isAllowHintEnabled() &&
	                   gameConfigurationWidget->getAllowHint());
	game->setAllowUndo(gameConfigurationWidget->isAllowUndoEnabled() &&
	                   gameConfigurationWidget->getAllowUndo());
	game->setSaveHighscore(gameConfigurationWidget->isSaveHighscoreEnabled() &&
	                       gameConfigurationWidget->getSaveHighscore());

	return game;
}

/**
 * Enables/disables the new game button in case the settings are invalid/incomplete.
 */
void NewGame::updateNewGameButton()
{
	this->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(this->gameSetupWidget->isValid());
}

/**
 * Retranslates all strings.
 */
void NewGame::retranslateUI()
{
	this->setWindowTitle(this->tr("New game"));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
void NewGame::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	QDialog::changeEvent(event);
}

}
}
