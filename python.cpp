#include"python.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

Python::Python(){
  //buffers
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);
  //for tex
  glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
  glEnableVertexAttribArray(1);

  //texture
  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  data = stbi_load("Graphics/snake.jpg", &width, &height, &nrChannels, 0);
  if(data){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);


  
  color = glm::vec3(0.0f,0.0f,1.0f);
  old_direction= 7;
  direction = 7;
  
  
}

Python::~Python(){

}

void Python::Update(glm::mat4 look){
  lookAt = look;
}

//handle input

void Python::moveNorth(){//north
  p_Pos -= glm::vec3(0.0f,0.0f,1.0f);
  if(p_Pos.z <0){
    p_Pos += glm::vec3(0.0f,0.0f,1.0f);
    crashed = true;
  }
}
void Python::moveSouth(){//south
  p_Pos += glm::vec3(0.0f,0.0f,1.0f);
  if(p_Pos.z >=10){
    p_Pos -= glm::vec3(0.0f,0.0f,1.0f);
    crashed = true;
  }
}
void Python::moveEast(){//east
  p_Pos += glm::vec3(1.0f,0.0f,0.0f);
  
  if(p_Pos.x >=10){
    p_Pos -=glm::vec3(1.0f,0.0f,0.0f);
    crashed = true;
  }
}
void Python::moveWest(){//west
  p_Pos -= glm::vec3(1.0f,0.0f,0.0f);
  if(p_Pos.x <0){
    p_Pos += glm::vec3(1.0f,0.0f,0.0f);
    crashed = true;
  }
}

//move
void Python::MoveToDir(){
  Move(direction);
}

void Python::Move(int dir){
  switch(dir){
    case 6:
    moveNorth();//north :6
    break;
  case 7:
    moveSouth();//south:7
    break;
  case 8:
    moveWest();//west
    break;
  case 9:
    moveEast();//east
    break;
  default:
    break;
  }   
}
void Python::Draw(){
  glUseProgram(ID);

  setVec3("color",color.x,color.y,color.z,ID);
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model,p_Pos);
  setMat4("model",model,ID);

  glm::mat4 projection =  glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
  glm::mat4 view = lookAt;
  setMat4("proj",projection,ID);
  setMat4("view",view,ID);

  glBindTexture(GL_TEXTURE_2D,texture);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES,0,36);
}
