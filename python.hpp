#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<limits>

#include"math.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"



class Python{
public:
  Python();
  ~Python();
  void SetID(unsigned int id){
    ID = id;
  }
  void Update(glm::mat4);
  void Draw();
  void moveSouth();
  void moveEast();
  void moveWest();
  void moveNorth();
  void MoveToDir();
  void Move(int);
  void setMat4(const std::string &name, const glm::mat4 &mat,unsigned int id) const
  {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }
  void setVec3(const std::string &name, float x, float y, float z,unsigned int id) const
  { 
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z); 
  }
  float GetPosX(){
    return p_Pos.x;
  }
  float GetPosY(){
    return p_Pos.y;
  }
  float GetPosZ(){
    return p_Pos.z;
  }
  void SetPosX(float x){
    p_Pos.x = x;
  }
  void SetPosY(float y){
    p_Pos.y = y;
  }
  void SetPosZ(float z){
    p_Pos.z = z;
  }
  void SetPos(glm::vec3 pos){
    p_Pos = pos;
  }
  glm::vec3 GetPos(){
    return p_Pos;
  }

  int GetOldDir(){
    return old_direction;
  }
  int GetDir(){
    return direction;
  }
  void SetDir(int dir){
    old_direction = direction;
    direction = dir;
  }
  void SetColor(glm::vec3 col){
    color = col;
  }
  void printV3(){
    std::cout<<"v3 x:"<<p_Pos.x<<"y:"<<p_Pos.y<<"z:"<<p_Pos.z<<std::endl;
  }
  bool IsCrashed(){
    return crashed;
  }
  
  void SetTexture(unsigned int tex){
    texture = tex;
  }
  //set light id
  void SetLightID(unsigned int id){
    l_ID = id;
  }
  void SetCameraPos(glm::vec3 pos){
    camPos = pos;
  }
  //directiojn,1-N,2-S,3-E,4-W
private:
  //texture
  unsigned int texture;
  bool crashed = false;
  glm::vec3 color;
  glm::vec3 lcolor= glm::vec3(1.0f,1.0f,1.0f);
  int old_direction;
  int direction;
  glm::mat4 lookAt;
  glm::vec3 p_Pos = glm::vec3(1.0f,1.0f,1.0f);
  glm::vec3 camPos;
  
  unsigned int ID,l_ID;
  unsigned int VAO,VBO,l_VAO;
  glm::vec3 l_pos = glm::vec3(5.0f,2.0f,5.0f);
 
  float vertices[288] = {
    //vertices                  //normals      //tex coord
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
    					                  
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,    1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,    1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,    1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
    					                  
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
					                  
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
					                  
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
					                  
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,   0.0f, 1.0f 
  };
};
