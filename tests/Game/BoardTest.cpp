#include "BoardTest.hpp"
#include "../../src/Game/Board.hpp"
#include "../../src/Game/CellSet.hpp"

#include <QDebug>

/**
 * Tests creating and copying boards and checks whether everything gets initialized correctly.
 */
void BoardTest::createAndCopyBoard()
{
	// Test whether it is possible to create a board with impossible dimensions.

	try
	{
		Game::Board invalidBoard(1, 0);
		QFAIL("Attempting to create an invalid board should throw an exception.");
	}
	catch(std::exception)
	{

	}

	// Create 10x5 board and check whether everything is initialized correctly.

	unsigned int rows = 10u;
	unsigned int columns = 5u;
	Game::Board::TokenType emptyToken = 12345;
	Game::Board testBoard(columns, rows, emptyToken);
	QVERIFY(testBoard.getNumberOfRows() == rows);
	QVERIFY(testBoard.getNumberOfColumns() == columns);
	QVERIFY(testBoard.getEmptyToken() == emptyToken);
	QVERIFY(testBoard.isEmpty());

	for (unsigned int x = 0; x < columns; ++x)
	{
		for (unsigned int y = 0; y < rows; ++y)
		{
			QVERIFY(testBoard.getCell(x, y) == emptyToken);
		}

		QVERIFY(testBoard.isColumnEmpty(x) == true);
		QVERIFY(testBoard.isColumnFull(x) == false);
	}

	for (unsigned int i = 0; i < rows; ++i)
	{
		QVERIFY(testBoard.isRowEmpty(i) == true);
		QVERIFY(testBoard.isRowFull(i) == false);
	}

	testBoard.setCell(0, 0, 1u);

	// Copy the board and verify that the copy has the same dimensions as the original and
	// check whether changing a cell in the original doesn't affect the copy and the other way
	// around.

	Game::Board copy(testBoard);
	QVERIFY(copy.getNumberOfRows() == rows);
	QVERIFY(copy.getNumberOfColumns() == columns);
	QCOMPARE(copy.getCell(0, 0), 1u);

	copy.setCell(0, 0, 0u);
	QCOMPARE(testBoard.getCell(0, 0), 1u);
	QCOMPARE(copy.getCell(0, 0), 0u);
}

/**
 * Creates a 5x5 board and fills it while checking that the cells contain the right tokens.
 */
void BoardTest::fillWholeBoard()
{
	unsigned int rows = 5u;
	unsigned int columns = 5u;
	Game::Board testBoard(columns, rows, 0u);

	// Fill whole board.

	QVERIFY(testBoard.isEmpty() == true);
	QVERIFY(testBoard.isFull() == false);

	for (unsigned int y = 0; y < rows; ++y)
	{
		QVERIFY(testBoard.isRowEmpty(y) == true);
		QVERIFY(testBoard.isRowFull(y) == false);

		for (unsigned int x = 0; x < columns; ++x)
		{
			QVERIFY(testBoard.isCellEmpty(x, y) == true);
			QVERIFY(testBoard.isCellOccupied(x, y) == false);

			testBoard.setCell(x, y, 1 + y * columns + x);

			QVERIFY(testBoard.isCellEmpty(x, y) == false);
			QVERIFY(testBoard.isCellOccupied(x, y) == true);
			QCOMPARE(testBoard.getCell(x, y), 1 + y * columns + x);
		}

		QVERIFY(testBoard.isRowEmpty(y) == false);
		QVERIFY(testBoard.isRowFull(y) == true);
	}

	for (unsigned int x = 0; x < columns; ++x)
	{
		QVERIFY(testBoard.isColumnEmpty(x) == false);
		QVERIFY(testBoard.isColumnFull(x) == true);
	}

	QVERIFY(testBoard.isEmpty() == false);
	QVERIFY(testBoard.isFull() == true);
}

/**
 * Checks whether swapping cells works.
 */
void BoardTest::swapCells()
{
	unsigned int rows = 5u;
	unsigned int columns = 5u;
	Game::Board testBoard(columns, rows, 0u);

	// Swap two cells and check whether they have been swapped.

	testBoard.setCell(0, 0, 1u);
	testBoard.setCell(0, 1, 2u);
	QVERIFY(testBoard.getCell(0, 0) == 1u);
	QVERIFY(testBoard.getCell(0, 1) == 2u);

	testBoard.swapCells(0, 0, 0, 1);
	QVERIFY(testBoard.getCell(0, 0) == 2u);
	QVERIFY(testBoard.getCell(0, 1) == 1u);

	// Swap a cell with itself. Nothing should happen.

	testBoard.setCell(1, 0, 1u);
	QVERIFY(testBoard.getCell(1, 0) == 1u);

	testBoard.swapCells(1, 0, 1, 0);
	QVERIFY(testBoard.getCell(1, 0) == 1u);
}

/**
 * Tries to access cells outside of the board's dimensions and checks whether they throw an
 * exception or not.
 */
