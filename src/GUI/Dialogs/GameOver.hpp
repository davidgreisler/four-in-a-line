#ifndef GUI_DIALOGS_GAMEOVER_HPP
#define GUI_DIALOGS_GAMEOVER_HPP

#include "../../Game/Game.hpp"

#include <QDialog>
#include <QSharedPointer>

class QDialogButtonBox;
class QPushButton;
class QLabel;
class QVBoxLayout;

namespace GUI
{
namespace Dialogs
{

/**
 * Game over dialog.
 *
 * This dialog is shown when a game is over. The game over dialog knows 3 game results:
 * * Player won: A player won the game.
 * * Draw, timeout: A player timed out, the game is a draw.
 * * Draw, board full: The board is full, the game is a draw.
 *
 * It is also possible to configure the actions available to the user, possible actions are:
 * PLAY_AGAIN, NEW_GAME, SAVE_REPLAY and UNDO_LAST_MOVE.
 *
 * When the user clicks on one of the action buttons, a signal is emitted accordingly. The dialog
 * has to be closed manually when a new game is started/the user wants to play again with a call
 * to accept().
 */
class GameOver : public QDialog
{
		Q_OBJECT
	public:
		/**
		 * Actions that can be offered by this dialog.
		 */
		enum class Action : int
		{
			PLAY_AGAIN     =  2,   ///< Play another game with the same settings.
			NEW_GAME       =  4,   ///< Play a new game.
			SAVE_REPLAY    =  8,   ///< Save the replay of the game.
			UNDO_LAST_MOVE = 16,   ///< Undo the last 2 moves.
		};

		/**
		 * The result of the game.
		 */
		enum class Result
		{
			PLAYER_WON,
			DRAW_TIMEOUT,
			DRAW_BOARD_FULL
		};

		explicit GameOver(int availableActions, Result result, QString playerName, QWidget* parent = 0);
		virtual ~GameOver();

	signals:
		/**
		 * Emitted when the user clicks on the save replay button.
		 */
		void saveReplay();

		/**
		 * Emitted when the user wants to play the game again from the beginning.
		 */
		void playAgain();

		/**
		 * Emitted when the user wants to play a new game.
		 */
		void newGame();

		/**
		 * Emitted when the user wants to undo the last move.
		 */
		void undoLastMove();

	private:
		Q_DISABLE_COPY(GameOver)

		void changeEvent(QEvent* event);
		void retranslateUI();

		/**
		 * Game result.
		 */
		Result result;

		/**
		 * The name of the player who won the game or who timed out.
		 *
		 * Empty when the game is a draw because the board is full.
		 */
		QString playerName;

		/**
		 * Vertical layout.
		 */
		QVBoxLayout* layout;

		/**
		 * Button box containing the dialog buttons.
		 */
		QDialogButtonBox* buttonBox;

		/**
		 * Button for undoing the last move.
		 */
		QPushButton* undoLastMoveButton;

		/**
		 * Button for saving the replay.
		 */
		QPushButton* saveReplayButton;

		/**
		 * Button for playing another game with the same settings.
		 */
		QPushButton* playAgainButton;

		/**
		 * Button for starting a new game.
		 */
		QPushButton* newGameButton;

		/**
		 * Button for closing the dialog.
		 */
		QPushButton* acceptButton;

		/**
		 * Game over text label.
		 */
		QLabel* textLabel;
};

}
}

#endif // GUI_DIALOGS_GAMEOVER_HPP
