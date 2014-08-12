#include "NewGameTest.hpp"
#include "../../src/GUI/Dialogs/NewGame.hpp"
#include "../../src/Game/Game.hpp"
#include "../../src/Game/Players/Factory.hpp"
#include "../../src/Game/Players/ArtificialIntelligence.hpp"

#include <QSpinBox>
#include <QQuickWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>

/**
 * Tests creating a new game.
 */
void NewGameTest::testNewGame()
{
	auto newGameDialog = new ::GUI::Dialogs::NewGame(0);
	auto newGameButton = newGameDialog->findChild<QPushButton*>("newGameButton");

	QTest::mouseClick(newGameButton, Qt::LeftButton, Qt::NoModifier, QPoint(5, 5), 50);

	QCOMPARE(static_cast<QDialog::DialogCode>(newGameDialog->result()), QDialog::Accepted);

	auto playerFactory = ::Game::Players::Factory(0);

	auto result = newGameDialog->createGame(playerFactory);

	QVERIFY(!result.isNull());
}

/**
 * Tests the board configuration.
 */
void NewGameTest::testBordConfiguration()
{
	auto newGameDialog = new ::GUI::Dialogs::NewGame(0);
	auto numberOfRowsWidget = newGameDialog->findChild<QSpinBox*>("numberOfRowsWidget");
	auto numberOfColumnsWidget = newGameDialog->findChild<QSpinBox*>("numberOfColumnsWidget");
	auto newGameButton = newGameDialog->findChild<QPushButton*>("newGameButton");

	QTest::keyClick(numberOfRowsWidget, Qt::Key_Backspace);
	QTest::keyClick(numberOfRowsWidget, Qt::Key_Delete);
	QTest::keyClick(numberOfRowsWidget, Qt::Key_Backspace);
	QTest::keyClick(numberOfRowsWidget, Qt::Key_8, Qt::NoModifier, 100);

	QTest::keyClick(numberOfColumnsWidget, Qt::Key_Backspace);
	QTest::keyClick(numberOfColumnsWidget, Qt::Key_Delete);
	QTest::keyClick(numberOfColumnsWidget, Qt::Key_Backspace);
	QTest::keyClick(numberOfColumnsWidget, Qt::Key_6, Qt::NoModifier, 100);

	QTest::mouseClick(newGameButton, Qt::LeftButton, Qt::NoModifier, QPoint(5, 5), 50);

	QCOMPARE(static_cast<QDialog::DialogCode>(newGameDialog->result()), QDialog::Accepted);

	auto playerFactory = ::Game::Players::Factory(0);

	auto result = newGameDialog->createGame(playerFactory);

	QCOMPARE(result->getGameLogic()->getBoard()->getNumberOfRows(), 8u);
	QCOMPARE(result->getGameLogic()->getBoard()->getNumberOfColumns(), 6u);
}

/**
 * Tests player configuration.
 */
