#ifndef GUI_WIDGETS_GAME_HPP
#define GUI_WIDGETS_GAME_HPP

#include <QWidget>
#include <QVBoxLayout>

namespace GUI
{
namespace Widgets
{

class Board;
class Chat;

/**
 * Combines game board widget and chat widget in one widget.
 *
 * This widget contains a board widget and a chat widget below it. It is possible to show/hide the
 * chat widget.
 *
 * The individual widgets can be accessed with getBoardWidget() and getChatWidget().
 */
class Game : public QWidget
{
		Q_OBJECT
	public:
		explicit Game(QWidget *parent = 0);

		Board* getBoardWidget() const;

		Chat* getChatWidget() const;

		void hideChatWidget();
		void showChatWidget();
		void setChatWidgetVisible(bool visible);
		bool isChatWidgetVisible() const;

	private:
		/**
		 * Vertical layout.
		 */
		QVBoxLayout* layout;

		/**
		 * Game board widget.
		 */
		Board* boardWidget;

		/**
		 * Chat widget.
		 */
		Chat* chatWidget;
};

}
}

#endif // GUI_WIDGETS_GAME_HPP
