#ifndef CONNECTFOUR_HPP
#define CONNECTFOUR_HPP

#include <QApplication>

/**
 * Sets up application at start and contains frequently used objects.
 */
class ConnectFour : public QApplication
{
	public:
		ConnectFour(int& argc, char** argv);
		virtual ~ConnectFour();

		static ConnectFour* getInstance();

	private:

};

#endif // CONNECTFOUR_HPP
