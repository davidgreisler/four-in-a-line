#include "ConnectFour.hpp"

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
}

/**
 * Frees all used resources.
 */
ConnectFour::~ConnectFour()
{

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
