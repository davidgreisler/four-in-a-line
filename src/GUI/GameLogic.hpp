#ifndef GUI_GAMELOGIC_HPP
#define GUI_GAMELOGIC_HPP

#include "../Game/FourInALine/Game.hpp"
#include "AbstractPlayer.hpp"

#include <QObject>
#include <QSharedPointer>

#include <vector>

class QTimer;

namespace GUI
{

class Game;

/**
 * Controls the gameplay.
 *
 * Provides methods to start/end a game and then manages the gameplay. This class requests the
 * next move from players when it is their turn and also checks whether the time limit is exceeded.
 * When the game state changes, it emits signals to inform listeners about the changes.
 *
 * Use startGame() to start a new game and endGame() to end it.
 */
class GameLogic : public QObject
{
		Q_OBJECT
	public:
		explicit GameLogic(QObject *parent = 0);
		virtual ~GameLogic();

		void startGame(QSharedPointer< ::GUI::Game> game);
		void endGame();

	signals:
		/**
		 * Emitted when a new game is started.
		 */
		void gameStarted(unsigned int nColumns, unsigned int nRows,
						 QSharedPointer<const ::GUI::AbstractPlayer> firstPlayer,
						 QSharedPointer<const ::GUI::AbstractPlayer> secondPlayer);

		/**
		 * Emitted when a game is over.
		 */
		void gameOver();

		/**
		 * Emitted when a game that was previously over is not over anymore.
		 *
		 * This happens when a move is undone.
		 */
		void gameNotOverAnymore();

		/**
		 * Emitted when a game has ended.
		 *
		 * A game ends when it is destroyed.
		 */
		void gameEnded();

		/**
		 * Emitted once per second to inform listeners about the remaining time the player has to
		 * make a move.
		 *
		 * @param timeLimit The total time limit in seconds.
		 * @param remainingSeconds Remaining time in seconds.
		 */
		void remainingTimeChanged(unsigned int timeLimit, unsigned int remainingSeconds);

		/**
		 * Emitted when a cell should change it's content (a token was dropped in it).
		 *
		 * @param x X position of the cell.
		 * @param y Y position of the cell.
		 * @param player The player who made the move.
		 */
		void setCell(unsigned int x, unsigned int y,
					 QSharedPointer<const ::GUI::AbstractPlayer> player);

		/**
		 * Emitted when a cell should be made empty (undo move).
		 *
		 * @param x X position of the cell.
		 * @param y Y position of the cell.
		 */
		void removeCell(unsigned int x, unsigned int y);

		/**
		 * Emitted when a player's turn begins.
		 *
		 * @param player The current player.
		 */
		void startPlayerTurn(QSharedPointer<const ::GUI::AbstractPlayer> player);

		/**
		 * Emitted when the turn of the current player ends.
		 */
		void endPlayerTurn();

		/**
		 * Emitted when hints should be shown for the columns of the board.
		 *
		 * Higher scores are better than lower scores for the current player. Negative scores are
		 * possible.
		 *
		 * @param columnScores Vector containing scores for each column.
		 */
		void showColumnHints(std::vector<int> columnScores);

	public slots:
		void undoLastMove();
		void showHint();

	private slots:
		void makeMove(unsigned int x);
		void updateRemainingTime();

	private:
		bool checkGameOver();
		void abortRequest();
		void requestNextMove();

		/**
		 * The game.
		 */
		QSharedPointer<Game> game;

		/**
		 * Timer for the time limit.
		 */
		QTimer* timeLimitTimer;

		/**
		 * How many seconds the current player has left to make a move.
		 */
		unsigned int remainingSeconds;

		/**
		 * Whether there is a move requested from a player.
		 */
		bool moveRequested;
};

}

#endif // GUI_GAMELOGIC_HPP
