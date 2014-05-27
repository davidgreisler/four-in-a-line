#ifndef TESTS_GAME_CELLSETITERATORTEST_HPP
#define TESTS_GAME_CELLSETITERATORTEST_HPP

#include <QtTest/QTest>

/**
 * Unit tests for the Game::CellSetIterator class.
 */
class CellSetIteratorTest : public QObject
{
		Q_OBJECT

	private slots:
		void basicTest();
		void testComparisonOperators();
		void iterateForward();
		void iterateBackward();

};

#endif // TESTS_GAME_CELLSETITERATORTEST_HPP
