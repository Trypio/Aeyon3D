//
//
//

#include "Input/SDLInput.hpp"
#include <SDL2/SDL.h>

namespace aeyon
{
	SDLInput::SDLInput()
	{
		m_keyboardState = SDL_GetKeyboardState(nullptr);
	}

	void SDLInput::update()
	{
		SDL_PumpEvents();

		m_mouseState.buttonState = SDL_GetMouseState(&m_mouseState.x, &m_mouseState.y);
		m_mouseStateRelative.buttonState = SDL_GetRelativeMouseState(&m_mouseStateRelative.x, &m_mouseStateRelative.y);
	}

	bool SDLInput::isKeyDown(KeyCode keycode) const
	{
		return m_keyboardState[static_cast<SDL_Scancode>(keycode)];
	}

	bool SDLInput::isKeyUp(KeyCode keycode) const
	{
		return !isKeyDown(keycode);
	}

	glm::vec2 SDLInput::getMousePosition() const
	{
		return glm::vec2(m_mouseState.x, m_mouseState.y);
	}

	glm::vec2 SDLInput::getMouseMotion() const
	{
		return glm::vec2(m_mouseStateRelative.x, m_mouseStateRelative.y);
	}
}