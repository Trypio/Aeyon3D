//
//
//

#ifndef AEYON3D_SDLINPUT_HPP
#define AEYON3D_SDLINPUT_HPP

#include <cstdint>
#include "Input.hpp"
#include <memory>


namespace aeyon
{
    class EventSystem;

	class SDLInput : public Input
	{
	private:
		struct MouseState
		{
			uint32_t buttonState;
			int x, y;
		};

		const uint8_t* m_keyboardState;
        std::unique_ptr<uint8_t[]> m_keyboardStatePrevious;
        std::unique_ptr<bool[]> m_keyboardStateDiff;
        int m_num_keys;
		MouseState m_mouseState;
		MouseState m_mouseStateRelative;

	public:
		SDLInput();

		void update() override;
        bool getKey(KeyCode keycode) const override;
		bool getKeyDown(KeyCode keycode) const override;
		bool getKeyUp(KeyCode keycode) const override;
        bool getMouseButton(MouseButton mouseButton) const override;
        bool getMouseButtonDown(MouseButton mouseButton) const override;
        bool getMouseButtonUp(MouseButton mouseButton) const override;
        glm::vec2 getMousePosition() const override;
		glm::vec2 getMouseMotion() const override;
	};
}


#endif //AEYON3D_SDLINPUT_HPP
