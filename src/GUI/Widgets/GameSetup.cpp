#include "GameSetup.hpp"
#include "BoardConfiguration.hpp"
#include "GameConfiguration.hpp"
#include "PlayerConfiguration.hpp"
#include "TimeLimitConfiguration.hpp"

#include <QGridLayout>
#include <QEvent>

namespace GUI
{
namespace Widgets
{

/**
 * Creates a new game setup widget.
 *
 * @param parent Parent widget.
 */
GameSetup::GameSetup(QWidget *parent) :
    QWidget(parent)
{
	auto playerOneId = ::Game::FourInALine::Game::PLAYER_ONE;
	auto playerTwoId = ::Game::FourInALine::Game::PLAYER_TWO;

	this->layout = new QGridLayout;
	this->setLayout(this->layout);

	this->boardConfigurationWidget = new BoardConfiguration;
	this->boardConfigurationWidget->setMinimumNumberOfColumns(6);
	this->boardConfigurationWidget->setMaximumNumberOfColumns(9);
	this->boardConfigurationWidget->setNumberOfColumns(8);
	this->boardConfigurationWidget->setMinimumNumberOfRows(6);
	this->boardConfigurationWidget->setMaximumNumberOfRows(9);
	this->boardConfigurationWidget->setNumberOfRows(8);
	this->layout->addWidget(this->boardConfigurationWidget, 0, 0, 1, 2);

	this->timeLimitConfigurationWidget = new TimeLimitConfiguration;
	this->layout->addWidget(this->timeLimitConfigurationWidget, 1, 0, 1, 2);

	this->firstPlayerConfigurationWidget = new PlayerConfiguration(playerOneId);
	this->layout->addWidget(this->firstPlayerConfigurationWidget, 2, 0, 1, 1);

	this->secondPlayerConfigurationWidget = new PlayerConfiguration(playerTwoId);
	this->layout->addWidget(this->secondPlayerConfigurationWidget, 2, 1, 1, 1);

	this->gameConfigurationWidget = new GameConfiguration;
	this->layout->addWidget(this->gameConfigurationWidget, 3, 0, 1, 2);

	this->connect(this->firstPlayerConfigurationWidget,
				  &PlayerConfiguration::playerTypeChanged,
				  this, &GameSetup::updatePlayerType);

	this->connect(this->secondPlayerConfigurationWidget,
				  &PlayerConfiguration::playerTypeChanged,
				  this, &GameSetup::updatePlayerType);

	this->connect(this->firstPlayerConfigurationWidget,
				  &PlayerConfiguration::configurationChanged,
				  this, &GameSetup::updateValidity);

	this->connect(this->secondPlayerConfigurationWidget,
				  &PlayerConfiguration::configurationChanged,
				  this, &GameSetup::updateValidity);

	this->retranslateUI();
	this->updatePlayerType();
	this->updateValidity();
}

/**
 * Frees all used resources.
 */
GameSetup::~GameSetup()
{

}

/**
 * Returns whether the configuration is valid or not.
 *
 * @return When it is valid true, otherwise false.
 */
bool GameSetup::isValid() const
{
	return this->valid;
}

/**
 * Returns the game configuration widget.
 *
 * @return The game configuration widget.
 */
GameConfiguration* GameSetup::getGameConfigurationWidget() const
{
	return gameConfigurationWidget;
}

/**
 * Returns the player configuration widget for the second player.
 *
 * @return Player configuration widget.
 */
PlayerConfiguration* GameSetup::getSecondPlayerConfigurationWidget() const
{
	return secondPlayerConfigurationWidget;
}

/**
 * Returns the player configuration widget for the first player.
 *
 * @return Player configuration widget.
 */
PlayerConfiguration* GameSetup::getFirstPlayerConfigurationWidget() const
{
	return firstPlayerConfigurationWidget;
}

/**
 * Returns the time limit configuration widget.
 *
 * @return Time limit configuration widget.
 */
TimeLimitConfiguration* GameSetup::getTimeLimitConfigurationWidget() const
{
	return timeLimitConfigurationWidget;
}

/**
 * Returns the board configuration widget.
 *
 * @return Board configuration widget.
 */
BoardConfiguration* GameSetup::getBoardConfigurationWidget() const
{
	return boardConfigurationWidget;
}

/**
 * Enables/disables some inputs that are not applicable if certain player types are present.
 */
void GameSetup::updatePlayerType()
{
	bool isGameAgainstArtificialIntelligence = false;
	auto playerTypeAI = Widgets::PlayerConfiguration::PlayerType::ARTIFICIAL_INTELLIGENCE;

	bool isFirstPlayerAI = this->firstPlayerConfigurationWidget->getPlayerType() == playerTypeAI;
	bool isSecondPlayerAI = this->secondPlayerConfigurationWidget->getPlayerType() == playerTypeAI;

	if (isFirstPlayerAI || isSecondPlayerAI)
	{
		isGameAgainstArtificialIntelligence = true;
	}

	if (isGameAgainstArtificialIntelligence)
	{
		this->gameConfigurationWidget->setAllowHintEnabled(true);
		this->gameConfigurationWidget->setAllowUndoEnabled(true);
		this->gameConfigurationWidget->setSaveHighscoreEnabled(false);
	}
	else
	{
		this->gameConfigurationWidget->setAllowHintEnabled(false);
		this->gameConfigurationWidget->setAllowUndoEnabled(false);
		this->gameConfigurationWidget->setSaveHighscoreEnabled(true);
	}
}

/**
 * Invoked when the configuration has changed, updates valid status and emits signals.
 */
void GameSetup::updateValidity()
{
	bool isConfigurationValid = true;

	if (!this->firstPlayerConfigurationWidget->isValid())
	{
		isConfigurationValid = false;
	}
	else if (!this->secondPlayerConfigurationWidget->isValid())
	{
		isConfigurationValid = false;
	}

	bool validBefore = this->valid;
	this->valid = isConfigurationValid;

	if (this->valid && !validBefore)
	{
		emit this->configurationValid();
	}
	else if (!this->valid && validBefore)
	{
		emit this->configurationInvalid();
	}

	emit this->configurationChanged();
}

/**
 * Retranslates all strings.
 */
void GameSetup::retranslateUI()
{

}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
void GameSetup::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	QWidget::changeEvent(event);
}

}
}
