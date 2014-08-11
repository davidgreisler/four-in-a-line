#include "Settings.hpp"
#include "../../../app/FourInALine.hpp"
#include "../../Settings/FourInALine.hpp"
#include "../Dialogs/Settings.hpp"

#include <QDebug>
#include <QActionGroup>
#include <QAction>
#include <QMenu>
#include <QIcon>

namespace GUI
{
namespace Actions
{

/**
 * Creates a new settings action container.
 *
 * @param parentWindow Parent window, used for dialogs.
 * @param parent Parent object.
 */
Settings::Settings(QWidget* parentWindow, QObject* parent) :
	QObject(parent), parentWindow(parentWindow)
{
	this->createActions();

	this->menu.reset(new QMenu(0));

	auto languageMenu = this->createLanguageMenu(this->menu.data());

	this->menu->addMenu(languageMenu);
	this->menu->addSeparator();
	this->menu->addAction(this->openSettingsAction);

	this->retranslateUI();
}

/**
 * Frees all used resources.
 */
Settings::~Settings()
{

}

/**
 * Returns the open settings action, which opens the settings dialog.
 *
 * @return Open settings action.
 */
QAction* Settings::getOpenSettingsAction() const
{
	return this->openSettingsAction;
}

/**
 * Returns the settings menu.
 *
 * The settings menu contains the language menu and an action for opening the settings.
 *
 * @return The settings menu.
 */
QMenu* Settings::getMenu() const
{
	return this->menu.data();
}

/**
 * Creates a languages menu.
 *
 * @return The languages menu.
 */
Widgets::SelectLanguageMenu* Settings::createLanguageMenu(QWidget* parent) const
{
	auto application = ::FourInALine::getInstance();
	auto applicationSettings = application->getSettings()->getApplicationSettings();
	auto languageMenu = new ::GUI::Widgets::SelectLanguageMenu(application, applicationSettings, parent);

	return languageMenu;
}

/**
 * Shows settings dialog.
 */
void Settings::showSettingsDialog()
{
	Dialogs::Settings dialog(this->parentWindow);

	dialog.exec();
}

/**
 * Create all actions and connect them.
 */
void Settings::createActions()
{
	QIcon settingsIcon;
	settingsIcon.addFile(":/icons/fatcow/16x16/setting_tools.png", QSize(16, 16));
	settingsIcon.addFile(":/icons/fatcow/32x32/setting_tools.png", QSize(32, 32));
	this->openSettingsAction = new QAction(settingsIcon, "", this);
	this->connect(this->openSettingsAction, &QAction::triggered,
				  this, &Settings::showSettingsDialog);
}

/**
 * Retranslates all strings.
 */
void Settings::retranslateUI()
{
	this->menu->setTitle(tr("&Settings"));

	this->openSettingsAction->setText(tr("Open &settings ..."));
	this->openSettingsAction->setStatusTip(tr("Open the settings dialog."));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
bool Settings::event(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	return QObject::event(event);
}

}
}
