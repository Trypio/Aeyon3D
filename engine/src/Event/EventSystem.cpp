//
//
//

#include "Event/EventSystem.hpp"
#include "QuitEvent.hpp"
#include "Input/KeyboardEvent.hpp"
#include <SDL2/SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl.h"

namespace aeyon
{
	void EventSystem::update()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
			{
				KeyboardEvent keyEvent;

				keyEvent.action = event.type == SDL_KEYDOWN ? KeyAction::Press : KeyAction::Release;
				keyEvent.repeat = event.key.repeat != 0;
				keyEvent.keycode = static_cast<KeyCode>(event.key.keysym.scancode);
				keyEvent.charcode = static_cast<KeyChar>(event.key.keysym.sym);
				keyEvent.modifier = static_cast<KeyMod>(event.key.keysym.mod);

				publish(keyEvent);
			}

			if (event.type == SDL_QUIT)
			{
				publish(QuitEvent());
			}
		}
	}
}
