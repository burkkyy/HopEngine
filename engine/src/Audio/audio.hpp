#pragma once
#include <miniaudio/miniaudio.h>
#include <string>
#include <memory>
#include <vector>

namespace hop{

class AudioEngine{
    
    public:

    AudioEngine();
    bool init();
    
    class EngineSound{
    
        public:

        EngineSound(const char* file_name);
        ~EngineSound();
        bool init(ma_engine* engine, bool loop_sound);
        void play();
        void pause();

        private:
        ma_engine* engine;
        ma_sound sound;
        std::string file_path;

    };
    std::shared_ptr<EngineSound> create_sound(const char* file_name, bool loop_sound);

    private:

    ma_engine engine;
    std::vector<std::shared_ptr<EngineSound>> sounds;


};

}