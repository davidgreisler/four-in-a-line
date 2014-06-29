#ifndef GUI_DIALOGS_SETTINGS_HPP
#define GUI_DIALOGS_SETTINGS_HPP

#include "../Widgets/ApplicationSettings.hpp"
#include "../Widgets/ViewSettings.hpp"
#include "../Widgets/SoundSettings.hpp"

#include <QDialog>

class QGridLayout;
class QDialogButtonBox;
class QPushButton;

namespace GUI
{
namespace Dialogs
{

/**
 * Settings dialog.
 *
 * This dialog contains widgets for configuring the application and view settings.
 *
 * It is possible to reload the settings from the configuration file, save them to the configuration
 * file and to apply the current changes. The current state can also be loaded with load(), this is
 * also done during construction of the dialog, so a newly created dialog shows the current
 * settings.
 */
class Settings : public QDialog
{
		Q_OBJECT
	public:
		explicit Settings(QWidget *parent = 0);
		virtual ~Settings();

	signals:

	public slots:
		void reset();
		void read();
		void write();
		void apply();
		void close();

	private:
		Q_DISABLE_COPY(Settings)

		void changeEvent(QEvent* event);
		void retranslateUI();

		/**
		 * Layout of the dialog.
		 */
		QGridLayout* layout;

		/**
		 * Group box containing application settings.
		 */
		::GUI::Widgets::ApplicationSettings* applicationSettingsWidget;

		/**
		 * Group box containing view settings.
		 */
		::GUI::Widgets::ViewSettings* viewSettingsWidget;

		/**
		 * Group box containing sound settings.
		 */
		::GUI::Widgets::SoundSettings* soundSettingsWidget;

		/**
		 * Button box for the dialog's buttons.
		 */
		QDialogButtonBox* buttonBox;

		/**
		 * Resets values to current configuration.
		 */
		QPushButton* resetButton;

		/**
		 * Applies settings.
		 */
		QPushButton* applyButton;

		/**
		 * Saves settings to file.
		 */
		QPushButton* saveButton;

		/**
		 * Closes the dialog.
		 */
		QPushButton* closeButton;
};

}
}

#endif // GUI_DIALOGS_SETTINGS_HPP
