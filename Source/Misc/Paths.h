#ifndef PATHS_H
#define PATHS_H

#include <string>

class CPaths
{
public:
    static std::string BaseDir();
    static std::string ProjectContentDir();
    static std::string SoundDir();
    static std::string Combine(const std::string& a, const std::string& b);
};

#endif
