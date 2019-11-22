//
//
//

#include <Event/WindowResizeEvent.hpp>
#include "SDLWindow.hpp"
#include "Event/EventSystem.hpp"

namespace aeyon
{
	SDLWindow::SDLWindow(const std::string& title, int x, int y, int width, int height, EventSystem* eventSystem)
	: m_eventSystem(eventSystem)
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

#ifndef NDEBUG
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		SDL_Window* window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_OPENGL);
		m_sdlWindow.reset(window);

		m_glContext = SDL_GL_CreateContext(window);

		SDL_GL_SetSwapInterval(1);
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

		WindowResizeEvent e;
		e.width = width;
		e.height = height;
		SDL_GL_GetDrawableSize(m_sdlWindow.get(), &e.viewportWidth, &e.viewportHeight);

		m_eventSystem->publish(e);
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
		int width;
		SDL_GL_GetDrawableSize(m_sdlWindow.get(), &width, nullptr);
		return width;
	}

	int SDLWindow::getViewportHeight() const 
	{
		int height;
		SDL_GL_GetDrawableSize(m_sdlWindow.get(), nullptr, &height);
		return height;
	}

	void SDLWindow::setSwapInterval(int interval)
	{
		// TODO: Error handling here
		SDL_GL_SetSwapInterval(interval);
	}

	int SDLWindow::getSwapInterval() const 
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
}
