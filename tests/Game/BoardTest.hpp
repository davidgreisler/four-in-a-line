#ifndef TESTS_GAME_BOARDTEST_HPP
#define TESTS_GAME_BOARDTEST_HPP

#include <QtTest/QTest>

/**
 * Unit tests for the Game::Board class.
 */
class BoardTest : public QObject
{
		Q_OBJECT

	private slots:
		void createAndCopyBoard();
		void fillWholeBoard();
		void swapCells();
		void accessOutOfRange();
		void checkRowsAndColumns();
		void checkDiagonalRows();
		void checkAllRows();
		void clearBoard();

};

#endif // TESTS_GAME_BOARDTEST_HPP
