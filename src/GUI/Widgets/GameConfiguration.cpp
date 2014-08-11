#include "GameConfiguration.hpp"

#include <QFormLayout>
#include <QLabel>
#include <QCheckBox>
#include <QRadioButton>
#include <QEvent>

namespace GUI
{
namespace Widgets
{

/**
 * Create a new game configuration widget.
 *
 * @param parent Parent widget.
 */
GameConfiguration::GameConfiguration(QWidget* parent) :
    QGroupBox(parent)
{
	this->formLayout = new QFormLayout(this);
	this->setLayout(this->formLayout);

	this->firstMoveLabel = new QLabel(this);
	this->formLayout->addRow(this->firstMoveLabel);

	this->firstMovePlayerOneButton = new QRadioButton(this);
	this->formLayout->addRow(this->firstMovePlayerOneButton);

	this->firstMovePlayerTwoButton = new QRadioButton(this);
	this->formLayout->addRow(this->firstMovePlayerTwoButton);

	this->saveHighscoreCheckBox = new QCheckBox(this);
	this->formLayout->addRow(this->saveHighscoreCheckBox);

	this->allowHintCheckBox = new QCheckBox(this);
	this->formLayout->addRow(this->allowHintCheckBox);

	this->allowUndoCheckBox = new QCheckBox(this);
	this->formLayout->addRow(this->allowUndoCheckBox);

	this->retranslateUI();

	// Set defaults.

	this->setFirstMove(::GameLogic::FourInALine::Game::PLAYER_ONE);
	this->setSaveHighscore(true);
	this->setAllowHint(true);
	this->setAllowUndo(true);
}

/**
 * Frees all used resources.
 */
GameConfiguration::~GameConfiguration()
{

}

/**
 * Sets the player who makes the first move.
 *
 * @param playerId Player who makes the first move.
 */
void GameConfiguration::setFirstMove(GameConfiguration::PlayerIdType playerId)
{
	if (playerId == ::GameLogic::FourInALine::Game::PLAYER_ONE)
	{
		this->firstMovePlayerOneButton->setChecked(true);
	}
	else
	{
		this->firstMovePlayerTwoButton->setChecked(true);
	}
}

/**
 * Returns the player who makes the first move.
 *
 * @return Player who makes the first move.
 */
GameConfiguration::PlayerIdType GameConfiguration::getFirstMove() const
{
	if (this->firstMovePlayerOneButton->isChecked())
	{
		return ::GameLogic::FourInALine::Game::PLAYER_ONE;
	}
	else
	{
		return ::GameLogic::FourInALine::Game::PLAYER_TWO;
	}
}

/**
 * Sets whether the first move radio buttons are enabled/disabled.
 *
 * @param enabled To enable true, to disable false.
 */
void GameConfiguration::setFirstMoveEnabled(bool enabled)
{
	this->firstMovePlayerOneButton->setEnabled(enabled);
	this->firstMovePlayerTwoButton->setEnabled(enabled);
}

/**
 * Returns whether the first move radio buttons are enabled/disabled.
 *
 * @return When they are enabled true, otherwise false.
 */
bool GameConfiguration::isFirstMoveEnabled() const
{
	return this->firstMovePlayerOneButton->isEnabled();
}

/**
 * Sets whether to save the game result in the highscore list or not.
 *
 * @param saveHighscore Whether to save the result or not.
 */
void GameConfiguration::setSaveHighscore(bool saveHighscore)
{
	this->saveHighscoreCheckBox->setChecked(saveHighscore);
}

/**
 * Returns whether the game result should be saved in the highscore list or not.
 *
 * @return When it should be saved true, otherwise false.
 */
bool GameConfiguration::getSaveHighscore() const
{
	return this->saveHighscoreCheckBox->isChecked();
}

/**
 * Sets whether the save highscore option is enabled/disabled.
 *
 * @param enabled Whether to enable/disable the option.
 */
void GameConfiguration::setSaveHighscoreEnabled(bool enabled)
{
	this->saveHighscoreCheckBox->setEnabled(enabled);
}

/**
 * Returns whether the save highscore check box is enabled (checkable) or not.
 *
 * @return When it is checkable true, when it is disabled false.
 */
bool GameConfiguration::isSaveHighscoreEnabled() const
{
	return this->saveHighscoreCheckBox->isEnabled();
}

/**
 * Sets whether the hint function is allowed or not.
 *
 * @param allowHint To allow hints true, otherwise false.
 */
void GameConfiguration::setAllowHint(bool allowHint)
{
	this->allowHintCheckBox->setChecked(allowHint);
}

/**
 * Returns whether the hint function is allowed or not.
 *
 * @return When it is allowed true, otherwise false.
 */
bool GameConfiguration::getAllowHint() const
{
	return this->allowHintCheckBox->isChecked();
}

/**
 * Sets whether the checkbox for the hint function is enabled/disabled.
 *
 * @param enabled To enable true, to disable false.
 */
void GameConfiguration::setAllowHintEnabled(bool enabled)
{
	this->allowHintCheckBox->setEnabled(enabled);
}

/**
 * Returns whether the checkbox for the hint function is enabled/disabled.
 *
 * @return When it is enabled true, otherwise false.
 */
bool GameConfiguration::isAllowHintEnabled() const
{
	return this->allowHintCheckBox->isEnabled();
}

/**
 * Sets whether the undo function is allowed or not.
 *
 * @param allowUndo To allow it true, to disallow it false.
 */
void GameConfiguration::setAllowUndo(bool allowUndo)
{
	this->allowUndoCheckBox->setChecked(allowUndo);
}

/**
 * Returns whether the undo function is allowed or not.
 *
 * @return When it is allowed true, otherwise false.
 */
bool GameConfiguration::getAllowUndo() const
{
	return this->allowUndoCheckBox->isChecked();
}

/**
 * Sets whether the checkbox for the undo function is enabled/disabled.
 *
 * @param enabled To enable it true, to disable it false.
 */
void GameConfiguration::setAllowUndoEnabled(bool enabled)
{
	this->allowUndoCheckBox->setEnabled(enabled);
}

/**
 * Returns whether the checkbox for the undo function is enabled/disabled.
 *
 * @return When it is enabled true, otherwise false.
 */
bool GameConfiguration::isAllowUndoEnabled() const
{
	return this->allowUndoCheckBox->isEnabled();
}

/**
 * Retranslates all strings.
 */
void GameConfiguration::retranslateUI()
{
	this->setTitle(tr("General settings"));

	this->saveHighscoreCheckBox->setText(tr("Save result in highscore list"));
	this->allowHintCheckBox->setText(tr("Allow use of the hint button to show a hint for the next move"));
	this->allowUndoCheckBox->setText(tr("Allow use of the undo button to undo the last move"));
	this->firstMoveLabel->setText(tr("Player who makes the first move"));
	this->firstMovePlayerOneButton->setText(tr("Player 1"));
	this->firstMovePlayerTwoButton->setText(tr("Player 2"));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
bool GameConfiguration::event(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	return QGroupBox::event(event);
}

}
}
