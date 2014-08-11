#ifndef GUI_WIDGETS_CHAT_HPP
#define GUI_WIDGETS_CHAT_HPP

#include <QWidget>
#include <QTextTableFormat>

class QVBoxLayout;
class QHBoxLayout;
class QLineEdit;
class QTextEdit;
class QPushButton;

namespace GUI
{
namespace Widgets
{

/**
 * Provides a message list and an input field for writing chat messages.
 */
class Chat : public QWidget
{
		Q_OBJECT
	public:
		explicit Chat(QWidget *parent = nullptr);
		virtual ~Chat();

		QString getUserName() const;
		void setUserName(const QString& value);

	protected slots:
		void appendMessage(QString playerName, QString message);
		void sendMessage();

	private:
		Q_DISABLE_COPY(Chat)

		void retranslateUI();
		bool event(QEvent* event);

		/**
		 * Vertical layout.
		 */
		QVBoxLayout* verticalLayout;

		/**
		 * Layout for the message input and the send button.
		 */
		QHBoxLayout* inputLayout;

		/**
		 * Chat messages edit.
		 */
		QTextEdit* messagesEdit;

		/**
		 * Message input edit.
		 */
		QLineEdit* inputEdit;

		/**
		 * Send button.
		 */
		QPushButton* sendButton;

		/**
		 * Name of the user.
		 */
		QString userName;

		/**
		 * Table format for a message.
		 */
		QTextTableFormat format;
};

}
}

#endif // GUI_WIDGETS_CHAT_HPP
