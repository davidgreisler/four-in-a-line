#include "Game.hpp"
#include "Chat.hpp"
#include "Board.hpp"
#include "../../Settings/View.hpp"
#include "../../Settings/FourInALine.hpp"
#include "../../../app/FourInALine.hpp"

namespace GUI
{
namespace Widgets
{

/**
 * Creates a new game widget.
 *
 * @param parent Parent widget.
 */
Game::Game(QWidget *parent) :
    QWidget(parent)
{
	this->layout = new QVBoxLayout(this);

	auto settings = ::FourInALine::getInstance()->getSettings();
	auto viewSettings = settings->getViewSettings();

	this->boardWidget = new Board(viewSettings->getTheme(), this);

	this->updateThemeConnection = this->connect(viewSettings, &Settings::View::changed, [=]() {
		this->boardWidget->setTheme(viewSettings->getTheme());
	});

	this->layout->addWidget(this->boardWidget, 2);

	this->chatWidget = new Chat(this);
	this->layout->addWidget(this->chatWidget, 1);
}

/**
 * Frees all used resources.
 */
Game::~Game()
{
	QObject::disconnect(this->updateThemeConnection);
}

/**
 * Returns the board widget.
 *
 * @return Board widget.
 */
Board* Game::getBoardWidget() const
{
	return this->boardWidget;
}

/**
 * Returns the chat widget.
 *
 * @return Chat widget.
 */
Chat* Game::getChatWidget() const
{
	return this->chatWidget;
}

/**
 * Hides the chat widget.
 */
void Game::hideChatWidget()
{
	this->chatWidget->hide();
}

/**
 * Shows the chat widget.
 */
void Game::showChatWidget()
{
	this->chatWidget->show();
}

/**
 * Sets whether the chat widget should be shown/hidden.
 *
 * @param visible When it should be shown true, otherwise false.
 */
void Game::setChatWidgetVisible(bool visible)
{
	if (visible)
	{
		this->showChatWidget();
	}
	else
	{
		this->hideChatWidget();
	}
}

/**
 * Returns whether the chat widget is shown or not.
 *
 * @return When it is visible true, otherwise false.
 */
bool Game::isChatWidgetVisible() const
{
	return !this->chatWidget->isHidden();
}

}
}
