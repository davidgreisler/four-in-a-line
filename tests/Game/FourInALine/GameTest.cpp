#include "GameTest.hpp"
#include "../../../src/GameLogic/FourInALine/Game.hpp"

#include <QDebug>

/**
 * Creates a new game and checks whether it is initialized correctly.
 */
void GameTest::createGame()
{
	unsigned int columns = 8;
	unsigned int rows = 5;
	GameLogic::FourInALine::Game game(columns, rows, 1);

	QCOMPARE(game.getBoard()->getNumberOfColumns(), columns);
	QCOMPARE(game.getBoard()->getNumberOfRows(), rows);
	QCOMPARE(game.getCurrentPlayer(), (GameLogic::FourInALine::Game::PlayerType)1);
	QCOMPARE(game.isUndoPossible(), false);
	QCOMPARE(game.isMovePossible(0), true);
	QCOMPARE(game.isOver(), false);
	QCOMPARE(game.isDraw(), false);

	auto replay = game.getReplay();
	QVERIFY(replay.size() == (std::size_t)0);
	QCOMPARE(game.getNumberOfMoves(), 0u);

	try
	{
		GameLogic::FourInALine::Game game(1, 2, 3);
		QFAIL("Attempting to create a game where the player who does the first move is neither player one or two should throw an exception.");
	}
	catch(std::exception) {}
}

/**
 * Starts a game and plays a draw.
 */
void GameTest::playDraw()
{
	unsigned int columns = 2;
	unsigned int rows = 4;
	GameLogic::FourInALine::Game game(columns, rows, 1);

	QCOMPARE(game.isUndoPossible(), false);
	QCOMPARE(game.isMovePossible(0), true);
	QCOMPARE(game.isOver(), false);
	QCOMPARE(game.isDraw(), false);

	// | 1 | 2 |

	game.makeMove(0);
	game.makeMove(1);

	// | 2 | 1 |

	game.makeMove(1);
	game.makeMove(0);

	QCOMPARE(game.isUndoPossible(), true);
	QCOMPARE(game.isMovePossible(0), true);
	QCOMPARE(game.isOver(), false);
	QCOMPARE(game.isDraw(), false);

	// | 1 | 2 |

	game.makeMove(0);
	game.makeMove(1);

	// | 2 | 1 |

	game.makeMove(1);

	QCOMPARE(game.isMovePossible(1), false);

	game.makeMove(0);

	QCOMPARE(game.isUndoPossible(), true);
	QCOMPARE(game.isMovePossible(0), false);
	QCOMPARE(game.isOver(), true);
	QCOMPARE(game.isDraw(), true);
	QCOMPARE(game.getNumberOfMoves(), 8u);
}

/**
 * Plays a game where player 1 wins.
 */
void GameTest::playAndWin()
{
	unsigned int columns = 8;
	unsigned int rows = 5;
	GameLogic::FourInALine::Game game(columns, rows, 1);

	QCOMPARE(game.isUndoPossible(), false);
	QCOMPARE(game.isMovePossible(0), true);
	QCOMPARE(game.isOver(), false);
	QCOMPARE(game.isDraw(), false);

	// | 1 | 2 |

	game.makeMove(0);
	game.makeMove(1);

	// | 1 | 2 |

	game.makeMove(0);
	game.makeMove(1);

	// | 1 | 2 |

	game.makeMove(0);
	game.makeMove(1);

	// | 1 |   |

	game.makeMove(0);

	QCOMPARE(game.isUndoPossible(), true);
	QCOMPARE(game.isMovePossible(0), false);
	QCOMPARE(game.isOver(), true);
	QCOMPARE(game.isDraw(), false);
	QCOMPARE(game.getWinner(), (GameLogic::FourInALine::Game::PlayerType)1);
}

/**
 * Plays a game and checks whether the replay reproduces the game played.
 */
