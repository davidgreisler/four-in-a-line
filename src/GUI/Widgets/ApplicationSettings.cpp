#include "ApplicationSettings.hpp"
#include "../../../app/FourInALine.hpp"

#include <QEvent>
#include <QLabel>
#include <QComboBox>
#include <QFormLayout>
#include <QMap>
#include <QString>

namespace GUI
{
namespace Widgets
{

/**
 * Creates a new application settings widget.
 *
 * @param applicationSettings Application settings.
 * @param parent Parent widget.
 */
ApplicationSettings::ApplicationSettings(Settings::Application* applicationSettings, QWidget *parent) :
    QGroupBox(parent), applicationSettings(applicationSettings)
{
	this->layout = new QFormLayout(this);
	this->setLayout(this->layout);

	this->languageLabel = new QLabel(this);
	this->languageComboBox = new QComboBox(this);
	this->layout->addRow(this->languageLabel, this->languageComboBox);

	this->reset();
	this->retranslateUI();
}

/**
 * Frees all used resources.
 */
ApplicationSettings::~ApplicationSettings()
{

}

/**
 * Loads current settings.
 */
void ApplicationSettings::reset()
{
	this->updateLanguages();
}

/**
 * Loads the settings from the configuration file.
 */
void ApplicationSettings::read()
{
	this->applicationSettings->read();
	this->updateLanguages();
}

/**
 * Applies the current changes to the configuration.
 */
void ApplicationSettings::apply()
{
	QString locale = this->languageComboBox->currentData().toString();

	this->applicationSettings->setLanguage(locale);
	this->applicationSettings->apply();
}

/**
 * Saves and applies the current configuration to the configuration file.
 */
void ApplicationSettings::write()
{
	this->apply();
	this->applicationSettings->save();
}

/**
 * Clears language combo box and reloads language list/current language from application.
 */
void ApplicationSettings::updateLanguages()
{
	QMap<QString, QString> languages = ::FourInALine::getInstance()->getAvailableLanguages();
	QString currentLanguage = ::FourInALine::getInstance()->getLanguage();

	this->languageComboBox->clear();

	for (auto i = languages.cbegin(); i != languages.cend(); ++i)
	{
		this->languageComboBox->addItem(i.value(), i.key());
	}

	this->languageComboBox->setCurrentIndex(this->languageComboBox->findData(currentLanguage));
}

/**
 * Retranslates all strings.
 */
void ApplicationSettings::retranslateUI()
{
	this->setTitle(this->tr("Application settings"));
	this->languageLabel->setText(this->tr("Language"));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
bool ApplicationSettings::event(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	return QGroupBox::event(event);
}

}
}
