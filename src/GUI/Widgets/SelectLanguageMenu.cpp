#include "SelectLanguageMenu.hpp"
#include "../../../app/FourInALine.hpp"

#include <QIcon>
#include <QSize>
#include <QEvent>

namespace GUI
{
namespace Widgets
{

/**
 * Creates a new select language menu.
 *
 * @param application The application used to change the language/listen for updates.
 * @param applicationSettings Application settings used to save the language when it is changed.
 * @param parent Parent widget.
 */
SelectLanguageMenu::SelectLanguageMenu(::FourInALine* application,
                                       ::Settings::Application* applicationSettings,
                                       QWidget *parent) :
    QMenu(parent), application(application), applicationSettings(applicationSettings)
{
	this->actionGroup = new QActionGroup(this);

	QIcon icon;

	icon.addFile(":/icons/fatcow/16x16/locate.png", QSize(16, 16));
	icon.addFile(":/icons/fatcow/32x32/locate.png", QSize(32, 32));

	this->setIcon(icon);

	this->connect(this->application, &::FourInALine::languageChanged,
	              this, &SelectLanguageMenu::updateLanguage);
	this->connect(this->actionGroup, &QActionGroup::triggered,
	              this, &SelectLanguageMenu::switchLanguage);

	this->updateLanguage();
	this->retranslateUI();
}

/**
 * Frees all used resources.
 */
SelectLanguageMenu::~SelectLanguageMenu()
{

}

/**
 * Updates menu when the language was changed.
 */
void SelectLanguageMenu::updateLanguage()
{
	this->updateActionGroup();

	auto languageActions = this->actionGroup->actions();

	this->clear();
	this->addActions(languageActions);
}

/**
 * Switches the application's language to the language of the given action.
 *
 * Also saves the language to the settings.
 *
 * @param action Action from the language list group.
 */
void SelectLanguageMenu::switchLanguage(QAction* action)
{
	QString locale = action->data().toString();

	this->applicationSettings->setLanguage(locale);

	// The application listens for the changed() signal of the settings
	// and will update the language.

	this->applicationSettings->save();
}

/**
 * Updates action group containing language actions.
 */
void SelectLanguageMenu::updateActionGroup()
{
	auto availableLanguages = this->application->getAvailableLanguages();
	auto currentLanguageId = this->application->getLanguage();

	// Clear group.

	auto oldActions = this->actionGroup->actions();
	for (auto action : oldActions)
	{
		delete action;
	}

	// Fill group with new actions.

	for (auto language = availableLanguages.cbegin(); language != availableLanguages.cend(); language++)
	{
		QAction* action;
		auto languageName = language.value();
		auto languageId = language.key();
		bool isCurrentLanguage = (languageId == currentLanguageId);

		action = new QAction(languageName, this->actionGroup);
		action->setCheckable(true);
		action->setData(languageId);
		action->setChecked(isCurrentLanguage);
	}
}


/**
 * Retranslates all strings.
 */
void SelectLanguageMenu::retranslateUI()
{
	this->setTitle(tr("&Language"));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
bool SelectLanguageMenu::event(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	return QMenu::event(event);
}

}
}
