#include"../include/python.hpp"

Python::Python(){
  //buffers
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

  //for pos
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);
  //for normal
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);
  //for tex coord
  glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
  glEnableVertexAttribArray(2);
  
  //for light
  glGenVertexArrays(1,&l_VAO);
  glBindVertexArray(l_VAO);

  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  //access light
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);
  
  color = glm::vec3(1.0f,0.0f,0.0f);
  old_direction= 7;
  direction = 7;
  
  
}

Python::~Python(){

}

//if event triggere
bool Python::IsEventTriggered(double time){
  float currentTime = glfwGetTime();
  if(currentTime -lastUpdatedTime >= time){
    lastUpdatedTime = currentTime;
    return true;
  }
  return false;
}
void Python::Update(glm::mat4 look){
  lookAt = look;
}

//handle input

void Python::moveNorth(){//north
  p_Pos -= glm::vec3(0.0f,0.0f,1.0f);
  if(p_Pos.z <=-1){
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
  if(p_Pos.x <=-1){
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
  setVec3("lightColor",lcolor.x,lcolor.y,lcolor.z,ID);
  setVec3("lightPos",l_pos.x,l_pos.y,l_pos.z,ID);
  setVec3("viewPos",camPos.x,camPos.y,camPos.z,ID);
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model,p_Pos);
  setMat4("model",model,ID);

  glm::mat4 projection =  glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
  glm::mat4 view = lookAt;
  setMat4("proj",projection,ID);
  setMat4("view",view,ID);


  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES,0,36);
  //for light
  glUseProgram(l_ID);

  glm::mat4 l_model = glm::mat4(1.0f);
  l_model = glm::translate(l_model,l_pos);
  l_model = glm::scale(l_model,glm::vec3(0.1f,0.1f,0.1f));

  setMat4("model",l_model,l_ID);
  setMat4("proj",projection,l_ID);
  setMat4("view",view,l_ID);

  glBindVertexArray(l_VAO);
  glDrawArrays(GL_TRIANGLES,0,36);
  
}
