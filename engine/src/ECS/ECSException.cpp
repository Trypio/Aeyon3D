//
//
//

#include "ECS/ECSException.hpp"

namespace aeyon
{
	ECSException::ECSException(const std::string& error)
	: m_error(error)
	{
	}

	const char* ECSException::what() const noexcept
	{
		return m_error.c_str();
	}
}
