#include"fruit.hpp"

Fruit::Fruit(){
  //buffers
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
  //for acces
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);
  
}

Fruit::~Fruit(){

}

void Fruit::Update(glm::mat4 look){
  lookAt = look;
}

void Fruit::Draw(){
  glUseProgram(ID);

  glm::mat4 projection =  glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
  glm::mat4 view = lookAt;
  setMat4("proj",projection,ID);
  setMat4("view",view,ID);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model,f_Pos);
  setMat4("model",model,ID);

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES,0,36);
}