#ifndef GUI_ABSTRACTVIEW_HPP
#define GUI_ABSTRACTVIEW_HPP

#include <QObject>

class QMainWindow;

namespace GUI
{

class ViewManager;

/**
 * Abstract base class for views, provides methods for activation/deactivation.
 *
 * This is the base class for all views. It provides methods for activation/deactivation of
 * the view. Use requestDeactivation to request the manager to deactivate the view,
 * requestActivation() can be used to request an activation. With isActive() it is possible to
 * find out whether the view is currently active or not.
 *
 * It is possible to reimplement confirmDeactivation() to display a confirmation dialog or so when
 * deactivation is requested.
 *
 * The getWidget() method must be reimplemented, it should return the widget that is shown as
 * central widget of the main window when the view is active. The widget must stay valid as
 * long as the view is active. It is possible to initialize the widget in activate() and
 * delete it in deactivate().
 */
class AbstractView : public QObject
{
		Q_OBJECT
	public:
		explicit AbstractView(ViewManager* manager);
		virtual ~AbstractView();

		virtual bool confirmDeactivation();
		bool requestDeactivation();
		bool requestActivation();
		bool isActive() const;

		/**
		 * Returns the main widget of this view which will be the central widget of the main
		 * window.
		 *
		 * It is the responsibility of the view to make sure this method returns a valid
		 * widget pointer after activate() is called. The widget will be used until deactivate()
		 * is called. Using the widget after deactivate() is called is undefined behaviour.
		 *
		 * @return The main widget of the view.
		 */
		virtual QWidget* getWidget() const = 0;

	signals:
		/**
		 * Emitted when the view is activated.
		 */
		void activated();

		/**
		 * Emitted when the view is deactivated.
		 */
		void deactivated();

	protected:
		QMainWindow* getMainWindow() const;

		virtual void activate();
		virtual void deactivate();

		/**
		 * Manages active view, used to request activation.
		 */
		ViewManager* manager;

	private:
		Q_DISABLE_COPY(AbstractView)

		/**
		 * The view manager needs to access activate() and deactivate().
		 */
		friend class ViewManager;
};

}

#endif // GUI_ABSTRACTVIEW_HPP
