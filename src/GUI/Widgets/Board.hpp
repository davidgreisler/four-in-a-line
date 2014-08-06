#ifndef GUI_WIDGETS_BOARD_HPP
#define GUI_WIDGETS_BOARD_HPP

#include "../../Game/Players/Human.hpp"
#include "../../Game/Players/AbstractPlayer.hpp"

#include <QVariantList>
#include <QWidget>
#include <QSharedPointer>
#include <QQmlContext>

class QQuickWidget;
class QVBoxLayout;

namespace GUI
{
namespace Widgets
{

/**
 * Widget showing the game board and allowing the user to make moves/drop tokens.
 *
 * @todo The structure of the game code is unneccessarily complicated because it must not use Qt (requirement)
 *       which makes it very hard to write a nice GUI for the game. Many "cool" features can't be
 *       implemented or are very hard to implement. If the QML code could easily access the
 *       Game/Board/Player objects and listen to their signals it would be much easier.
 */
class Board : public QWidget
{
		Q_OBJECT
	public:
		explicit Board(QString theme, QWidget *parent = 0);
		virtual ~Board();

		void setTheme(QString theme);

	signals:
		/**
		 * Emitted when the human player made a move.
		 *
		 * @param columnNo Column number.
		 */
		void moveReady(unsigned int columnNo);

		/**
		 * Emitted when a new game was started.
		 *
		 * @param nColumns Number of columns in the board.
		 * @param nRows Number of rows in the board.
		 * @param firstPlayerName Name of the first player.
		 * @param secondPlayerName Name of the second player.
		 * @param hasTimeLimit Whether the game has a time limit or not.
		 */
		void newGameStarted(unsigned int nColumns, unsigned int nRows,
		                    QString firstPlayerName, QString secondPlayerName, bool hasTimeLimit);

		/**
		 * Emitted when the game has ended (is closed).
		 */
		void gameEnded();

		/**
		 * Emitted when the game is over.
		 */
		void gameIsOver();

		/**
		 * Emitted when the game is not over anymore (undo).
		 */
		void gameIsNotOverAnymore();

		/**
		 * Emitted when it's the first player's turn.
		 */
		void firstPlayerTurn();

		/**
		 * Emitted when it's the second player's turn.
		 */
		void secondPlayerTurn();

		/**
		 * Emitted when a player's turn has ended.
		 */
		void playerTurnEnded();

		/**
		 * Emitted when a move is requested.
		 *
		 * @param availableColumns Available columns as list of column numbers.
		 * @param allowKeyboard Whether the user can use the keyboard.
		 * @param allowMouse Whether the user can use the mouse.
		 */
		void moveRequested(QVariantList availableColumns, bool allowKeyboard, bool allowMouse);

		/**
		 * Emitted when a move request is aborted.
		 */
		void moveRequestAborted();

		/**
		 * Emitted when a token is dropped.
		 *
		 * @param x X coordinate.
		 * @param y Y coordinate.
		 * @param playerId Player id (1 or 2).
		 */
		void tokenDropped(unsigned int x, unsigned int y, unsigned int playerId);

		/**
		 * Emitted when a token is removed from the board.
		 *
		 * @param x X coordinate of the token to remove.
		 * @param y Y coordinate of the token to remove.
		 */
		void tokenRemoved(unsigned int x, unsigned int y);

		/**
		 * Emitted when the remaining time is updated.
		 *
		 * @param totalMinutes Total time (minutes part)
		 * @param totalSeconds Total time (seconds part)
		 * @param remainingMinutes Remaining minutes.
		 * @param remainingSeconds Remaining seconds.
		 */
		void remainingTimeUpdated(unsigned int totalMinutes, unsigned int totalSeconds,
		                          unsigned int remainingMinutes, unsigned int remainingSeconds);

		/**
		 * Emitted when a cell should be highlighted or not highlighted anymore.
		 *
		 * This is used to highlight the winning cells when the game is over.
		 *
		 * @param x X coordinate of the cell.
		 * @param y Y coordinate of the cell.
		 * @param highlight Whether the cell should be highlighted (true) or not (false).
		 */
		void cellHighlightedChanged(unsigned int x, unsigned int y, bool highlight);

		/**
		 * Emitted when column scores should be shown as hint for the user.
		 *
		 * @param columnScores List of scores, a score from -100 to +100 for every column.
		 */
		void columnHintsShown(QVariantList columnScores);

	public slots:
		void startNewGame(unsigned int nColumns, unsigned int nRows,
		                  QSharedPointer<const ::Game::Players::AbstractPlayer> firstPlayer,
		                  QSharedPointer<const ::Game::Players::AbstractPlayer> secondPlayer,
		                  bool hasTimeLimit);
		void gameOver();
		void gameNotOverAnymore();
		void endGame();

		void startPlayerTurn(QSharedPointer<const ::Game::Players::AbstractPlayer> player);
		void updateTimeLimit(unsigned int timeLimit, unsigned int remainingTime);
		void endPlayerTurn();

		void makeMove(unsigned int x, unsigned int y, QSharedPointer<const ::Game::Players::AbstractPlayer> player);
		void makeCellEmpty(unsigned int x, unsigned int y);

		void requestMove(std::vector<unsigned int> availableColumns, ::Game::Players::Human* player);
		void abortRequestMove();

		void showColumnHints(std::vector<int> columnScores);
		void setCellHighlighted(unsigned int x, unsigned int y, bool highlight);

	private slots:
		void playerMadeMove(int columnNo);

	private:
		Q_DISABLE_COPY(Board)

		void initializeQML();

		/**
		 * Layout for the quick widget.
		 */
		QVBoxLayout* layout;

		/**
		 * Quick widget for displaying the game board/player information.
		 */
		QQuickWidget* quickWidget;

		/**
		 * The first player (if a game is running).
		 */
		QSharedPointer<const ::Game::Players::AbstractPlayer> firstPlayer;

		/**
		 * The second player (if a game is running).
		 */
		QSharedPointer<const ::Game::Players::AbstractPlayer> secondPlayer;

		/**
		 * The player who makes the move (when a move is requested).
		 */
		::Game::Players::Human* movePlayer;

		/**
		 * Current theme name.
		 */
		QString theme;

		/**
		 * Whether the QML should be reloaded when a new game is started.
		 */
		bool reloadQML;
};

}
}

#endif // GUI_WIDGETS_BOARD_HPP
