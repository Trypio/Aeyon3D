//
//
//

#ifndef AEYON3D_SDLEXCEPTION_HPP
#define AEYON3D_SDLEXCEPTION_HPP

#include <exception>
#include <string>

namespace aeyon
{
	class SDLException : public std::exception
	{
	private:
		std::string m_error;

	public:
		explicit SDLException(const std::string& error);

		const char* what() const noexcept override;
	};
}

#endif //AEYON3D_SDLEXCEPTION_HPP
