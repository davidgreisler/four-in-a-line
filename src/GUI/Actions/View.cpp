#include "View.hpp"
#include "../MainWindow.hpp"
#include "../../../app/FourInALine.hpp"
#include "../../Settings/FourInALine.hpp"
#include "../../Settings/View.hpp"

#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QIcon>
#include <QActionGroup>

namespace GUI
{
namespace Actions
{

/**
 * Creates a new view actions container.
 *
 * @param mainWindow Main window.
 * @param parent Parent object.
 */
View::View(::GUI::MainWindow* mainWindow, QObject *parent) :
	QObject(parent), mainWindow(mainWindow)
{
	this->createActions();
	this->createMenu();
	this->retranslateUI();

	auto settings = ::FourInALine::getInstance()->getSettings();
	auto viewSettings = settings->getViewSettings();

	this->connect(viewSettings, &::Settings::View::changed, this, &View::updateFullscreen);
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

/**
 * Returns the toolbar menu.
 *
 * The toolbar menu contains an action for every toolbar to toggle display on/off.
 *
 * Important: The toolbars are not yet known when this class is created. The toolbar menu therefore
 * is empty until updateToolbars() is called to populate it.
 *
 * @return The toolbar menu.
 */
QMenu* View::getToolbarMenu() const
{
	return this->toolbarMenu.data();
}

/**
 * (De)activates full screen mode when the checkbox is (un)checked.
 *
 * Invoked when the fullscreen checkbox is triggered/changed.
 */
void View::changeFullscreen()
{
	auto settings = ::FourInALine::getInstance()->getSettings();
	auto viewSettings = settings->getViewSettings();

	bool isFullscreen = this->fullscreenCheckboxAction->isChecked();
	viewSettings->setFullscreen(isFullscreen);
	viewSettings->apply();
}

/**
 * Updates the checkbox when the view settings were changed.
 */
void View::updateFullscreen()
{
	auto settings = ::FourInALine::getInstance()->getSettings();
	auto viewSettings = settings->getViewSettings();

	bool isFullscreen = viewSettings->isFullscreen();
	this->fullscreenCheckboxAction->setChecked(isFullscreen);
}

/**
 * Clears the toolbar menu and then adds given actions to it.
 *
 * @param actions List of QActions, one action for every toolbar to toggle display on/off.
 */
void View::updateToolbars(QList<QAction*> actions)
{
	this->toolbarMenu->clear();

	QList<QAction*>::ConstIterator actionsIt;
	for(actionsIt = actions.constBegin(); actionsIt != actions.constEnd(); ++actionsIt)
	{
		this->toolbarMenu->addAction(*actionsIt);
	}
}

/**
 * Create all actions and connect them.
 */
void View::createActions()
{
	auto settings = ::FourInALine::getInstance()->getSettings();
	auto viewSettings = settings->getViewSettings();

	QIcon fullscreenCheckboxIcon;
	fullscreenCheckboxIcon.addFile(":/icons/fatcow/16x16/monitor.png", QSize(16, 16));
	fullscreenCheckboxIcon.addFile(":/icons/fatcow/32x32/monitor.png", QSize(32, 32));
	this->fullscreenCheckboxAction = new QAction(fullscreenCheckboxIcon, "", this);
	this->fullscreenCheckboxAction->setCheckable(true);
	this->fullscreenCheckboxAction->setChecked(viewSettings->isFullscreen());

	this->connect(this->fullscreenCheckboxAction, &QAction::triggered, this, &View::changeFullscreen);
}

/**
 * Creates the view menu and the toolbar menu.
 */
void View::createMenu()
{
	this->createToolbarMenu();

	this->menu.reset(new QMenu(0));
	this->menu->addAction(this->fullscreenCheckboxAction);
	this->menu->addSeparator();
	this->menu->addMenu(this->toolbarMenu.data());

	QIcon toolbarMenuIcon;
	toolbarMenuIcon.addFile(":/icons/fatcow/16x16/application_control_bar.png", QSize(16, 16));
	toolbarMenuIcon.addFile(":/icons/fatcow/32x32/application_control_bar.png", QSize(32, 32));
	this->toolbarMenu->setIcon(toolbarMenuIcon);
}

/**
 * Creates the toolbar menu, containing a checkbox for every toolbar to toggle display on/off.
 *
 * The toolbar menu is created empty because at creation time the toolbars are not known yet. After
 * the toolbars have been created, updateToolbars() must be called to populate the toolbar menu.
 */
void View::createToolbarMenu()
{
	this->toolbarMenu.reset(new QMenu(0));
}

/**
 * Retranslates all strings.
 */
void View::retranslateUI()
{
	this->fullscreenCheckboxAction->setText(tr("&Fullscreen mode"));
	this->fullscreenCheckboxAction->setStatusTip(tr("Toggles fullscreen mode on/off."));

	this->menu->setTitle(tr("&View"));
	this->toolbarMenu->setTitle(tr("&Toolbars"));
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
