#include "LoadGame.hpp"
#include "../../Game/Game.hpp"

#include <QPushButton>
#include <QEvent>
#include <QGridLayout>
#include <QDialogButtonBox>

namespace GUI
{
namespace Dialogs
{

/**
 * Creates a new load game dialog for the given game.
 *
 * @param game Game to load.
 * @param parent Parent widget.
 */
LoadGame::LoadGame(QSharedPointer< ::Game::Game> game, QWidget *parent) :
    QDialog(parent), game(game)
{
	this->layout = new QVBoxLayout;
	this->setLayout(this->layout);

	this->gameSetupWidget = new Widgets::GameSetup(this);
	this->layout->addWidget(this->gameSetupWidget);

	this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
	this->layout->addWidget(this->buttonBox);

	this->loadGameButton = this->buttonBox->button(QDialogButtonBox::Ok);

	// Load game settings.

	auto boardWidget = this->gameSetupWidget->getBoardConfigurationWidget();
	boardWidget->setNumberOfRows(game->getGameLogic()->getBoard()->getNumberOfRows());
	boardWidget->setNumberOfColumns(game->getGameLogic()->getBoard()->getNumberOfColumns());

	auto timeLimitWidget = this->gameSetupWidget->getTimeLimitConfigurationWidget();
	timeLimitWidget->setHasTimeLimit(game->getGameLogic()->hasTimeLimit());
	timeLimitWidget->setTimeLimit(game->getGameLogic()->getTimeLimit());
	timeLimitWidget->setTimeoutAction(game->getGameLogic()->getTimeoutAction());

	auto gameWidget = this->gameSetupWidget->getGameConfigurationWidget();
	gameWidget->setAllowHint(game->isHintAllowed());
	gameWidget->setAllowUndo(game->isUndoAllowed());
	gameWidget->setSaveHighscore(game->isSavingHighscore());

	auto firstPlayerWidget = this->gameSetupWidget->getFirstPlayerConfigurationWidget();
	firstPlayerWidget->setPlayerName(game->getFirstPlayer()->getName());
	firstPlayerWidget->setPlayerType(::GUI::Widgets::PlayerConfiguration::PlayerType::HUMAN_PLAYER);

	auto secondPlayerWidget = this->gameSetupWidget->getSecondPlayerConfigurationWidget();
	secondPlayerWidget->setPlayerName(game->getSecondPlayer()->getName());
	secondPlayerWidget->setPlayerType(
	            ::GUI::Widgets::PlayerConfiguration::PlayerType::ARTIFICIAL_INTELLIGENCE);

	// Disable widgets.

	boardWidget->setEnabled(false);
	timeLimitWidget->setEnabled(false);
	gameWidget->setEnabled(false);
	firstPlayerWidget->setEnabled(true);
	secondPlayerWidget->setEnabled(true);

	this->retranslateUI();

	this->connect(this->buttonBox, &QDialogButtonBox::accepted, this, &LoadGame::accept);
	this->connect(this->buttonBox, &QDialogButtonBox::rejected, this, &LoadGame::reject);
	this->connect(this->gameSetupWidget, &Widgets::GameSetup::configurationChanged,
	              this, &LoadGame::updateLoadGameButton);
}

/**
 * Frees all used resoures.
 */
LoadGame::~LoadGame()
{

}

/**
 * Replaces the placeholder players in the game with players created according to the configuration.
 *
 * @param playerFactory Player factory used to create the players.
 */
void LoadGame::replacePlayers(::Game::Players::Factory& playerFactory)
{
	auto firstPlayer =
	        this->gameSetupWidget->getFirstPlayerConfigurationWidget()->createPlayer(playerFactory);
	auto secondPlayer =
	        this->gameSetupWidget->getSecondPlayerConfigurationWidget()->createPlayer(playerFactory);

	this->game->replacePlayers(firstPlayer, secondPlayer);
}

/**
 * Enables/disabled the load game button according to whether the game setup is valid or not.
 */
void LoadGame::updateLoadGameButton()
{
	this->loadGameButton->setEnabled(this->gameSetupWidget->isValid());
}

/**
 * Retranslates all strings.
 */
void LoadGame::retranslateUI()
{
	this->setWindowTitle(this->tr("Load game"));
	this->loadGameButton->setText(this->tr("Start game"));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
void LoadGame::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	QDialog::changeEvent(event);
}

}
}
