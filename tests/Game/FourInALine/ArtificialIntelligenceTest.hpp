#ifndef TESTS_GAME_FOUR_IN_A_LINE_ARTIFICIALINTELLIGENCETEST_HPP
#define TESTS_GAME_FOUR_IN_A_LINE_ARTIFICIALINTELLIGENCETEST_HPP

#include <QtTest/QTest>

/**
 * Units tests for the Game::FourInALine::ArtificialIntelligence class.
 */
class ArtificialIntelligenceTest : public QObject
{
		Q_OBJECT

		private slots:
			void obviousWin();
			void preventOpponentWin();
			void basicTest();
};

#endif // TESTS_GAME_FOUR_IN_A_LINE_ARTIFICIALINTELLIGENCETEST_HPP
