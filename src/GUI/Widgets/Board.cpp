#include "Board.hpp"

#include <QPalette>
#include <QDebug>

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
                         QSharedPointer<const ::Game::Players::AbstractPlayer> firstPlayer,
                         QSharedPointer<const ::Game::Players::AbstractPlayer> secondPlayer)
{
	Q_UNUSED(nColumns);
	Q_UNUSED(nRows);
	Q_UNUSED(firstPlayer);
	Q_UNUSED(secondPlayer);

	qDebug() << "[" << this << "::startNewGame ] New game started with" << nColumns << "columns and"
	         << nRows << "rows.";
	qDebug() << "[" << this << "::startNewGame ] First player:" << firstPlayer->getName();
	qDebug() << "[" << this << "::startNewGame ] Second player:" << secondPlayer->getName();
}

/**
 * @todo Implement.
 */
void Board::gameOver()
{
	qDebug() << "[" << this << "::gameOver ] Game is over.";
}

/**
 * @todo Implement.
 */
void Board::gameNotOverAnymore()
{
	qDebug() << "[" << this << "::gameNotOverAnymore ] Game is not over anymore.";
}

/**
 * @todo Implement.
 */
void Board::endGame()
{
	qDebug() << "[" << this << "::endGame ] Game ended.";
}

/**
 * @todo Implement.
 */
void Board::startPlayerTurn(QSharedPointer<const ::Game::Players::AbstractPlayer> player)
{
	Q_UNUSED(player);

	qDebug() << "[" << this << "::startPlayerTurn ] Start player turn:" << player->getName();
}

/**
 * @todo Implement.
 */
void Board::updateTimeLimit(unsigned int timeLimit, unsigned int remainingTime)
{
	Q_UNUSED(timeLimit);
	Q_UNUSED(remainingTime);

	qDebug() << "[" << this << "::updateTimeLimit ] Time remaining:" << remainingTime;
}

/**
 * @todo Implement.
 */
void Board::endPlayerTurn()
{
	qDebug() << "[" << this << "::endPlayerTurn ] End player turn.";
}

/**
 * @todo Implement.
 */
void Board::makeMove(unsigned int x, unsigned int y, QSharedPointer<const ::Game::Players::AbstractPlayer> player)
{
	Q_UNUSED(player);
	Q_UNUSED(x);
	Q_UNUSED(y);

	qDebug() << "[" << this << "::makeMove ] Player " << player->getName()
	         << "dropped token in" << x;
}

/**
 * @todo Implement.
 */
void Board::makeCellEmpty(unsigned int x, unsigned int y)
{
	qDebug() << "[" << this << "::makeCellEmpty ] Make cell empty, x:" << x << "y:" << y;
}

/**
 * @todo Implement.
 */
void Board::requestMove(std::vector<unsigned int> availableColumns, ::Game::Players::Human::Controls controls)
{
	Q_UNUSED(availableColumns);
	Q_UNUSED(controls);

	qDebug() << "[" << this << "::requestMove ] Move requested.";
}

/**
 * @todo Implement.
 */
void Board::abortRequestMove()
{
	qDebug() << "[" << this << "::abortRequestMove ] Move request aborted.";
}

/**
 * @todo Implement.
 */
void Board::showColumnHints(std::vector<int> columnScores)
{
	Q_UNUSED(columnScores);

	qDebug() << "[" << this << "::showColumnHints ] Showing column hints.";
}

}
}
