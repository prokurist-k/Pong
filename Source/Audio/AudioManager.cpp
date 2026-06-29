#include "AudioManager.h"
#include <SDL_error.h>
#include <string>

bool CAudioManager::Initialize()
{
    if (ma_engine_init(nullptr, &engine) != MA_SUCCESS)
    {
        return false;
    }
    return true;
}

void CAudioManager::Shutdown()
{
    ma_engine_uninit(&engine);
}

void CAudioManager::LoadSound(const std::string& name, const std::string& file_path)
{
    sounds[name] = file_path;
}

bool CAudioManager::PlaySound(const std::string& name)
{
    if (sounds.find(name) == sounds.end())
    {
        return false;
    }

    ma_result result = ma_engine_play_sound(&engine, sounds[name].c_str(), NULL);
    return result == MA_SUCCESS;
}

bool CAudioManager::PlayMusic(const std::string& filepath)
{
    if (is_music_playing)
        return false;

    ma_result result = ma_sound_init_from_file(&engine, filepath.c_str(), MA_SOUND_FLAG_STREAM, NULL, NULL, &menu_music);
    if (result == MA_SUCCESS)
    {
        ma_sound_set_looping(&menu_music, MA_TRUE);
        ma_sound_start(&menu_music);
        is_music_playing = true;
    }
    return result == MA_SUCCESS;
}

bool CAudioManager::StopMusic()
{
    if (!is_music_playing)
        return false;

    return ma_sound_stop(&menu_music) == MA_SUCCESS;
}

void CAudioManager::SetVolume(const float volume)
{
    ma_engine_set_volume(&engine, volume);
}