void NewGameTest::testPlayerConfiguration()
{
	auto newGameDialog = new ::GUI::Dialogs::NewGame(0);
	auto newGameButton = newGameDialog->findChild<QPushButton*>("newGameButton");
	auto firstPlayerConfiguration = newGameDialog->findChild<QWidget*>("firstPlayerConfigurationWidget");
	auto firstPlayerNameEdit = firstPlayerConfiguration->findChild<QLineEdit*>("playerNameEdit");
	auto firstPlayerTypeComboBox = firstPlayerConfiguration->findChild<QComboBox*>("playerTypeComboBox");
	auto firstPlayerLevelOfDifficultyComboBox = firstPlayerConfiguration->findChild<QComboBox*>("levelOfDifficultyComboBox");
	auto secondPlayerConfiguration = newGameDialog->findChild<QWidget*>("secondPlayerConfigurationWidget");
	auto secondPlayerNameEdit = secondPlayerConfiguration->findChild<QLineEdit*>("playerNameEdit");
	auto secondPlayerControlsComboBox = secondPlayerConfiguration->findChild<QComboBox*>("controlsComboBox");

	QTest::mouseClick(firstPlayerTypeComboBox, Qt::LeftButton, Qt::NoModifier, QPoint(5, 5), 50);
	QTest::keyClick(firstPlayerTypeComboBox, Qt::Key_Down);
	QTest::keyClick(firstPlayerTypeComboBox, Qt::Key_Enter);

	for (int i = 0; i < 30; ++i)
	{
		QTest::keyClick(firstPlayerNameEdit, Qt::Key_Delete, Qt::NoModifier);
		QTest::keyClick(firstPlayerNameEdit, Qt::Key_Backspace, Qt::NoModifier);
		QTest::keyClick(secondPlayerNameEdit, Qt::Key_Delete, Qt::NoModifier);
		QTest::keyClick(secondPlayerNameEdit, Qt::Key_Backspace, Qt::NoModifier);
	}

	QTest::mouseClick(firstPlayerLevelOfDifficultyComboBox, Qt::LeftButton, Qt::NoModifier, QPoint(5, 5), 50);

	for (int i = 0; i < 5; ++i)
	{
		QTest::keyClick(firstPlayerLevelOfDifficultyComboBox, Qt::Key_Down, Qt::NoModifier, 15);
	}

	QTest::keyClick(firstPlayerLevelOfDifficultyComboBox, Qt::Key_Enter);

	QTest::mouseClick(secondPlayerControlsComboBox, Qt::LeftButton, Qt::NoModifier, QPoint(5, 5), 50);

	for (int i = 0; i < 5; ++i)
	{
		QTest::keyClick(secondPlayerControlsComboBox, Qt::Key_Down, Qt::NoModifier, 15);
	}

	QTest::keyClick(secondPlayerControlsComboBox, Qt::Key_Enter);

	QTest::keyClicks(firstPlayerNameEdit, "abcde123", Qt::NoModifier, 25);
	QTest::keyClicks(secondPlayerNameEdit, "123abc", Qt::NoModifier, 25);

	QTest::mouseClick(newGameButton, Qt::LeftButton, Qt::NoModifier, QPoint(5, 5), 50);

	QCOMPARE(static_cast<QDialog::DialogCode>(newGameDialog->result()), QDialog::Accepted);

	auto playerFactory = ::Game::Players::Factory(0);

	auto result = newGameDialog->createGame(playerFactory);

	auto firstPlayer = qSharedPointerDynamicCast< ::Game::Players::ArtificialIntelligence>(result->getFirstPlayer());
	auto secondPlayer = qSharedPointerDynamicCast<const ::Game::Players::Human>(result->getSecondPlayer());

	QCOMPARE(result->getFirstPlayer()->getName(), QString("abcde123"));
	QVERIFY(firstPlayer != nullptr);
	QCOMPARE(firstPlayer->getLevelOfDifficulty(), ::Game::Players::ArtificialIntelligence::LevelOfDifficulty::CHALLENGE);

	QCOMPARE(result->getSecondPlayer()->getName(), QString("123abc"));
	QVERIFY(secondPlayer != nullptr);
	QCOMPARE(secondPlayer->getControls(), ::Game::Players::Human::Controls::MOUSE_AND_KEYBOARD);
}

/**
 * Tests first move/game options.
 */
