#include "AbstractController.hpp"
#include "ControllerManager.hpp"

namespace GUI
{

/**
 * Creates a new abstract controller.
 *
 * @param manager The controller manager.
 */
AbstractController::AbstractController(ControllerManager* manager) :
	QObject(manager), manager(manager)
{
}

/**
 * Frees all used resources.
 */
AbstractController::~AbstractController()
{

}

/**
 * Returns whether the controller should be deactivated or not.
 *
 * This method is called by the controller manager before deactivating a controller, it can be
 * reimplemented to show a confirmation message and possibly discard the request for deactivation.
 *
 * @return When the controller should be deactivated true, otherwise false.
 */
bool AbstractController::confirmDeactivation()
{
	return true;
}

/**
 * Asks the controller manager to deactivate this controller.
 *
 * The manager will call the confirmDeactivation() method of this object and if it returns false the
 * controller is not deactivated and this method returns false.
 *
 * If the controller is not active, does nothing and returns true.
 *
 * @return When this controller is deactivated true, otherwise false.
 */
bool AbstractController::requestDeactivation()
{
	bool result = true;

	if (this->manager->getCurrentController() == this)
	{
		if (!this->manager->requestController(nullptr))
		{
			result = false;
		}
	}

	return result;
}

/**
 * Asks the controller manager to activate this controller.
 *
 * The manager can refuse this request, in that case this method returns false.
 *
 * If the controller is already active, does nothing and returns true.
 *
 * @return When this controller is active true, otherwise false.
 */
bool AbstractController::requestActivation()
{
	if (this->manager->getCurrentController() != this)
	{
		if (!this->manager->requestController(this))
		{
			return false;
		}
	}

	return true;
}

/**
 * Returns whether this controller is currently active.
 *
 * @return When it is active true, otherwise false.
 */
bool AbstractController::isActive() const
{
	return this->manager->getCurrentController() == this;
}

/**
 * Returns the main window for which the controller manager manages the central widget.
 *
 * @return The main window.
 */
QMainWindow* AbstractController::getMainWindow() const
{
	return this->manager->getMainWindow();
}

/**
 * Invoked by the controller manager when the controller is activated.
 *
 * getWidget() must return a valid widget after this method was called.
 *
 * This method must emit activated().
 */
void AbstractController::activate()
{
	emit this->activated();
}

/**
 * Invoked by the controller manager when the controller is deactivated.
 *
 * getWidget() is not required to return a valid widget after this method was called anymore.
 *
 * This method must emit deactivated().
 */
void AbstractController::deactivate()
{
	emit this->deactivated();
}

}
