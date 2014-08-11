#include "Board.hpp"
#include "../../../app/FourInALine.hpp"
#include "../../Settings/Sound.hpp"
#include "../../Settings/FourInALine.hpp"

#include <QPalette>
#include <QDebug>
#include <QVBoxLayout>
#include <QtQuickWidgets/QQuickWidget>
#include <QtQuick/QQuickItem>
#include <QMessageBox>

namespace GUI
{
namespace Widgets
{

/**
 * Creates a new game board widget.
 *
 * @param theme Theme name.
 * @param parent Parent widget.
 */
Board::Board(QString theme, QWidget* parent) :
    QWidget(parent)
{
	this->quickWidget = nullptr;
	this->movePlayer = nullptr;
	this->theme = theme;
	this->reloadQML = false;

	auto application = ::FourInALine::getInstance();
	auto soundSettings = application->getSettings()->getSoundSettings();

	this->connect(soundSettings, &::Settings::Sound::changed, this, &Board::updateSoundSettings);
	this->updateSoundSettings();

	this->setAutoFillBackground(true);

	QPalette palette = this->palette();
	palette.setColor(this->backgroundRole(), Qt::black);
	this->setPalette(palette);

	this->layout = new QVBoxLayout(this);
	this->layout->setSpacing(0);
	this->layout->setMargin(0);

	this->initializeQML();
}

/**
 * Frees all used resources.
 */
Board::~Board()
{

}

/**
 * Sets theme (will be loaded when next game is started).
 *
 * @param theme Theme name.
 */
void Board::setTheme(QString theme)
{
	if (theme == this->theme)
	{
		return;
	}

	this->theme = theme;

	// Check whether game is running and display message box informing user that the theme
	// will be loaded when the next game starts.

	if (!this->firstPlayer.isNull())
	{
		this->reloadQML = true;
		QMessageBox::information(this, tr("Theme will be loaded next game"),
		                      tr("The theme will be loaded when you start a new game."));
	}
	else
	{
		this->initializeQML();
	}
}

/**
 * Informs QML about new game.
 *
 * @param nColumns Number of columns.
 * @param nRows Number of rows.
 * @param firstPlayer The first player.
 * @param secondPlayer The second player.
 * @param hasTimeLimit Whether the game has a time limit or not.
 */
void Board::startNewGame(unsigned int nColumns, unsigned int nRows,
                         QSharedPointer<const ::Game::Players::AbstractPlayer> firstPlayer,
                         QSharedPointer<const ::Game::Players::AbstractPlayer> secondPlayer, bool hasTimeLimit)
{
	if (this->reloadQML)
	{
		this->initializeQML();
	}

	emit this->newGameStarted(nColumns, nRows, firstPlayer->getName(), secondPlayer->getName(), hasTimeLimit);
	this->firstPlayer = firstPlayer;
	this->secondPlayer = secondPlayer;

	qDebug() << "[" << this << "::startNewGame ] New game started with" << nColumns << "columns and"
	         << nRows << "rows.";
	qDebug() << "[" << this << "::startNewGame ] First player:" << firstPlayer->getName();
	qDebug() << "[" << this << "::startNewGame ] Second player:" << secondPlayer->getName();

	this->quickWidget->show();
}

/**
 * Informs QML that the game is over.
 *
 * @param draw When it is a draw true otherwise false.
 */
void Board::gameOver(bool draw)
{
	emit this->gameIsOver(draw);

	qDebug() << "[" << this << "::gameOver ] Game is over.";
}

/**
 * Informs QML that the game is not over anymore.
 */
void Board::gameNotOverAnymore()
{
	emit this->gameIsNotOverAnymore();

	qDebug() << "[" << this << "::gameNotOverAnymore ] Game is not over anymore.";
}

/**
 * Informs QML that the game has ended.
 */
void Board::endGame()
{
	emit this->gameEnded();

	this->firstPlayer.reset();
	this->secondPlayer.reset();

	qDebug() << "[" << this << "::endGame ] Game ended.";
}

/**
 * Informs QML that the given player can now make a move.
 *
 * @param player The player who can now make a move.
 */
void Board::startPlayerTurn(QSharedPointer<const ::Game::Players::AbstractPlayer> player)
{
	if (player == this->firstPlayer)
	{
		emit this->firstPlayerTurn();
	}
	else
	{
		emit this->secondPlayerTurn();
	}

	qDebug() << "[" << this << "::startPlayerTurn ] Start player turn:" << player->getName();
}

/**
 * Updates the time limit in the QML.
 *
 * @param timeLimit Time limit in seconds.
 * @param remainingTime Remaining time in seconds.
 */
void Board::updateTimeLimit(unsigned int timeLimit, unsigned int remainingTime)
{
	emit this->remainingTimeUpdated(timeLimit / 60, timeLimit % 60, remainingTime / 60, remainingTime % 60);

	qDebug() << "[" << this << "::updateTimeLimit ] Time remaining:" << remainingTime;
}

/**
 * Informs QML that the current player's turn has ended.
 */
void Board::endPlayerTurn()
{
	emit this->playerTurnEnded();

	qDebug() << "[" << this << "::endPlayerTurn ] End player turn.";
}

/**
 * Informs QML that a move was made.
 *
 * @param x X coordinate of the cell.
 * @param y Y coordinate of the cell.
 * @param player The player who made the move.
 */
void Board::makeMove(unsigned int x, unsigned int y, QSharedPointer<const ::Game::Players::AbstractPlayer> player)
{
	emit this->tokenDropped(x, y, player->getPlayer());

	qDebug() << "[" << this << "::makeMove ] Player " << player->getName()
	         << "dropped token in" << x;
}

/**
 * Informs QML that a cell should be made empty.
 *
 * @param x X coordinate of the cell.
 * @param y Y coordinate of the cell.
 */
void Board::makeCellEmpty(unsigned int x, unsigned int y)
{
	emit this->tokenRemoved(x, y);

	qDebug() << "[" << this << "::makeCellEmpty ] Make cell empty, x:" << x << "y:" << y;
}

/**
 * Requests a move from the QML.
 *
 * @param availableColumns Vector containing available column numbers.
 * @param player Which player makes the move.
 */
void Board::requestMove(std::vector<unsigned int> availableColumns, Game::Players::Human* player)
{
	QVariantList availableColumnsList;
	for (auto i = availableColumns.cbegin(); i < availableColumns.cend(); ++i)
	{
		availableColumnsList.append(*i);
	}

	bool allowKeyboard = false;
	bool allowMouse = false;
	auto controls = player->getControls();

	if (controls == ::Game::Players::Human::Controls::KEYBOARD)
	{
		allowKeyboard = true;
	}
	else if (controls == ::Game::Players::Human::Controls::MOUSE)
	{
		allowMouse = true;
	}
	else if (controls == ::Game::Players::Human::Controls::MOUSE_AND_KEYBOARD)
	{
		allowKeyboard = true;
		allowMouse = true;
	}

	this->movePlayer = player;
	emit this->moveRequested(availableColumnsList, allowKeyboard, allowMouse);

	qDebug() << "[" << this << "::requestMove ] Move requested.";
}

/**
 * Aborts move request.
 */
void Board::abortRequestMove()
{
	emit this->moveRequestAborted();
	this->movePlayer = nullptr;

	qDebug() << "[" << this << "::abortRequestMove ] Move request aborted.";
}

/**
 * Informs QML that column hints should be shown.
 *
 * @param columnScores Vector containing column scores.
 */
void Board::showColumnHints(std::vector<int> columnScores)
{
	QVariantList columnScoreList;
	for (auto i = columnScores.cbegin(); i < columnScores.cend(); ++i)
	{
		columnScoreList.append(*i);
	}

	emit this->columnHintsShown(columnScoreList);

	qDebug() << "[" << this << "::showColumnHints ] Showing column hints.";
}

/**
 * Informs QML that the given cell should be highlighted/not highlighted.
 *
 * @param x X coordinate of the cell.
 * @param y Y coordinate of the cell.
 * @param highlight Whether it should be highlighted or not.
 */
void Board::setCellHighlighted(unsigned int x, unsigned int y, bool highlight)
{
	emit this->cellHighlightedChanged(x, y, highlight);
}

/**
 * Reads sound settings from sound settings object.
 */
void Board::updateSoundSettings()
{
	auto application = ::FourInALine::getInstance();
	auto soundSettings = application->getSettings()->getSoundSettings();

	this->setSoundMuted(!soundSettings->isSoundEnabled());
	this->setSoundVolume(soundSettings->getVolume());
}

/**
 * Informs the human player about the move made by the user.
 *
 * Invoked when the user/player made a move.
 *
 * @param columnNo Column number where the user wants to drop the token.
 */
void Board::playerMadeMove(int columnNo)
{
	if (this->movePlayer == nullptr)
	{
		qDebug() << "[" << this << "] ERROR: Player who made the move is not set.";
	}

	// The userMadeMove() method will usually inform the game controller about the move
	// which will consequently request a move from the other player who (in case the other
	// player is a human player too) will call Board::requestMove which sets the movePlayer
	// attribute to the other player.
	//
	// Therefore movePlayer has to be set to nullptr BEFORE calling userMadeMove!

	auto player = this->movePlayer;
	this->movePlayer = nullptr;
	player->userMadeMove(columnNo);

	qDebug() << "[" << this << "::playerMadeMove ] Player dropped token in column" << columnNo;
}

/**
 * Loads theme and initializes QML view.
 */
void Board::initializeQML()
{
	if (nullptr != this->quickWidget)
	{
		// Deleting the quickWidget crashes the program.
		// I think this is a Qt bug.
		/// @todo Try again with Qt 5.4.

		QObject* rootObject = this->quickWidget->rootObject();
		QObject* gameController = rootObject->findChild<QObject*>("gameController");
		this->disconnect(gameController, SIGNAL(playerMadeMove(int)), this, SLOT(playerMadeMove(int)));
		this->layout->removeWidget(this->quickWidget);
	}

	QMap<QString, QString> themeFilenameMap;
	themeFilenameMap["standard"] = "StandardTheme.qml";
	themeFilenameMap["dark"] = "DarkTheme.qml";
	themeFilenameMap["white"] = "WhiteTheme.qml";

	qDebug() << "[" << this << "::initializeQML ] Loading theme:" << this->theme << "from" << themeFilenameMap[this->theme];

	this->quickWidget = new QQuickWidget(this);
	this->quickWidget->rootContext()->setContextProperty("Game", this);
	this->quickWidget->setSource(QUrl(QString("qrc:/qml/%1").arg(themeFilenameMap[this->theme])));
	this->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

	QObject* rootObject = this->quickWidget->rootObject();
	QObject* gameController = rootObject->findChild<QObject*>("gameController");
	this->connect(gameController, SIGNAL(playerMadeMove(int)), this, SLOT(playerMadeMove(int)));

	this->layout->addWidget(this->quickWidget);
	this->reloadQML = false;
}

/**
 * Returns whether the sound is muted or not.
 *
 * @return When it is muted true, otherwise false.
 */
bool Board::isSoundMuted() const
{
	return this->soundMuted;
}

/**
 * Sets the sound to muted/unmuted.
 *
 * @param value True for muted, otherwise false.
 */
void Board::setSoundMuted(bool value)
{
	this->soundMuted = value;

	emit this->soundMutedChanged();
}

/**
 * Returns the current sound volume.
 *
 * @return Sound volume (0 - 1).
 */
float Board::getSoundVolume() const
{
	return this->soundVolume;
}

/**
 * Sets the sound volume to the given value.
 *
 * @param value New volume (0 - 1).
 */
void Board::setSoundVolume(float value)
{
	this->soundVolume = value;

	emit this->soundVolumeChanged();
}

}
}
