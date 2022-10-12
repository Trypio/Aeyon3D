//
//
//

#include "Input/SDLInput.hpp"
#include <SDL2/SDL.h>
#include "Input/MouseButton.hpp"

namespace aeyon
{
    static constexpr std::uint32_t ToMouseButtonMask(MouseButton button)
    {
        return 1 << (static_cast<std::uint32_t>(button) - 1);
    }

	SDLInput::SDLInput()
	{
		m_keyboardState = SDL_GetKeyboardState(&m_num_keys);
        m_keyboardStatePrevious = std::make_unique<uint8_t[]>(m_num_keys);
        m_keyboardStateDiff = std::make_unique<bool[]>(m_num_keys);
	}

	void SDLInput::update()
	{
		m_mouseState.buttonState = SDL_GetMouseState(&m_mouseState.x, &m_mouseState.y);
		m_mouseStateRelative.buttonState = SDL_GetRelativeMouseState(&m_mouseStateRelative.x, &m_mouseStateRelative.y);

        for (int i = 0; i < m_num_keys; i++)
        {
            m_keyboardStateDiff[i] = m_keyboardState[i] != m_keyboardStatePrevious[i];
        }

        memcpy(m_keyboardStatePrevious.get(), m_keyboardState, m_num_keys);
	}

    bool SDLInput::getKey(KeyCode keycode) const
    {
        return m_keyboardState[static_cast<SDL_Scancode>(keycode)];
    }

    bool SDLInput::getKeyDown(KeyCode keycode) const
	{
        auto scancode = static_cast<SDL_Scancode>(keycode);
        return m_keyboardStateDiff[scancode] && m_keyboardState[scancode];
	}

	bool SDLInput::getKeyUp(KeyCode keycode) const
	{
        auto scancode = static_cast<SDL_Scancode>(keycode);
        return m_keyboardStateDiff[scancode] && !m_keyboardState[scancode];
	}

	glm::vec2 SDLInput::getMousePosition() const
	{
		return glm::vec2(m_mouseState.x, m_mouseState.y);
	}

	glm::vec2 SDLInput::getMouseMotion() const
	{
		return glm::vec2(m_mouseStateRelative.x, m_mouseStateRelative.y);
	}

    bool SDLInput::getMouseButton(MouseButton mouseButton) const
    {
        return m_mouseState.buttonState & ToMouseButtonMask(mouseButton);
    }

    bool SDLInput::getMouseButtonDown(MouseButton mouseButton) const
    {
        return false;
    }

    bool SDLInput::getMouseButtonUp(MouseButton mouseButton) const
    {
        return false;
    }
}
