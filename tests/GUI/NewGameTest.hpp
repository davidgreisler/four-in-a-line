#ifndef TESTS_GUI_NEWGAMETEST_HPP
#define TESTS_GUI_NEWGAMETEST_HPP

#include <QObject>
#include <QtTest/QTest>

/**
 * Tests for the new game dialog.
 */
class NewGameTest : public QObject
{
		Q_OBJECT

	private slots:
		void testNewGame();
		void testBordConfiguration();
		void testPlayerConfiguration();
		void testGameConfiguration();
		void testTimeLimitConfiguration();

};

#endif // TESTS_GUI_NEWGAMETEST_HPP
