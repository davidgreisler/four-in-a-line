#include "BoardTest.hpp"
#include "../../../src/GameLogic/FourInALine/Board.hpp"
#include "../../../src/GameLogic/Board.hpp"
#include "../../../src/GameLogic/CellSet.hpp"

#include <QDebug>
#include <memory>

/**
 * Creates a game board and copies it, checks whether everything is initialized correctly and the
 * copy/original do not affect each other.
 */
void BoardTest::createAndCopy()
{
	// Test whether it is possible to create a board with impossible dimensions.

	try
	{
		GameLogic::FourInALine::Board invalidBoard(1, 0);
		QFAIL("Attempting to create an invalid board should throw an exception.");
	}
	catch(std::exception)
	{

	}

	// Create 10x5 board and check whether everything is initialized correctly.

	unsigned int rows = 10u;
	unsigned int columns = 5u;
	GameLogic::FourInALine::Board testBoard(columns, rows);
	QVERIFY(testBoard.getNumberOfRows() == rows);
	QVERIFY(testBoard.getNumberOfColumns() == columns);
	QVERIFY(testBoard.getEmptyToken() == GameLogic::FourInALine::Board::CELL_EMPTY);
	QVERIFY(testBoard.isEmpty() == true);

	testBoard.dropToken(0, 123u);

	QVERIFY(testBoard.isEmpty() == false);
	QCOMPARE(testBoard.getCell(0, rows - 1), 123u);

	// Copy the board and check whether it is copied correctly and changes to the copy/original do
	// not affect each other.

	GameLogic::FourInALine::Board copy(testBoard);

	QVERIFY(copy.isEmpty() == false);
	QCOMPARE(copy.getCell(0, rows - 1), 123u);

	copy.dropToken(0, 456u);

	QCOMPARE(copy.getCell(0, rows - 2), 456u);
	QCOMPARE(testBoard.getCell(0, rows - 2), GameLogic::FourInALine::Board::CELL_EMPTY);

}

/**
 * Fills the board by dropping tokens and then empties it again with removeToken().
 */
void BoardTest::fillAndEmpty()
{
	unsigned int rows = 10u;
	unsigned int columns = 5u;
	GameLogic::FourInALine::Board testBoard(columns, rows);

	QVERIFY(testBoard.isEmpty() == true);

	// Fill board.

	for (unsigned int i = 0; i < columns; ++i)
	{
		QVERIFY(testBoard.isColumnEmpty(i) == true);
		QVERIFY(testBoard.isColumnFull(i) == false);

		for (unsigned int j = 0; j < rows; ++j)
		{
			QVERIFY(testBoard.canDropToken(i) == true);

			testBoard.dropToken(i, j + 1);

			QCOMPARE(testBoard.getCell(i, rows - j - 1), j + 1);
		}

		QVERIFY(testBoard.canDropToken(i) == false);
		QVERIFY(testBoard.isColumnFull(i) == true);
	}

	// Empty board.

	for (unsigned int i = 0; i < rows; ++i)
	{
		QVERIFY(testBoard.isRowEmpty(i) == false);
		QVERIFY(testBoard.isRowFull(i) == true);

		for (unsigned int j = 0; j < columns; ++j)
		{
			// Remove token with a given column.

			testBoard.removeToken(j);

			QVERIFY(testBoard.isCellEmpty(j, i));
			QVERIFY(testBoard.canDropToken(j) == true);

			// Add token at the same place.

			testBoard.dropToken(j, 123u);

			QCOMPARE(testBoard.getCell(j, i), 123u);

			// Remove token with a given position.

			testBoard.removeToken(j, i);

			QVERIFY(testBoard.isCellEmpty(j, i));
			QVERIFY(testBoard.canDropToken(j) == true);
		}

		QVERIFY(testBoard.isRowEmpty(i) == true);
		QVERIFY(testBoard.isRowFull(i) == false);
	}
}

/**
 * Tries to drop tokens/access cells outside the board.
 */
