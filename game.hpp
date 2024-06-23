#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include<random>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"


#include"shader.hpp"
#include"camera.hpp"
#include"fruit.hpp"
#include"grid.hpp"
#include"python.hpp"
//test texture
#include"tx_test.hpp"

class Game{
public:
  Game();
  ~Game();
  void Update(glm::vec3,float);
  void Draw();
  void HandleInput(int);
  void CheckCollision();
  void NewFruitPos();
  void GetRandPos();
  float GetRandNum();
  void AddBody();
  void InitPython();
  bool n_IsEatingSelf();
  bool s_IsEatingSelf();
  bool e_IsEatingSelf();
  bool w_IsEatingSelf();
  void InitTexture();
private:
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
  int height,width,nrChannels;
  unsigned char* data;
  
};
