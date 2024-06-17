#include"python.hpp"

Python::Python(){
  //buffers
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);
}

Python::~Python(){

}

void Python::Update(glm::mat4 look){
  lookAt = look;
}

//handle input

void Python::moveAhead(){
  p_Pos -= glm::vec3(0.0f,0.0f,1.0f);
}
void Python::moveLeft(){
  p_Pos -= glm::vec3(1.0f,0.0f,0.0f);
}

void Python::moveRight(){
  p_Pos += glm::vec3(1.0f,0.0f,0.0f);
}
void Python::moveBack(){
  p_Pos += glm::vec3(0.0f,0.0f,1.0f);
}

void Python::HandleInput(int val){
  switch(val){
  case 6:
    moveAhead();
    break;
  case 7:
    moveLeft();break;
  case 8:
    moveRight();break;
    break;
  case 9:
    moveBack();break;
  default:
    break;
    
  }
}
void Python::Draw(){
  glUseProgram(ID);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model,p_Pos);
  setMat4("model",model,ID);

  glm::mat4 projection =  glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
  glm::mat4 view = lookAt;
  setMat4("proj",projection,ID);
  setMat4("view",view,ID);

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES,0,36);
}
