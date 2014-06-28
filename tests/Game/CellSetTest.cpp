#include "CellSetTest.hpp"
#include "../../src/GameLogic/Board.hpp"
#include "../../src/GameLogic/CellSet.hpp"

#include <QDebug>

/**
 * Create and copy cell sets and check whether their attributes are correct.
 */
void CellSetTest::createAndAssignCellSet()
{
	unsigned int rows = 5u;
	unsigned int columns = 5u;
	GameLogic::Board::TokenType emptyToken = 12345;
	GameLogic::Board testBoard(columns, rows, emptyToken);

	// Create a set from (0,0) to (4, 4).

	GameLogic::CellSet cellSet(&testBoard, 0, 0, 1, 1, 5);

	QVERIFY(cellSet.isEmpty() == false);
	QCOMPARE(cellSet.getCellXPosition(0), 0u);
	QCOMPARE(cellSet.getCellYPosition(0), 0u);
	QCOMPARE(cellSet.getDeltaX(), 1);
	QCOMPARE(cellSet.getDeltaY(), 1);
	QCOMPARE(cellSet.getLength(), 5u);

	// Create an empty set, then copy the first set into the empty set.

	GameLogic::CellSet otherSet;
	QVERIFY(otherSet.isEmpty() == true);

	otherSet = cellSet;

	QVERIFY(otherSet.isEmpty() == false);
	QCOMPARE(otherSet.getCellXPosition(0), 0u);
	QCOMPARE(otherSet.getCellYPosition(0), 0u);
	QCOMPARE(otherSet.getDeltaX(), 1);
	QCOMPARE(otherSet.getDeltaY(), 1);
	QCOMPARE(otherSet.getLength(), 5u);

	// Copy the first set using the copy constructor.

	GameLogic::CellSet anotherSet(cellSet);

	QCOMPARE(anotherSet.getCellXPosition(0), 0u);
	QCOMPARE(anotherSet.getCellYPosition(0), 0u);
	QCOMPARE(anotherSet.getDeltaX(), 1);
	QCOMPARE(anotherSet.getDeltaY(), 1);
	QCOMPARE(anotherSet.getLength(), 5u);
}

/**
 * Creates a cell set and retrieves all cells/positions and checks whether they are correct.
 */
void CellSetTest::retrieveAllCells()
{
	unsigned int rows = 3u;
	unsigned int columns = 3u;
	GameLogic::Board::TokenType emptyToken = 0u;
	GameLogic::Board testBoard(columns, rows, emptyToken);
	testBoard.setCell(0, 0, 1u);
	testBoard.setCell(1, 1, 2u);
	testBoard.setCell(2, 2, 3u);

	// Create a set from (0,0) to (2, 2).

	GameLogic::CellSet cellSet(&testBoard, 0, 0, 1, 1, 3);

	std::vector<GameLogic::Board::TokenType> tokens = cellSet.getContents();
	QCOMPARE(tokens.size(), (std::size_t)3);
	QCOMPARE(tokens.at(0), 1u);
	QCOMPARE(tokens.at(1), 2u);
	QCOMPARE(tokens.at(2), 3u);

	std::vector<std::pair<unsigned int, unsigned int> > positions = cellSet.getCellPositions();
	QCOMPARE(positions.size(), (std::size_t)3);
	QCOMPARE(positions.at(0), std::make_pair(0u, 0u));
	QCOMPARE(positions.at(1), std::make_pair(1u, 1u));
	QCOMPARE(positions.at(2), std::make_pair(2u, 2u));
}

/**
 * Accesses a cell with an index out of range and checks whether an exception is thrown.
 */
void CellSetTest::accessOutOfRange()
{
	unsigned int rows = 3u;
	unsigned int columns = 3u;
	GameLogic::Board::TokenType emptyToken = 0u;
	GameLogic::Board testBoard(columns, rows, emptyToken);

	GameLogic::CellSet cellSet(&testBoard, 0, 0, 1, 1, 1);

	try
	{
		cellSet.getContent(1);
		QFAIL("Attempting to retrieve content of a cell with an index greater or equal to the length of the set should throw an exception.");
	}
	catch(std::exception) {}
}

/**
 * Creates an iterator at the beginning/end of the cell set and checks whether their positions are
 * right.
 */
void CellSetTest::createIterator()
{
	unsigned int rows = 3u;
	unsigned int columns = 3u;
	GameLogic::Board::TokenType emptyToken = 0u;
	GameLogic::Board testBoard(columns, rows, emptyToken);

	testBoard.setCell(0, 0, 1u);
	testBoard.setCell(1, 1, 2u);
	testBoard.setCell(2, 2, 3u);

	GameLogic::CellSet cellSet(&testBoard, 0, 0, 1, 1, 3);

	QCOMPARE(cellSet.begin().getContent(), 1u);

	GameLogic::CellSetIterator end = cellSet.end();
	end--;
	QCOMPARE(end.getContent(), 3u);
}

QTEST_MAIN(CellSetTest)
