#include "GameStateMainMenu.h"
#include "Audio/AudioManager.h"
#include "Game/Game.h"

#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>

#include "Misc/Paths.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"

void CGameStateMainMenu::OnEnter(CGame* game)
{
    CAudioManager::Get().PlayMusic(CPaths::Combine(CPaths::SoundDir(), "menu_music.mp3"));
}

void CGameStateMainMenu::OnExit(CGame* game)
{
    CAudioManager::Get().StopMusic();
}

void CGameStateMainMenu::Update(CGame* game, float delta_seconds)
{
}

void CGameStateMainMenu::Render(CGame* game)
{
    uint32 center_x = game->GetWorld().GetWindowWidth() / 2;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize;

    ImGui::SetNextWindowPos(ImVec2(center_x, 200), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::Begin("pause_menu", nullptr, window_flags);

    for (int i = 0; i < max_buttons; ++i)
    {
        const bool is_selected = (selected_button_index == i);

        if (is_selected)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
        }
        else
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        }

        ImGui::Button(labels[i], ImVec2(button_width, 60.0f));

        ImGui::PopStyleColor(3);
        if (i < max_buttons - 1)
        {
            ImGui::Dummy(ImVec2(0, 10));
        }
    }

    ImGui::End();
}

void CGameStateMainMenu::HandleInput(SDL_Event& event, CGame* game)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            selected_button_index--;
            if (selected_button_index < 0)
            {
                selected_button_index = max_buttons - 1;
            }
            break;
        case SDLK_DOWN:
            selected_button_index++;
            if (selected_button_index >= max_buttons)
            {
                selected_button_index = 0;
            }
            break;
        case SDLK_RETURN:
        case SDLK_SPACE:
            switch (selected_button_index)
            {
            case 0:
                game->StartGame();
                break;
            case 1:
                game->ExitGame();
                break;
            }
            break;
        }
    }
}

std::string CGameStateMainMenu::GetName() const
{
    return "Main Menu";
}
