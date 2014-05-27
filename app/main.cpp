#include "../src/GUI/MainWindow.hpp"
#include "../src/FourInALine.hpp"

/**
 * Four in a line game.
 *
 * @param argc Argument count.
 * @param argv Array of command line arguments.
 * @return 0 on success, an integer >0 if an error occurs.
 */
int main(int argc, char *argv[])
{
	FourInALine app(argc, argv);

	GUI::MainWindow mainWindow;
	mainWindow.show();

	return app.exec();
}
