#ifndef GUI_WIDGETS_BOARD_HPP
#define GUI_WIDGETS_BOARD_HPP

#include "../HumanPlayer.hpp"
#include "../AbstractPlayer.hpp"

#include <QWidget>
#include <QSharedPointer>

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
		                  QSharedPointer<const ::GUI::AbstractPlayer> firstPlayer,
		                  QSharedPointer<const ::GUI::AbstractPlayer> secondPlayer);
		void gameOver();
		void gameNotOverAnymore();
		void endGame();

		void startPlayerTurn(QSharedPointer<const ::GUI::AbstractPlayer> player);
		void updateTimeLimit(unsigned int timeLimit, unsigned int remainingTime);
		void endPlayerTurn();

		void makeMove(unsigned int x, unsigned int y, QSharedPointer<const ::GUI::AbstractPlayer>);
		void makeCellEmpty(unsigned int x, unsigned int y);

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
