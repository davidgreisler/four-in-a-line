#ifndef GUI_VIEWMANAGER_HPP
#define GUI_VIEWMANAGER_HPP

#include <QObject>

class QMainWindow;

namespace GUI
{

class AbstractView;

/**
 * Manages central widget of the main window and currently active view.
 *
 * A view provides a specific functionality and a widget. This class manages the currently
 * visible/usable view and makes sure it's widget is shown as central widget of the main
 * window.
 *
 * It is possible to request a view to become active with requestView(), but the
 * currently active view can refuse the request, e.g. if the user clicked no in a confirmation
 * dialog. Reimplement AbstractView::confirmDeactivation() to change the behaviour when the
 * view is asked to deactivate. Use setView() to force switching to another view.
 *
 * The current view can be retrieved with getCurrentView().
 */
class ViewManager : public QObject
{
		Q_OBJECT
	public:
		explicit ViewManager(QMainWindow* mainWindow, QObject *parent = 0);
		virtual ~ViewManager();

		void setView(AbstractView* view);
		bool requestView(AbstractView* view);

		AbstractView* getCurrentView() const;
		QMainWindow* getMainWindow() const;

	signals:
		/**
		 * Emitted when a view is deactivated.
		 *
		 * @param view The view that was deactivated.
		 */
		void viewDeactivated(AbstractView* view);

		/**
		 * Emitted when a view is activated.
		 *
		 * @param view The view that was activated.
		 */
		void viewActivated(AbstractView* view);

	private:
		Q_DISABLE_COPY(ViewManager)

		/**
		 * Pointer to the main window, used to change central widget.
		 */
		QMainWindow* mainWindow;

		/**
		 * The currently active view.
		 */
		AbstractView* currentView;
};

}

#endif // GUI_VIEWMANAGER_HPP
