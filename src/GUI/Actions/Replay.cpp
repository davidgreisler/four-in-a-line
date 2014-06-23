#include "Replay.hpp"
#include "../ReplayController.hpp"
#include "../GameController.hpp"

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
 * Creates a new replay action container.
 *
 * @param replayController Replay controller.
 * @param parentWindow Parent window, used for dialogs.
 * @param parent Parent object.
 */
Replay::Replay(GameController* gameController, ReplayController* replayController,
			   QWidget* parentWindow, QObject* parent) :
	QObject(parent), parentWindow(parentWindow), gameController(gameController),
	replayController(replayController)
{
	this->createActions();
	this->createMenu();
	this->retranslateUI();
	this->updateActions();

	this->connect(this->replayController, &::GUI::ReplayController::stateChanged,
				  this, &Replay::updateActions);
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
 * Returns the replay menu.
 *
 * The replay menu contains all replay actions.
 *
 * @return The replay menu.
 */
QMenu* Replay::getMenu() const
{
	return this->menu.data();
}

/**
 * Updates actions, i.e. checks whether they have to be disabled/enabled.
 */
void Replay::updateActions()
{
	// Load replay is always possible.

	this->loadReplayAction->setEnabled(true);

	// Disable all other actions.

	this->saveReplayAction->setEnabled(false);
	this->nextMoveAction->setEnabled(false);
	this->previousMoveAction->setEnabled(false);
	this->jumpToStartAction->setEnabled(false);
	this->jumpToEndAction->setEnabled(false);

	// Check which actions should be enabled.

	if (this->gameController->isActive())
	{
		if (this->gameController->hasGame())
		{
			this->saveReplayAction->setEnabled(true);
		}
	}

	if (this->replayController->isActive())
	{
		if (this->replayController->hasReplay())
		{
			this->jumpToStartAction->setEnabled(true);
			this->jumpToEndAction->setEnabled(true);
			this->nextMoveAction->setEnabled(this->replayController->hasNextMove());
			this->previousMoveAction->setEnabled(this->replayController->hasPreviousMove());
		}
	}
}

/**
 * Create all actions and connect them.
 */
void Replay::createActions()
{
	QIcon loadReplayIcon;
	loadReplayIcon.addFile(":/icons/fatcow/16x16/film.png", QSize(16, 16));
	loadReplayIcon.addFile(":/icons/fatcow/32x32/film.png", QSize(32, 32));
	this->loadReplayAction = new QAction(loadReplayIcon, "", this);
	this->connect(this->loadReplayAction, &QAction::triggered,
				  this->replayController, &::GUI::ReplayController::loadReplay);

	QIcon saveReplayIcon;
	saveReplayIcon.addFile(":/icons/fatcow/16x16/film_save.png", QSize(16, 16));
	saveReplayIcon.addFile(":/icons/fatcow/32x32/film_save.png", QSize(32, 32));
	this->saveReplayAction = new QAction(saveReplayIcon, "", this);
	this->connect(this->saveReplayAction, &QAction::triggered,
				  this->gameController, &::GUI::GameController::saveReplay);

	QIcon nextMoveIcon;
	nextMoveIcon.addFile(":/icons/fatcow/16x16/control_play_blue.png", QSize(16, 16));
	nextMoveIcon.addFile(":/icons/fatcow/32x32/control_play_blue.png", QSize(32, 32));
	this->nextMoveAction = new QAction(nextMoveIcon, "", this);
	this->connect(this->nextMoveAction, &QAction::triggered,
				  this->replayController, &::GUI::ReplayController::nextMove);

	QIcon previousMoveIcon;
	previousMoveIcon.addFile(":/icons/fatcow/16x16/control_play_blue_mirror.png", QSize(16, 16));
	previousMoveIcon.addFile(":/icons/fatcow/32x32/control_play_blue_mirror.png", QSize(32, 32));
	this->previousMoveAction = new QAction(previousMoveIcon, "", this);
	this->connect(this->previousMoveAction, &QAction::triggered,
				  this->replayController, &::GUI::ReplayController::previousMove);

	QIcon jumpToStartIcon;
	jumpToStartIcon.addFile(":/icons/fatcow/16x16/control_start_blue.png", QSize(16, 16));
	jumpToStartIcon.addFile(":/icons/fatcow/32x32/control_start_blue.png", QSize(32, 32));
	this->jumpToStartAction = new QAction(jumpToStartIcon, "", this);
	this->connect(this->jumpToStartAction, &QAction::triggered,
				  this->replayController, &::GUI::ReplayController::jumpToStart);

	QIcon jumpToEndIcon;
	jumpToEndIcon.addFile(":/icons/fatcow/16x16/control_end_blue.png", QSize(16, 16));
	jumpToEndIcon.addFile(":/icons/fatcow/32x32/control_end_blue.png", QSize(32, 32));
	this->jumpToEndAction = new QAction(jumpToEndIcon, "", this);
	this->connect(this->jumpToEndAction, &QAction::triggered,
				  this->replayController, &::GUI::ReplayController::jumpToEnd);
}

/**
 * Creates the replay menu.
 */
void Replay::createMenu()
{
	this->menu.reset(new QMenu(0));
	this->menu->addAction(this->loadReplayAction);
	this->menu->addAction(this->saveReplayAction);
	this->menu->addSeparator();
	this->menu->addAction(this->previousMoveAction);
	this->menu->addAction(this->nextMoveAction);
	this->menu->addAction(this->jumpToStartAction);
	this->menu->addAction(this->jumpToEndAction);
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

	this->menu->setTitle(tr("&Replay"));
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
