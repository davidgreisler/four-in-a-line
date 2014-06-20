#ifndef TESTS_GAME_FOUR_IN_A_LINE_ARTIFICIALINTELLIGENCETEST_HPP
#define TESTS_GAME_FOUR_IN_A_LINE_ARTIFICIALINTELLIGENCETEST_HPP

#include "../../../src/Game/FourInALine/Game.hpp"
#include "../../../src/Game/FourInALine/AsynchronousArtificialIntelligence.hpp"

#include <QtTest/QTest>

/**
 * Units tests for the Game::FourInALine::AsynchronousArtificialIntelligence class.
 */
class AsynchronousArtificialIntelligenceTest : public QObject
{
		Q_OBJECT

	private slots:
		void obviousWin();
		void preventOpponentWin();
		void basicTest();
		void testCancel();
};

#endif // TESTS_GAME_FOUR_IN_A_LINE_ARTIFICIALINTELLIGENCETEST_HPP
