#include "ReplayController.hpp"
#include "FileIO.hpp"

#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

namespace GUI
{

/**
 * Creates a new replay controller.
 *
 * @param manager Controller manager to use.
 */
ReplayController::ReplayController(ControllerManager* manager)
	: AbstractController(manager)
{
	// @todo Implement replay viewer widget.

	this->widget = new QWidget(0);
	this->widget->setAutoFillBackground(true);

	QPalette palette = this->widget->palette();
	palette.setColor(this->widget->backgroundRole(), Qt::green);
	this->widget->setPalette(palette);
}

/**
 * Frees all used resources.
 */
ReplayController::~ReplayController()
{

}

/**
 * Returns the central widget of this controller.
 *
 * @return Widget for the controller.
 */
QWidget* ReplayController::getWidget() const
{
	return this->widget;
}

/**
 * Returns whether there is a replay loaded or not.
 *
 * @return When a replay is loaded true, otherwise false.
 */
bool ReplayController::hasReplay() const
{
	// @todo Implement.

	return false;
}

/**
 * Returns whether the currently loaded replay has a next move or not.
 *
 * Returns false when no replay is loaded.
 *
 * @return When there is a next move true, otherwise false.
 */
bool ReplayController::hasNextMove() const
{
	// @todo Implement.

	return false;
}

/**
 * Returns whether the currently loaded replay has a previous move or not.
 *
 * Returns false when no replay is loaded.
 *
 * @return When there is a previous move true, otherwise false.
 */
bool ReplayController::hasPreviousMove() const
{
	// @todo Implement.

	return false;
}

/**
 * Does nothing and returns true.
 *
 * This method is called by the controller manager before deactivating the controller.
 *
 * @return When the controller should be deactivated true, otherwise false.
 */
bool ReplayController::confirmDeactivation()
{
	return true;
}

/**
 * Shows a dialog asking the user to open a replay file, then opens the file and loads the replay.
 */
void ReplayController::loadReplay()
{
	QString fileName;
	QString nameFilter = this->tr("Replays (*.replay)");

	if (FileIO::GetExistingFileName(this->getWidget(), fileName, nameFilter))
	{
		if (this->requestActivation())
		{
			this->closeReplay();

			// Load replay.

			// @todo Implement.

			emit this->stateChanged();
		}
	}
}

/**
 * Closes the currently open replay.
 *
 * Does nothing if no replay is opened.
 */
void ReplayController::closeReplay()
{
	if (this->hasReplay())
	{
		// @todo Implement.

		emit this->stateChanged();
	}
}

/**
 * Step to the next move.
 */
void ReplayController::nextMove()
{
	// @todo Implement.

	emit this->stateChanged();
}

/**
 * Step to the previous move.
 */
void ReplayController::previousMove()
{
	// @todo Implement.

	emit this->stateChanged();
}

/**
 * Jump to the start of the replay.
 */
void ReplayController::jumpToStart()
{
	// @todo Implement.

	emit this->stateChanged();
}

/**
 * Jump to the end of the replay.
 */
void ReplayController::jumpToEnd()
{
	// @todo Implement.

	emit this->stateChanged();
}

}
