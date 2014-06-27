#ifndef GUI_WIDGETS_PLAYERCONFIGURATION_HPP
#define GUI_WIDGETS_PLAYERCONFIGURATION_HPP

#include "../ArtificialIntelligencePlayer.hpp"
#include "../HumanPlayer.hpp"
#include "../PlayerFactory.hpp"

#include <QGroupBox>

class QFormLayout;
class QLabel;
class QComboBox;
class QLineEdit;

namespace GUI
{
namespace Widgets
{

/**
 * Widget for configuring a player for the game.
 *
 * This widget provides a form for entering a player name, selecting the player type (human,
 * artificial intelligence, network) and configuring player type specific settings like level of
 * difficulty for the artificial intelligence.
 *
 * The specified player id is the id used by the game engine to distinguish player one and two. The
 * id can be retrieved with getPlayerId() and changed with setPlayerId().
 *
 * The entered player name can be retrieved with getPlayerName() and set with setPlayerName().
 *
 * Use getPlayerType() to retrieve the player type and setPlayerType() to change the player type.
 *
 * The level of difficulty is returned by getLevelOfDifficulty() and can be set with
 * setLevelOfDifficulty().
 *
 * The controls used by a human player can be retrieved with getControls() and set with
 * setControls().
 *
 * A player according to the settings made by the user can be constructed with createPlayer(). It is
 * possible to check whether the player configuration is valid with isValid().
 */
class PlayerConfiguration : public QGroupBox
{
		Q_OBJECT
	public:
		/**
		 * Player id type.
		 */
		using PlayerIdType = ::Game::FourInALine::Game::PlayerType;

		/**
		 * Player type.
		 */
		enum class PlayerType : int
		{
			HUMAN_PLAYER,
			ARTIFICIAL_INTELLIGENCE,
			NETWORK_PLAYER
		};

		explicit PlayerConfiguration(PlayerIdType playerId,
		                             QWidget* parent = 0);
		virtual ~PlayerConfiguration();

		void setPlayerId(::Game::FourInALine::Game::PlayerType playerId);
		::Game::FourInALine::Game::PlayerType getPlayerId() const;

		void setPlayerName(const QString& name);
		QString getPlayerName() const;

		void setPlayerType(PlayerType playerType);
		PlayerType getPlayerType() const;

		void setLevelOfDifficulty(::GUI::ArtificialIntelligencePlayer::LevelOfDifficulty levelOfDifficulty);
		::GUI::ArtificialIntelligencePlayer::LevelOfDifficulty getLevelOfDifficulty() const;

		void setControls(::GUI::HumanPlayer::Controls controls);
		::GUI::HumanPlayer::Controls getControls() const;

		QSharedPointer<AbstractPlayer> createPlayer(::GUI::PlayerFactory& factory) const;

		bool isValid() const;

	signals:
		/**
		 * Emitted when the player type is changed.
		 *
		 * @param newPlayerType The new player type.
		 */
		void playerTypeChanged(::GUI::Widgets::PlayerConfiguration::PlayerType newPlayerType);

		/**
		 * Emitted when the player configuration changed.
		 */
		void configurationChanged();

	public slots:
		void updatePlayerType();

	private:
		Q_DISABLE_COPY(PlayerConfiguration)

		void setupControlsComboBox();
		void setupPlayerTypeComboBox();
		void setupLevelOfDifficultyComboBox();

		void retranslateUI();
		bool event(QEvent* event);

		/**
		 * Player number used by the engine and shown on top of the widget.
		 */
		PlayerIdType playerId;

		/**
		 * Layout of the form.
		 */
		QFormLayout* formLayout;

		/**
		 * Label for the player name.
		 */
		QLabel* playerNameLabel;

		/**
		 * Line edit for the player name.
		 */
		QLineEdit* playerNameEdit;

		/**
		 * Label for the player type.
		 */
		QLabel* playerTypeLabel;

		/**
		 * Combo box to select the player type.
		 */
		QComboBox* playerTypeComboBox;

		/**
		 * Labels for the controls.
		 */
		QLabel* controlsLabel;

		/**
		 * Combo box for selecting the controls.
		 */
		QComboBox* controlsComboBox;

		/**
		 * Label for the level of difficulty.
		 */
		QLabel* levelOfDifficultyLabel;

		/**
		 * Combo box for selecting the level of difficulty.
		 */
		QComboBox* levelOfDifficultyComboBox;

		/**
		 * Label for the host address.
		 */
		QLabel* hostAddressLabel;

		/**
		 * Line edit for the host address.
		 */
		QLineEdit* hostAddressEdit;
};

}
}

Q_DECLARE_METATYPE(GUI::Widgets::PlayerConfiguration::PlayerType)

#endif // GUI_WIDGETS_PLAYERCONFIGURATION_HPP
