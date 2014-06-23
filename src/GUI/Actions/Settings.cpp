#include "Settings.hpp"
#include "../../FourInALine.hpp"
#include "../../FourInALineSettings.hpp"
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
	this->updateLanguages();
	this->createMenu();
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
 * Returns the languages menu.
 *
 * @return The languages menu.
 */
QMenu* Settings::getLanguageMenu() const
{
	return this->languageMenu.data();
}

/**
 * Returns an action group containing one action for every language supported by the application.
 *
 * A language action changes the program's translation to the respective language when invoked.
 *
 * @return Action group containing actions for every supported language.
 */
QSharedPointer<QActionGroup> Settings::getLanguages() const
{
	return this->languageGroup;
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
 * Switches the application's language to the language of the given action.
 *
 * Also saves the language to the settings.
 *
 * @param action Action from the language list group.
 */
void Settings::switchLanguage(QAction* action)
{
	::FourInALine* application;
	::Settings::Application* applicationSettings;

	QString locale = action->data().toString();

	application = ::FourInALine::getInstance();
	applicationSettings = application->getSettings()->getApplicationSettings();
	applicationSettings->setLanguage(locale);
	applicationSettings->save();
	application->setLanguage(locale);

	qDebug() << "[" << this << "] Language switched to: " << locale;
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
 * Creates the settings menu and the languages menu.
 */
void Settings::createMenu()
{
	this->createLanguagesMenu();

	this->menu.reset(new QMenu(0));
	this->menu->addMenu(this->languageMenu.data());
	this->menu->addSeparator();
	this->menu->addAction(this->openSettingsAction);
}

/**
 * Creates the languages menu.
 */
void Settings::createLanguagesMenu()
{
	this->languageMenu.reset(new QMenu(0));

	QIcon languageMenuIcon;
	languageMenuIcon.addFile(":/icons/fatcow/16x16/locate.png", QSize(16, 16));
	languageMenuIcon.addFile(":/icons/fatcow/32x32/locate.png", QSize(32, 32));
	this->languageMenu->setIcon(languageMenuIcon);

	this->languageGroup = this->getLanguages();

	QList<QAction*> languageActions = this->languageGroup->actions();

	int nLanguageActions = languageActions.count();
	for (int i = 0; i < nLanguageActions; ++i)
	{
		this->languageMenu->addAction(languageActions[i]);
	}
}

/**
 * Retranslates all strings.
 */
void Settings::retranslateUI()
{
	this->menu->setTitle(tr("&Settings"));
	this->languageMenu->setTitle(tr("&Language"));

	this->openSettingsAction->setText(tr("Open &settings ..."));
	this->openSettingsAction->setStatusTip(tr("Open the settings dialog."));
}

/**
 * Gets a list of languages supported by the application and creates one action for each language.
 *
 * Also connects the language group's triggered signal to the switchLanguage slot of this class.
 */
void Settings::updateLanguages()
{
	this->languageGroup = QSharedPointer<QActionGroup>(new QActionGroup(0), &QObject::deleteLater);

	::FourInALine* application = ::FourInALine::getInstance();
	QMap<QString, QString> languages = application->getAvailableLanguages();

	QMapIterator<QString, QString> it(languages);
	while (it.hasNext())
	{
		it.next();

		QAction* languageAction = new QAction(it.value(), this->languageGroup.data());
		languageAction->setCheckable(true);
		languageAction->setData(it.key());

		this->languageGroup->addAction(languageAction);

		if (it.key() == application->getLanguage())
		{
			languageAction->setChecked(true);
		}
	}

	this->connect(this->languageGroup.data(), &QActionGroup::triggered,
				  this, &Settings::switchLanguage);
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
