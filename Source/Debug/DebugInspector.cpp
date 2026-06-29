#include "DebugInspector.h"
#include "Game/Game.h"
#include "imgui.h"

void CDebugInspector::Render(const SFrameMetrics& frame_metrics, CGame* game)
{
    if (!is_visible)
        return;

    ImGui::SetNextWindowBgAlpha(0.35f);
    ImGui::Begin("debug_inspector", &is_visible);

    if (ImGui::CollapsingHeader("Performance"))
    {
        ImGui::Text("Frame Time: %.3f ms", frame_metrics.frame_time);
        ImGui::Text("Draw Calls: %d", frame_metrics.draw_calls);
    }

    ImGui::End();
}

void CDebugInspector::SetVisiblity(const bool visible)
{
    is_visible = visible;
}

void CDebugInspector::ToggleVisibility()
{
    is_visible = !is_visible;
}
