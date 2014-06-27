#include "../Game/FourInALine/Game.hpp"

#include "Dialogs/LoadGame.hpp"
#include "Dialogs/NewGame.hpp"
#include "Dialogs/GameOver.hpp"

#include "GameController.hpp"
#include "AbstractPlayer.hpp"
#include "FileIO.hpp"
#include "Game.hpp"
#include "GameLogic.hpp"

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
	this->widget = new Widgets::Game(0);
	this->gameLogic = new GameLogic(this);

	this->connect(this->gameLogic, &GameLogic::gameStarted,
	              this->widget->getBoardWidget(), &Widgets::Board::startNewGame);

	this->connect(this->gameLogic, &GameLogic::gameOver,
	              this->widget->getBoardWidget(), &Widgets::Board::gameOver);
	this->connect(this->gameLogic, &GameLogic::gameOver,
	              this, &GameController::showGameOverDialog);

	this->connect(this->gameLogic, &GameLogic::gameNotOverAnymore,
	              this->widget->getBoardWidget(), &Widgets::Board::gameNotOverAnymore);

	this->connect(this->gameLogic, &GameLogic::gameEnded,
	              this->widget->getBoardWidget(), &Widgets::Board::endGame);

	this->connect(this->gameLogic, &GameLogic::remainingTimeChanged,
	              this->widget->getBoardWidget(), &Widgets::Board::updateTimeLimit);

	this->connect(this->gameLogic, &GameLogic::setCell,
	              this->widget->getBoardWidget(), &Widgets::Board::makeMove);

	this->connect(this->gameLogic, &GameLogic::removeCell,
	              this->widget->getBoardWidget(), &Widgets::Board::makeCellEmpty);

	this->connect(this->gameLogic, &GameLogic::startPlayerTurn,
	              this->widget->getBoardWidget(), &Widgets::Board::startPlayerTurn);

	this->connect(this->gameLogic, &GameLogic::endPlayerTurn,
	              this->widget->getBoardWidget(), &Widgets::Board::endPlayerTurn);

	this->connect(this->gameLogic, &GameLogic::showColumnHints,
	              this->widget->getBoardWidget(), &Widgets::Board::showColumnHints);
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
QSharedPointer<Game> GameController::getGame() const
{
	return this->game;
}

/**
 * Returns whether it is possible for the current player to undo a move.
 *
 * Returns false if no game is being played.
 *
 * @return When it is possible true, otherwise false.
 * @see ::GUI::Game::isUndoPossible()
 */
bool GameController::isUndoPossible() const
{
	return this->hasGame() && this->game->isUndoPossible();
}

/**
 * Returns whether it is possible for the current player to show a hint.
 *
 * Returns false if no game is being played.
 *
 * @return When it is possible true, otherwise false.
 * @see ::GUI::Game::isShowHintPossible()
 */
