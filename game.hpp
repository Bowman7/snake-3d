#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include<random>
#include<string>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

//for fruit bite
#include<irrklang/irrKlang.h>
using namespace irrklang;
//#pragma comment(lib,"lib/*")



#include"shader.hpp"
#include"camera.hpp"
#include"fruit.hpp"
#include"grid.hpp"
#include"python.hpp"
#include"screen.hpp"
//for text
#include"text.hpp"


//test texture
#include"tx_test.hpp"

class Game{
public:
  Game();
  ~Game();
  void Update(glm::vec3,float);
  void Draw();
  void DrawLoading();
  void DrawGameOver();
  void HandleInput(int);
  void CheckCollision();
  void NewFruitPos();
  void GetRandPos();
  float GetRandNum();
  void AddBody();
  void InitPython(unsigned int );
  bool n_IsEatingSelf();
  bool s_IsEatingSelf();
  bool e_IsEatingSelf();
  bool w_IsEatingSelf();
  void InitTexture();
  bool CheckGameOver(){
    return gameOver;
  }
  void Reset();
  bool EventTriggered(double);
  void PlayBite(){
    soundEngine->play2D(bite,false);
    //soundEngine->stopAllSounds();
  }
  void SetState(){
    gameState = true;
  }
  void UnsetState(){
    gameState =false;
  }
private:
  //is in game stat
  bool gameState = false;
  //fruit eating sound
  ISoundEngine *soundEngine = createIrrKlangDevice();
  const char* bite="Music/bite2.mp3";
  
  //for timestep
  double speed = 1.0;
  double lastUpdatedTime =0.0;
  //gameover flag
  bool gameOver = false;
  //fruit temp pos
  float tempX,tempZ;
  Python python[100];
  Shader pythonShader;
  int bodyID = 0;
  
  Shader gridShader;
  Grid grid;

  Fruit fruit;
  Shader fruitShader;
  
  Camera camera;
  //for testing texture
  Tex tex[2];
  Shader texShader;
  //for texture
  unsigned int g_texture;
  unsigned int grass_texture;
  int height,width,nrChannels;
  unsigned char* data;
  //for light
  Shader lightShader;
  //for loading screen
  screen loading;
  Shader loadingShader;
  unsigned int l_texture;
  //for end loading screen
  screen endLoading;
  Shader endLoadingShader;
  unsigned int el_texture;
  //for text loading
  Shader textShader;
  Text text;
  unsigned int score = 0;
  unsigned int finalScore = 0;
  
  
};
