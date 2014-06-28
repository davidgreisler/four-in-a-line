#ifndef GUI_WIDGETS_TIMELIMITCONFIGURATION_HPP
#define GUI_WIDGETS_TIMELIMITCONFIGURATION_HPP

#include "../../GameLogic/FourInALine/Game.hpp"

#include <QGroupBox>

class QFormLayout;
class QLabel;
class QSpinBox;
class QRadioButton;

namespace GUI
{
namespace Widgets
{

/**
 * Widget for configuring the time limit.
 *
 * This widget provides a form to configure the time limit and the timeout action of a game.
 *
 * It is possible to deactivate the time limit completely. Use hasTimeLimit() to check whether there
 * is a time limit and setHasTimeLimit() to activate/deactivate the time limit.
 *
 * The current time limit can be retrieved with getTimeLimit() and set with setTimeLimit().
 *
 * Use getTimeoutAction() to retrieve the timeout action and setTimeoutAction() to set it.
 */
class TimeLimitConfiguration : public QGroupBox
{
		Q_OBJECT
	public:
		explicit TimeLimitConfiguration(QWidget* parent = 0);
		virtual ~TimeLimitConfiguration();

		bool hasTimeLimit() const;
		void setHasTimeLimit(bool hasTimeLimit);

		unsigned int getTimeLimit() const;
		void setTimeLimit(unsigned int timeLimit);

		::GameLogic::FourInALine::Game::TimeoutAction getTimeoutAction() const;
		void setTimeoutAction(::GameLogic::FourInALine::Game::TimeoutAction action);

		/**
		 * Minimum time limit in seconds.
		 */
		static const unsigned int MINIMUM_TIME_LIMIT;

		/**
		 * Maximum time limit in seconds.
		 */
		static const unsigned int MAXIMUM_TIME_LIMIT;

		/**
		 * The default timeout action.
		 */
		static const ::GameLogic::FourInALine::Game::TimeoutAction DEFAULT_TIMEOUT_ACTION;

	private:
		Q_DISABLE_COPY(TimeLimitConfiguration)

		void retranslateUI();
		bool event(QEvent* event);

		/**
		 * Layout of the form.
		 */
		QFormLayout* formLayout;

		/**
		 * Label for the time limit edit.
		 */
		QLabel* timeLimitLabel;

		/**
		 * Spin box for the time limit.
		 */
		QSpinBox* timeLimitSpinBox;

		/**
		 * Label for the timeout action radio buttons.
		 */
		QLabel* timeoutActionLabel;

		/**
		 * Radio button for drawing the game on timeout.
		 */
		QRadioButton* drawActionRadioButton;

		/**
		 * Radio button for making the player lose the game on timeout.
		 */
		QRadioButton* loseActionRadioButton;

		/**
		 * Radio button for making a random move when a player exceeds the time limit.
		 */
		QRadioButton* randomMoveRadioButton;
};

}
}

#endif // GUI_WIDGETS_TIMELIMITCONFIGURATION_HPP
