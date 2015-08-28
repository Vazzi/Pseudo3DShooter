#include "SoundManager.hpp"

#include <iostream>

SoundManager* SoundManager::s_pInstance = 0;

SoundManager::SoundManager() {
    Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
}

SoundManager::~SoundManager() {
    Mix_CloseAudio();
}

bool SoundManager::load(string fileName, string id, sound_type type) {
    if (type == SOUND_MUSIC) {
        Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());

        if (pMusic == 0) {
            std::cout << "Could not load music: ERROR - " << Mix_GetError()
                << std::endl;
            return false;
        }
        m_music[id] = pMusic;
    } else if (type == SOUND_SFX) {
        Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
        if (pChunk == 0) {
            std::cout << "Could not load SFX: ERROR - " << Mix_GetError()
                << std::endl;
            return false;
        }
        m_sfxs[id] = pChunk;
        return true;
    }
    return false;
}

void SoundManager::playMusic(string id, int loop) {
    Mix_PlayMusic(m_music[id], loop);
}

void SoundManager::playSound(string id, int loop) {
    Mix_PlayChannel(-1, m_sfxs[id], loop);
}