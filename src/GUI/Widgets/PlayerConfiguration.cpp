#include "PlayerConfiguration.hpp"

#include <QEvent>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QFormLayout>
#include <QVariant>

#include <stdexcept>

namespace GUI
{
namespace Widgets
{

/**
 * Creates a new player configuration widget.
 *
 * @param playerId Player id to show in the title of the widget and used by the game engine.
 * @param parent Parent widget.
 */
PlayerConfiguration::PlayerConfiguration(PlayerIdType playerId, QWidget* parent) :
    QGroupBox(parent), playerId(playerId)
{
	this->formLayout = new QFormLayout(this);
	this->setLayout(this->formLayout);

	this->playerNameLabel = new QLabel(this);
	this->playerNameEdit = new QLineEdit(this);
	this->formLayout->addRow(this->playerNameLabel, this->playerNameEdit);

	this->playerTypeLabel = new QLabel(this);
	this->playerTypeComboBox = new QComboBox(this);
	this->formLayout->addRow(this->playerTypeLabel, this->playerTypeComboBox);

	this->controlsLabel = new QLabel(this);
	this->controlsComboBox = new QComboBox(this);
	this->formLayout->addRow(this->controlsLabel, this->controlsComboBox);

	this->levelOfDifficultyLabel = new QLabel(this);
	this->levelOfDifficultyComboBox = new QComboBox(this);
	this->formLayout->addRow(this->levelOfDifficultyLabel, this->levelOfDifficultyComboBox);

	this->hostAddressLabel = new QLabel(this);
	this->hostAddressEdit = new QLineEdit(this);
	this->formLayout->addRow(this->hostAddressLabel, this->hostAddressEdit);

	// Sets up combo box items.

	this->retranslateUI();

	// Set defaults after the combo boxes are set up.

	this->playerNameEdit->setText(QString(this->tr("Player %1")).arg(playerId));
	this->playerTypeComboBox->setCurrentIndex(0);
	this->controlsComboBox->setCurrentIndex(2);
	this->levelOfDifficultyComboBox->setCurrentIndex(2);

	this->updatePlayerType();

	this->connect(this->playerTypeComboBox,
	              static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
	              this, &PlayerConfiguration::updatePlayerType);
	this->connect(this->playerTypeComboBox,
	              static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
	              this, &PlayerConfiguration::configurationChanged);
	this->connect(this->playerNameEdit, &QLineEdit::textChanged,
	              this, &PlayerConfiguration::configurationChanged);
	this->connect(this->hostAddressEdit, &QLineEdit::textChanged,
	              this, &PlayerConfiguration::configurationChanged);
	this->connect(this->controlsComboBox,
	              static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
	              this, &PlayerConfiguration::configurationChanged);
	this->connect(this->levelOfDifficultyComboBox,
	              static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
	              this, &PlayerConfiguration::configurationChanged);
}

/**
 * Frees all used resources.
 */
PlayerConfiguration::~PlayerConfiguration()
{

}

/**
 * Sets the player id used by the game engine and displayed in the widget's title.
 *
 * @param playerId Player id.
 */
void PlayerConfiguration::setPlayerId(::GameLogic::FourInALine::Game::PlayerType playerId)
{
	this->playerId = playerId;
}

/**
 * Returns the player id used by the game engine and displayed in the widget's title.
 *
 * @return Player id.
 */
::GameLogic::FourInALine::Game::PlayerType PlayerConfiguration::getPlayerId() const
{
	return this->playerId;
}

/**
 * Set the player name to the given name.
 *
 * @param name New player name
 */
void PlayerConfiguration::setPlayerName(const QString& name)
{
	this->playerNameEdit->setText(name);
}

/**
 * Returns the player name.
 *
 * @return Player name.
 */
QString PlayerConfiguration::getPlayerName() const
{
	return this->playerNameEdit->text();
}

/**
 * Set the player type to the given one.
 *
 * @param playerType Player type.
 */
void PlayerConfiguration::setPlayerType(PlayerConfiguration::PlayerType playerType)
{
	int index = this->playerTypeComboBox->findData(QVariant::fromValue(playerType));

	if (-1 != index)
	{
		this->playerTypeComboBox->setCurrentIndex(index);
	}
}

/**
 * Returns the currently selected player type.
 *
 * @return Player type.
 */
PlayerConfiguration::PlayerType PlayerConfiguration::getPlayerType() const
{
	QVariant itemData = this->playerTypeComboBox->currentData();

	return itemData.value<PlayerConfiguration::PlayerType>();
}

/**
 * Sets the level of difficulty for the artificial intelligence.
 *
 * @param levelOfDifficulty Level of difficulty.
 */
void PlayerConfiguration::setLevelOfDifficulty(::Game::Players::ArtificialIntelligence::LevelOfDifficulty levelOfDifficulty)
{
	int index = this->levelOfDifficultyComboBox->findData(QVariant::fromValue(levelOfDifficulty));

	if (-1 != index)
	{
		this->levelOfDifficultyComboBox->setCurrentIndex(index);
	}
}

/**
 * Returns the level of difficulty for the artificial intelligence.
 *
 * @return Level of difficulty.
 */
::Game::Players::ArtificialIntelligence::LevelOfDifficulty PlayerConfiguration::getLevelOfDifficulty() const
{
	QVariant itemData =  this->levelOfDifficultyComboBox->currentData();

	return itemData.value< ::Game::Players::ArtificialIntelligence::LevelOfDifficulty>();
}

/**
 * Sets the controls for the human player.
 *
 * @param controls Human player controls.
 */
void PlayerConfiguration::setControls(::Game::Players::Human::Controls controls)
{
	int index = this->controlsComboBox->findData(QVariant::fromValue(controls));

	if (-1 != index)
	{
		this->controlsComboBox->setCurrentIndex(index);
	}
}

/**
 * Returns the selected controls for the human player.
 *
 * @return Controls for the human player.
 */
::Game::Players::Human::Controls PlayerConfiguration::getControls() const
{
	QVariant itemData =  this->controlsComboBox->currentData();

	return itemData.value< ::Game::Players::Human::Controls>();
}

/**
 * Uses the given player factory to construct a new player according to the settings made by the
 * user.
 *
 * @param factory Player factory used to create the player.
 * @return A new player object.
 */
QSharedPointer< ::Game::Players::AbstractPlayer> PlayerConfiguration::createPlayer(Game::Players::Factory& factory) const
{
	QSharedPointer< ::Game::Players::AbstractPlayer> result;
	PlayerType playerType = this->playerTypeComboBox->currentData().value<PlayerType>();
	switch (playerType)
	{
		case PlayerType::HUMAN_PLAYER:
			result = factory.createHumanPlayer(this->getPlayerId(), this->getPlayerName(),
			                                   this->getControls());
			break;

		case PlayerType::ARTIFICIAL_INTELLIGENCE:
			result = factory.createArtificialIntelligencePlayer(this->getPlayerId(),
			                                                    this->getPlayerName(),
			                                                    this->getLevelOfDifficulty());
			break;

		case PlayerType::NETWORK_PLAYER:
			result = factory.createNetworkPlayer(this->getPlayerId(), this->getPlayerName());
			break;

		default:
			throw std::runtime_error("Unknown player type.");
	}

	return result;
}

/**
 * Returns whether the player configuration is valid.
 *
 * This checks whether the player name is not empty, etc.
 *
 * @return When it is valid true, otherwise false.
 */
bool PlayerConfiguration::isValid() const
{
	if (this->playerNameEdit->text().isEmpty())
	{
		return false;
	}

	if (this->playerTypeComboBox->currentData().value<PlayerType>() == PlayerType::NETWORK_PLAYER)
	{
		// @todo Implement network player and remove this.

		return false;
	}

	return true;
}

/**
 * Hides all rows that are not applicable to the selected player type.
 */
void PlayerConfiguration::updatePlayerType()
{
	// Hide all player type specific rows.

	this->controlsLabel->hide();
	this->controlsComboBox->hide();
	this->formLayout->removeWidget(this->controlsLabel);
	this->formLayout->removeWidget(this->controlsComboBox);

	this->hostAddressLabel->hide();
	this->hostAddressEdit->hide();
	this->formLayout->removeWidget(this->hostAddressLabel);
	this->formLayout->removeWidget(this->hostAddressEdit);

	this->levelOfDifficultyLabel->hide();
	this->levelOfDifficultyComboBox->hide();
	this->formLayout->removeWidget(this->levelOfDifficultyLabel);
	this->formLayout->removeWidget(this->levelOfDifficultyComboBox);

	// Who rows for selected player type.

	PlayerType playerType = this->playerTypeComboBox->currentData().value<PlayerType>();
	switch (playerType)
	{
		case PlayerType::HUMAN_PLAYER:
			this->controlsLabel->show();
			this->controlsComboBox->show();
			this->formLayout->addRow(this->controlsLabel, this->controlsComboBox);
			break;

		case PlayerType::ARTIFICIAL_INTELLIGENCE:
			this->levelOfDifficultyLabel->show();
			this->levelOfDifficultyComboBox->show();
			this->formLayout->addRow(this->levelOfDifficultyLabel, this->levelOfDifficultyComboBox);
			break;

		case PlayerType::NETWORK_PLAYER:
			this->hostAddressLabel->show();
			this->hostAddressEdit->show();
			this->formLayout->addRow(this->hostAddressLabel, this->hostAddressEdit);
			break;

		default:
			throw std::runtime_error("Unknown player type.");
	}

	emit this->playerTypeChanged(playerType);
}

/**
 * Clears the controls combo box and adds newly translated items again, the index will be restored.
 */
void PlayerConfiguration::setupControlsComboBox()
{
	// Save index to restore it later.

	int index = this->controlsComboBox->currentIndex();

	this->controlsComboBox->clear();

	QIcon mouseIcon;
	mouseIcon.addFile(":/icons/fatcow/16x16/mouse.png", QSize(16, 16));
	mouseIcon.addFile(":/icons/fatcow/32x32/mouse.png", QSize(32, 32));
	this->controlsComboBox->addItem(mouseIcon, this->tr("Mouse"),
	                                QVariant::fromValue(::Game::Players::Human::Controls::MOUSE));

	QIcon keyboardIcon;
	keyboardIcon.addFile(":/icons/fatcow/16x16/keyboard.png", QSize(16, 16));
	keyboardIcon.addFile(":/icons/fatcow/32x32/keyboard.png", QSize(32, 32));
	this->controlsComboBox->addItem(keyboardIcon, this->tr("Keyboard"),
	                                QVariant::fromValue(::Game::Players::Human::Controls::KEYBOARD));

	QIcon keyboardAndMouseIcon;
	keyboardAndMouseIcon.addFile(":/icons/fatcow/16x16/computer.png", QSize(16, 16));
	keyboardAndMouseIcon.addFile(":/icons/fatcow/32x32/computer.png", QSize(32, 32));
	this->controlsComboBox->addItem(keyboardAndMouseIcon, this->tr("Keyboard and mouse"),
	                                QVariant::fromValue(::Game::Players::Human::Controls::MOUSE_AND_KEYBOARD));

	// Restore index.

	this->controlsComboBox->setCurrentIndex(index);
}

/**
 * Clears the player type combo box and adds newly translated items again, the index will be restored.
 */
void PlayerConfiguration::setupPlayerTypeComboBox()
{
	// Save index to restore it later.

	int index = this->playerTypeComboBox->currentIndex();

	this->playerTypeComboBox->clear();

	QIcon humanIcon;
	humanIcon.addFile(":/icons/fatcow/16x16/user.png", QSize(16, 16));
	humanIcon.addFile(":/icons/fatcow/32x32/user.png", QSize(32, 32));
	this->playerTypeComboBox->addItem(humanIcon, this->tr("Human player"),
	                                  QVariant::fromValue(PlayerType::HUMAN_PLAYER));

	QIcon artificialIntelligenceIcon;
	artificialIntelligenceIcon.addFile(":/icons/fatcow/16x16/server.png", QSize(16, 16));
	artificialIntelligenceIcon.addFile(":/icons/fatcow/32x32/server.png", QSize(32, 32));
	this->playerTypeComboBox->addItem(artificialIntelligenceIcon, this->tr("Artificial intelligence"),
	                                  QVariant::fromValue(PlayerType::ARTIFICIAL_INTELLIGENCE));

	QIcon networkIcon;
	networkIcon.addFile(":/icons/fatcow/16x16/connect.png", QSize(16, 16));
	networkIcon.addFile(":/icons/fatcow/32x32/connect.png", QSize(32, 32));
	this->playerTypeComboBox->addItem(networkIcon, this->tr("Network player"),
	                                  QVariant::fromValue(PlayerType::NETWORK_PLAYER));

	// Restore index.

	this->playerTypeComboBox->setCurrentIndex(index);
}

/**
 * Clears the level of difficulty combo box and adds newly translated items again, the index will be
 * restored.
 */
void PlayerConfiguration::setupLevelOfDifficultyComboBox()
{
	// Save index to restore it later.

	QVariant value;
	int index = this->levelOfDifficultyComboBox->currentIndex();

	this->levelOfDifficultyComboBox->clear();

	value = QVariant::fromValue(::Game::Players::ArtificialIntelligence::LevelOfDifficulty::VERY_EASY);
	this->levelOfDifficultyComboBox->addItem(this->tr("Very easy"), value);

	value = QVariant::fromValue(::Game::Players::ArtificialIntelligence::LevelOfDifficulty::EASY);
	this->levelOfDifficultyComboBox->addItem(this->tr("Easy"), value);

	value = QVariant::fromValue(::Game::Players::ArtificialIntelligence::LevelOfDifficulty::NORMAL);
	this->levelOfDifficultyComboBox->addItem(this->tr("Normal"), value);

	value = QVariant::fromValue(::Game::Players::ArtificialIntelligence::LevelOfDifficulty::DIFFICULT);
	this->levelOfDifficultyComboBox->addItem(this->tr("Difficult"), value);

	value = QVariant::fromValue(::Game::Players::ArtificialIntelligence::LevelOfDifficulty::CHALLENGE);
	this->levelOfDifficultyComboBox->addItem(this->tr("Challenge"), value);

	// Restore index.

	this->levelOfDifficultyComboBox->setCurrentIndex(index);
}

/**
 * Retranslates all strings.
 */
void PlayerConfiguration::retranslateUI()
{
	this->setTitle(QString(this->tr("Player %1")).arg(this->playerId));
	this->playerNameLabel->setText(this->tr("Name"));
	this->playerTypeLabel->setText(this->tr("Type"));
	this->controlsLabel->setText(this->tr("Controls"));
	this->levelOfDifficultyLabel->setText(this->tr("Level of difficulty"));
	this->hostAddressLabel->setText(this->tr("Host address"));

	this->setupControlsComboBox();
	this->setupLevelOfDifficultyComboBox();
	this->setupPlayerTypeComboBox();
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
bool PlayerConfiguration::event(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	return QGroupBox::event(event);
}

}
}