void GameTest::checkReplay()
{
	unsigned int columns = 8;
	unsigned int rows = 5;
	GameLogic::FourInALine::Game game(columns, rows, 1);

	// | 1 | 2 |

	game.makeMove(0);
	game.makeMove(1);

	// | 1 | 2 |

	game.makeMove(0);
	game.makeMove(1);

	auto replay = game.getReplay();
	QVERIFY(replay.size() == (std::size_t)4);
	QCOMPARE(game.getNumberOfMoves(), 4u);

	QCOMPARE(replay[0].first, (GameLogic::FourInALine::Game::PlayerType)1);
	QCOMPARE(replay[1].first, (GameLogic::FourInALine::Game::PlayerType)2);
	QCOMPARE(replay[2].first, (GameLogic::FourInALine::Game::PlayerType)1);
	QCOMPARE(replay[3].first, (GameLogic::FourInALine::Game::PlayerType)2);

	QCOMPARE(replay[0].second, 0u);
	QCOMPARE(replay[1].second, 1u);
	QCOMPARE(replay[2].second, 0u);
	QCOMPARE(replay[3].second, 1u);
}

/**
 * Makes a few moves and then undoes them.
 */
void GameTest::undoMove()
{
	unsigned int columns = 8;
	unsigned int rows = 5;
	GameLogic::FourInALine::Game game(columns, rows, 1);

	QCOMPARE(game.getNumberOfMoves(), 0u);
	QCOMPARE(game.isUndoPossible(), false);

	// | 1 | 2 |

	game.makeMove(0);
	game.makeMove(1);

	// | 1 | 2 |

	game.makeMove(0);
	game.makeMove(1);

	QCOMPARE(game.getNumberOfMoves(), 4u);
	QCOMPARE(game.isUndoPossible(), true);

	game.undoLastMove();

	QCOMPARE(game.getNumberOfMoves(), 3u);
	QCOMPARE(game.getBoard()->getCell(1, rows - 2), game.getBoard()->getEmptyToken());
	QCOMPARE(game.isUndoPossible(), true);

	game.undoLastMove();

	QCOMPARE(game.getNumberOfMoves(), 2u);
	QCOMPARE(game.getBoard()->getCell(0, rows - 2), game.getBoard()->getEmptyToken());
	QCOMPARE(game.isUndoPossible(), true);

	game.undoLastMove();

	QCOMPARE(game.getNumberOfMoves(), 1u);
	QCOMPARE(game.getBoard()->getCell(1, rows - 1), game.getBoard()->getEmptyToken());
	QCOMPARE(game.isUndoPossible(), true);

	game.undoLastMove();

	QCOMPARE(game.getNumberOfMoves(), 0u);
	QCOMPARE(game.getBoard()->getCell(0, rows - 1), game.getBoard()->getEmptyToken());
	QCOMPARE(game.isUndoPossible(), false);
}

/**
 * Call methods in a wrong way to check whether they throw exceptions.
 */
