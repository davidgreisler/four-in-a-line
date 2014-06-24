#include "GameOver.hpp"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QEvent>

namespace GUI
{
namespace Dialogs
{

/**
 * Creates a new game over dialog.
 *
 * It is possible to specify which actions should be available to the user by OR-ing the
 * actions together. Buttons for unavailable actions are not shown.
 *
 * The game over dialog knows 3 game results:
 * * Player won: The player with the given player name won the game.
 * * Draw, timeout: The player with the given player name timed out, the game is a draw.
 * * Draw, board full: The board is full, the game is a draw. The player name is not used.
 *
 * @param availableActions Which actions should be available?
 * @param result Result of the game.
 * @param playerName Name of the player who won/timed out.
 * @param parent Parent widget.
 */
GameOver::GameOver(int availableActions, Result result, QString playerName, QWidget *parent) :
	QDialog(parent), result(result), playerName(playerName), undoLastMoveButton(nullptr),
	saveReplayButton(nullptr), playAgainButton(nullptr), newGameButton(nullptr),
	acceptButton(nullptr)
{
	this->layout = new QVBoxLayout(this);
	this->setLayout(this->layout);

	this->textLabel = new QLabel(this);
	this->textLabel->setAlignment(Qt::AlignCenter);
	this->layout->addWidget(this->textLabel);

	this->buttonBox = new QDialogButtonBox(this);
	this->layout->addWidget(this->buttonBox);

	// Create buttons.

	if (availableActions & static_cast<int>(Action::UNDO_LAST_MOVE))
	{
		this->undoLastMoveButton = new QPushButton(this);
		this->buttonBox->addButton(this->undoLastMoveButton, QDialogButtonBox::ActionRole);
		this->connect(this->undoLastMoveButton, &QPushButton::clicked,
					  this, &GameOver::undoLastMove);
	}

	if (availableActions & static_cast<int>(Action::SAVE_REPLAY))
	{
		this->saveReplayButton = new QPushButton(this);
		this->buttonBox->addButton(this->saveReplayButton, QDialogButtonBox::ActionRole);
		this->connect(this->saveReplayButton, &QPushButton::clicked,
					  this, &GameOver::saveReplay);
	}

	if (availableActions & static_cast<int>(Action::PLAY_AGAIN))
	{
		this->playAgainButton = new QPushButton(this);
		this->buttonBox->addButton(this->playAgainButton, QDialogButtonBox::ActionRole);
		this->connect(this->playAgainButton, &QPushButton::clicked,
					  this, &GameOver::playAgain);
	}

	if (availableActions & static_cast<int>(Action::NEW_GAME))
	{
		this->newGameButton = new QPushButton(this);
		this->buttonBox->addButton(this->newGameButton, QDialogButtonBox::ActionRole);
		this->connect(this->newGameButton, &QPushButton::clicked,
					  this, &GameOver::newGame);
	}

	this->acceptButton = new QPushButton(this);
	this->buttonBox->addButton(this->acceptButton, QDialogButtonBox::AcceptRole);
	this->connect(this->acceptButton, &QPushButton::clicked, this, &GameOver::accept);

	this->retranslateUI();
}

/**
 * Frees all used resources.
 */
GameOver::~GameOver()
{

}

/**
 * Retranslates all strings.
 */
void GameOver::retranslateUI()
{
	this->setWindowTitle(this->tr("Game over"));

	switch (this->result)
	{
		case Result::PLAYER_WON:
			this->textLabel->setText(QString(this->tr(
				"<span style=\"font-weight:bold;font-size:200%;color:red;\">"
				"%1 has won the game!</span>").arg(this->playerName)));
			break;

		case Result::DRAW_BOARD_FULL:
			this->textLabel->setText(this->tr(
				"<span style=\"font-weight:bold;font-size:200%;color:blue;\">"
				"Draw! The board is full.</span>"));
			break;

		case Result::DRAW_TIMEOUT:
			this->textLabel->setText(QString(this->tr(
				"<span style=\"font-weight:bold;font-size:200%;color:blue;\">"
				"Draw! %1 has exceeded the time limit for making a "
				"move.</span>").arg(this->playerName)));
			break;

		default:
			throw std::runtime_error("Unknown game result.");
	}

	if (nullptr != this->undoLastMoveButton)
	{
		this->undoLastMoveButton->setText(this->tr("Undo last move"));
	}

	if (nullptr != this->saveReplayButton)
	{
		this->saveReplayButton->setText(this->tr("Save replay"));
	}

	if (nullptr != this->playAgainButton)
	{
		this->playAgainButton->setText(this->tr("Play again"));
	}

	if (nullptr != this->newGameButton)
	{
		this->newGameButton->setText(this->tr("New game"));
	}

	this->acceptButton->setText(this->tr("OK"));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
void GameOver::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	QDialog::changeEvent(event);
}

}
}
