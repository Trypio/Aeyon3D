//
//
//

#ifndef AEYON3D_WINDOW_HPP
#define AEYON3D_WINDOW_HPP

#include <string>

namespace aeyon
{
	class Window
	{
	public:
		virtual ~Window() = default;

		virtual void show() = 0;
		virtual void hide() = 0;
		virtual bool isHidden() const = 0;

		virtual void focus() = 0;
		virtual bool isFocused() const = 0;

		virtual void close() = 0;
		virtual bool shouldClose() const = 0;

		virtual void swapBuffers() = 0;

		virtual void setTitle(const std::string& title) = 0;
		virtual std::string getTitle() const = 0;

		virtual void setPosition(int x, int y) = 0;
		virtual int getPositionX() const = 0;
		virtual int getPositionY() const = 0;

		virtual void setSize(int width, int height) = 0;
		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;

		virtual void minimize() = 0;
		virtual void maximize() = 0;
		virtual void restore() = 0;

		virtual int getViewportWidth() const = 0;
		virtual int getViewportHeight() const = 0;
		virtual void setSwapInterval(int interval) = 0;
		virtual int getSwapInterval() const = 0;
	};
}

#endif //AEYON3D_WINDOW_HPP
