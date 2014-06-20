#ifndef GUI_WIDGETS_BOARD_HPP
#define GUI_WIDGETS_BOARD_HPP

#include "../HumanPlayer.hpp"

#include <QWidget>

namespace GUI
{
namespace Widgets
{

/**
 * Widget showing the game board and allowing the user to make moves/drop tokens.
 *
 * @todo Implement.
 */
class Board : public QWidget
{
		Q_OBJECT
	public:
		explicit Board(QWidget *parent = 0);
		virtual ~Board();

	signals:

	public slots:
		void startNewGame(unsigned int nColumns, unsigned int nRows,
						  const ::GUI::AbstractPlayer* firstPlayer,
						  const ::GUI::AbstractPlayer* secondPlayer);
		void gameOver();
		void endGame();

		void startPlayerTurn(const ::GUI::AbstractPlayer* player);
		void updateTimeLimit(unsigned int timeLimit, unsigned int remainingTime);
		void endPlayerTurn();

		void makeMove(const ::GUI::AbstractPlayer*, unsigned int x);
		void undoLastMove();

		void requestMove(std::vector<unsigned int> availableColumns,
						 ::GUI::HumanPlayer::Controls controls);
		void abortRequestMove();

		void showColumnHints(std::vector<int> columnScores);

	private:
		Q_DISABLE_COPY(Board)

};

}
}

#endif // GUI_WIDGETS_BOARD_HPP
