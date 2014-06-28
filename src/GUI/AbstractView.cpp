#include "AbstractView.hpp"
#include "ViewManager.hpp"

namespace GUI
{

/**
 * Creates a new abstract view.
 *
 * @param manager The view manager.
 */
AbstractView::AbstractView(ViewManager* manager) :
    QObject(manager), manager(manager)
{
}

/**
 * Frees all used resources.
 */
AbstractView::~AbstractView()
{

}

/**
 * Returns whether the view should be deactivated or not.
 *
 * This method is called by the view manager before deactivating a view, it can be
 * reimplemented to show a confirmation message and possibly discard the request for deactivation.
 *
 * @return When the view should be deactivated true, otherwise false.
 */
bool AbstractView::confirmDeactivation()
{
	return true;
}

/**
 * Asks the view manager to deactivate this view.
 *
 * The manager will call the confirmDeactivation() method of this object and if it returns false the
 * view is not deactivated and this method returns false.
 *
 * If the view is not active, does nothing and returns true.
 *
 * @return When this view is deactivated true, otherwise false.
 */
bool AbstractView::requestDeactivation()
{
	bool result = true;

	if (this->manager->getCurrentView() == this)
	{
		if (!this->manager->requestView(nullptr))
		{
			result = false;
		}
	}

	return result;
}

/**
 * Asks the view manager to activate this view.
 *
 * The manager can refuse this request, in that case this method returns false.
 *
 * If the view is already active, does nothing and returns true.
 *
 * @return When this view is active true, otherwise false.
 */
bool AbstractView::requestActivation()
{
	if (this->manager->getCurrentView() != this)
	{
		if (!this->manager->requestView(this))
		{
			return false;
		}
	}

	return true;
}

/**
 * Returns whether this view is currently active.
 *
 * @return When it is active true, otherwise false.
 */
bool AbstractView::isActive() const
{
	return this->manager->getCurrentView() == this;
}

/**
 * Returns the main window for which the view manager manages the central widget.
 *
 * @return The main window.
 */
QMainWindow* AbstractView::getMainWindow() const
{
	return this->manager->getMainWindow();
}

/**
 * Invoked by the view manager when the view is activated.
 *
 * getWidget() must return a valid widget after this method was called.
 *
 * This method must emit activated().
 */
void AbstractView::activate()
{
	emit this->activated();
}

/**
 * Invoked by the view manager when the view is deactivated.
 *
 * getWidget() is not required to return a valid widget after this method was called anymore.
 *
 * This method must emit deactivated().
 */
void AbstractView::deactivate()
{
	emit this->deactivated();
}

}
