#include "View.hpp"

namespace Settings
{

/**
 * Creates a new view settings container.
 *
 * @param settings Key/value storage to use.
 * @param parent Parent object.
 */
View::View(QSharedPointer<QSettings> settings, QObject *parent) :
    AbstractSettings(settings, parent)
{

}

/**
 * Sets fullscreen option to the given value.
 *
 * @param fullscreen When the main window should be displayed fullscreen true, otherwise false.
 */
void View::setFullscreen(bool fullscreen)
{
	this->fullscreen = fullscreen;
}

/**
 * Returns whether fullscreen mode should be used or not.
 *
 * @return When fullscreen should be used true, otherwise false.
 */
bool View::isFullscreen() const
{
	return this->fullscreen;
}

/**
 * Sets the current theme.
 *
 * @param themeName Name of the theme.
 */
void View::setTheme(QString themeName)
{
	this->theme = themeName;
}

/**
 * Returns the name of the current theme.
 *
 * @return Current theme name.
 */
QString View::getTheme() const
{
	return this->theme;
}

/**
 * Returns map mapping theme names to translated/display names of themes.
 *
 * @return Map with themes.
 */
QMap<QString, QString> View::getThemeList() const
{
	QMap<QString, QString> themeList;

	themeList["standard"] = this->tr("Standard");
	themeList["dark"] = this->tr("Dark");
	themeList["white"] = this->tr("White");

	return themeList;
}

/**
 * Sets the stored window geometry of the window with the given name to the given geometry.
 *
 * @param windowName Name of the window.
 * @param geometry New geometry.
 */
void View::setWindowGeometry(QString windowName, QByteArray geometry)
{
	this->windowGeometries.insert(windowName, geometry);
}

/**
 * Returns the stored geometry of the window with the given name or an empty byte array when no
 * stored geometry is found for the given window name.
 *
 * @param windowName Name of the window.
 * @return Window geometry or empty byte array if no geometry was stored for the given window name.
 */
QByteArray View::getWindowGeometry(QString windowName)
{
	return this->windowGeometries.value(windowName, QByteArray());
}

/**
 * Sets the stored window state of the window with the given name to the given state.
 *
 * @param windowName Name of the window.
 * @param state New state.
 */
void View::setWindowState(QString windowName, QByteArray state)
{
	this->windowStates.insert(windowName, state);
}

/**
 * Returns the stored state of the window with the given name or an empty byte array when no state
 * is found for the given window name.
 *
 * @param windowName Name of the window.
 * @return Window state or empty byte array if no state was stored for the given window name.
 */
QByteArray View::getWindowState(QString windowName)
{
	return this->windowStates.value(windowName, QByteArray());
}

void View::read()
{
	QSharedPointer<QSettings> settings = this->getSettings();
	QStringList windowNames;
	QStringList::ConstIterator it;
	QString settingsPath;

	this->fullscreen = settings->value("view/is_fullscreen", false).toBool();
	this->theme = settings->value("view/theme_name", "standard").toString();

	settings->beginGroup("view/window/");

	windowNames = settings->childGroups();
	it = windowNames.constBegin();
	while (it != windowNames.constEnd())
	{
		settingsPath = QString("%1/geometry").arg(*it);
		this->windowGeometries.insert(*it, settings->value(settingsPath).toByteArray());

		settingsPath = QString("%1/state").arg(*it);
		this->windowStates.insert(*it, settings->value(settingsPath).toByteArray());

		++it;
	}

	settings->endGroup();
}

void View::save()
{
	QSharedPointer<QSettings> settings = this->getSettings();
	QMap<QString, QByteArray>::ConstIterator it;

	settings->setValue("view/is_fullscreen", this->fullscreen);
	settings->setValue("view/theme_name", this->theme);

	it = this->windowGeometries.constBegin();
	while (it != this->windowGeometries.constEnd())
	{
		settings->setValue(QString("view/window/%1/geometry").arg(it.key()), it.value());
		++it;
	}

	it = this->windowStates.constBegin();
	while (it != this->windowStates.constEnd())
	{
		settings->setValue(QString("view/window/%1/state").arg(it.key()), it.value());
		++it;
	}
}

}
