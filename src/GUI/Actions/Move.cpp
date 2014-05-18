#include "Move.hpp"

#include <QAction>
#include <QEvent>

namespace GUI
{
namespace Actions
{

/**
 * Creates a new move action container.
 *
 * @param parent Parent window, used for dialogs.
 */
Move::Move(QWidget* parentWindow, QObject* parent) :
	QObject(parent), parentWindow(parentWindow)
{
	this->createActions();
	this->retranslateUI();
}

/**
 * Frees all used resources.
 */
Move::~Move()
{

}

/**
 * Returns the undo action.
 *
 * @return Action for undoing last move.
 */
QAction* Move::getUndoAction() const
{
	return this->undoAction;
}

/**
 * Returns the get hint action.
 *
 * @return Action for showing a hint for the next move.
 */
QAction* Move::getHintAction() const
{
	return this->hintAction;
}

/**
 * Undoes the last move of the player.
 */
void Move::undoLastMove()
{

}

/**
 * Shows a hint for the next step.
 */
void Move::showHint()
{

}

/**
 * Create all actions and connect them.
 */
void Move::createActions()
{
	this->undoAction = new QAction("", this);

	this->hintAction = new QAction("", this);

	this->connect(this->undoAction, &QAction::triggered, this, &Move::undoLastMove);
	this->connect(this->hintAction, &QAction::triggered, this, &Move::showHint);
}

/**
 * Retranslates all strings.
 */
void Move::retranslateUI()
{
	this->undoAction->setText(tr("&Undo last move"));
	this->undoAction->setStatusTip(tr("Undoes last move."));

	this->hintAction->setText(tr("&Show hint"));
	this->hintAction->setStatusTip(tr("Shows a hint for the next move."));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
bool Move::event(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	return QObject::event(event);
}

}
}
