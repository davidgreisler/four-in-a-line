#ifndef GUI_GAME_HPP
#define GUI_GAME_HPP

#include "../Game/FourInALine/Game.hpp"
#include "AbstractPlayer.hpp"

namespace GUI
{

/**
 * Connects the game engine with the player logic and provides helper methods for the GUI.
 *
 * The game engine just works with player ids, it isn't aware of the concept of remote players,
 * or that the players have names, etc. This class acts as a mediator between the GUI logic/player
 * logic and the game engine. It also contains some extensions to the game engine logic like
 * flags for allowing/disallowing undo/hints and saving the game result in the highscore table.
 *
 * The game engine can be retrieved with getGameEngine().
 *
 * The first/second players can be retrieved with getFirstPlayer() and getSecondPlayer(). Use
 * getStartingPlayer() to get the player who makes the first move and getCurrentPlayer() to get the
 * player who makes the next move.
 *
 * To check whether one of the players is an artificial intelligence or a remote player use
 * isArtificialIntelligenceGame() and isNetworkGame().
 *
 * Use isUndoPossible() or isShowHintPossible() to check whether it is possible to undo a move or
 * show a hint. These methods check whether it is allowed and whether it is possible while the
 * game engine only checks whether it would be possible.
 *
 * The undo/hint function can be (dis)allowed with setAllowUndo() and setAllowHint(), use
 * isUndoAllowed() and isHintAllowed() to check whether they are allowed.
 *
 * Whether the game result should be saved in the highscore table can be set with setSaveHighscore()
 * and queried with isSavingHighscore().
 */
class Game
{
	public:
		/**
		 * Shared pointer of a game engine.
		 */
		using GameEnginePointerType = QSharedPointer< ::Game::FourInALine::Game>;

		/**
		 * Shared pointer of a constant game engine.
		 */
		using ConstGameEnginePointerType = QSharedPointer<const ::Game::FourInALine::Game>;

		/**
		 * Shared pointer to an abstract player.
		 */
		using PlayerPointerType = QSharedPointer<AbstractPlayer>;

		/**
		 * Shared pointer to a constant abstract player.
		 */
		using ConstPlayerPointerType = QSharedPointer<const AbstractPlayer>;

		Game(GameEnginePointerType game, PlayerPointerType firstPlayer, PlayerPointerType secondPlayer);
		Game(const Game& orig) = delete;
		virtual ~Game();

		PlayerPointerType getFirstPlayer();
		ConstPlayerPointerType getFirstPlayer() const;

		ConstPlayerPointerType getSecondPlayer() const;

		ConstPlayerPointerType getStartingPlayer() const;

		PlayerPointerType getCurrentPlayer();
		ConstPlayerPointerType getCurrentPlayer() const;

		ConstPlayerPointerType getWinningPlayer() const;

		ConstPlayerPointerType getTimedOutPlayer() const;

		void replacePlayers(PlayerPointerType firstPlayer, PlayerPointerType secondPlayer);

		bool hasPlaceholderPlayers() const;
		bool isArtificialIntelligenceGame() const;
		bool isNetworkGame() const;

		void setSaveHighscore(bool saveHighscore);
		bool isSavingHighscore() const;

		bool isUndoPossible() const;
		void setAllowUndo(bool allow);
		bool isUndoAllowed() const;

		bool isShowHintPossible() const;
		void setAllowHint(bool allow);
		bool isHintAllowed() const;

		GameEnginePointerType getGameEngine() const;

		QString toString() const;
		static QSharedPointer<Game> CreateFromString(const QString& savegame);
		static QSharedPointer<Game> CreateWithSettingsFrom(QSharedPointer<const Game> game,
														   PlayerPointerType firstPlayer,
														   PlayerPointerType secondPlayer);

	private:
		PlayerPointerType playerIdToPlayer(::Game::FourInALine::Game::PlayerType playerId) const;

		/**
		 * The current game.
		 */
		GameEnginePointerType game;

		/**
		 * The first player.
		 */
		PlayerPointerType firstPlayer;

		/**
		 * The second player.
		 */
		PlayerPointerType secondPlayer;

		/**
		 * Whether the result of the game should be saved to the highscore list or not.
		 */
		bool saveHighscore;

		/**
		 * Whether the undo function is allowed or not.
		 *
		 * The undo function can only be allowed in games against an artificial intelligence.
		 */
		bool allowUndo;

		/**
		 * Whether the hint function is allowed or not.
		 *
		 * The hint function can only be allowed in games against an artificial intelligence.
		 */
		bool allowHint;
};

}

#endif // GUI_GAME_HPP
