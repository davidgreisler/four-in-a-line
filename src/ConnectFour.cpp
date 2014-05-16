#include "ConnectFour.hpp"
#include "ConnectFourSettings.hpp"

#include <QDir>
#include <QLibraryInfo>
#include <QDebug>

/**
 * Creates a new application.
 *
 * @param argc Argument count.
 * @param argv Array containing command line arguments.
 */
ConnectFour::ConnectFour(int& argc, char** argv)
	: QApplication(argc, argv)
{
	QApplication::setOrganizationDomain("");
	QApplication::setOrganizationName("MM-EMS");
	QApplication::setApplicationName("ConnectFour");
	QApplication::setApplicationVersion("0.1");

	this->settings = new ConnectFourSettings(this);

	this->setLanguage(this->settings->getApplicationSettings()->getLanguage());
	this->installTranslator(&this->qtTranslator);
	this->installTranslator(&this->appTranslator);
}

/**
 * Frees all used resources.
 */
ConnectFour::~ConnectFour()
{

}

/**
 * Returns settings object.
 *
 * @return Settings.
 */
ConnectFourSettings* ConnectFour::getSettings() const
{
	return this->settings;
}

/**
 * Returns the instance of the ConnectFour application.
 *
 * @return The ConnectFour application.
 */
ConnectFour* ConnectFour::getInstance()
{
	QCoreApplication* app = ConnectFour::instance();
	ConnectFour* connectFour = static_cast<ConnectFour*>(app);

	return connectFour;
}

/**
 * Returns a map containing the available languages.
 *
 * The language name is the value and the key is the language locale used by
 * setLanguage/getLanguage.
 *
 * @return Map containing all available languages.
 */
QMap<QString, QString> ConnectFour::getAvailableLanguages() const
{
	QMap<QString, QString> languages;
	QDir qmDirectory = QDir(":/i18n/");
	QStringList qmFiles = qmDirectory.entryList(QStringList("connectfour_*.qm"));

	for (int i = 0; i < qmFiles.size(); ++i)
	{
		QString locale = qmFiles[i];

		// Transform filename to locale, e.g. "connectfour_en.qm" -> "en".

		locale.remove(0, locale.indexOf('_') + 1);
		locale.chop(3);

		QTranslator translator;
		translator.load(qmFiles[i], qmDirectory.absolutePath());

		QString languageName = translator.translate("ConnectFour", "LANGUAGE_NAME");

		languages.insert(locale, languageName);
	}

	return languages;
}

/**
 * Sets the applications language.
 *
 * Does not save the language to the settings!
 *
 * @param locale The locale of the new language.
 */
void ConnectFour::setLanguage(QString locale)
{
	this->qtTranslator.load("qt_" + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	this->appTranslator.load("connectfour_" + locale, ":/i18n/");

	this->currentLanguage = locale;
}

/**
 * @brief ConnectFour::getLanguage
 * @return
 */
QString ConnectFour::getLanguage() const
{
	return this->currentLanguage;
}
