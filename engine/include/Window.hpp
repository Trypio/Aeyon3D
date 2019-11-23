//
//
//

#ifndef AEYON3D_WINDOW_HPP
#define AEYON3D_WINDOW_HPP

#include <string>

namespace aeyon
{
	class EventSystem;

	class Window
	{
	public:
		enum class SyncMode
		{
			None,
			VSync,
			GSync
		};

		enum class WindowMode
		{
			Windowed,
			WindowedFullscreen,
			Fullscreen
		};


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
		virtual void setPositionX(int x) = 0;
		virtual void setPositionY(int y) = 0;
		virtual int getPositionX() const = 0;
		virtual int getPositionY() const = 0;

		virtual void setSize(int width, int height) = 0;
		virtual void setWidth(int width) = 0;
		virtual void setHeight(int height) = 0;
		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;

		virtual void minimize() = 0;
		virtual void maximize() = 0;
		virtual void restore() = 0;

		virtual int getViewportWidth() const = 0;
		virtual int getViewportHeight() const = 0;

		virtual void setVSyncMode(SyncMode mode) = 0;
		virtual SyncMode getVSyncMode() const = 0;

		virtual void setWindowMode(WindowMode mode) = 0;
		virtual WindowMode getWindowMode() const = 0;
	};
}

#endif //AEYON3D_WINDOW_HPP
