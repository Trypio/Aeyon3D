//
//
//

#include "ECSException.hpp"

namespace aeyon
{
	SDLException::SDLException(const std::string& error)
	: m_error(error)
	{
	}

	const char* SDLException::what() const noexcept
	{
		return m_error.c_str();
	}
}
