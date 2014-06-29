#ifndef GUI_WIDGETS_SOUNDSETTINGS_HPP
#define GUI_WIDGETS_SOUNDSETTINGS_HPP

#include "../../Settings/Sound.hpp"

#include <QGroupBox>

class QFormLayout;
class QCheckBox;
class QSlider;
class QLabel;

namespace GUI
{
namespace Widgets
{

/**
 * Widget for configuring sound settings.
 *
 * This widget contains a checkbox to enable/disable sound and a slider to change
 * the volume.
 */
class SoundSettings : public QGroupBox
{
		Q_OBJECT
	public:
		explicit SoundSettings(::Settings::Sound* soundSettings, QWidget* parent = 0);
		virtual ~SoundSettings();

	public slots:
		void reset();
		void read();
		void apply();
		void write();

	private:
		Q_DISABLE_COPY(SoundSettings)

		void retranslateUI();
		bool event(QEvent* event);

		/**
		 * The sound settings.
		 */
		::Settings::Sound* soundSettings;

		/**
		 * Layout of the form.
		 */
		QFormLayout* layout;

		/**
		 * Checkbox for toggling sound on/off.
		 */
		QCheckBox* soundEnabledCheckBox;

		/**
		 * Label for the volume slider.
		 */
		QLabel* volumeLabel;

		/**
		 * Slider for the volume.
		 */
		QSlider* volumeSlider;
};

}
}

#endif // GUI_WIDGETS_SOUNDSETTINGS_HPP
