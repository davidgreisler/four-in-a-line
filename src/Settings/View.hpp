#ifndef SETTINGS_VIEW_HPP
#define SETTINGS_VIEW_HPP

#include "AbstractSettings.hpp"

#include <QMap>
#include <QByteArray>
#include <QString>

namespace Settings
{

/**
 * Contains view settings, stores window geometry/state.
 *
 * Whether the main window should be displayed full screen can be retrieved with isFullscreen(), and
 * set with setFullscreen().
 *
 * Window state/geometry can be set with setWindowState()/setWindowGeometry() and retrieved with
 * getWindowState()/getWindowGeometry().
 *
 * Do not forget to call read()/save() to read the stored values/save them!
 */
class View : public AbstractSettings
{
		Q_OBJECT
	public:
		explicit View(QSharedPointer<QSettings> settings, QObject *parent = 0);

		void setFullscreen(bool fullscreen);
		bool isFullscreen() const;

		void setWindowGeometry(QString windowName, QByteArray geometry);
		QByteArray getWindowGeometry(QString windowName);

		void setWindowState(QString windowName, QByteArray state);
		QByteArray getWindowState(QString windowName);

		virtual void read() override;
		virtual void save() override;

	private:
		Q_DISABLE_COPY(View)

		/**
		 * Whether the main window should be displayed in full screen mode or not.
		 */
		bool fullscreen;

		/**
		 * Maps window names to stored window geometries.
		 */
		QMap<QString, QByteArray> windowGeometries;

		/**
		 * Maps window names to stored window states.
		 */
		QMap<QString, QByteArray> windowStates;
};

}

#endif // SETTINGS_VIEW_HPP
