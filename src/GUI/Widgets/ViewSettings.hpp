#ifndef GUI_WIDGETS_VIEWSETTINGS_HPP
#define GUI_WIDGETS_VIEWSETTINGS_HPP

#include "../../Settings/View.hpp"

#include <QGroupBox>

class QCheckBox;
class QLabel;
class QFormLayout;
class QComboBox;

namespace GUI
{
namespace Widgets
{

/**
 * Widget for configuring view settings.
 *
 * This widget provides slots for loading/applying/saving the settings.
 */
class ViewSettings : public QGroupBox
{
		Q_OBJECT
	public:
		explicit ViewSettings(::Settings::View* viewSettings, QWidget* parent = 0);
		virtual ~ViewSettings();

	public slots:
		void reset();
		void read();
		void apply();
		void write();

	private:
		Q_DISABLE_COPY(ViewSettings)

		void retranslateUI();
		bool event(QEvent* event);

		/**
		 * The view settings.
		 */
		::Settings::View* viewSettings;

		/**
		 * Layout of the form.
		 */
		QFormLayout* layout;

		/**
		 * Checkbox for toggling fullscreen mode.
		 */
		QCheckBox* fullscreenCheckBox;

		/**
		 * Label for the theme combo box.
		 */
		QLabel* themeLabel;

		/**
		 * Combo box for selecting a theme.
		 */
		QComboBox* themeComboBox;
};

}
}

#endif // GUI_WIDGETS_VIEWSETTINGS_HPP
