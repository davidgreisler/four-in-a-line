#include "ArtificialIntelligenceTest.hpp"
#include "../../../src/Game/FourInALine/ArtificialIntelligence.hpp"
#include "../../../src/Game/FourInALine/Game.hpp"

#include <QDebug>

/**
 * Checks whether the artificial intelligence is able to detect an obvious win.
 */
void ArtificialIntelligenceTest::obviousWin()
{
	unsigned int columns = 4;
	unsigned int rows = 4;
	Game::FourInALine::Game game(columns, rows, 1);
	Game::FourInALine::ArtificialIntelligence ai(3);

	game.makeMove(0);
	game.makeMove(0);

	game.makeMove(1);
	game.makeMove(1);

	game.makeMove(2);
	game.makeMove(2);

	// Dropping a token in column 4 will win the game. The AI should be able to figure that out.

	QCOMPARE(ai.computeNextMove(game), 3u);
}

/**
 * Checks whether the artificial intelligence is able to see that the opponent is about to win and
 * does the right move to prevent that.
 */
void ArtificialIntelligenceTest::preventOpponentWin()
{
	unsigned int columns = 8;
	unsigned int rows = 8;
	Game::FourInALine::Game game(columns, rows, 1);
	Game::FourInALine::ArtificialIntelligence ai(3);

	game.makeMove(0);
	game.makeMove(0);

	game.makeMove(1);
	game.makeMove(1);

	game.makeMove(2);

	// Dropping a token in column 4 will prevent player 1 from winning.

	QCOMPARE(ai.computeNextMove(game), 3u);
}

/**
 * Does some basic tests.
 */
void ArtificialIntelligenceTest::basicTest()
{
	Game::FourInALine::ArtificialIntelligence ai(3);

	QCOMPARE(ai.getSearchDepth(), 3u);

	ai.setSearchDepth(4);

	QCOMPARE(ai.getSearchDepth(), 4u);
}

QTEST_MAIN(ArtificialIntelligenceTest)
