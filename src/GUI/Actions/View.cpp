#include "View.hpp"
#include "../MainWindow.hpp"
#include "../../ConnectFour.hpp"
#include "../../ConnectFourSettings.hpp"
#include "../../Settings/View.hpp"

namespace GUI
{
namespace Actions
{

View::View(::GUI::MainWindow* mainWindow, QObject *parent) :
	QObject(parent), mainWindow(mainWindow)
{
	this->createActions();
	this->retranslateUI();
}

/**
 * Frees all used resources.
 */
View::~View()
{

}

/**
 * Returns the fullscreen checkbox, which allows the user to switch to/from fullscreen mode.
 *
 * @return Fullscreen checkbox.
 */
QAction* View::getFullscreenCheckboxAction() const
{
	return this->fullscreenCheckboxAction;
}

void View::changeFullscreen()
{
	::ConnectFourSettings* settings = ::ConnectFour::getInstance()->getSettings();
	::Settings::View* viewSettings = settings->getViewSettings();

	bool isFullscreen = this->fullscreenCheckboxAction->isChecked();
	viewSettings->setFullscreen(isFullscreen);
	this->mainWindow->setFullscreen(isFullscreen);
}

/**
 * Create all actions and connect them.
 */
void View::createActions()
{
	::ConnectFourSettings* settings = ::ConnectFour::getInstance()->getSettings();
	::Settings::View* viewSettings = settings->getViewSettings();

	this->fullscreenCheckboxAction = new QAction("", this);
	this->fullscreenCheckboxAction->setCheckable(true);
	this->fullscreenCheckboxAction->setChecked(viewSettings->isFullscreen());

	this->connect(this->fullscreenCheckboxAction, &QAction::triggered, this, &View::changeFullscreen);
}

/**
 * Retranslates all strings.
 */
void View::retranslateUI()
{
	this->fullscreenCheckboxAction->setText(tr("&Fullscreen mode"));
	this->fullscreenCheckboxAction->setStatusTip(tr("Toggles fullscreen mode on/off."));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
bool View::event(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	return QObject::event(event);
}

}
}
