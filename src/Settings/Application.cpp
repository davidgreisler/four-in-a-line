#include "Application.hpp"

namespace Settings
{

/**
 * Creates a new application settings container and reads settings from given key/value storage.
 *
 * @param settings Key/value storage to use for storing/retrieving settings.
 * @param parent Parent object.
 */
Application::Application(QSharedPointer<QSettings> settings, QObject *parent) :
	AbstractSettings(settings, parent)
{
	this->read();
}

/**
 * Returns the current application's language.
 *
 * @return The current language.
 */
QString Application::getLanguage() const
{
	return this->language;
}

/**
 * Sets the application's language to the given locale.
 *
 * @param locale Locale of the language to use.
 */
void Application::setLanguage(QString locale)
{
	this->language = locale;
}

void Application::read()
{
	this->language = this->getSettings()->value(this->language, "en").toString();

	emit this->changed();
}

void Application::save()
{
	emit this->changed();

	this->getSettings()->setValue("application/language", this->language);

	emit this->saved();
}

}
