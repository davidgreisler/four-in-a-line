#ifndef GAME_PARSEERROR_HPP
#define GAME_PARSEERROR_HPP

#include <QString>

#include <stdexcept>

namespace Game
{

/**
 * Parse error thrown by savegame/replay parsers.
 */
class ParseError : public std::runtime_error
{
	public:
		ParseError(QString message);
		virtual ~ParseError() noexcept;
};

}

#endif // GAME_PARSEERROR_HPP
