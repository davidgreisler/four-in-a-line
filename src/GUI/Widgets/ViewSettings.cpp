#include "ViewSettings.hpp"

#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QEvent>

namespace GUI
{
namespace Widgets
{

/**
 * Creates a new view settings widget.
 *
 * @param viewSettings View settings.
 * @param parent Parent widget.
 */
ViewSettings::ViewSettings(Settings::View* viewSettings, QWidget *parent) :
    QGroupBox(parent), viewSettings(viewSettings)
{
	this->layout = new QFormLayout(this);
	this->setLayout(this->layout);

	this->fullscreenCheckBox = new QCheckBox(this);
	this->layout->addWidget(this->fullscreenCheckBox);

	this->themeLabel = new QLabel(this);
	this->themeComboBox = new QComboBox(this);
	this->layout->addRow(this->themeLabel, this->themeComboBox);

	this->reset();
	this->retranslateUI();
}

/**
 * Frees all used resources.
 */
ViewSettings::~ViewSettings()
{

}

/**
 * Loads the current settings.
 */
void ViewSettings::reset()
{
	this->fullscreenCheckBox->setChecked(this->viewSettings->isFullscreen());
}

/**
 * Loads the settings from the settings file.
 */
void ViewSettings::read()
{
	this->viewSettings->read();
	this->fullscreenCheckBox->setChecked(this->viewSettings->isFullscreen());
}

/**
 * Applies the current configuration.
 */
void ViewSettings::apply()
{
	this->viewSettings->setFullscreen(this->fullscreenCheckBox->isChecked());
	this->viewSettings->apply();
}

/**
 * Saves and applies the current configuration to the settings file.
 */
void ViewSettings::write()
{
	this->apply();
	this->viewSettings->save();
}

/**
 * Retranslates all strings.
 */
void ViewSettings::retranslateUI()
{
	this->setTitle(this->tr("View settings"));
	this->themeLabel->setText(this->tr("Theme"));
	this->fullscreenCheckBox->setText(this->tr("Fullscreen mode"));
}

/**
 * Retranslates strings when the application's language has been changed.
 *
 * @param event Change event.
 */
bool ViewSettings::event(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		this->retranslateUI();
	}

	return QGroupBox::event(event);
}

}
}
