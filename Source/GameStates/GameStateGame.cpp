#include "GameStateGame.h"
#include "Game/Game.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_log.h>

#include "GameStateMainMenu.h"

void CGameStateGame::OnEnter(CGame* game)
{
    max_buttons = sizeof(labels) / sizeof(labels[0]);
}

void CGameStateGame::OnExit()
{
}

void CGameStateGame::Update(CGame* game, float delta_seconds)
{
    game->GetWorld().UpdateTimer(delta_seconds);

    if (!game->GetWorld().IsServing() && !game->IsPaused())
    {
        game->GetInputSystem().Update(game->GetWorld());
        game->GetMovementSystem().Update(game->GetWorld(), delta_seconds);
        game->GetCollisionSystem().Update(game->GetWorld());
        game->GetGameRulesSystem().Update(game->GetWorld());
    }
}

void CGameStateGame::Render(CGame* game)
{
    game->GetRenderSystem().Update(game->GetWorld());

    ImGuiWindowFlags score_hud_window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | // Klicks gehen durch das Fenster durch
        ImGuiWindowFlags_NoBackground;

    ImGui::SetNextWindowPos(ImVec2(400, 50), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

    ImGui::Begin("score_hud", nullptr, score_hud_window_flags);
    ImGui::Text("%d  :  %d", game->GetWorld().GetScoreP1(), game->GetWorld().GetScoreP2());
    ImGui::End();

    if (game->IsPaused())
    {
        uint32 center_x = game->GetWorld().GetWindowWidth() / 2;

        ImGuiWindowFlags pause_menu_window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize;

        ImGui::SetNextWindowPos(ImVec2(center_x, 200), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::Begin("main_menu", nullptr, pause_menu_window_flags);

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
}

void CGameStateGame::HandleInput(SDL_Event& event, CGame* game)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            if (game->IsPaused())
            {
                game->UnPauseGame();
            }
            else
            {
                game->PauseGame();
            }
            break;
        }

        if (game->IsPaused())
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
                    game->UnPauseGame();
                    break;
                case 1:
                    game->ChangeGameState(new CGameStateMainMenu());
                    break;
                }
                break;
            }
        }
    }
}

std::string CGameStateGame::GetName() const
{
    return "Game";
}
