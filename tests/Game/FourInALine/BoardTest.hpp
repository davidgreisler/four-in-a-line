#ifndef TESTS_GAME_FOUR_IN_A_LINE_BOARDTEST_HPP
#define TESTS_GAME_FOUR_IN_A_LINE_BOARDTEST_HPP

#include <QtTest/QTest>

/**
 * Unit tests for the Game::FourInALine::Board class.
 */
class BoardTest : public QObject
{
		Q_OBJECT

	private slots:
		void createAndCopy();
		void fillAndEmpty();
		void accessOutOfRange();
		void doTokensFallDownOnRemove();
		void findWinningCells();
		void getAvailableColumns();
};

#endif // TESTS_GAME_FOUR_IN_A_LINE_BOARDTEST_HPP
