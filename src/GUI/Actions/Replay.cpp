#include "Replay.hpp"

#include <QAction>
#include <QEvent>

namespace GUI
{
namespace Actions
{

/**
 * Creates a new replay action container.
 *
 * @param parent Parent window, used for dialogs.
 */
Replay::Replay(QWidget* parentWindow, QObject* parent) :
	QObject(parent), parentWindow(parentWindow)
{
	this->createActions();
	this->retranslateUI();
}

/**
 * Frees all used resources.
 */
Replay::~Replay()
{

}

/**
 * Returns the load replay action.
 *
 * @return Action for loading a replay.
 */
QAction* Replay::getLoadReplayAction() const
{
	return this->loadReplayAction;
}

/**
 * Returns the save replay action.
 *
 * @return Action for saving the replay of the current game.
 */
QAction* Replay::getSaveReplayAction() const
{
	return this->saveReplayAction;
}

/**
 * Returns the next move action.
 *
 * @return Action for stepping to the next move.
 */
QAction* Replay::getNextMoveAction() const
{
	return this->nextMoveAction;
}

/**
 * Returns the previous move action.
 *
 * @return Action for stepping to the previous move.
 */
QAction* Replay::getPreviousMoveAction() const
{
	return this->previousMoveAction;
}

/**
 * Returns the jump to start action.
 *
 * @return Action for jumping back to start of the replay.
 */
QAction* Replay::getJumpToStartAction() const
{
	return this->jumpToStartAction;
}

/**
 * Returns the jump to end action.
 *
 * @return Action for jumping to the end of the replay.
 */
QAction* Replay::getJumpToEndAction() const
{
	return this->jumpToEndAction;
}

/**
 * Load a replay.
 */
void Replay::loadReplay()
{

}

/**
 * Save a replay of the current game.
 */
void Replay::saveReplay()
{

}

/**
 * Step to the next move.
 */
void Replay::nextMove()
{

}

/**
 * Step to the previous move.
 */
void Replay::previousMove()
{

}

/**
 * Jump to the start of the replay.
 */
void Replay::jumpToStart()
{

}

/**
 * Jump to the end of the replay.
 */
void Replay::jumpToEnd()
{

}

/**
 * Create all actions and connect them.
 */
void Replay::createActions()
{
	this->loadReplayAction = new QAction("", this);

	this->saveReplayAction = new QAction("", this);

	this->nextMoveAction = new QAction("", this);

	this->previousMoveAction = new QAction("", this);

	this->jumpToStartAction = new QAction("", this);

	this->jumpToEndAction = new QAction("", this);

	this->connect(this->loadReplayAction, &QAction::triggered, this, &Replay::loadReplay);
	this->connect(this->saveReplayAction, &QAction::triggered, this, &Replay::saveReplay);
	this->connect(this->nextMoveAction, &QAction::triggered, this, &Replay::nextMove);
	this->connect(this->previousMoveAction, &QAction::triggered, this, &Replay::previousMove);
	this->connect(this->jumpToStartAction, &QAction::triggered, this, &Replay::jumpToStart);
	this->connect(this->jumpToEndAction, &QAction::triggered, this, &Replay::jumpToEnd);
}

/**
 * Retranslates all strings.
 */
void Replay::retranslateUI()
{
	this->loadReplayAction->setText(tr("&Load replay ..."));
	this->loadReplayAction->setStatusTip(tr("Load a replay."));

	this->saveReplayAction->setText(tr("&Save replay ..."));
	this->saveReplayAction->setStatusTip(tr("Save a replay of the current game."));

	this->nextMoveAction->setText(tr("&Next move"));
	this->nextMoveAction->setStatusTip(tr("Step to the next move."));

	this->previousMoveAction->setText(tr("&Previous move"));
	this->previousMoveAction->setStatusTip(tr("Step to the previous move."));

	this->jumpToStartAction->setText(tr("&Jump to start"));
	this->jumpToStartAction->setStatusTip(tr("Jump to the start of the replay."));

	this->jumpToEndAction->setText(tr("&Jump to end"));
	this->jumpToEndAction->setStatusTip(tr("Jump to the end of the replay."));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
bool Replay::event(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	return QObject::event(event);
}

}
}
