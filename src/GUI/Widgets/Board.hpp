#ifndef GUI_WIDGETS_BOARD_HPP
#define GUI_WIDGETS_BOARD_HPP

#include "../../Game/Players/Human.hpp"
#include "../../Game/Players/AbstractPlayer.hpp"

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
		                  QSharedPointer<const ::Game::Players::AbstractPlayer> firstPlayer,
		                  QSharedPointer<const ::Game::Players::AbstractPlayer> secondPlayer);
		void gameOver();
		void gameNotOverAnymore();
		void endGame();

		void startPlayerTurn(QSharedPointer<const ::Game::Players::AbstractPlayer> player);
		void updateTimeLimit(unsigned int timeLimit, unsigned int remainingTime);
		void endPlayerTurn();

		void makeMove(unsigned int x, unsigned int y, QSharedPointer<const ::Game::Players::AbstractPlayer>);
		void makeCellEmpty(unsigned int x, unsigned int y);

		void requestMove(std::vector<unsigned int> availableColumns,
		                 ::Game::Players::Human::Controls controls);
		void abortRequestMove();

		void showColumnHints(std::vector<int> columnScores);

	private:
		Q_DISABLE_COPY(Board)

};

}
}

#endif // GUI_WIDGETS_BOARD_HPP
