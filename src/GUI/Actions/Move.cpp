#include "Move.hpp"
#include "../GameView.hpp"

#include <QAction>
#include <QEvent>
#include <QWidget>
#include <QMenu>
#include <QIcon>

namespace GUI
{
namespace Actions
{

/**
 * Creates a new move action container.
 *
 * @param gameView Game view, used to invoke undo/show hint actions for the game.
 * @param parentWindow Parent window, used for dialogs.
 * @param parent Parent object.
 */
Move::Move(GameView* gameView, QWidget* parentWindow, QObject* parent) :
	QObject(parent), gameView(gameView), parentWindow(parentWindow)
{
	this->createActions();
	this->createMenu();
	this->retranslateUI();
	this->updateActions();

	this->connect(this->gameView, &::GUI::GameView::stateChanged,
				  this, &Move::updateActions);
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
 * Returns the move menu.
 *
 * The move menu contains all move actions.
 *
 * @return The move menu.
 */
QMenu* Move::getMenu() const
{
	return this->menu.data();
}

/**
 * Updates actions, i.e. checks whether they have to be disabled/enabled.
 */
void Move::updateActions()
{
	// Disable all actions.

	this->undoAction->setEnabled(false);
	this->hintAction->setEnabled(false);

	// Check which actions should be enabled.

	if (this->gameView->isActive())
	{
		this->undoAction->setEnabled(this->gameView->isUndoPossible());
		this->hintAction->setEnabled(this->gameView->isShowHintPossible());
	}
}

/**
 * Create all actions and connect them.
 */
void Move::createActions()
{
	QIcon undoIcon;
	undoIcon.addFile(":/icons/fatcow/16x16/undo.png", QSize(16, 16));
	undoIcon.addFile(":/icons/fatcow/32x32/undo.png", QSize(32, 32));
	this->undoAction = new QAction(undoIcon, "", this);
	this->connect(this->undoAction, &QAction::triggered,
				  this->gameView, &::GUI::GameView::undoLastMove);

	QIcon hintIcon;
	hintIcon.addFile(":/icons/fatcow/16x16/lightbulb.png", QSize(16, 16));
	hintIcon.addFile(":/icons/fatcow/32x32/lightbulb.png", QSize(32, 32));
	this->hintAction = new QAction(hintIcon, "", this);


	this->connect(this->hintAction, &QAction::triggered,
				  this->gameView, &::GUI::GameView::showHint);
}

/**
 * Creates the move menu.
 */
void Move::createMenu()
{
	this->menu.reset(new QMenu(0));
	this->menu->addAction(this->undoAction);
	this->menu->addAction(this->hintAction);
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

	this->menu->setTitle(tr("&Move"));
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
