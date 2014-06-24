#ifndef GUI_WIDGETS_GAMESETUP_HPP
#define GUI_WIDGETS_GAMESETUP_HPP

#include <QWidget>

class QGridLayout;

namespace GUI
{
namespace Widgets
{

class BoardConfiguration;
class TimeLimitConfiguration;
class PlayerConfiguration;
class GameConfiguration;

/**
 * Game setup widget combining the configuration widgets for a game.
 *
 * This widget contains widgets for configuring the board, the time limit, general game settings
 * and the two players. The individial configuration widgets can be retrieved with the get*Widget()
 * methods.
 *
 * When the configuration is changed, configurationChanged() is emitted, configurationValid() and
 * configurationInvalid() are emitted when the configuration becomes valid/invalid. Whether the
 * current configuration is valid can be checked with isValid().
 */
class GameSetup : public QWidget
{
		Q_OBJECT
	public:
		explicit GameSetup(QWidget *parent = 0);
		virtual ~GameSetup();

		bool isValid() const;

		BoardConfiguration* getBoardConfigurationWidget() const;

		TimeLimitConfiguration* getTimeLimitConfigurationWidget() const;

		PlayerConfiguration* getFirstPlayerConfigurationWidget() const;

		PlayerConfiguration* getSecondPlayerConfigurationWidget() const;

		GameConfiguration* getGameConfigurationWidget() const;

	signals:
		/**
		 * Emitted when the configuration becomes invalid.
		 */
		void configurationInvalid();

		/**
		 * Emitted when the configuration becomes valid.
		 */
		void configurationValid();

		/**
		 * Emitted when the configuration has changed.
		 *
		 * @todo Not yet implemented for all settings.
		 */
		void configurationChanged();

	private slots:
		void updatePlayerType();
		void updateValidity();

	private:
		Q_DISABLE_COPY(GameSetup)

		void changeEvent(QEvent* event);
		void retranslateUI();

		/**
		 * Whether the current configuration is valid or not.
		 */
		bool valid;

		/**
		 * Layout of the dialog.
		 */
		QGridLayout* layout;

		/**
		 * Widget to configure the board.
		 */
		BoardConfiguration* boardConfigurationWidget;

		/**
		 * Widget to configure the time limit.
		 */
		TimeLimitConfiguration* timeLimitConfigurationWidget;

		/**
		 * Configuration widget for the first player.
		 */
		PlayerConfiguration* firstPlayerConfigurationWidget;

		/**
		 * Configuration widget for the second player.
		 */
		PlayerConfiguration* secondPlayerConfigurationWidget;

		/**
		 * Configuration widget for general game settings.
		 */
		GameConfiguration* gameConfigurationWidget;
};

}
}

#endif // GUI_WIDGETS_GAMESETUP_HPP
