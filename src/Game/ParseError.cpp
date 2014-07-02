#include "ParseError.hpp"

namespace Game
{

/**
 * Creates a new parse error with the given message.
 *
 * @param message Message describing the error.
 */
ParseError::ParseError(QString message)
    : std::runtime_error(message.toStdString())
{

}

/**
 * Frees all used resources.
 */
ParseError::~ParseError() noexcept
{

}

}
