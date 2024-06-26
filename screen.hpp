#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

class screen{
public:
  screen();
  ~screen();
  void Draw();
  void SetID(unsigned int id){
    ID =id;
  }
  void SetTexture(unsigned int tex){
    texture = tex;
  }
private:
  unsigned int VBO,VAO,EBO,texture;
  unsigned int ID;
  float vertices[30]={
    //vertices                   //tex coord 
    0.5f, 0.5f, 0.0f,    1.0f, 1.0f, //tr
    0.5f, -0.5f, 0.0f,   1.0f, 0.0f, //br
    -0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, //bl
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, //tr
  };
  unsigned int indices[6]={
    0,1,3,
    1,2,3
  };
};
                                                           
