//
//
//

#ifndef AEYON3D_GUISYSTEM_HPP
#define AEYON3D_GUISYSTEM_HPP

#include "System.hpp"
#include "Graphics/GraphicsSystem.hpp"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "Graphics/SDLWindow.hpp"
#include <iostream>
#include "Time.hpp"

namespace aeyon
{
	class GUISystem : public System
	{
	private:
		GraphicsSystem* m_graphics;
		SDLWindow* m_window;

		float m_previousTime = 0.0f;
		float m_frameTime = 0.0f;
		int m_numFrames = 0;

	public:
		explicit GUISystem(GraphicsSystem* graphics)
		: m_graphics(graphics), m_window(graphics->getWindow())
		{
			// Init Gui
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();

			ImGui::StyleColorsDark();

			if (!ImGui_ImplSDL2_InitForOpenGL(m_window->getSDLWindow(), m_window->getGLContext()))
			{
				std::cout << "ImGui: Failed to initialize SDL2 context" << std::endl;
			}

			if (!ImGui_ImplOpenGL3_Init("#version 330"))
			{
				std::cout << "ImGui: Failed to initialize OpenGL3 context" << std::endl;
			}
		}

		void update() override
		{
			// Render GUI
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame(m_window->getSDLWindow());
			ImGui::NewFrame();

			float currentTime = Time::getTime();
			m_numFrames++;

			float timePassed = currentTime - m_previousTime;

			if (timePassed >= 0.25f)
			{
				m_frameTime = (timePassed > 0.0f) ? static_cast<float>(m_numFrames) / timePassed : 0.0f;
				m_numFrames = 0;
				m_previousTime = currentTime;
			}

			ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
			if (ImGui::Begin("Performance", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground))
			{
				ImGui::Text("%d FPS", static_cast<int>(m_frameTime));
				ImGui::Text("%.1f ms", (m_frameTime > 0.0f) ? 1000.0f / m_frameTime : 0.0f);
			}

			ImGui::End();

			static float pos[3];

			if(ImGui::Begin("World"))
			{
				if (ImGui::CollapsingHeader("Entities"))
				{
					if (ImGui::TreeNode("nanosuit"))
					{
						if (ImGui::TreeNode("Transform"))
						{
							if (ImGui::TreeNode("Position"))
							{
								ImGui::InputFloat3("##nanosuit-pos", pos);
								ImGui::TreePop();
							}

							if (ImGui::TreeNode("Rotation"))
							{
								ImGui::InputFloat3("##nanosuit-rot", pos);
								ImGui::TreePop();
							}

							if (ImGui::TreeNode("Scale"))
							{
								ImGui::InputFloat3("##nanosuit-scale", pos);
								ImGui::TreePop();
							}
							ImGui::TreePop();
						}

						if (ImGui::TreeNode("MeshRenderer"))
						{
							ImGui::TreePop();
						}
						ImGui::TreePop();
						ImGui::Separator();
					}

					if (ImGui::TreeNode("Ground"))
					{
						ImGui::TreePop();
						ImGui::Separator();
					}
				}
			}

			ImGui::End();

			ImGui::Render();
			glViewport(0, 0, static_cast<int>(ImGui::GetIO().DisplaySize.x), static_cast<int>(ImGui::GetIO().DisplaySize.y));
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glViewport(0, 0, m_window->getViewportWidth(), m_window->getViewportHeight());
		}

		~GUISystem() override
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplSDL2_Shutdown();
			ImGui::DestroyContext();
		}
	};
}

#endif //AEYON3D_GUISYSTEM_HPP
