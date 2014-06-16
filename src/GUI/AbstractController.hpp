#ifndef GUI_ABSTRACTCONTROLLER_HPP
#define GUI_ABSTRACTCONTROLLER_HPP

#include <QObject>

class QMainWindow;

namespace GUI
{

class ControllerManager;

/**
 * Abstract base class for controllers, provides methods for activation/deactivation.
 *
 * This is the base class for all controllers. It provides methods for activation/deactivation of
 * the controller. Use requestDeactivation to request the manager to deactivate the controller,
 * requestActivation() can be used to request an activation. With isActive() it is possible to
 * find out whether the controller is currently active or not.
 *
 * It is possible to reimplement confirmDeactivation() to display a confirmation dialog or so when
 * deactivation is requested.
 *
 * The getWidget() method must be reimplemented, it should return the widget that is shown as
 * central widget of the main window when the controller is active. The widget must stay valid as
 * long as the controller is active. It is possible to initialize the widget in activate() and
 * delete it in deactivate().
 */
class AbstractController : public QObject
{
		Q_OBJECT
	public:
		explicit AbstractController(ControllerManager* manager);
		virtual ~AbstractController();

		virtual bool confirmDeactivation();
		bool requestDeactivation();
		bool requestActivation();
		bool isActive() const;

		/**
		 * Returns the main widget of this controller which will be the central widget of the main
		 * window.
		 *
		 * It is the responsibility of the controller to make sure this method returns a valid
		 * widget pointer after activate() is called. The widget will be used until deactivate()
		 * is called. Using the widget after deactivate() is called is undefined behaviour.
		 *
		 * @return The main widget of the controller.
		 */
		virtual QWidget* getWidget() const = 0;

	signals:
		/**
		 * Emitted when the controller is activated.
		 */
		void activated();

		/**
		 * Emitted when the controller is deactivated.
		 */
		void deactivated();

	protected:
		QMainWindow* getMainWindow() const;

		virtual void activate();
		virtual void deactivate();

		/**
		 * Manages active controller, used to request activation.
		 */
		ControllerManager* manager;

	private:
		Q_DISABLE_COPY(AbstractController)

		/**
		 * The controller manager needs to access activate() and deactivate().
		 */
		friend class ControllerManager;
};

}

#endif // GUI_ABSTRACTCONTROLLER_HPP
