#include "FourInALine.hpp"
#include "FourInALineSettings.hpp"

#include <QDir>
#include <QLibraryInfo>
#include <QDebug>

/**
 * Creates a new application.
 *
 * @param argc Argument count.
 * @param argv Array containing command line arguments.
 */
FourInALine::FourInALine(int& argc, char** argv)
	: QApplication(argc, argv)
{
	QApplication::setOrganizationDomain("");
	QApplication::setOrganizationName("MM-EMS");
	QApplication::setApplicationName("FourInALine");
	QApplication::setApplicationVersion("0.1");

	this->settings = new FourInALineSettings(this);

	this->setLanguage(this->settings->getApplicationSettings()->getLanguage());
	this->installTranslator(&this->qtTranslator);
	this->installTranslator(&this->appTranslator);

	this->connect(settings->getApplicationSettings(), &Settings::Application::changed,
				  this, &FourInALine::updateLanguage);
}

/**
 * Frees all used resources.
 */
FourInALine::~FourInALine()
{

}

/**
 * Returns settings object.
 *
 * @return Settings.
 */
FourInALineSettings* FourInALine::getSettings() const
{
	return this->settings;
}

/**
 * Returns the instance of the FourInALine application.
 *
 * @return The FourInALine application.
 */
FourInALine* FourInALine::getInstance()
{
	QCoreApplication* app = FourInALine::instance();
	FourInALine* fourInALine = static_cast<FourInALine*>(app);

	return fourInALine;
}

/**
 * Returns a map containing the available languages.
 *
 * The language name is the value and the key is the language locale used by
 * setLanguage/getLanguage.
 *
 * @return Map containing all available languages.
 */
QMap<QString, QString> FourInALine::getAvailableLanguages() const
{
	QMap<QString, QString> languages;
	QDir qmDirectory = QDir(":/i18n/");
	QStringList qmFiles = qmDirectory.entryList(QStringList("fourinaline_*.qm"));

	for (int i = 0; i < qmFiles.size(); ++i)
	{
		QString locale = qmFiles[i];

		// Transform filename to locale, e.g. "fourinaline_en.qm" -> "en".

		locale.remove(0, locale.indexOf('_') + 1);
		locale.chop(3);

		QTranslator translator;
		translator.load(qmFiles[i], qmDirectory.absolutePath());

		QString languageName = translator.translate("FourInALine", "LANGUAGE_NAME");

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
void FourInALine::setLanguage(QString locale)
{
	this->qtTranslator.load("qt_" + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	this->appTranslator.load("fourinaline_" + locale, ":/i18n/");

	this->currentLanguage = locale;

	qDebug() << "[" << this << "] Language switched to: " << locale;
}

/**
 * Returns the current locale.
 *
 * @return Current locale.
 */
QString FourInALine::getLanguage() const
{
	return this->currentLanguage;
}

/**
 * Changes the application language to the language currently configured in the settings.
 */
void FourInALine::updateLanguage()
{
	auto applicationSettings = settings->getApplicationSettings();

	this->setLanguage(applicationSettings->getLanguage());
}
