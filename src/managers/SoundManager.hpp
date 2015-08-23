#ifndef __SOUND_MANAGER__
#define __SOUND_MANAGER__

#include <string>
#include <map>
#include <SDL2/SDL_mixer.h>

using std::string;
using std::map;

enum sound_type {

    SOUND_MUSIC = 0,
    SOUND_SFX = 1
};

class SoundManager {
    public:
        static SoundManager* Instance() {
            if (s_pInstance == 0) {
                s_pInstance = new SoundManager();
                return s_pInstance;
            }
            return s_pInstance;
        }

        bool load(string fileName, string id, sound_type type);
        void playSound(string id, int loop);
        void playMusic(string id, int loop);

    private:
        static SoundManager* s_pInstance;
        map<string, Mix_Chunk*> m_sfxs;
        map<string, Mix_Music*> m_music;

        SoundManager();
        ~SoundManager();

        SoundManager(const SoundManager&);
        SoundManager &operator= (const SoundManager&);
};

typedef SoundManager TheSoundManager;

#endif
