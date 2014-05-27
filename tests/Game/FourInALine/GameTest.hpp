#ifndef TESTS_GAME_FOUR_IN_A_LINE_GAMETEST_HPP
#define TESTS_GAME_FOUR_IN_A_LINE_GAMETEST_HPP

#include <QtTest/QTest>

/**
 * Unit tests for the Game::FourInALine::Game class.
 */
class GameTest : public QObject
{
		Q_OBJECT

	private slots:
		void createGame();
		void playDraw();
		void playAndWin();
		void checkReplay();
		void undoMove();
		void makeMistakes();

};

#endif // TESTS_GAME_FOUR_IN_A_LINE_GAMETEST_HPP
