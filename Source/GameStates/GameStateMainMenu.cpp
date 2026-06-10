#include "GameStateMainMenu.h"
#include "Game/Game.h"

#include <SDL_render.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

void CGameStateMainMenu::OnEnter(CGame* game)
{
}

void CGameStateMainMenu::OnExit()
{
}

void CGameStateMainMenu::Update(CGame* game, float delta_seconds)
{
}

void CGameStateMainMenu::Render(CGame* game)
{
    uint32 center_x = game->GetWorld().GetWindowWidth() / 2;

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoBackground;
    window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

    ImGui::SetNextWindowPos(ImVec2(center_x, 300), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::Begin("main_menu", nullptr, window_flags);

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 0.4f, 0.4f, 0.5f));

    ImGui::Text("P O N G");
    ImGui::Dummy(ImVec2(0, 20));

    if (ImGui::Button("START GAME"))
    {
        game->StartGame();
    }

    if (ImGui::Button("EXIT"))
    {
    }

    ImGui::PopStyleColor(3);
    ImGui::End();

    SDL_SetRenderDrawColor(game->GetRenderSystem().GetRenderer(), 20, 20, 20, 255);
    SDL_RenderClear(game->GetRenderSystem().GetRenderer());

    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), game->GetRenderSystem().GetRenderer());

    SDL_RenderPresent(game->GetRenderSystem().GetRenderer());
}

std::string CGameStateMainMenu::GetName() const
{
    return "Main Menu";
}
