#include "CellSetIteratorTest.hpp"
#include "../../src/GameLogic/Board.hpp"
#include "../../src/GameLogic/CellSet.hpp"
#include "../../src/GameLogic/CellSetIterator.hpp"

/**
 * Creates an iterator and a copy of it and then tests basic functionality.
 */
void CellSetIteratorTest::basicTest()
{
	unsigned int rows = 3u;
	unsigned int columns = 3u;
	GameLogic::Board testBoard(columns, rows, 0u);

	GameLogic::CellSet cellSet(&testBoard, 0, 0, 1, 1, 3);
	GameLogic::CellSetIterator i = cellSet.begin();
	GameLogic::CellSetIterator copy(i);

	// Check whether attributes of the iterator and the copy are correct.

	QCOMPARE(i.getIndex(), 0u);
	QCOMPARE(i.getContent(), 0u);
	QCOMPARE(i.getXPosition(), 0u);
	QCOMPARE(i.getYPosition(), 0u);

	QCOMPARE(copy.getIndex(), 0u);
	QCOMPARE(copy.getContent(), 0u);
	QCOMPARE(copy.getXPosition(), 0u);
	QCOMPARE(copy.getYPosition(), 0u);

	// Check whether the iterator is at the next position and the copy unchanged.

	i++;

	QCOMPARE(i.getIndex(), 1u);
	QCOMPARE(i.getContent(), 0u);
	QCOMPARE(i.getXPosition(), 1u);
	QCOMPARE(i.getYPosition(), 1u);

	QCOMPARE(copy.getIndex(), 0u);
	QCOMPARE(copy.getContent(), 0u);
	QCOMPARE(copy.getXPosition(), 0u);
	QCOMPARE(copy.getYPosition(), 0u);

	// Advance both copy and iterator and check whether both are at the next position.

	copy++;
	i++;

	QCOMPARE(i.getIndex(), 2u);
	QCOMPARE(i.getContent(), 0u);
	QCOMPARE(i.getXPosition(), 2u);
	QCOMPARE(i.getYPosition(), 2u);
}

/**
 * Tests comparison operators using two iterators.
 */
void CellSetIteratorTest::testComparisonOperators()
{
	unsigned int rows = 3u;
	unsigned int columns = 3u;
	GameLogic::Board testBoard(columns, rows, 0u);

	GameLogic::CellSet cellSet(&testBoard, 0, 0, 1, 1, 3);
	GameLogic::CellSetIterator a = cellSet.begin();
	GameLogic::CellSetIterator b = cellSet.begin();

	QVERIFY((a == b) == true);
	QVERIFY((a != b) == false);
	QVERIFY((a > b) == false);
	QVERIFY((a >= b) == true);
	QVERIFY((a < b) == false);
	QVERIFY((a <= b) == true);

	a++;

	QVERIFY((a == b) == false);
	QVERIFY((a != b) == true);
	QVERIFY((a > b) == true);
	QVERIFY((a >= b) == true);
	QVERIFY((a < b) == false);
	QVERIFY((a <= b) == false);

	b++;
	b++;

	QVERIFY((a == b) == false);
	QVERIFY((a != b) == true);
	QVERIFY((a > b) == false);
	QVERIFY((a >= b) == false);
	QVERIFY((a < b) == true);
	QVERIFY((a <= b) == true);

	a++;

	QVERIFY((a >= b) == true);
	QVERIFY((a <= b) == true);
}

/**
 * Tests forward iteration using post-increment/pre-increment operators and next() method.
 */
void CellSetIteratorTest::iterateForward()
{
	unsigned int rows = 3u;
	unsigned int columns = 3u;
	GameLogic::Board testBoard(columns, rows, 0u);
	testBoard.setCell(0, 0, 0u);
	testBoard.setCell(1, 0, 1u);
	testBoard.setCell(2, 0, 2u);

	GameLogic::CellSet cellSet(&testBoard, 0, 0, 1, 0, 3);
	GameLogic::CellSetIterator i;
	unsigned int c;

	// Post-increment operator.

	for(i = cellSet.begin(), c = 0; i != cellSet.end(); c++, i++)
	{
		QCOMPARE(*i, c);
	}

	QCOMPARE(c, 3u);

	// Pre-increment operator.

	for(i = cellSet.begin(), c = 0; i != cellSet.end(); c++, ++i)
	{
		QCOMPARE(*i, c);
	}

	QCOMPARE(c, 3u);

	// Using next() method.

	for(i = cellSet.begin(), c = 0; i != cellSet.end(); c++, i.next())
	{
		QCOMPARE(*i, c);
	}

	QCOMPARE(c, 3u);
}

/**
 * Tests backward iteration using post-decrement/pre-decrement operators and previous() method.
 */
void CellSetIteratorTest::iterateBackward()
{
	unsigned int rows = 3u;
	unsigned int columns = 3u;
	GameLogic::Board testBoard(columns, rows, 0u);
	testBoard.setCell(0, 0, 2u);
	testBoard.setCell(1, 0, 1u);
	testBoard.setCell(2, 0, 0u);

	GameLogic::CellSet cellSet(&testBoard, 0, 0, 1, 0, 3);
	GameLogic::CellSetIterator i;
	unsigned int c;

	// Post-decrement operator.

	for(i = cellSet.end(), c = 0; i != cellSet.begin();)
	{
		i--;

		QCOMPARE(*i, c);

		c++;
	}

	QCOMPARE(c, 3u);

	// Pre-decrement operator.

	for(i = cellSet.end(), c = 0; i != cellSet.begin();)
	{
		--i;

		QCOMPARE(*i, c);

		c++;
	}

	QCOMPARE(c, 3u);

	// Using previous() method.

	for(i = cellSet.end(), c = 0; i != cellSet.begin();)
	{
		i.previous();

		QCOMPARE(*i, c);

		c++;
	}

	QCOMPARE(c, 3u);
}

QTEST_MAIN(CellSetIteratorTest)