void BoardTest::accessOutOfRange()
{
	unsigned int rows = 2u;
	unsigned int columns = 2u;
	GameLogic::FourInALine::Board testBoard(columns, rows);

	try
	{
		testBoard.dropToken(2u, 1u);
		QFAIL("Attempting to drop a token outside the board on the x-axis should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		testBoard.dropToken(1u, 1u);
		testBoard.dropToken(1u, 1u);
		testBoard.dropToken(1u, 1u);
		QFAIL("Attempting to drop a token in a full column should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		testBoard.removeToken(0);
		QFAIL("Attempting to remove a token from an empty column should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		testBoard.removeToken(0, 0);
		QFAIL("Attempting to remove an empty cell should throw an exception.");
	}
	catch(std::exception) {}
}

/**
 * Fills a column on a board and then removes the tokens one-by-one from the bottom and checks
 * whether the tokens above fall down correctly.
 */
void BoardTest::doTokensFallDownOnRemove()
{
	unsigned int rows = 3u;
	unsigned int columns = 2u;
	GameLogic::FourInALine::Board testBoard(columns, rows);

	testBoard.dropToken(0, 1u);
	testBoard.dropToken(0, 2u);
	testBoard.dropToken(0, 3u);

	QCOMPARE(testBoard.getCell(0, 2), 1u);
	QCOMPARE(testBoard.getCell(0, 1), 2u);
	QCOMPARE(testBoard.getCell(0, 0), 3u);

	testBoard.removeToken(0, 2);

	QCOMPARE(testBoard.getCell(0, 2), 2u);
	QCOMPARE(testBoard.getCell(0, 1), 3u);
	QCOMPARE(testBoard.getCell(0, 0), GameLogic::FourInALine::Board::CELL_EMPTY);

	testBoard.removeToken(0, 2);

	QCOMPARE(testBoard.getCell(0, 2), 3u);
	QCOMPARE(testBoard.getCell(0, 1), GameLogic::FourInALine::Board::CELL_EMPTY);
	QCOMPARE(testBoard.getCell(0, 0), GameLogic::FourInALine::Board::CELL_EMPTY);

	testBoard.removeToken(0, 2);

	QCOMPARE(testBoard.getCell(0, 2), GameLogic::FourInALine::Board::CELL_EMPTY);
	QCOMPARE(testBoard.getCell(0, 1), GameLogic::FourInALine::Board::CELL_EMPTY);
	QCOMPARE(testBoard.getCell(0, 0), GameLogic::FourInALine::Board::CELL_EMPTY);
}

/**
 * Creates board with winning cells in all orientations and checks whether findWinningCells() finds
 * them.
 */
void BoardTest::findWinningCells()
{
	unsigned int rows = 5u;
	unsigned int columns = 5u;
	std::unique_ptr<GameLogic::FourInALine::Board> testBoard(new GameLogic::FourInALine::Board(columns, rows));

	// No winner yet, findWinningCells() should return an empty cell set.

	QVERIFY(testBoard->findWinningCells().isEmpty() == true);

	// Horizontal.

	testBoard->dropToken(0, 1u);
	testBoard->dropToken(1, 1u);
	testBoard->dropToken(2, 1u);
	testBoard->dropToken(3, 1u);

	GameLogic::CellSet winningCells = testBoard->findWinningCells();

	QCOMPARE(winningCells.getLength(), 4u);

	std::vector<GameLogic::Board::TokenType> content = winningCells.getContents();
	for (unsigned int i = 0; i < 4; ++i)
	{
		QCOMPARE(content.at(i), 1u);
	}

	// Vertical.

	testBoard.reset(new GameLogic::FourInALine::Board(columns, rows));

	testBoard->dropToken(0, 1u);
	testBoard->dropToken(0, 1u);
	testBoard->dropToken(0, 1u);
	testBoard->dropToken(0, 1u);

	winningCells = testBoard->findWinningCells();

	QCOMPARE(winningCells.getLength(), 4u);

	content = winningCells.getContents();
	for (unsigned int i = 0; i < 4; ++i)
	{
		QCOMPARE(content.at(i), 1u);
	}

	// Minor diagonal.

	testBoard.reset(new GameLogic::FourInALine::Board(columns, rows));

	testBoard->dropToken(0, 1u);
	testBoard->dropToken(1, 2u);
	testBoard->dropToken(1, 1u);
	testBoard->dropToken(2, 1u);
	testBoard->dropToken(2, 2u);
	testBoard->dropToken(2, 1u);
	testBoard->dropToken(3, 2u);
	testBoard->dropToken(3, 2u);
	testBoard->dropToken(3, 2u);
	testBoard->dropToken(3, 1u);

	winningCells = testBoard->findWinningCells();

	QCOMPARE(winningCells.getLength(), 4u);

	content = winningCells.getContents();
	for (unsigned int i = 0; i < 4; ++i)
	{
		QCOMPARE(content.at(i), 1u);
	}

	// Major diagonal.

	testBoard.reset(new GameLogic::FourInALine::Board(columns, rows));

	testBoard->dropToken(3, 1u);
	testBoard->dropToken(2, 2u);
	testBoard->dropToken(2, 1u);
	testBoard->dropToken(1, 1u);
	testBoard->dropToken(1, 2u);
	testBoard->dropToken(1, 1u);
	testBoard->dropToken(0, 2u);
	testBoard->dropToken(0, 2u);
	testBoard->dropToken(0, 2u);
	testBoard->dropToken(0, 1u);

	winningCells = testBoard->findWinningCells();

	QCOMPARE(winningCells.getLength(), 4u);

	content = winningCells.getContents();
	for (unsigned int i = 0; i < 4; ++i)
	{
		QCOMPARE(content.at(i), 1u);
	}
}

/**
 * Drops tokens in a board until half of the columns are full and then checks whether
 * getAvailableColumns() returns the correct column numbers.
 */
void BoardTest::getAvailableColumns()
{
	unsigned int rows = 1u;
	unsigned int columns = 4u;
	GameLogic::FourInALine::Board testBoard(columns, rows);

	testBoard.dropToken(0, 1u);
	testBoard.dropToken(2, 2u);

	std::vector<unsigned int> availableColumns = testBoard.getAvailableColumns();

	QVERIFY(availableColumns.size() == 2);
	QVERIFY(availableColumns[0] == 1 || availableColumns[0] == 3);
	QVERIFY(availableColumns[1] == 1 || availableColumns[1] == 3);
}

QTEST_MAIN(BoardTest)
