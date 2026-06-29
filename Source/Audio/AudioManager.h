#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "miniaudio.h"
#include <string>
#include <unordered_map>

class CAudioManager
{
public:
    static CAudioManager& Get()
    {
        static CAudioManager instance;
        return instance;
    }

    CAudioManager(const CAudioManager&) = delete;
    CAudioManager& operator=(const CAudioManager&) = delete;

    bool Initialize();
    void Shutdown();

    void LoadSound(const std::string& name, const std::string& file_path);
    bool PlaySound(const std::string& name);
    bool PlayMusic(const std::string& name);
    bool StopMusic();

    void SetVolume(const float volume);

private:
    CAudioManager() = default;
    ~CAudioManager() = default;

private:
    ma_engine engine;
    std::unordered_map<std::string, std::string> sounds;

    ma_sound menu_music;
    bool is_music_playing = false;
};

#endif
