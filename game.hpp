#pragma once


#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"


#include"snake.hpp"
#include"shader.hpp"
#include"camera.hpp"
#include"fruit.hpp"


class Game{
public:
  Game();
  ~Game();
  void Update(glm::vec3,float);
  void Draw();
  void HandleInput(int);
private:
  int ip;
  Shader snakeShader;
  Shader lightShader;
  Shader s_Shader;
  Snake snake;

  Fruit fruit;
  Shader fruitShader;
  Camera camera;
  
};
