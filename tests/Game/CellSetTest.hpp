#ifndef TESTS_GAME_CELLSETTEST_HPP
#define TESTS_GAME_CELLSETTEST_HPP

#include <QtTest/QTest>

/**
 * Unit tests for the Game::CellSet class.
 */
class CellSetTest : public QObject
{
		Q_OBJECT

	private slots:
		void createAndAssignCellSet();
		void retrieveAllCells();
		void accessOutOfRange();
		void createIterator();
};

#endif // TESTS_GAME_CELLSETTEST_HPP
