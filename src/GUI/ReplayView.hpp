#ifndef GUI_REPLAYVIEW_HPP
#define GUI_REPLAYVIEW_HPP

#include "../GameLogic/FourInALine/Game.hpp"
#include "AbstractView.hpp"
#include "Widgets/Board.hpp"
#include "../Game/Replay.hpp"

class QWidget;

namespace GUI
{

class ViewManager;

/**
 * The replay view manages the replay currently being played back.
 *
 * The replay view manages the replay currently being played back. It provides a slot for
 * opening a replay: loadReplay. It is then possible to navigate through the replay with
 * nextMove(), previousMove(), jumpToStart() and jumpToEnd(). The replay can be closed with
 * closeReplay().
 *
 * It is possible to check whether a replay is loaded using hasReplay(), and hasNextMove()/
 * hasPreviousMove() can be used to check whether it is possible to step one move forward/backward.
 */
class ReplayView : public AbstractView
{
		Q_OBJECT
	public:
		ReplayView(ViewManager* manager);
		virtual ~ReplayView();

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
		Q_DISABLE_COPY(ReplayView)

		QSharedPointer< ::Game::Players::Placeholder> playerIdToPlayer(::GameLogic::FourInALine::Game::PlayerType playerId) const;

		/**
		 * The replay view widget.
		 */
		Widgets::Board* widget;

		/**
		 * The currently loaded replay.
		 */
		QSharedPointer< ::Game::Replay> replay;

		/**
		 * Current move number (position).
		 */
		unsigned int currentMoveNo;
};

}

#endif // GUI_REPLAYVIEW_HPP
