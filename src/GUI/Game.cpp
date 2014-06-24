#include "Game.hpp"
#include "ArtificialIntelligencePlayer.hpp"
#include "PlaceholderPlayer.hpp"
#include "NetworkPlayer.hpp"
#include "../Game/FourInALine/Game.hpp"

#include <stdexcept>

namespace GUI
{

/**
 * Creates a new game.
 *
 * @param game Game engine.
 * @param firstPlayer The first player.
 * @param secondPlayer The second player.
 */
Game::Game(GameEnginePointerType game, PlayerPointerType firstPlayer, PlayerPointerType secondPlayer)
	: game(game), firstPlayer(firstPlayer), secondPlayer(secondPlayer)
{

}

/**
 * Frees all used resources.
 */
Game::~Game()
{

}

/**
 * Returns the player who makes/made the first move.
 *
 * @return The player who makes/made the first move.
 */
Game::ConstPlayerPointerType Game::getStartingPlayer() const
{
	return this->playerIdToPlayer(this->game->getPlayerWhoMakesFirstMove());
}

/**
 * Returns the current player.
 *
 * @return Current player.
 */
Game::PlayerPointerType Game::getCurrentPlayer()
{
	return this->playerIdToPlayer(this->game->getCurrentPlayer());
}

/**
 * Returns the current player.
 *
 * @return Current player.
 */
Game::ConstPlayerPointerType Game::getCurrentPlayer() const
{
	return this->playerIdToPlayer(this->game->getCurrentPlayer());
}

/**
 * Returns the player who won the game.
 *
 * Do not call this method when the game is not over yet.
 *
 * @return The player who won the game.
 * @see ::Game::FourInALine::Game::getWinner() Used to determine the winner.
 */
Game::ConstPlayerPointerType Game::getWinningPlayer() const
{
	return this->playerIdToPlayer(this->game->getWinner());
}

/**
 * Returns the player who timed out.
 *
 * Do not call this method when no player timed out.
 *
 * @return The player who timed out.
 */
Game::ConstPlayerPointerType Game::getTimedOutPlayer() const
{
	return this->playerIdToPlayer(this->game->getPlayerWhoTimedOut());
}

/**
 * Replaces the players with the given ones.
 *
 * This only works when the current players are placeholder players.
 *
 * @param firstPlayer New first player.
 * @param secondPlayer New second player.
 */
void Game::replacePlayers(Game::PlayerPointerType firstPlayer, Game::PlayerPointerType secondPlayer)
{
	if (!this->hasPlaceholderPlayers())
	{
		throw std::runtime_error("Replacing players is only possible when the current players are"
								 " placeholders.");
	}

	this->firstPlayer = firstPlayer;
	this->secondPlayer = secondPlayer;
}

/**
 * Returns whether the players of this game are placeholders or not.
 *
 * @return When they are placeholders true, otherwise false.
 */
bool Game::hasPlaceholderPlayers() const
{
	bool firstPlayerIsPlaceholder =
			(nullptr != dynamic_cast<PlaceholderPlayer*>(this->firstPlayer.data()));
	bool secondPlayerIsPlaceholder =
			(nullptr != dynamic_cast<PlaceholderPlayer*>(this->secondPlayer.data()));

	return firstPlayerIsPlaceholder && secondPlayerIsPlaceholder;
}

/**
 * Returns the first player of the game.
 *
 * @return First player.
 */
Game::PlayerPointerType Game::getFirstPlayer()
{
	return this->firstPlayer;
}

/**
 * Returns the first player of the game.
 *
 * @return The first player.
 */
Game::ConstPlayerPointerType Game::getFirstPlayer() const
{
	return this->firstPlayer;
}

/**
 * Returns the second player of the game.
 *
 * @return The second player.
 */
Game::ConstPlayerPointerType Game::getSecondPlayer() const
{
	return this->secondPlayer;
}

/**
 * Returns whether one of the players is an artificial intelligence or not.
 *
 * @return When at least one player is an artificial intelligence true, otherwise false.
 */
bool Game::isArtificialIntelligenceGame() const
{
	bool firstPlayerIsAI =
			(nullptr != dynamic_cast<ArtificialIntelligencePlayer*>(this->firstPlayer.data()));
	bool secondPlayerIsAI =
			(nullptr != dynamic_cast<ArtificialIntelligencePlayer*>(this->secondPlayer.data()));

	return firstPlayerIsAI || secondPlayerIsAI;
}

/**
 * Returns whether one of the players is a network player or not.
 *
 * @return When at least one player is a network player true, otherwise false.
 */
bool Game::isNetworkGame() const
{
	bool firstPlayerIsNetwork =
			(nullptr != dynamic_cast<NetworkPlayer*>(this->firstPlayer.data()));
	bool secondPlayerIsNetwork =
			(nullptr != dynamic_cast<NetworkPlayer*>(this->secondPlayer.data()));

	return firstPlayerIsNetwork || secondPlayerIsNetwork;
}

/**
 * Returns whether undoing the last move is possible for the current player.
 *
 * Returns false when the undo function has been disabled in this game.
 *
 * @return When it is possible to undo the last move true, otherwise false.
 */
bool Game::isUndoPossible() const
{
	// At least 2 moves are required, one by the current player and one by the other player.

	if (this->isUndoAllowed() && this->game->getNumberOfMoves() >= 2)
	{
			return true;
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
bool Game::isShowHintPossible() const
{
	if (this->isHintAllowed() && !this->game->isOver())
	{
		return true;
	}

	return false;
}

/**
 * Sets whether the game's result will be stored in the highscore list.
 *
 * @param saveHighscore To save it true, otherwise false.
 */
void Game::setSaveHighscore(bool saveHighscore)
{
	if (saveHighscore && this->isArtificialIntelligenceGame())
	{
		throw std::runtime_error("Games against AI are not saved in the highscore list.");
	}

	this->saveHighscore = saveHighscore;
}

/**
 * Returns whether the game's result will be stored in the highscore list.
 *
 * @return When it is saved in the highscore list true, otherwise false.
 */
bool Game::isSavingHighscore() const
{
	return this->saveHighscore;
}

/**
 * Sets whether the undo function is allowed in this game.
 *
 * @param allow To allow it true, to disallow it false.
 */
void Game::setAllowUndo(bool allow)
{
	if (allow && !this->isArtificialIntelligenceGame())
	{
		throw std::runtime_error("Undo function can only be allowed in AI games.");
	}

	this->allowUndo = allow;
}

/**
 * Returns whether the undo function is allowed in this game.
 *
 * @return When it is allowed true, otherwise false.
 */
bool Game::isUndoAllowed() const
{
	return this->allowUndo;
}

/**
 * Sets whether the hint function is allowed in this game.
 *
 * @param allow To allow it true, otherwise false.
 */
void Game::setAllowHint(bool allow)
{
	if (allow && !this->isArtificialIntelligenceGame())
	{
		throw std::runtime_error("Hint function can only be allowed in AI games.");
	}

	this->allowHint = allow;
}

/**
 * Returns whether the hint function is allowed in this game.
 *
 * The hint function can only be enabled in games against an artificial intelligence.
 *
 * @return When it is allowed true, otherwise false.
 */
bool Game::isHintAllowed() const
{
	return this->allowHint;
}

/**
 * Returns the game engine.
 *
 * @return Game engine.
 */
Game::GameEnginePointerType Game::getGameEngine() const
{
	return this->game;
}

/**
 * Builds and returns a string representing the current game state (savegame).
 *
 * @return String representing game state (savegame).
 */
QString Game::toString() const
{
	QString result;

	// @todo Implement this.

	result = "savegame";

	return result;
}

/**
 * Creates a new game from the given string.
 *
 * @param savegame String representing game state (savegame).
 * @return Game in the state it was in when the savegame was created.
 */
QSharedPointer<Game> Game::CreateFromString(const QString& savegame)
{
	Q_UNUSED(savegame);

	// @todo Implement this.

	QSharedPointer< ::Game::FourInALine::Game> gameEngine(new ::Game::FourInALine::Game(5, 5, 1));
	QSharedPointer<PlaceholderPlayer> firstPlayer(new PlaceholderPlayer(::Game::FourInALine::Game::PLAYER_ONE,
																		"Player 1"));
	QSharedPointer<PlaceholderPlayer> secondPlayer(new PlaceholderPlayer(::Game::FourInALine::Game::PLAYER_TWO,
																		 "Player 2"));

	QSharedPointer<Game> newGame = QSharedPointer<Game>(new Game(gameEngine, firstPlayer,
																 secondPlayer));

	return newGame;
}

/**
 * Creates a new game with the same settings as the given game but with the two given players.
 *
 * @param game Game to copy settings from.
 * @param firstPlayer First player of the new game.
 * @param secondPlayer Second player of the new game.
 * @return New game with the given players and the settings from the given game.
 */
QSharedPointer<Game> Game::CreateWithSettingsFrom(QSharedPointer<const Game> game,
												  PlayerPointerType firstPlayer,
												  PlayerPointerType secondPlayer)
{
	using GameEngine = ::Game::FourInALine::Game;

	auto nRows = game->getGameEngine()->getBoard()->getNumberOfRows();
	auto nColumns = game->getGameEngine()->getBoard()->getNumberOfColumns();
	auto firstMovePlayerId = game->getGameEngine()->getPlayerWhoMakesFirstMove();

	auto gameEngine = QSharedPointer<GameEngine>::create(nRows, nColumns, firstMovePlayerId);
	gameEngine->setTimeLimit(game->getGameEngine()->getTimeLimit());
	gameEngine->setTimeoutAction(game->getGameEngine()->getTimeoutAction());

	auto newGame = QSharedPointer<Game>::create(gameEngine, firstPlayer, secondPlayer);

	newGame->setAllowUndo(game->isUndoAllowed());
	newGame->setAllowHint(game->isHintAllowed());
	newGame->setSaveHighscore(game->isSavingHighscore());

	return newGame;
}

/**
 * Returns the player object matching the given player id.
 *
 * @param playerId Player id.
 * @return Player object.
 */
Game::PlayerPointerType Game::playerIdToPlayer(::Game::FourInALine::Game::PlayerType playerId) const
{
	if (playerId == ::Game::FourInALine::Game::PLAYER_ONE)
	{
		return this->firstPlayer;
	}
	else
	{
		return this->secondPlayer;
	}
}

}
