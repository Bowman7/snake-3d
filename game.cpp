#include"game.hpp"

Game::Game(){
  snakeShader.Init("snake_shader.vert","snake_shader.frag");
  lightShader.Init("snake_shader.vert","light_shader.frag");
  s_Shader.Init("s_shader.vert","s_shader.frag");
  
  snake.SetID(snakeShader.GetID());
  snake.l_SetID(lightShader.GetID());
  snake.s_SetID(s_Shader.GetID());
  //for grid
  snake.InitGrid();
}

Game::~Game(){

}

void Game::HandleInput(int val){
  snake.HandleInput(val);
  camera.HandleInput(val);
}
//update
void Game::Update(glm::vec3 camFront,float fv){
  //handle input
  camera.UpdateCameraFront(camFront,fv);
  snake.Update(camera.GetViewMatrix());
  snake.setView(camera.GetPos());
}

//draw
void Game::Draw(){
  //draw snake
  snake.Draw();
}

