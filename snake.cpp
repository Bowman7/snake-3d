#include "snake.hpp"

Snake::Snake(){
  
  //buffers
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1,&EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
   //for accessing
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);
  

  //for light
  glGenVertexArrays(1,&l_VAO);
  glBindVertexArray(l_VAO);

  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  //attrib ptr
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);

  //for snake
  glGenVertexArrays(1,&s_VAO);
  glBindVertexArray(s_VAO);
  //attrib
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER,s_VBO);
  //for grid
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      grid[i][j] =  glm::vec3(0.0f,0.0f,0.0f);
    }
  }

}

Snake::~Snake(){
  
}

void Snake::SetID(unsigned int id){
  ID = id;
  
};
//init grid
void Snake::InitGrid(){
  glm::vec3 temp = glm::vec3(0.0f,0.0f,0.0f);
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      grid[i][j] = temp;
      temp += glm::vec3(1.0f,0.0f,0.0f);
    }
    temp.x = 0.0f;
    temp  += glm::vec3(0.0f,0.0f,1.0f);
  }
}
void Snake::Update(glm::mat4 look){
  lookMat = look;
  //update model pos
  /*
  lightPos.x = 1.0f + sin(glfwGetTime())*2.0f;
  lightPos.y = sin(glfwGetTime()/2.0f)*1.0f;
  if(EventTriggered(1)){
    snake_pos[3] -= glm::vec3(0.0f,0.0f,0.1f);
   
    }*/
 
}
void Snake::Draw(){
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //for cube
  glUseProgram(ID);
  
  glm::vec3 objColor = glm::vec3(0.0f,0.5f,0.2f);
  unsigned int objColorLoc = glGetUniformLocation(ID,"ObjectColor");
  glUniform3fv(objColorLoc,1,glm::value_ptr(objColor));
 
  glm::vec3 lightColor = glm::vec3(1.0f,1.0f,1.0f);
  unsigned int lightColorLoc = glGetUniformLocation(ID,"LightColor");
  glUniform3fv(lightColorLoc,1,glm::value_ptr(lightColor));
  //proj
  glm::mat4 projection =  glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
  glm::mat4 view = lookMat;
  setMat4("proj",projection,ID);
  setMat4("view",view,ID);
  setVec3("ViewPos",viewPos.x,viewPos.y,viewPos.z,ID);
  glBindVertexArray(VAO);
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      //std::cout<<"grid x:"<<grid[i][j].x<<" Y:"<<grid[i][j].y<<std::endl;
       glm::mat4 model = glm::mat4(1.0f);
       model = glm::translate(model,grid[i][j]);
      
       setMat4("model",model,ID);
      
       glDrawArrays(GL_TRIANGLES,0,36);
    }
  }
 
  
  
  //for light
  glUseProgram(l_ID);

  glm::mat4 l_model = glm::mat4(1.0f);
  l_model = glm::translate(l_model,lightPos);
  l_model = glm::scale(l_model,glm::vec3(0.2f));

  setVec3("LightPos",lightPos.x,lightPos.y,lightPos.z,l_ID);
  setMat4("model",l_model,l_ID);
  setMat4("proj",projection,l_ID);
  setMat4("view",view,l_ID);
  
  glBindVertexArray(l_VAO);
  glDrawArrays(GL_TRIANGLES,0,36);
  
  //for snake

  glUseProgram(s_ID);

  glm::vec3 s_objColor = glm::vec3(1.0f,0.0f,0.0f);
  setVec3("ObjectColor",s_objColor.x,s_objColor.y,s_objColor.z,s_ID);
 
  glm::vec3 s_lightColor = glm::vec3(1.0f,1.0f,1.0f);
  setVec3("LightColor",s_lightColor.x,s_lightColor.y,s_lightColor.x,s_ID);
  glm::mat4 s_model = glm::mat4(1.0f);
  s_model = glm::translate(s_model,s_Pos);
  setMat4("model",s_model,s_ID);
  setMat4("proj",projection,s_ID);
  setMat4("view",view,s_ID);

  glBindVertexArray(s_VAO);
  glDrawArrays(GL_TRIANGLES,0,36);

  
}
//event triggered
bool Snake::EventTriggered(double interval){
  double currentTime = (double)glfwGetTime();
  if(currentTime-lastUpdatedTime >=interval){
    lastUpdatedTime = currentTime;
    return true;
  }
  return false;
}
//handle input

void Snake::moveAhead(){
  glm::vec3 temp = s_Pos;
  temp += glm::vec3(0.0f,0.0f,1.0f);
  std::cout<<"temp x:"<<temp.x<<"y:"<<temp.y<<"z:"<<temp.z<<std::endl;
  s_Pos = temp;
}
void Snake::moveLeft(){
 
}

void Snake::moveRight(){
 
}

void Snake::HandleInput(int val){
  switch(val){
  case 6:
    moveAhead();
    break;
  case 7:
    moveLeft();break;
  case 8:
    moveRight();break;
    break;
  default:
    break;
    
  }
}
