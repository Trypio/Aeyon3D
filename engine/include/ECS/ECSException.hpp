//
//
//

#ifndef AEYON3D_ECSEXCEPTION_HPP
#define AEYON3D_ECSEXCEPTION_HPP

#include <exception>
#include <string>

namespace aeyon
{
	/**
	 * Thrown by the ECS in case of error.
	 */
	class ECSException : public std::exception
	{
	private:
		std::string m_error;

	public:
		explicit ECSException(const std::string& error);

		const char* what() const noexcept override;
	};
}

#endif //AEYON3D_ECSEXCEPTION_HPP
