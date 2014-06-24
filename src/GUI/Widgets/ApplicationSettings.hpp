#ifndef GUI_WIDGETS_APPLICATIONSETTINGS_HPP
#define GUI_WIDGETS_APPLICATIONSETTINGS_HPP

#include "../../Settings/Application.hpp"

#include <QGroupBox>

class QFormLayout;
class QLabel;
class QComboBox;

namespace GUI
{
namespace Widgets
{

/**
 * Widget for configuring application settings.
 *
 * This widget provides slots for loading/applying/saving the settings.
 */
class ApplicationSettings : public QGroupBox
{
		Q_OBJECT
	public:
		explicit ApplicationSettings(::Settings::Application* applicationSettings,
									 QWidget *parent = 0);
		virtual ~ApplicationSettings();

	signals:

	public slots:
		void reset();
		void read();
		void write();
		void apply();

		void updateLanguages();

	private:
		Q_DISABLE_COPY(ApplicationSettings)

		void retranslateUI();
		bool event(QEvent* event);

		/**
		 * Application settings.
		 */
		::Settings::Application* applicationSettings;

		/**
		 * Layout of the form.
		 */
		QFormLayout* layout;

		/**
		 * Label for the language selection.
		 */
		QLabel* languageLabel;

		/**
		 * Combo box for selecting the language.
		 */
		QComboBox* languageComboBox;

};

}
}

#endif // GUI_WIDGETS_APPLICATIONSETTINGS_HPP
