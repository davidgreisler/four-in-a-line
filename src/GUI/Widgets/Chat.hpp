#ifndef GUI_WIDGETS_CHAT_HPP
#define GUI_WIDGETS_CHAT_HPP

#include <QWidget>

namespace GUI
{
namespace Widgets
{

/**
 * Provides a message list and an input field for writing chat messages.
 *
 * @todo Implement.
 */
class Chat : public QWidget
{
		Q_OBJECT
	public:
		explicit Chat(QWidget *parent = 0);
		virtual ~Chat();

	signals:

	public slots:

	private:
		Q_DISABLE_COPY(Chat)

};

}
}

#endif // GUI_WIDGETS_CHAT_HPP
