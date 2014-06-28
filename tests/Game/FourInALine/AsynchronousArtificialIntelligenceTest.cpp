#include "AsynchronousArtificialIntelligenceTest.hpp"
#include "../../../src/GameLogic/FourInALine/ArtificialIntelligence.hpp"
#include "../../../src/GameLogic/FourInALine/AsynchronousArtificialIntelligence.hpp"
#include "../../../src/GameLogic/FourInALine/Game.hpp"

#include <chrono>
#include <QThread>

/**
 * Checks whether the artificial intelligence is able to detect an obvious win.
 */
void AsynchronousArtificialIntelligenceTest::obviousWin()
{
	unsigned int columns = 4;
	unsigned int rows = 4;
	GameLogic::FourInALine::Game game(columns, rows, 1);
	GameLogic::FourInALine::AsynchronousArtificialIntelligence ai(5);

	game.makeMove(0);
	game.makeMove(0);

	game.makeMove(1);
	game.makeMove(1);

	game.makeMove(2);
	game.makeMove(2);

	// Dropping a token in column 4 will win the game. The AI should be able to figure that out.

	ai.computeNextMoveAsynchronously(game);

	QCOMPARE(ai.getNextMove(std::chrono::milliseconds(10000)), 3u);
	QCOMPARE(ai.getNextMove(), 3u);
	QCOMPARE(ai.isNextMoveReady(), true);
	QCOMPARE(ai.isNextMoveValid(), true);
	QCOMPARE(ai.isComputing(), false);
}

/**
 * Checks whether the artificial intelligence is able to see that the opponent is about to win and
 * does the right move to prevent that.
 */
void AsynchronousArtificialIntelligenceTest::preventOpponentWin()
{
	unsigned int columns = 8;
	unsigned int rows = 8;
	GameLogic::FourInALine::Game game(columns, rows, 1);
	GameLogic::FourInALine::AsynchronousArtificialIntelligence ai(3);

	game.makeMove(0);
	game.makeMove(0);

	game.makeMove(1);
	game.makeMove(1);

	game.makeMove(2);

	// Dropping a token in column 4 will prevent player 1 from winning.

	ai.computeNextMoveAsynchronously(game);
	QCOMPARE(ai.getNextMove(std::chrono::milliseconds(10000)), 3u);
}

/**
 * Does some basic tests.
 */
void AsynchronousArtificialIntelligenceTest::basicTest()
{
	GameLogic::FourInALine::AsynchronousArtificialIntelligence ai(3);

	QCOMPARE(ai.isNextMoveReady(), false);
	QCOMPARE(ai.isNextMoveValid(), false);
	QCOMPARE(ai.isComputing(), false);
	QCOMPARE(ai.getNextMove(), GameLogic::FourInALine::AsynchronousArtificialIntelligence::INVALID_RESULT);

	QCOMPARE(ai.getSearchDepth(), 3u);

	ai.setSearchDepth(4);

	QCOMPARE(ai.getSearchDepth(), 4u);
}

/**
 * Creates a big board and an AI with a very high search depth, asks for the next move and then
 * tries to cancel the computation.
 */
void AsynchronousArtificialIntelligenceTest::testCancel()
{
	unsigned int columns = 9;
	unsigned int rows = 9;
	GameLogic::FourInALine::Game game(columns, rows, 1);
	GameLogic::FourInALine::AsynchronousArtificialIntelligence ai(12);

	ai.computeNextMoveAsynchronously(game);

	QCOMPARE(ai.isNextMoveReady(), false);
	QCOMPARE(ai.isNextMoveValid(), false);
	QCOMPARE(ai.isComputing(), true);
	QCOMPARE(ai.getNextMove(), GameLogic::FourInALine::AsynchronousArtificialIntelligence::INVALID_RESULT);

	ai.cancelComputation();

	QThread::msleep(1000);

	QCOMPARE(ai.isNextMoveReady(), false);
	QCOMPARE(ai.isNextMoveValid(), false);
	QCOMPARE(ai.isComputing(), false);
	QCOMPARE(ai.getNextMove(), GameLogic::FourInALine::AsynchronousArtificialIntelligence::INVALID_RESULT);
}

QTEST_MAIN(AsynchronousArtificialIntelligenceTest)
