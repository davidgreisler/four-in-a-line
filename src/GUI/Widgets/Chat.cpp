#include "Chat.hpp"

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
	this->setAutoFillBackground(true);

	QPalette palette = this->palette();
	palette.setColor(this->backgroundRole(), Qt::yellow);
	this->setPalette(palette);
}

/**
 * Frees all used resources.
 */
Chat::~Chat()
{

}

}
}
