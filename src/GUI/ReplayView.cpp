#include "ReplayView.hpp"
#include "../Game/Replay.hpp"
#include "FileIO.hpp"
#include "../Game/ParseError.hpp"
#include "../Game/Players/Placeholder.hpp"

#include <QMessageBox>
#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

namespace GUI
{

/**
 * Creates a new replay view.
 *
 * @param manager View manager to use.
 */
ReplayView::ReplayView(ViewManager* manager)
    : AbstractView(manager), currentMoveNo(0)
{
	this->widget = new Widgets::Board(0);
}

/**
 * Frees all used resources.
 */
ReplayView::~ReplayView()
{

}

/**
 * Returns the central widget of this view.
 *
 * @return Widget for the view.
 */
QWidget* ReplayView::getWidget() const
{
	return this->widget;
}

/**
 * Returns whether there is a replay loaded or not.
 *
 * @return When a replay is loaded true, otherwise false.
 */
bool ReplayView::hasReplay() const
{
	return !this->replay.isNull();
}

/**
 * Returns whether the currently loaded replay has a next move or not.
 *
 * Returns false when no replay is loaded.
 *
 * @return When there is a next move true, otherwise false.
 */
bool ReplayView::hasNextMove() const
{
	if (this->hasReplay())
	{
		return this->currentMoveNo + 1 < this->replay->getNumberOfMoves();
	}

	return false;
}

/**
 * Returns whether the currently loaded replay has a previous move or not.
 *
 * Returns false when no replay is loaded.
 *
 * @return When there is a previous move true, otherwise false.
 */
bool ReplayView::hasPreviousMove() const
{
	if (this->hasReplay())
	{
		return this->currentMoveNo > 0;
	}

	return false;
}

/**
 * Does nothing and returns true.
 *
 * This method is called by the view manager before deactivating the view.
 *
 * @return When the view should be deactivated true, otherwise false.
 */
bool ReplayView::confirmDeactivation()
{
	return true;
}

/**
 * Shows a dialog asking the user to open a replay file, then opens the file and loads the replay.
 */
void ReplayView::loadReplay()
{
	QString fileContent;
	QString fileName;
	QString nameFilter = this->tr("Replays (*.replay)");

	if (FileIO::GetExistingFileName(this->getWidget(), fileName, nameFilter) &&
	        FileIO::GetFileContent(this->getWidget(), fileName, fileContent) &&
	        this->requestActivation())
	{
		try
		{
			::Game::Players::Factory playerFactory(this->widget);
			auto loadedReplay = ::Game::Replay::CreateFromString(fileContent, playerFactory);

			this->closeReplay();
			this->replay = loadedReplay;
			this->currentMoveNo = 0;
			this->jumpToStart();

			emit this->stateChanged();
		}
		catch (const ::Game::ParseError& error)
		{
			QMessageBox::critical(this->getWidget(), this->tr("Failed to load replay"),
			                      this->tr("Failed to load replay due to parse error: %1").arg(error.what()));
		}
	}
}

/**
 * Closes the currently open replay.
 *
 * Does nothing if no replay is opened.
 */
void ReplayView::closeReplay()
{
	if (this->hasReplay())
	{
		this->replay.reset();
		this->currentMoveNo = 0;

		emit this->stateChanged();
	}
}

/**
 * Step to the next move.
 */
void ReplayView::nextMove()
{
	if (this->hasNextMove())
	{
		this->currentMoveNo++;

		auto currentMove = this->replay->getMove(this->currentMoveNo);
		auto position = this->replay->computeMovePosition(this->currentMoveNo);
		auto player = this->playerIdToPlayer(currentMove.first);

		this->widget->startPlayerTurn(player);
		this->widget->makeMove(position.first, position.second, player);
		this->widget->endPlayerTurn();

		emit this->stateChanged();
	}
}

/**
 * Step to the previous move.
 */
void ReplayView::previousMove()
{
	if (this->hasPreviousMove())
	{
		auto position = this->replay->computeMovePosition(this->currentMoveNo);

		this->widget->makeCellEmpty(position.first, position.second);

		this->currentMoveNo--;

		emit this->stateChanged();
	}
}

/**
 * Jump to the start of the replay.
 */
void ReplayView::jumpToStart()
{
	if (this->hasReplay())
	{
		this->widget->startNewGame(this->replay->getNumberOfColumns(),
		                           this->replay->getNumberOfRows(),
		                           this->replay->getFirstPlayer(),
		                           this->replay->getSecondPlayer());

		this->currentMoveNo = 0;

		auto currentMove = this->replay->getMove(this->currentMoveNo);
		auto position = this->replay->computeMovePosition(this->currentMoveNo);
		auto player = this->playerIdToPlayer(currentMove.first);

		this->widget->startPlayerTurn(player);
		this->widget->makeMove(position.first, position.second, player);
		this->widget->endPlayerTurn();

		emit this->stateChanged();
	}
}

/**
 * Jump to the end of the replay.
 */
void ReplayView::jumpToEnd()
{
	while (this->hasNextMove())
	{
		this->nextMove();
	}
}

/**
 * Returns the placeholder player for the given player id.
 *
 * @param playerId Player id as used in the game engine.
 * @return Placeholder player with the given id.
 */
QSharedPointer< ::Game::Players::Placeholder> ReplayView::playerIdToPlayer(::GameLogic::FourInALine::Game::PlayerType playerId) const
{
	if (playerId == ::GameLogic::FourInALine::Game::PLAYER_ONE)
	{
		return this->replay->getFirstPlayer();
	}
	else
	{
		return this->replay->getSecondPlayer();
	}
}

}
