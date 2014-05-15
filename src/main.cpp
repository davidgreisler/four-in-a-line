#include "GUI/MainWindow.hpp"

#include <QApplication>

/**
 * Connect four game.
 *
 * @param argc Argument count.
 * @param argv Array of command line arguments.
 * @return 0 on success, an integer >0 if an error occurs.
 */
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	GUI::MainWindow mainWindow;
	mainWindow.show();

	return app.exec();
}
