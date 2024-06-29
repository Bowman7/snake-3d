//sound
#include<irrklang/irrKlang.h>
using namespace irrklang;


class Music{
public:
  Music(){
    SoundEngine = createIrrKlangDevice();
    play = loading;
  };
  ~Music(){
    SoundEngine->drop();
  };
  void Play(){
    SoundEngine->play2D(play,false);
  }
  void PlayGame(){
    SoundEngine->play2D(game,true);
  }
  void PlayOver(){
    SoundEngine->play2D(over,false);
  }
  void Stop(){
    SoundEngine->stopAllSounds();
  }
  void ChangeToGame(){
    play = game;
  }
private:
   //for sound
  ISoundEngine *SoundEngine;
  const char* over = "/home/bat/24/snake-3d/Music/gameover.mp3";
  const char* loading = "/home/bat/24/snake-3d/Music/loading.mp3";
  const char* game = "/home/bat/24/snake-3d/Music/main.mp3";
  const char* play;
};