void BoardTest::accessOutOfRange()
{
	unsigned int rows = 2u;
	unsigned int columns = 2u;
	Game::Board testBoard(columns, rows, 0u);

	try
	{
		testBoard.setCell(0, 2, 1u);
		QFAIL("Attempting to set a cell positioned outside the board on the y-axis should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		testBoard.setCell(2, 0, 1u);
		QFAIL("Attempting to set a cell positioned outside the board on the x-axis should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		testBoard.setCell(3, 3, 1u);
		QFAIL("Attempting to set a cell positioned outside the board should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		testBoard.getCell(2, 2);
		QFAIL("Attempting to get a cell positioned outside the board should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		testBoard.swapCells(0, 0, 2, 0);
		QFAIL("Attempting to swap two cells positioned outside the board should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		testBoard.getColumn(2);
		QFAIL("Attempting to get a column positioned outside the board should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		testBoard.getRow(2);
		QFAIL("Attempting to get a row positioned outside the board should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		testBoard.getMinorDiagonal(2, 0);
		QFAIL("Attempting to get a minor diagonal row positioned outside the board should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		testBoard.getMajorDiagonal(2, 0);
		QFAIL("Attempting to get a major diagonal row positioned outside the board should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		testBoard.isRowEmpty(2);
		QFAIL("Attempting to check whether a row positioned outside the board is empty should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		testBoard.isRowFull(2);
		QFAIL("Attempting to check whether a row positioned outside the board is full should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		testBoard.isColumnEmpty(2);
		QFAIL("Attempting to check whether a column positioned outside the board is empty should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		testBoard.isColumnFull(2);
		QFAIL("Attempting to check whether a column positioned outside the board is full should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		testBoard.isCellEmpty(2, 2);
		QFAIL("Attempting to check whether a cell positioned outside the board is empty should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		testBoard.isCellOccupied(2, 2);
		QFAIL("Attempting to check whether a cell positioned outside the board is occupied should throw an exception.");
	}
	catch(std::exception) {}
}

/**
 * Retrieves cell sets referencing all rows/columns and checks whether they reference the right
 * cells.
 */
void BoardTest::checkRowsAndColumns()
{
	unsigned int rows = 8u;
	unsigned int columns = 5u;
	Game::Board testBoard(columns, rows, 0u);

	// Fill board, every cell gets a unique token.

	for (unsigned int x = 0; x < columns; ++x)
	{
		for (unsigned int y = 0; y < rows; ++y)
		{
			testBoard.setCell(x, y, y * columns + x);
		}
	}

	// Check columns.

	for (unsigned int x = 0; x < columns; ++x)
	{
		Game::CellSet column = testBoard.getColumn(x);

		for (unsigned int y = 0; y < column.getLength(); ++y)
		{
			QCOMPARE(column.getContent(y), y * columns + x);
		}
	}

	// Check rows.

	for (unsigned int y = 0; y < rows; ++y)
	{
		Game::CellSet row = testBoard.getRow(y);

		for (unsigned int x = 0; x < row.getLength(); ++x)
		{
			QCOMPARE(row.getContent(x), y * columns + x);
		}
	}
}

/**
 * Retrieves cell sets referencing all diagonal rows and checks whether they reference the right
 * cells.
 */
void BoardTest::checkDiagonalRows()
{
	unsigned int rows = 5u;
	unsigned int columns = 5u;
	Game::Board testBoard(columns, rows, 0u);

	// Fill board, every cell gets a unique token.

	for (unsigned int x = 0; x < columns; ++x)
	{
		for (unsigned int y = 0; y < rows; ++y)
		{
			testBoard.setCell(x, y, y * columns + x);
		}
	}

	// Check major diagonal rows.

	for(unsigned int i = 1; i < columns; ++i)
	{
		Game::CellSet diagonal = testBoard.getMajorDiagonal(i, 0);

		for (unsigned int j = 0; j < diagonal.getLength(); ++j)
		{
			QCOMPARE(diagonal.getContent(j), j * columns + (i + j));
		}
	}

	for(unsigned int i = 0; i < rows; ++i)
	{
		Game::CellSet diagonal = testBoard.getMajorDiagonal(0, i);

		for (unsigned int j = 0; j < diagonal.getLength(); ++j)
		{
			QCOMPARE(diagonal.getContent(j), (i + j) * columns + j);
		}
	}

	// Check minor diagonal rows.

	for(unsigned int i = 0; i < columns; ++i)
	{
		Game::CellSet diagonal = testBoard.getMinorDiagonal(i, 0);

		for (unsigned int j = 0; j < diagonal.getLength(); ++j)
		{
			QCOMPARE(diagonal.getContent(j), j * columns + (i - j));
		}
	}

	for(unsigned int i = 1; i < rows; ++i)
	{
		Game::CellSet diagonal = testBoard.getMinorDiagonal(i, columns - 1);

		for (unsigned int j = 0; j < diagonal.getLength(); ++j)
		{
			QCOMPARE(diagonal.getContent(j), (i + j) * columns + (columns - j - 1));
		}
	}
}

/**
 * Checks whether allRows() returns the correct amount of rows.
 */
void BoardTest::checkAllRows()
{
	Game::Board testBoard(3, 3, 0u);
	std::vector<Game::CellSet> allRows = testBoard.getAllRows();
	QCOMPARE(allRows.size(), (std::size_t)16);

	Game::Board testBoard2 = Game::Board(4, 4, 0u);
	allRows = testBoard2.getAllRows();
	QCOMPARE(allRows.size(), (std::size_t)22);
}


QTEST_MAIN(BoardTest)
