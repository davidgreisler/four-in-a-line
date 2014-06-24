#ifndef GUI_REPLAYCONTROLLER_HPP
#define GUI_REPLAYCONTROLLER_HPP

#include "../Game/FourInALine/Game.hpp"
#include "AbstractController.hpp"
#include "Widgets/Board.hpp"
#include "Replay.hpp"

class QWidget;

namespace GUI
{

class ControllerManager;

/**
 * The replay controller manages the replay currently being played back.
 *
 * The replay controller manages the replay currently being played back. It provides a slot for
 * opening a replay: loadReplay. It is then possible to navigate through the replay with
 * nextMove(), previousMove(), jumpToStart() and jumpToEnd(). The replay can be closed with
 * closeReplay().
 *
 * It is possible to check whether a replay is loaded using hasReplay(), and hasNextMove()/
 * hasPreviousMove() can be used to check whether it is possible to step one move forward/backward.
 */
class ReplayController : public AbstractController
{
		Q_OBJECT
	public:
		ReplayController(ControllerManager* manager);
		virtual ~ReplayController();

		QWidget* getWidget() const;

		bool hasReplay() const;
		bool hasNextMove() const;
		bool hasPreviousMove() const;

		virtual bool confirmDeactivation();

	signals:
		/**
		 * Emitted when the state changed.
		 *
		 * This signal can be used to evaluate whether actions have to be disabled/enabled, etc.
		 */
		void stateChanged();

	public slots:
		void loadReplay();
		void closeReplay();

		void nextMove();
		void previousMove();

		void jumpToStart();
		void jumpToEnd();

	private:
		Q_DISABLE_COPY(ReplayController)

		QSharedPointer<PlaceholderPlayer> playerIdToPlayer(::Game::FourInALine::Game::PlayerType playerId) const;

		/**
		 * The replay view widget.
		 */
		Widgets::Board* widget;

		/**
		 * The currently loaded replay.
		 */
		QSharedPointer<Replay> replay;

		/**
		 * Current move number (position).
		 */
		unsigned int currentMoveNo;
};

}

#endif // GUI_REPLAYCONTROLLER_HPP