bool GameController::isShowHintPossible() const
{
	return this->hasGame() && this->game->isShowHintPossible();
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
 * Shows the new game dialog and then starts a new game.
 *
 * When the user aborts the new game dialog, no new game is started.
 */
void GameController::newGame()
{
	if (this->confirmEndGame())
	{
		this->showNewGameDialog();
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
 * Starts the same game again from the beginning.
 *
 * If a game is currently being played, the user is asked whether the current game should be aborted.
 */
void GameController::playAgain()
{
	if (this->confirmEndGame())
	{
		PlayerFactory playerFactory(this->widget->getBoardWidget());
		auto firstPlayer = playerFactory.createCopy(this->game->getFirstPlayer());
		auto secondPlayer = playerFactory.createCopy(this->game->getSecondPlayer());

		QSharedPointer<Game> newGame = Game::CreateWithSettingsFrom(this->game, firstPlayer, secondPlayer);

		this->startGame(newGame);
	}
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

	if (!this->confirmEndGame())
	{
		return;
	}

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
	if (this->hasGame())
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
	if (this->hasGame() && this->game->isUndoPossible())
	{
		this->gameLogic->undoLastMove();

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
	if (this->hasGame() && this->game->isShowHintPossible())
	{
		this->gameLogic->showHint();
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

void GameController::showGameOverDialog()
{
	QString playerName;
	Dialogs::GameOver::Result result;
	int availableActions = static_cast<int>(Dialogs::GameOver::Action::NEW_GAME);
	availableActions |= static_cast<int>(Dialogs::GameOver::Action::PLAY_AGAIN);
	availableActions |= static_cast<int>(Dialogs::GameOver::Action::SAVE_REPLAY);

	if (this->game->isArtificialIntelligenceGame())
	{
		availableActions |= static_cast<int>(Dialogs::GameOver::Action::UNDO_LAST_MOVE);
	}

	if (this->game->getGameEngine()->isDraw())
	{
		if (this->game->getGameEngine()->isTimeout())
		{
			result = Dialogs::GameOver::Result::DRAW_TIMEOUT;
			playerName = this->game->getTimedOutPlayer()->getName();
		}
		else
		{
			result = Dialogs::GameOver::Result::DRAW_BOARD_FULL;
		}
	}
	else
	{
		result = Dialogs::GameOver::Result::PLAYER_WON;
		playerName = this->game->getWinningPlayer()->getName();
	}

	Dialogs::GameOver dialog(availableActions, result, playerName, this->getWidget());

	this->connect(&dialog, &Dialogs::GameOver::newGame, this, &GameController::newGame);
	this->connect(&dialog, &Dialogs::GameOver::playAgain, this, &GameController::playAgain);
	this->connect(&dialog, &Dialogs::GameOver::saveReplay, this, &GameController::saveReplay);
	this->connect(&dialog, &Dialogs::GameOver::undoLastMove, this, &GameController::undoLastMove);
	this->connect(&dialog, &Dialogs::GameOver::undoLastMove, &dialog, &Dialogs::GameOver::accept);

	// When a new game is started/play again invoked, close the game over dialog.

	this->connect(this, &GameController::stateChanged, &dialog, &Dialogs::GameOver::accept);

	dialog.exec();
}

/**
 * Ends the current game and starts the given game.
 *
 * @param game The game to start.
 */
void GameController::startGame(QSharedPointer<Game> game)
{
	this->destroyGame();

	this->game = game;
	this->gameLogic->startGame(this->game);
	this->widget->setChatWidgetVisible(this->game->isNetworkGame());

	emit this->stateChanged();
}

/**
 * Shows the new game dialog and starts a new game if the user wants that.
 *
 * The current game is ended when a new game is started, the user is not asked for confirmation.
 *
 * @return When a new game was started true, otherwise false.
 */
bool GameController::showNewGameDialog()
{
	Dialogs::NewGame dialog(this->getWidget());
	dialog.exec();

	if (dialog.result() == QDialog::Accepted && this->requestActivation())
	{
		PlayerFactory playerFactory(this->widget->getBoardWidget());
		auto game = dialog.createGame(playerFactory);

		this->startGame(game);

		return true;
	}

	return false;
}

/**
 * Destroys the game that is currently being played/frees all game resources.
 */
void GameController::destroyGame()
{
	if (this->hasGame())
	{
		this->gameLogic->endGame();
		this->game.reset();

		emit this->stateChanged();
	}
}

/**
 * Displays a dialog to confirm whether the user wants to end the current game.
 *
 * Does nothing and returns true when no game is being played or the current game is already over.
 *
 * @return When the user wants to end the game or no game is running true, if the user declines
 *         false.
 */
bool GameController::confirmEndGame() const
{
	if (this->hasGame() && !this->getGame()->getGameEngine()->isOver())
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

	QString content = this->game->toString();

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

		auto game = Game::CreateFromString(content);

		Dialogs::LoadGame dialog(game, this->getWidget());
		dialog.exec();

		if (dialog.result() == QDialog::Accepted)
		{
			PlayerFactory playerFactory(this->widget->getBoardWidget());
			dialog.replacePlayers(playerFactory);

			this->startGame(game);

			return true;
		}
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
