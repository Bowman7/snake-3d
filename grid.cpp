#include"grid.hpp"

Grid::Grid(){
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
  //for accessing
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);

  //init grid
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      grid[i][j] = glm::vec3(0.0f,0.0f,0.0f);
    }
  }
}

Grid::~Grid(){

}

void Grid::Update(glm::mat4 look){
  lookAt = look;
}

void Grid::InitGrid(){
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
void Grid::Draw(){
  glUseProgram(ID);

  glm::mat4 projection =  glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
  glm::mat4 view = lookAt;
  setMat4("proj",projection,ID);
  setMat4("view",view,ID);

  glBindVertexArray(VAO);
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
       glm::mat4 model = glm::mat4(1.0f);
       model = glm::translate(model,grid[i][j]);
      
       setMat4("model",model,ID);
      
       glDrawArrays(GL_TRIANGLES,0,36);
    }
  }
}
