#ifndef GUI_PARSEERROR_HPP
#define GUI_PARSEERROR_HPP

#include <QString>

#include <stdexcept>

namespace GUI
{

/**
 * Parse error thrown by savegame/replay parsers.
 */
class ParseError : public std::runtime_error
{
	public:
		ParseError(QString message);
		virtual ~ParseError();
};

}

#endif // GUI_PARSEERROR_HPP
