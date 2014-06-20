#include "Board.hpp"

#include <QPalette>

namespace GUI
{
namespace Widgets
{

/**
 * Creates a new game board widget.
 *
 * @param parent Parent widget.
 */
Board::Board(QWidget *parent) :
    QWidget(parent)
{
	this->setAutoFillBackground(true);

	QPalette palette = this->palette();
	palette.setColor(this->backgroundRole(), Qt::red);
	this->setPalette(palette);
}

/**
 * Frees all used resources.
 */
Board::~Board()
{

}

/**
 * @todo Implement.
 */
void Board::startNewGame(unsigned int nColumns, unsigned int nRows,
						 const ::GUI::AbstractPlayer* firstPlayer,
						 const ::GUI::AbstractPlayer* secondPlayer)
{
	Q_UNUSED(nColumns);
	Q_UNUSED(nRows);
	Q_UNUSED(firstPlayer);
	Q_UNUSED(secondPlayer);
}

/**
 * @todo Implement.
 */
void Board::gameOver()
{

}

/**
 * @todo Implement.
 */
void Board::endGame()
{

}

/**
 * @todo Implement.
 */
void Board::startPlayerTurn(const AbstractPlayer* player)
{
	Q_UNUSED(player);
}

/**
 * @todo Implement.
 */
void Board::updateTimeLimit(unsigned int timeLimit, unsigned int remainingTime)
{
	Q_UNUSED(timeLimit);
	Q_UNUSED(remainingTime);
}

/**
 * @todo Implement.
 */
void Board::endPlayerTurn()
{

}

/**
 * @todo Implement.
 */
void Board::makeMove(const AbstractPlayer* player, unsigned int x)
{
	Q_UNUSED(player);
	Q_UNUSED(x);
}

/**
 * @todo Implement.
 */
void Board::undoLastMove()
{

}

/**
 * @todo Implement.
 */
void Board::requestMove(std::vector<unsigned int> availableColumns, HumanPlayer::Controls controls)
{
	Q_UNUSED(availableColumns);
	Q_UNUSED(controls);
}

/**
 * @todo Implement.
 */
void Board::abortRequestMove()
{

}

/**
 * @todo Implement.
 */
void Board::showColumnHints(std::vector<int> columnScores)
{
	Q_UNUSED(columnScores);
}

}
}