void GameTest::makeMistakes()
{
	unsigned int columns = 3;
	unsigned int rows = 2;
	GameLogic::FourInALine::Game game(columns, rows, 1);

	try
	{
		game.undoLastMove();
		QFAIL("Attempting to undo a move when no move has been made yet should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		game.getWinner();
		QFAIL("Attempting to retrieve the winner of a game with no winner should throw an exception.");
	}
	catch(std::exception) {}

	try
	{
		game.makeMove(0);
		game.makeMove(0);
		game.makeMove(0);
		QFAIL("Attempting to drop a token in a full column should throw an exception.");
	}
	catch(std::exception) {}
}

/**
 * Creates games with time limits and tests whether the games are ended correctly when a player
 * times out.
 */
void GameTest::timeOutPlayer()
{
	unsigned int columns = 5;
	unsigned int rows = 5;
	GameLogic::FourInALine::Game game(columns, rows, 1);

	// Verify default values.

	QCOMPARE(game.getTimeLimit(), 0u);
	QCOMPARE(game.getTimeoutAction(), GameLogic::FourInALine::Game::TimeoutAction::DRAW_GAME);

	// Change them and check whether that worked.

	game.setTimeLimit(123);
	game.setTimeoutAction(GameLogic::FourInALine::Game::TimeoutAction::LOSE_GAME);

	QCOMPARE(game.getTimeLimit(), 123u);
	QCOMPARE(game.getTimeoutAction(), GameLogic::FourInALine::Game::TimeoutAction::LOSE_GAME);

	// Time out player and check whether he loses.

	game.makeTimeoutMove();

	QCOMPARE(game.isOver(), true);
	QCOMPARE(game.isDraw(), false);
	QCOMPARE(game.isTimeout(), true);
	QCOMPARE(game.isMovePossible(0u), false);
	QCOMPARE(game.getWinner(), 2u);
	QCOMPARE(game.getPlayerWhoTimedOut(), 1u);

	// Undo the last move.

	game.undoLastMove();

	QCOMPARE(game.isOver(), false);
	QCOMPARE(game.isDraw(), false);
	QCOMPARE(game.isTimeout(), false);
	QCOMPARE(game.isMovePossible(0u), true);

	// Time out player and check whether the game is a draw

	game.setTimeoutAction(GameLogic::FourInALine::Game::TimeoutAction::DRAW_GAME);
	game.makeTimeoutMove();

	QCOMPARE(game.isOver(), true);
	QCOMPARE(game.isDraw(), true);
	QCOMPARE(game.isTimeout(), true);
	QCOMPARE(game.isMovePossible(0u), false);
	QCOMPARE(game.getPlayerWhoTimedOut(), 1u);
}

/**
 * Creates two games and makes some moves, checks whether the method to find the player who did
 * the first move works.
 */
void GameTest::firstMove()
{
	GameLogic::FourInALine::Game game(5, 5, 1);

	QCOMPARE(game.getPlayerWhoMakesFirstMove(), 1u);

	game.makeMove(0u);

	QCOMPARE(game.getPlayerWhoMakesFirstMove(), 1u);

	game.makeMove(1u);

	QCOMPARE(game.getPlayerWhoMakesFirstMove(), 1u);

	GameLogic::FourInALine::Game anotherGame(4, 4, 2);

	QCOMPARE(anotherGame.getPlayerWhoMakesFirstMove(), 2u);

	game.makeMove(0u);

	QCOMPARE(anotherGame.getPlayerWhoMakesFirstMove(), 2u);
}

/**
 * Makes a few moves and computes the positions with computeMovePosition(), then checks whether the
 * returned positions are correct.
 */
void GameTest::checkPositions()
{
	GameLogic::FourInALine::Game game(5, 5, 1);

	game.makeMove(0);

	QCOMPARE(game.getBoard()->getCell(0, 4), GameLogic::FourInALine::Game::PLAYER_ONE);
	QCOMPARE(game.computeMovePosition(0).first, 0u);
	QCOMPARE(game.computeMovePosition(0).second, 4u);

	game.makeMove(0);

	QCOMPARE(game.getBoard()->getCell(0, 3), GameLogic::FourInALine::Game::PLAYER_TWO);
	QCOMPARE(game.computeMovePosition(1).first, 0u);
	QCOMPARE(game.computeMovePosition(1).second, 3u);

	game.makeMove(1);

	QCOMPARE(game.getBoard()->getCell(0, 4), GameLogic::FourInALine::Game::PLAYER_ONE);
	QCOMPARE(game.computeMovePosition(2).first, 1u);
	QCOMPARE(game.computeMovePosition(2).second, 4u);

	game.makeMove(0);

	QCOMPARE(game.getBoard()->getCell(0, 2), GameLogic::FourInALine::Game::PLAYER_TWO);
	QCOMPARE(game.computeMovePosition(3).first, 0u);
	QCOMPARE(game.computeMovePosition(3).second, 2u);

	// Is the first move still the same?

	QCOMPARE(game.computeMovePosition(0).first, 0u);
	QCOMPARE(game.computeMovePosition(0).second, 4u);
}

QTEST_MAIN(GameTest)
