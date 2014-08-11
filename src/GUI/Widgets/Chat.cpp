#include "Chat.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QTextTable>
#include <QScrollBar>

namespace GUI
{
namespace Widgets
{

/**
 * Creates a new chat widget.
 *
 * @param parent Parent widget.
 */
Chat::Chat(QWidget *parent) :
    QWidget(parent)
{
	this->messagesEdit = new QTextEdit(this);
	this->messagesEdit->setContextMenuPolicy(Qt::NoContextMenu);
	this->messagesEdit->setReadOnly(true);

	this->format.setBorder(0);

	this->inputEdit = new QLineEdit(this);

	this->sendButton = new QPushButton(this);

	this->inputLayout = new QHBoxLayout();
	this->inputLayout->addWidget(this->inputEdit);
	this->inputLayout->addWidget(this->sendButton);

	this->verticalLayout = new QVBoxLayout(this);
	this->verticalLayout->setContentsMargins(0, 0, 0, 0);
	this->verticalLayout->addWidget(this->messagesEdit);
	this->verticalLayout->addLayout(this->inputLayout);

	this->setLayout(this->verticalLayout);

	this->connect(this->inputEdit, &QLineEdit::returnPressed, this, &Chat::sendMessage);
	this->connect(this->sendButton, &QPushButton::clicked, this, &Chat::sendMessage);

	this->retranslateUI();
	this->setUserName("User");
}

/**
 * Frees all used resources.
 */
Chat::~Chat()
{

}

/**
 * Returns the user name.
 *
 * @return The user name.
 */
QString Chat::getUserName() const
{
	return this->userName;
}

/**
 * Sets the name of the user.
 *
 * @param userName The new user name.
 */
void Chat::setUserName(const QString& userName)
{
	this->userName = userName;
}

/**
 * Appends given message to message widget.
 *
 * @param playerName Player name.
 * @param message The message.
 */
void Chat::appendMessage(QString playerName, QString message)
{
	QTextCursor cursor(this->messagesEdit->textCursor());
	cursor.movePosition(QTextCursor::End);

	QTextTable* table = cursor.insertTable(1, 2, this->format);
	table->cellAt(0, 0).firstCursorPosition().insertText(playerName + ':');
	table->cellAt(0, 1).firstCursorPosition().insertText(message);

	QScrollBar* scrollBar = this->messagesEdit->verticalScrollBar();
	scrollBar->setValue(scrollBar->maximum());
}

/**
 * Sends the message in the input edit.
 */
void Chat::sendMessage()
{
	QString messageText = this->inputEdit->text();

	if (!messageText.isEmpty())
	{
		// Send message here.

		/// @todo Implement.

		this->appendMessage(this->userName, messageText);
		this->inputEdit->clear();
	}
}

/**
 * Retranslates all strings.
 */
void Chat::retranslateUI()
{
	this->sendButton->setText(this->tr("Send"));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
bool Chat::event(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	return QWidget::event(event);
}

}
}
