#include "Paths.h"
#include <SDL_filesystem.h>

std::string CPaths::BaseDir()
{
    return SDL_GetBasePath();
}

std::string CPaths::ProjectContentDir()
{
    return Combine(BaseDir(), "../Assets/");
}

std::string CPaths::SoundDir()
{
    return Combine(ProjectContentDir(), "Sounds/");
}

std::string CPaths::Combine(const std::string& a, const std::string& b)
{
    if (a.empty())
        return b;

    std::string combined = a;
    if (a.back() != '/' && a.back() != '\\' && !b.empty() && b.front() != '/' && b.front() != '\\')
    {
        combined += '/';
    }

    combined += b;
    return combined;
}
