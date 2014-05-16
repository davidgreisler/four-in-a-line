#include "ConnectFourSettings.hpp"

#include <QApplication>

/**
 * Creates a new settings container and reads all settings.
 *
 * @param parent Parent object.
 */
ConnectFourSettings::ConnectFourSettings(QObject *parent) :
	QObject(parent)
{
	QString organization = QApplication::organizationName();
	QString applicationName = QApplication::applicationName();
	this->settings = QSharedPointer<QSettings>(new QSettings(organization, applicationName));

	this->applicationSettings = new Settings::Application(this->settings, this);

	this->read();
}

/**
 * Frees all used resources.
 */
ConnectFourSettings::~ConnectFourSettings()
{

}

/**
 * Returns application settings.
 *
 * @return Application settings.
 */
Settings::Application* ConnectFourSettings::getApplicationSettings() const
{
	return this->applicationSettings;
}

/**
 * Reads all settings and emits changed().
 */
void ConnectFourSettings::read()
{
	this->applicationSettings->read();

	emit this->changed();
}

/**
 * Emits changed().
 */
void ConnectFourSettings::apply()
{
	emit this->changed();
}

/**
 * Saves all settings and emits saved().
 */
void ConnectFourSettings::save()
{
	this->applicationSettings->save();

	emit this->saved();
}
