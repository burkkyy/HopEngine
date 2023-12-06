#define MINIAUDIO_IMPLEMENTATION
#include "audio.hpp"
#include <iostream>
using namespace hop;

AudioEngine::AudioEngine(){}
        

bool AudioEngine::init(){
    
    ma_result result;
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        return false;
    }
    else{
    }
    return true;
}


AudioEngine::EngineSound::EngineSound(const char* file_name){
    file_path = "sounds/";
    file_path = file_path + file_name;
}

AudioEngine::EngineSound::~EngineSound(){
    ma_sound_uninit(&sound);
}


bool AudioEngine::EngineSound::init(ma_engine* engine, bool loop_sound){
this->engine = engine;
ma_result result = ma_sound_init_from_file(engine, file_path.c_str(), 0, NULL, NULL, &sound);
if (result != MA_SUCCESS) {
    return false;
}
else{
    if(loop_sound){
        ma_sound_set_looping(&sound, true);
    }
    return true;
}

}

std::shared_ptr<AudioEngine::EngineSound> AudioEngine::create_sound(const char* file_name, bool loop_sound){

    std::shared_ptr<EngineSound> return_sound = std::make_shared<EngineSound>(file_name);
    if(!(return_sound->init(&this->engine, loop_sound))){
        return nullptr;
    }
    else{
        if(loop_sound){

        }
        sounds.push_back(return_sound);
        return return_sound;
    }
}

void AudioEngine::EngineSound::play(){  
    if(ma_sound_is_playing(&sound)){
        ma_sound_seek_to_pcm_frame(&sound, 0);
    }
    ma_sound_start(&sound);
}

void AudioEngine::EngineSound::pause(){
    ma_sound_stop(&sound);
}