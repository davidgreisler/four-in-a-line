#ifndef GUI_GAMECONTROLLER_HPP
#define GUI_GAMECONTROLLER_HPP

#include "AbstractController.hpp"

#include <QSharedPointer>

namespace Game
{
namespace FourInALine
{
class Game;
}
}

namespace GUI
{

class AbstractPlayer;

/**
 * The game controller manages the current game.
 *
 * The game controller manages the game that is currently being played. It provides slots/methods to
 * start a new game, save it, etc. and methods to retrieve information about the current game.
 *
 * To start a new game, call startGame(), it will display a new game dialog and then start a new
 * game. The game can be ended with endGame() which will display a confirmation dialog before
 * ending the game. The game can be saved with saveGame() or saveGameAs(), at which the latter saves
 * the game under a new path while the first remembers the savegame path that was used when the
 * game was loaded/saved the last time. Use loadGame() to open a dialog where the user can select a
 * savegame which is then loaded. The replay can be saved with saveReplay() which will also use
 * a dialog to specify a filename.
 *
 * The last move can be undone with undoLastMove() and showHint() can be used to display a hint
 * for the current player indicating which move would be best.
 *
 * When a game is started/ended/loaded/saved or anything else happens that changes the game state,
 * stateChanged() is emitted. The signal can be used to update actions, i.e. check whether they
 * should be enabled/disabled.
 */
class GameController : public AbstractController
{
		Q_OBJECT
	public:
		using GamePointerType = QSharedPointer< ::Game::FourInALine::Game>;
		using ConstGamePointerType = const QSharedPointer<const ::Game::FourInALine::Game>;
		using PlayerPointerType = QSharedPointer<AbstractPlayer>;
		using ConstPlayerPointerType = const QSharedPointer<const AbstractPlayer>;

		GameController(ControllerManager* manager);
		virtual ~GameController();

		virtual QWidget* getWidget() const;
		virtual bool confirmDeactivation();

		bool hasGame() const;
		ConstGamePointerType getGame() const;

		ConstPlayerPointerType getFirstPlayer() const;
		ConstPlayerPointerType getSecondPlayer() const;

		bool isUndoPossible() const;
		bool isShowHintPossible() const;

	signals:
		/**
		 * Emitted when the game state changed.
		 *
		 * This signal can be used to evaluate whether actions have to be disabled/enabled, etc.
		 */
		void stateChanged();

	public slots:
		void startGame();
		bool endGame();

		void loadGame();
		void saveGame();
		void saveGameAs();

		void saveReplay();

		void undoLastMove();

		void showHint();

	protected:
		virtual void activate();
		virtual void deactivate();

	private:
		Q_DISABLE_COPY(GameController)

		bool saveGameToFile(QString path);
		bool loadGameFromFile(QString path);
		bool saveReplayToFile(QString path);

		void destroyGame();
		bool confirmEndGame() const;

		/**
		 * The game widget.
		 */
		QWidget* widget;

		/**
		 * The current game.
		 */
		GamePointerType game;

		/**
		 * The first player.
		 */
		PlayerPointerType firstPlayer;

		/**
		 * The second player.
		 */
		PlayerPointerType secondPlayer;

		/**
		 * Path of the savegame of the current game or empty.
		 */
		QString savegameFileName;
};

}

#endif // GUI_GAMECONTROLLER_HPP