void NewGameTest::testGameConfiguration()
{
	auto playerFactory = ::Game::Players::Factory(0);
	auto newGameDialog = new ::GUI::Dialogs::NewGame(0);
	auto newGameButton = newGameDialog->findChild<QPushButton*>("newGameButton");
	auto firstMovePlayerOneRadioButton = newGameDialog->findChild<QRadioButton*>("firstMovePlayerOneRadio");
	auto firstMovePlayerTwoRadioButton = newGameDialog->findChild<QRadioButton*>("firstMovePlayerTwoRadio");
	auto saveHighscoreCheckBox = newGameDialog->findChild<QCheckBox*>("saveHighscoreCheckBox");
	auto allowUndoCheckBox = newGameDialog->findChild<QCheckBox*>("allowUndoCheckBox");
	auto allowHintCheckBox = newGameDialog->findChild<QCheckBox*>("allowHintCheckBox");

	// Set first player to AI, so that all controls are available.

	auto firstPlayerConfiguration = newGameDialog->findChild<QWidget*>("firstPlayerConfigurationWidget");
	auto firstPlayerTypeComboBox = firstPlayerConfiguration->findChild<QComboBox*>("playerTypeComboBox");

	QTest::mouseClick(firstPlayerTypeComboBox, Qt::LeftButton, Qt::NoModifier, QPoint(5, 5), 50);
	QTest::keyClick(firstPlayerTypeComboBox, Qt::Key_Down);
	QTest::keyClick(firstPlayerTypeComboBox, Qt::Key_Enter);

	// Test all options off, player 1 makes first move.

	firstMovePlayerOneRadioButton->click();
	saveHighscoreCheckBox->setCheckState(Qt::Unchecked);
	allowHintCheckBox->setCheckState(Qt::Unchecked);
	allowUndoCheckBox->setCheckState(Qt::Unchecked);

	QTest::mouseClick(newGameButton, Qt::LeftButton, Qt::NoModifier, QPoint(5, 5), 50);

	QCOMPARE(static_cast<QDialog::DialogCode>(newGameDialog->result()), QDialog::Accepted);

	auto result = newGameDialog->createGame(playerFactory);

	QCOMPARE(result->isUndoAllowed(), false);
	QCOMPARE(result->isSavingHighscore(), false);
	QCOMPARE(result->isHintAllowed(), false);
	QCOMPARE(result->getStartingPlayer()->getPlayer(), 1u);

	// Test all options on, player 2 makes first move.

	newGameDialog = new ::GUI::Dialogs::NewGame(0);
	newGameButton = newGameDialog->findChild<QPushButton*>("newGameButton");
	firstMovePlayerOneRadioButton = newGameDialog->findChild<QRadioButton*>("firstMovePlayerOneRadio");
	firstMovePlayerTwoRadioButton = newGameDialog->findChild<QRadioButton*>("firstMovePlayerTwoRadio");
	saveHighscoreCheckBox = newGameDialog->findChild<QCheckBox*>("saveHighscoreCheckBox");
	allowUndoCheckBox = newGameDialog->findChild<QCheckBox*>("allowUndoCheckBox");
	allowHintCheckBox = newGameDialog->findChild<QCheckBox*>("allowHintCheckBox");

	// Set first player to AI, so that all controls are available.

	firstPlayerConfiguration = newGameDialog->findChild<QWidget*>("firstPlayerConfigurationWidget");
	firstPlayerTypeComboBox = firstPlayerConfiguration->findChild<QComboBox*>("playerTypeComboBox");

	QTest::mouseClick(firstPlayerTypeComboBox, Qt::LeftButton, Qt::NoModifier, QPoint(5, 5), 50);
	QTest::keyClick(firstPlayerTypeComboBox, Qt::Key_Down);
	QTest::keyClick(firstPlayerTypeComboBox, Qt::Key_Enter);

	firstMovePlayerTwoRadioButton->click();
	allowHintCheckBox->setCheckState(Qt::Checked);
	allowUndoCheckBox->setCheckState(Qt::Checked);

	QTest::mouseClick(newGameButton, Qt::LeftButton, Qt::NoModifier, QPoint(5, 5), 50);

	QCOMPARE(static_cast<QDialog::DialogCode>(newGameDialog->result()), QDialog::Accepted);

	result = newGameDialog->createGame(playerFactory);

	QCOMPARE(result->isUndoAllowed(), true);

	// Highscores are not saved in AI games.

	QCOMPARE(result->isSavingHighscore(), false);
	QCOMPARE(result->isHintAllowed(), true);
	QCOMPARE(result->getStartingPlayer()->getPlayer(), 2u);
}

/**
 * Tests the time limit configuration.
 */
void NewGameTest::testTimeLimitConfiguration()
{
	auto newGameDialog = new ::GUI::Dialogs::NewGame(0);
	auto newGameButton = newGameDialog->findChild<QPushButton*>("newGameButton");
	auto timeLimitEditWidget = newGameDialog->findChild<QSpinBox*>("timeLimitEdit");
	auto timeLimitActionRandomRadioButton = newGameDialog->findChild<QRadioButton*>("timeLimitRandomRadio");

	QTest::mouseDClick(timeLimitEditWidget, Qt::LeftButton, Qt::NoModifier, QPoint(5, 5), 50);
	QTest::keyClick(timeLimitEditWidget, Qt::Key_Delete);
	QTest::keyClick(timeLimitEditWidget, Qt::Key_Delete);
	QTest::keyClick(timeLimitEditWidget, Qt::Key_Delete);

	timeLimitActionRandomRadioButton->click();

	QTest::keyClick(timeLimitEditWidget, Qt::Key_4, Qt::NoModifier, 10);
	QTest::keyClick(timeLimitEditWidget, Qt::Key_5, Qt::NoModifier, 10);
	QTest::keyClick(timeLimitEditWidget, Qt::Key_6, Qt::NoModifier, 10);

	QTest::mouseClick(newGameButton, Qt::LeftButton, Qt::NoModifier, QPoint(5, 5), 50);

	QCOMPARE(static_cast<QDialog::DialogCode>(newGameDialog->result()), QDialog::Accepted);

	auto playerFactory = ::Game::Players::Factory(0);

	auto result = newGameDialog->createGame(playerFactory);

	QCOMPARE(result->getGameLogic()->hasTimeLimit(), true);
	QCOMPARE(result->getGameLogic()->getTimeLimit(), 456u);
	QCOMPARE(result->getGameLogic()->getTimeoutAction(), ::GameLogic::FourInALine::Game::TimeoutAction::RANDOM_MOVE);
}

QTEST_MAIN(NewGameTest)
