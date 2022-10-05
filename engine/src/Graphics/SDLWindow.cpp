//
//
//

#include "Graphics/SDLWindow.hpp"
#include <iostream>

namespace aeyon
{
	SDLWindow::SDLWindow(
			const std::string& title,
			int x, int y,
			int width, int height,
			const Uint32& flags
			)
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

#ifndef NDEBUG
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		SDL_Window* window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
		m_sdlWindow.reset(window);

		m_glContext = SDL_GL_CreateContext(window);

		setVSync(true);
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}

	SDLWindow::~SDLWindow()
	{
		SDL_GL_DeleteContext(m_glContext);
	}

	void SDLWindow::show() 
	{
		SDL_ShowWindow(m_sdlWindow.get());
	}

	void SDLWindow::hide() 
	{
		SDL_HideWindow(m_sdlWindow.get());
	}

	bool SDLWindow::isHidden() const 
	{
		return (SDL_GetWindowFlags(m_sdlWindow.get()) & SDL_WINDOW_HIDDEN) != 0;
	}

	void SDLWindow::focus() 
	{
		SDL_RaiseWindow(m_sdlWindow.get());
	}

	bool SDLWindow::isFocused() const 
	{
		return (SDL_GetWindowFlags(m_sdlWindow.get()) & SDL_WINDOW_INPUT_FOCUS) != 0;
	}

	void SDLWindow::close() 
	{
		m_shouldClose = true;
	}

	bool SDLWindow::shouldClose() const 
	{
		return m_shouldClose;
	}

	void SDLWindow::swapBuffers() 
	{
		SDL_GL_SwapWindow(m_sdlWindow.get());
	}

	void SDLWindow::setTitle(const std::string& title) 
	{
		SDL_SetWindowTitle(m_sdlWindow.get(), title.c_str());
	}

	std::string SDLWindow::getTitle() const 
	{
		return SDL_GetWindowTitle(m_sdlWindow.get());
	}

	void SDLWindow::setPosition(int x, int y) 
	{
		SDL_SetWindowPosition(m_sdlWindow.get(), x, y);
	}

	void SDLWindow::setPositionX(int x)
	{
		setPosition(x, getPositionY());
	}

	void SDLWindow::setPositionY(int y)
	{
		setPosition(getPositionX(), y);
	}

	int SDLWindow::getPositionX() const 
	{
		int x;
		SDL_GetWindowPosition(m_sdlWindow.get(), &x, nullptr);
		return x;
	}

	int SDLWindow::getPositionY() const 
	{
		int y;
		SDL_GetWindowPosition(m_sdlWindow.get(), nullptr, &y);
		return y;
	}

	void SDLWindow::setSize(int width, int height) 
	{
		SDL_SetWindowSize(m_sdlWindow.get(), width, height);

		/*
		WindowResizeEvent e;
		e.width = width;
		e.height = height;
		SDL_GL_GetDrawableSize(m_sdlWindow.get(), &e.viewportWidth, &e.viewportHeight);

		m_eventSystem->publish(e);
		 */
	}

	void SDLWindow::setWidth(int width)
	{
		setSize(width, getHeight());
	}

	void SDLWindow::setHeight(int height)
	{
		setSize(getWidth(), height);
	}

	int SDLWindow::getWidth() const 
	{
		int width;
		SDL_GetWindowSize(m_sdlWindow.get(), &width, nullptr);
		return width;
	}

	int SDLWindow::getHeight() const 
	{
		int height;
		SDL_GetWindowSize(m_sdlWindow.get(), nullptr, &height);
		return height;
	}

	void SDLWindow::minimize() 
	{
		SDL_MinimizeWindow(m_sdlWindow.get());
	}

	void SDLWindow::maximize() 
	{
		SDL_MaximizeWindow(m_sdlWindow.get());
	}

	void SDLWindow::restore() 
	{
		SDL_RestoreWindow(m_sdlWindow.get());
	}

	SDLWindow::ProcAddress SDLWindow::getProcAddress() const
	{
		return SDL_GL_GetProcAddress;
	}

	void SDLWindow::makeContextCurrent()
	{
		// TODO: Error handling here
		SDL_GL_MakeCurrent(m_sdlWindow.get(), m_glContext);
	}

	int SDLWindow::getViewportWidth() const 
	{
		int width, height;
		SDL_GL_GetDrawableSize(m_sdlWindow.get(), &width, &height);

		return width;
	}

	int SDLWindow::getViewportHeight() const 
	{
		int width, height;
		SDL_GL_GetDrawableSize(m_sdlWindow.get(), &width, &height);

		return height;
	}

	void SDLWindow::setVSync(bool active)
	{
		SDL_GL_SetSwapInterval(active ? 1 : 0);
	}

	bool SDLWindow::isVSyncEnabled() const
	{
		return SDL_GL_GetSwapInterval();
	}

	SDL_GLContext SDLWindow::getGLContext() const
	{
		return m_glContext;
	}

	SDL_Window* SDLWindow::getSDLWindow()
	{
		return m_sdlWindow.get();
	}

	void SDLWindow::setWindowMode(WindowMode mode)
	{
		switch (mode)
		{
			case WindowMode::Windowed:
				SDL_SetWindowFullscreen(m_sdlWindow.get(), 0);
				break;
			case WindowMode::WindowedFullscreen:
				SDL_SetWindowFullscreen(m_sdlWindow.get(), SDL_WINDOW_FULLSCREEN_DESKTOP);
				break;
			case WindowMode::Fullscreen:
				SDL_SetWindowFullscreen(m_sdlWindow.get(), SDL_WINDOW_FULLSCREEN);
				break;
		}

		/*
		WindowResizeEvent e;
		SDL_GetWindowSize(m_sdlWindow.get(), &e.width, &e.height);
		SDL_GL_GetDrawableSize(m_sdlWindow.get(), &e.viewportWidth, &e.viewportHeight);

		m_eventSystem->publish(e);
		 */
	}

	Window::WindowMode SDLWindow::getWindowMode() const
	{
		Uint32 flags = SDL_GetWindowFlags(m_sdlWindow.get());

		if ((flags & SDL_WINDOW_FULLSCREEN) != 0 && (flags & (SDL_WINDOW_FULLSCREEN_DESKTOP & ~SDL_WINDOW_FULLSCREEN)) == 0)
		{
			return WindowMode::Fullscreen;
		}
		else if ((flags & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0)
		{
			return WindowMode::WindowedFullscreen;
		}
		else
		{
			return WindowMode::Windowed;
		}
	}
}
