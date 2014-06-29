#include "SoundSettings.hpp"

#include <QSlider>
#include <QFormLayout>
#include <QLabel>
#include <QEvent>
#include <QDebug>
#include <QCheckBox>

namespace GUI
{
namespace Widgets
{

/**
 * Creates a new sound settings widget.
 *
 * @param soundSettings Sound settings.
 * @param parent Parent widget.
 */
SoundSettings::SoundSettings(Settings::Sound* soundSettings, QWidget *parent) :
    QGroupBox(parent), soundSettings(soundSettings)
{
	this->layout = new QFormLayout(this);
	this->setLayout(this->layout);

	this->soundEnabledCheckBox = new QCheckBox(this);
	this->layout->addWidget(this->soundEnabledCheckBox);

	this->volumeLabel = new QLabel(this);
	this->volumeSlider = new QSlider(Qt::Horizontal, this);
	this->volumeSlider->setMaximum(100);
	this->layout->addRow(this->volumeLabel, this->volumeSlider);

	this->reset();
	this->retranslateUI();
}

/**
 * Frees all used resources.
 */
SoundSettings::~SoundSettings()
{

}

/**
 * Loads the current settings.
 */
void SoundSettings::reset()
{
	int volumeInteger = this->soundSettings->getVolume() * 100;

	this->soundEnabledCheckBox->setChecked(this->soundSettings->isSoundEnabled());
	this->volumeSlider->setValue(volumeInteger);
}

/**
 * Loads the settings from the settings file.
 */
void SoundSettings::read()
{
	this->soundSettings->read();
	this->soundEnabledCheckBox->setChecked(this->soundSettings->isSoundEnabled());
}

/**
 * Applies the current configuration.
 */
void SoundSettings::apply()
{
	float volume = (float)this->volumeSlider->value() / 100;

	this->soundSettings->setSoundEnabled(this->soundEnabledCheckBox->isChecked());
	this->soundSettings->setVolume(volume);
	this->soundSettings->apply();
}

/**
 * Saves and applies the current configuration to the settings file.
 */
void SoundSettings::write()
{
	this->apply();
	this->soundSettings->save();
}

/**
 * Retranslates all strings.
 */
void SoundSettings::retranslateUI()
{
	this->setTitle(this->tr("Sound settings"));
	this->volumeLabel->setText(this->tr("Volume"));
	this->soundEnabledCheckBox->setText(this->tr("Sound enabled"));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
bool SoundSettings::event(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	return QGroupBox::event(event);
}

}
}
