//
//
//

#ifndef AEYON3D_INPUT_HPP
#define AEYON3D_INPUT_HPP

#include "KeyChar.hpp"
#include "KeyCode.hpp"
#include "MouseButton.hpp"
#include <glm/glm.hpp>

namespace aeyon
{
	class Input
	{
    public:
		virtual ~Input() = default;

		virtual void update() = 0;

        virtual bool getKey(KeyCode keycode) const = 0;
		virtual bool getKeyDown(KeyCode keycode) const = 0;
		virtual bool getKeyUp(KeyCode keycode) const = 0;
        virtual bool getMouseButton(MouseButton mouseButton) const = 0;
        virtual bool getMouseButtonDown(MouseButton mouseButton) const = 0;
        virtual bool getMouseButtonUp(MouseButton mouseButton) const = 0;
		virtual glm::vec2 getMousePosition() const = 0;
		virtual glm::vec2 getMouseMotion() const = 0;
	};
}

#endif //AEYON3D_INPUT_HPP
