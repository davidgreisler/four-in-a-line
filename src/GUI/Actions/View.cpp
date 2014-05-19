#include "View.hpp"
#include "../MainWindow.hpp"
#include "../../ConnectFour.hpp"
#include "../../ConnectFourSettings.hpp"
#include "../../Settings/View.hpp"

#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QIcon>

namespace GUI
{
namespace Actions
{

View::View(::GUI::MainWindow* mainWindow, QObject *parent) :
	QObject(parent), mainWindow(mainWindow)
{
	this->createActions();
	this->createMenu();
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

/**
 * Returns the view menu.
 *
 * The view menu contains all view actions.
 *
 * @return The view menu.
 */
QMenu* View::getMenu() const
{
	return this->menu.data();
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

	QIcon fullscreenCheckboxIcon;
	fullscreenCheckboxIcon.addFile(":/icons/16x16/monitor.png", QSize(16, 16));
	fullscreenCheckboxIcon.addFile(":/icons/32x32/monitor.png", QSize(32, 32));
	this->fullscreenCheckboxAction = new QAction(fullscreenCheckboxIcon, "", this);
	this->fullscreenCheckboxAction->setCheckable(true);
	this->fullscreenCheckboxAction->setChecked(viewSettings->isFullscreen());

	this->connect(this->fullscreenCheckboxAction, &QAction::triggered, this, &View::changeFullscreen);
}

/**
 * Creates the move menu.
 */
void View::createMenu()
{
	this->menu.reset(new QMenu(0));
	this->menu->addAction(this->fullscreenCheckboxAction);
}

/**
 * Retranslates all strings.
 */
void View::retranslateUI()
{
	this->fullscreenCheckboxAction->setText(tr("&Fullscreen mode"));
	this->fullscreenCheckboxAction->setStatusTip(tr("Toggles fullscreen mode on/off."));

	this->menu->setTitle(tr("&View"));
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
