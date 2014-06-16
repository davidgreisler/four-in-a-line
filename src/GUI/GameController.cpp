#include "GameController.hpp"
#include "../Game/FourInALine/Game.hpp"
#include "AbstractPlayer.hpp"
#include "FileIO.hpp"

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>

namespace GUI
{

/**
 * Creates a new game controller.
 *
 * @param manager Controller manager.
 */
GameController::GameController(ControllerManager* manager)
	: AbstractController(manager)
{
	// @todo Implement game widget.

	this->widget = new QWidget(0);
	this->widget->setAutoFillBackground(true);

	QPalette palette = this->widget->palette();
	palette.setColor(this->widget->backgroundRole(), Qt::red);
	this->widget->setPalette(palette);
}

/**
 * Frees all used resources.
 */
GameController::~GameController()
{
	delete this->widget;
}

/**
 * Returns the central widget of this controller.
 *
 * @return Widget for the controller.
 */
QWidget* GameController::getWidget() const
{
	return this->widget;
}

/**
 * Returns whether there is a game being played.
 *
 * @return When a game is being played true, otherwise false.
 */
bool GameController::hasGame() const
{
	return !this->game.isNull();
}

/**
 * Returns the game currently being played.
 *
 * @return The current game or a null pointer if no game is being played.
 */
GameController::ConstGamePointerType GameController::getGame() const
{
	return this->game;
}

/**
 * Returns the first player of the game.
 *
 * @return The first player or a null pointer when no game is being played.
 */
const QSharedPointer<const AbstractPlayer> GameController::getFirstPlayer() const
{
	return this->firstPlayer;
}

/**
 * Returns the second player of the game.
 *
 * @return The second player or a null pointer when no game is being played.
 */
const QSharedPointer<const AbstractPlayer> GameController::getSecondPlayer() const
{
	return this->secondPlayer;
}

/**
 * Asks the user whether he wants to abort the current game and returns whether the controller can
 * be deactivated or not.
 *
 * This method is called by the controller manager before deactivating the controller.
 *
 * @return When the controller should be deactivated true, otherwise false.
 */
bool GameController::confirmDeactivation()
{
	return this->endGame();
}

/**
 * Returns whether undoing the last move is possible for the current player.
 *
 * When no game is being played, returns false.
 *
 * @return When it is possible to undo the last move true, otherwise false.
 */
bool GameController::isUndoPossible() const
{
	if (this->hasGame())
	{
		// At least 2 moves are required, one by the current player and one by the other player.

		if (this->game->getNumberOfMoves() >= 2)
		{
			return true;
		}
	}

	return false;
}

/**
 * Returns whether it is possible to show a hint for the current player, indicating which next move
 * would be best for him.
 *
 * When no game is being played, returns false.
 *
 * @return When showing a hint is possible true, otherwise false.
 */
bool GameController::isShowHintPossible() const
{
	if (this->hasGame())
	{
		// @todo Check whether it is a local game against the artificial intelligence.

		return true;
	}

	return false;
}

/**
 * Shows the new game dialog and then starts a new game.
 *
 * When the user aborts the new game dialog, no new game is started.
 */
void GameController::startGame()
{
	if (this->endGame())
	{
		// @todo Show new game dialog.

		// @todo Start new game.

		if (this->requestActivation())
		{
			this->game = GamePointerType(new ::Game::FourInALine::Game(6, 6, 1));
			this->firstPlayer = PlayerPointerType(new AbstractPlayer(this->tr("Player 1")));
			this->secondPlayer = PlayerPointerType(new AbstractPlayer(this->tr("Player 1")));

			emit this->stateChanged();
		}
	}
}

/**
 * Shows a confirmation dialog and if the user confirms, ends the current game.
 *
 * Does nothing if there is no game being played at the moment.
 *
 * @return When no game is being played/the game was ended true, otherwise false.
 */
bool GameController::endGame()
{
	if (!this->hasGame())
	{
		return true;
	}

	if (this->confirmEndGame())
	{
		this->destroyGame();

		return true;
	}

	return false;
}

/**
 * Shows a dialog for the user to select a savegame and then loads the savegame.
 *
 * If a game is currently being played, the user is asked whether the current game should be aborted.
 */
void GameController::loadGame()
{
	QString fileName;
	QString nameFilter = this->tr("Savegames (*.savegame)");

	if (FileIO::GetExistingFileName(this->getWidget(), fileName, nameFilter))
	{
		this->loadGameFromFile(fileName);
	}
}

/**
 * Saves the game to the remembered savegame or if there is none calls the save as method which
 * lets the user enter a filename.
 *
 * Does nothing if no game is being played.
 */
void GameController::saveGame()
{
	if (!this->hasGame())
	{
		if (this->savegameFileName.isEmpty())
		{
			this->saveGameAs();
		}
		else
		{
			this->saveGameToFile(this->savegameFileName);
		}
	}
}

/**
 * Opens a dialog for the user to enter a filename for the savegame and then saves the game into
 * the given file.
 *
 * The path is stored in the savegameFileName attribute, which is used by the normal save method, so
 * that the user does not have to select the file every time.
 *
 * Does nothing if no game is being played.
 */
void GameController::saveGameAs()
{
	QString fileName;
	QString defaultSuffix = "savegame";
	QString nameFilter = this->tr("Savegames (*.savegame)");

	if (this->hasGame() && FileIO::GetSaveFileName(this->getWidget(), fileName, defaultSuffix,
												   nameFilter))
	{
		if (this->saveGameToFile(fileName))
		{
			this->savegameFileName = fileName;

			emit this->stateChanged();
		}
	}
}

/**
 * Asks the user to specify a filename and then saves the replay of the current game to the file.
 *
 * Does nothing if no game is being played.
 */
void GameController::saveReplay()
{
	QString fileName;
	QString defaultSuffix = "replay";
	QString nameFilter = this->tr("Replays (*.replay)");

	if (this->hasGame() && FileIO::GetSaveFileName(this->getWidget(), fileName, defaultSuffix,
												   nameFilter))
	{
		this->saveReplayToFile(fileName);
	}
}

/**
 * Undoes the last move of the human player (works only when playing against the AI).
 *
 * @todo Make sure this does only work when playing against the artificial intelligence.
 */
void GameController::undoLastMove()
{
	if (this->isUndoPossible())
	{
		this->game->undoLastMove();
		this->game->undoLastMove();

		emit this->stateChanged();
	}
}

/**
 * Shows a hint for the player, which possible move would be best.
 *
 * @todo Make sure this does only work when playing against the artificial intelligence.
 */
void GameController::showHint()
{
	if (!this->isShowHintPossible())
	{
		// @todo Implement this.
	}
}

/**
 * Invoked by the controller manager when the controller is activated.
 *
 * getWidget() must return a valid widget after this method was called.
 *
 * Emits activated().
 */
void GameController::activate()
{
	emit this->activated();
}

/**
 * Invoked by the controller manager when the controller is deactivated.
 *
 * getWidget() is not required to return a valid widget after this method was called anymore.
 *
 * Emits deactivated().
 */
void GameController::deactivate()
{
	this->destroyGame();

	emit this->deactivated();
}

/**
 * Destroys the game that is currently being played/frees all game resources.
 */
void GameController::destroyGame()
{
	this->game.reset();

	emit this->stateChanged();
}

/**
 * Displays a dialog to confirm whether the user wants to end the current game.
 *
 * Does nothing and returns true when no game is being played.
 *
 * @return When the user wants to end the game or no game is running true, if the user declines
 *         false.
 */
bool GameController::confirmEndGame() const
{
	if (this->hasGame())
	{
		QMessageBox::StandardButton reply;

		reply = QMessageBox::question(this->getWidget(),
									  this->tr("End current game?"),
									  this->tr("Are you sure you want to end the current game?"),
									  QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

		if (reply == QMessageBox::No || reply == QMessageBox::Cancel)
		{
			return false;
		}
	}

	return true;
}

/**
 * Saves the current game to the file with the given path.
 *
 * Does nothing if no game is being played.
 *
 * @param path Path of the savegame file.
 * @return When the game was saved true, otherwise false.
 */
bool GameController::saveGameToFile(QString path)
{
	if (!this->hasGame())
	{
		return false;
	}

	// Save game to string.

	QString content = "savegame";

	// @todo Implement.

	// Write string to file.

	return FileIO::SetFileContent(this->getWidget(), path, content);
}

/**
 * Loads savegame with specified path.
 *
 * This method will request the controller to become active and won't load the savegame if the
 * request is declined.
 *
 * @param path Path to the savegame.
 * @return When the savegame was loaded true, otherwise false.
 */
bool GameController::loadGameFromFile(QString path)
{
	QString content;

	if (FileIO::GetFileContent(this->getWidget(), path, content) && this->requestActivation())
	{
		this->endGame();

		// Load savegame.

		// @todo Implement.

		this->game = GamePointerType(new ::Game::FourInALine::Game(6, 6, 1));
		this->game->makeMove(1);
		this->game->makeMove(2);
		this->game->makeMove(3);

		emit this->stateChanged();

		return true;
	}

	return false;
}

/**
 * Saves replay of the current game to the file under the given path.
 *
 * Does nothing if no game is being played.
 *
 * @param path Path to the replay file.
 * @return When the replay was saved true, otherwise false.
 */
bool GameController::saveReplayToFile(QString path)
{
	if (!this->hasGame())
	{
		return false;
	}

	// Save replay to string.

	QString content = "replay";

	// @todo Implement.

	// Write string to file.

	return FileIO::SetFileContent(this->getWidget(), path, content);
}

}
