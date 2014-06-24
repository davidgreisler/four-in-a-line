#include "TimeLimitConfiguration.hpp"

#include <QEvent>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include <QRadioButton>

#include <algorithm>

namespace GUI
{
namespace Widgets
{

using TimeoutAction = ::Game::FourInALine::Game::TimeoutAction;

const unsigned int TimeLimitConfiguration::MINIMUM_TIME_LIMIT = 5;
const unsigned int TimeLimitConfiguration::MAXIMUM_TIME_LIMIT = 86400;
const TimeoutAction TimeLimitConfiguration::DEFAULT_TIMEOUT_ACTION = TimeoutAction::DRAW_GAME;

/**
 * Creates a new time limit configuration widget.
 *
 * @param parent Parent widget.
 */
TimeLimitConfiguration::TimeLimitConfiguration(QWidget *parent) :
    QGroupBox(parent)
{
	this->setCheckable(true);

	this->formLayout = new QFormLayout(this);
	this->setLayout(this->formLayout);

	this->timeLimitLabel = new QLabel(this);
	this->timeLimitSpinBox = new QSpinBox(this);
	this->timeLimitSpinBox->setMinimum(TimeLimitConfiguration::MINIMUM_TIME_LIMIT);
	this->timeLimitSpinBox->setMaximum(TimeLimitConfiguration::MAXIMUM_TIME_LIMIT);
	this->formLayout->addRow(this->timeLimitLabel, this->timeLimitSpinBox);

	this->timeoutActionLabel = new QLabel(this);
	this->formLayout->addRow(this->timeoutActionLabel);

	this->drawActionRadioButton = new QRadioButton(this);
	this->formLayout->addRow(this->drawActionRadioButton);

	this->loseActionRadioButton = new QRadioButton(this);
	this->formLayout->addRow(this->loseActionRadioButton);

	this->setTimeoutAction(TimeLimitConfiguration::DEFAULT_TIMEOUT_ACTION);

	this->retranslateUI();
}

/**
 * Frees all used resources.
 */
TimeLimitConfiguration::~TimeLimitConfiguration()
{

}

/**
 * Returns whether there is a time limit or not.
 *
 * @return When there is a time limit true, otherwise false.
 */
bool TimeLimitConfiguration::hasTimeLimit() const
{
	return this->isChecked();
}

/**
 * Set whether there is a time limit or not.
 *
 * @param hasTimeLimit Whether there is a time limit or not.
 */
void TimeLimitConfiguration::setHasTimeLimit(bool hasTimeLimit)
{
	this->setChecked(hasTimeLimit);
}

/**
 * Returns the time limit.
 *
 * @return Time limit in seconds.
 */
unsigned int TimeLimitConfiguration::getTimeLimit() const
{
	return this->timeLimitSpinBox->value();
}

/**
 * Sets the time limit.
 *
 * @param timeLimit Time limit in seconds. Range: MINIMUM_TIME_LIMIT to MAXIMUM_TIME_LIMIT, values
 *        out of range are set to the minimum/maximum.
 */
void TimeLimitConfiguration::setTimeLimit(unsigned int timeLimit)
{
	unsigned int newTimeLimit;

	newTimeLimit = std::min(TimeLimitConfiguration::MAXIMUM_TIME_LIMIT, timeLimit);
	newTimeLimit = std::max(TimeLimitConfiguration::MINIMUM_TIME_LIMIT, timeLimit);

	this->timeLimitSpinBox->setValue(newTimeLimit);
}

/**
 * Returns the timeout action.
 *
 * @return The selected timeout action.
 */
TimeoutAction TimeLimitConfiguration::getTimeoutAction() const
{
	Game::FourInALine::Game::TimeoutAction action;

	if (this->drawActionRadioButton->isChecked())
	{
		action = TimeoutAction::DRAW_GAME;
	}
	else
	{
		action = TimeoutAction::LOSE_GAME;
	}

	return action;
}

/**
 * Sets the timeout action.
 *
 * @param action The new timeout action.
 */
void TimeLimitConfiguration::setTimeoutAction(TimeoutAction action)
{
	if (TimeoutAction::DRAW_GAME == action)
	{
		this->drawActionRadioButton->setChecked(true);
	}
	else
	{
		this->loseActionRadioButton->setChecked(true);
	}
}

/**
 * Retranslates all strings.
 */
void TimeLimitConfiguration::retranslateUI()
{
	this->setTitle(this->tr("Time limit"));
	this->timeLimitLabel->setText(this->tr("Time limit"));
	this->timeLimitSpinBox->setSuffix(this->tr(" seconds"));
	this->timeoutActionLabel->setText(this->tr("Action when a player times out"));
	this->drawActionRadioButton->setText(this->tr("Draw the game."));
	this->loseActionRadioButton->setText(this->tr("Player loses the game."));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
bool TimeLimitConfiguration::event(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	return QGroupBox::event(event);
}

}
}
