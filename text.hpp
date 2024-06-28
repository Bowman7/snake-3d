#pragma once

#include<ft2build.h>
#include FT_FREETYPE_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include<iostream>
#include<map>
#include<string>

class Text{
public:
  Text();
  ~Text(){}
  void SetID(unsigned int id){
    ID = id;
  }
  void RenderText(std::string,float,float,float,glm::vec3);
   void setMat4(const std::string &name, const glm::mat4 &mat,unsigned int id) const
  {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }
private:
  unsigned int ID;
  unsigned int VAO,VBO;
  FT_Library ft;
  FT_Face face;

  struct Character{
    unsigned int TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    unsigned int Advance;
  };

  std::map<char,Character> Characters;
  glm::mat4 projection = glm::ortho(0.0f,1080.0f,0.0f,720.0f);
 
};
