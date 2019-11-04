//
//
//

#ifndef AEYON3D_SDLINPUT_HPP
#define AEYON3D_SDLINPUT_HPP

#include <cstdint>
#include "Input.hpp"


namespace aeyon
{
	class SDLInput : public Input
	{
	private:
		struct MouseState
		{
			uint32_t buttonState;
			int x, y;
		};

		const uint8_t* m_keyboardState;
		MouseState m_mouseState;
		MouseState m_mouseStateRelative;

	public:
		SDLInput();

		void update() override;
		bool isKeyDown(KeyCode keycode) const override;
		bool isKeyUp(KeyCode keycode) const override;
		glm::vec2 getMousePosition() const override;
		glm::vec2 getMouseMotion() const override;
	};
}


#endif //AEYON3D_SDLINPUT_HPP
