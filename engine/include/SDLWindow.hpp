//
//
//

#ifndef AEYON3D_SDLWINDOW_HPP
#define AEYON3D_SDLWINDOW_HPP

#include "Window.hpp"
#include <SDL2/SDL.h>
#include <memory>
#include "ECSException.hpp"

namespace aeyon
{
	class SDLWindow : public Window
	{
	private:

		struct SDLWindowDestroyer
		{
			void operator()(SDL_Window* window) const
			{
				SDL_DestroyWindow(window);
			}
		};

		std::unique_ptr<SDL_Window, SDLWindowDestroyer> m_sdlWindow;
		SDL_GLContext m_glContext;
		bool m_shouldClose;

	public:

		SDLWindow(const std::string& title, int x, int y, int width, int height);

		SDLWindow(const SDLWindow&) = delete;
		SDLWindow(SDLWindow&& src) noexcept;

		SDLWindow& operator=(const SDLWindow&) = delete;
		SDLWindow& operator=(SDLWindow&& rhs) noexcept;

		~SDLWindow() override;


		void show() override;
		void hide() override;
		bool isHidden() const override;

		void focus() override;
		bool isFocused() const override;

		void close() override;
		bool shouldClose() const override;

		void swapBuffers() override;

		void setTitle(const std::string& title) override;
		std::string getTitle() const override;

		void setPosition(int x, int y) override;
		int getPositionX() const override;
		int getPositionY() const override;

		void setSize(int width, int height) override;
		int getWidth() const override;
		int getHeight() const override;

		void minimize() override;
		void maximize() override;
		void restore() override;

		ProcAddress getProcAddress() const override;

		void makeContextCurrent() override;
		int getViewportWidth() const override;
		int getViewportHeight() const override;
		void setSwapInterval(int interval) override;
		int getSwapInterval() const override;
	};
}


#endif //AEYON3D_SDLWINDOW_HPP
