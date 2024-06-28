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
  const char* over = "Music/gameover.mp3";
  const char* loading = "Music/loading.mp3";
  const char* game = "Music/main.mp3";
  const char* play;
};
