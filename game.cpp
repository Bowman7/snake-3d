#include"game.hpp"

Game::Game(){
  
  fruitShader.Init("f_shader.vert","f_shader.frag");
  gridShader.Init("grid_shader.vert","grid_shader.frag");
  pythonShader.Init("p_shader.vert","p_shader.frag");
  
  python.SetID(pythonShader.GetID());
  grid.SetID(gridShader.GetID());
  fruit.SetID(fruitShader.GetID());
  //for grid
  grid.InitGrid();
}

Game::~Game(){

}
//get random num
float Game::GetRandNum(){
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(0,9);
  float random = dist6(rng);
  return random;
}
void Game::GetRandPos(){
  tempX = GetRandNum();
  tempZ = GetRandNum();
  if(python.GetPosX()==tempX && python.GetPosZ() == tempZ){
    return GetRandPos();
  }
}
//add fruit
void Game::NewFruitPos(){
  GetRandPos();
  glm::vec3 pos = glm::vec3(tempX,1.0f,tempZ);
  fruit.SetPos(pos);
  fruit.printV3();
}
//check collision
void Game::CheckCollision(){
  if(python.GetPosX() == fruit.GetPosX() && python.GetPosZ() == fruit.GetPosZ()){
    //std::cout<<"Collision!"<<std::endl;
    NewFruitPos();
  }
}
void Game::HandleInput(int val){
  
  python.HandleInput(val);
  camera.HandleInput(val);

}
//update
void Game::Update(glm::vec3 camFront,float fv){
  //check collision
  CheckCollision();
  //handle input
  camera.UpdateCameraFront(camFront,fv); 

  python.Update(camera.GetViewMatrix());
  fruit.Update(camera.GetViewMatrix());
  grid.Update(camera.GetViewMatrix());

  
}

//draw
void Game::Draw(){
  
  python.Draw();
  fruit.Draw();
  grid.Draw();
 
}

