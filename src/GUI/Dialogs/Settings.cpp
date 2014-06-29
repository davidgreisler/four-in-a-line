#include "Settings.hpp"
#include "../../../app/FourInALine.hpp"
#include "../../Settings/FourInALine.hpp"

#include <QEvent>
#include <QGridLayout>
#include <QPushButton>
#include <QDialogButtonBox>

class QEvent;

namespace GUI
{
namespace Dialogs
{

/**
 * Creates a new settings dialog.
 *
 * @param parent Parent widget.
 */
Settings::Settings(QWidget *parent) :
    QDialog(parent)
{
	this->layout = new QGridLayout;
	this->setLayout(this->layout);

	auto applicationSettings = ::FourInALine::getInstance()->getSettings()->getApplicationSettings();
	auto viewSettings = ::FourInALine::getInstance()->getSettings()->getViewSettings();
	auto soundSettings = ::FourInALine::getInstance()->getSettings()->getSoundSettings();

	this->applicationSettingsWidget =
	        new ::GUI::Widgets::ApplicationSettings(applicationSettings, this);
	this->layout->addWidget(this->applicationSettingsWidget, 0, 0, 1, 1);

	this->viewSettingsWidget = new ::GUI::Widgets::ViewSettings(viewSettings, this);
	this->layout->addWidget(this->viewSettingsWidget, 1, 0, 1, 1);

	this->soundSettingsWidget = new ::GUI::Widgets::SoundSettings(soundSettings, this);
	this->layout->addWidget(this->soundSettingsWidget, 2, 0, 1, 1);

	this->buttonBox = new QDialogButtonBox(this);
	this->layout->addWidget(this->buttonBox, 3, 0, 1, 1);

	this->resetButton = new QPushButton(this);
	this->buttonBox->addButton(this->resetButton, QDialogButtonBox::ActionRole);
	this->connect(this->resetButton, &QPushButton::clicked, this, &Settings::reset);

	this->applyButton = new QPushButton(this);
	this->buttonBox->addButton(this->applyButton, QDialogButtonBox::ActionRole);
	this->connect(this->applyButton, &QPushButton::clicked, this, &Settings::apply);

	this->saveButton = new QPushButton(this);
	this->buttonBox->addButton(this->saveButton, QDialogButtonBox::ActionRole);
	this->connect(this->saveButton, &QPushButton::clicked, this, &Settings::write);

	this->closeButton = new QPushButton(this);
	this->buttonBox->addButton(this->closeButton, QDialogButtonBox::ActionRole);
	this->connect(this->closeButton, &QPushButton::clicked, this, &Settings::close);

	this->reset();
	this->retranslateUI();
}

/**
 * Frees all used resources.
 */
Settings::~Settings()
{

}

/**
 * Loads the current settings.
 */
void Settings::reset()
{
	this->applicationSettingsWidget->reset();
	this->viewSettingsWidget->reset();
	this->soundSettingsWidget->reset();
}

/**
 * Loads the settings from the configuration file.
 */
void Settings::read()
{
	this->applicationSettingsWidget->read();
	this->viewSettingsWidget->read();
	this->soundSettingsWidget->read();
}

/**
 * Writes the current configuration to the configuration file.
 */
void Settings::write()
{
	this->applicationSettingsWidget->write();
	this->viewSettingsWidget->write();
	this->soundSettingsWidget->write();
}

/**
 * Applies the current configuration.
 */
void Settings::apply()
{
	this->applicationSettingsWidget->apply();
	this->viewSettingsWidget->apply();
	this->soundSettingsWidget->apply();
}

/**
 * Closes the dialog.
 */
void Settings::close()
{
	this->accept();
}

/**
 * Retranslates all strings.
 */
void Settings::retranslateUI()
{
	this->setWindowTitle(this->tr("Settings"));
	this->resetButton->setText(this->tr("Reset"));
	this->applyButton->setText(this->tr("Apply"));
	this->saveButton->setText(this->tr("Save"));
	this->closeButton->setText(this->tr("Close"));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
void Settings::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	QDialog::changeEvent(event);
}

}
}
