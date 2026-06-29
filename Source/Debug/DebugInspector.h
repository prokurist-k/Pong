#ifndef INSPECTOR_H
#define INSPECTOR_H

#include "CoreTypes.h"

struct SFrameMetrics
{
    float frame_time;
    int32 draw_calls;
};

class CDebugInspector
{
public:
    void Render(const SFrameMetrics& frame_metrics, class CGame* game);
    void SetVisiblity(const bool visible);
    void ToggleVisibility();
    bool IsVisible() const
    {
        return is_visible;
    }

private:
    bool is_visible = false;
};

#endif
