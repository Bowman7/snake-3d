#include"game.hpp"

Game::Game(){
  
  fruitShader.Init("f_shader.vert","f_shader.frag");
  gridShader.Init("grid_shader.vert","grid_shader.frag");
  pythonShader.Init("p_shader.vert","p_shader.frag");

  InitPython();
  python[0].SetID(pythonShader.GetID());
  python[0].SetPos(glm::vec3(1.0f,1.0f,2.0f));
  python[0].SetColor(glm::vec3(1.0f,0.75f,0.80f));
  python[0].SetDir(7);
  bodyID++;
  python[bodyID].SetID(pythonShader.GetID());
  python[bodyID].SetPos(glm::vec3(1.0f,1.0f,1.0f));
  python[bodyID].SetDir(7);
  bodyID++;
  python[bodyID].SetID(pythonShader.GetID());
  python[bodyID].SetPos(glm::vec3(1.0f,1.0f,0.0f));
  python[bodyID].SetDir(7);
  bodyID++;
  grid.SetID(gridShader.GetID());
  fruit.SetID(fruitShader.GetID());
  //for grid
  grid.InitGrid();
}

Game::~Game(){

}
//init python
void Game::InitPython(){
  for(int i=0;i<100;i++){
    python[i].SetID(pythonShader.GetID());
    python[i].SetPos(glm::vec3(0.0f,1.0f,0.0f));
    python[i].SetColor(glm::vec3(0.0f,0.0f,1.0f));
    python[i].SetDir(7);
  }
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
  for(int i=0;i<bodyID;i++){
    if(python[i].GetPosX()==tempX && python[i].GetPosZ() == tempZ){
      return GetRandPos();
    }
  }
}
//add fruit
void Game::NewFruitPos(){
  GetRandPos();
  glm::vec3 pos = glm::vec3(tempX,1.0f,tempZ);
  fruit.SetPos(pos);
  //fruit.printV3();
}
//add body
void Game::AddBody(){
  //FOR EASTSIDE FOOD!!
  
  //case 1 from top 
  if(python[bodyID-1].GetOldDir()==7 && python[0].GetDir()==9){
    python[bodyID].SetPos(python[bodyID-1].GetPos()-=glm::vec3(0.0f,0.0f,1.0f));
    python[bodyID].SetDir(7);
    bodyID++;
  }
  //case 2 from bottom
  if(python[bodyID-1].GetOldDir()==6 && python[0].GetDir()==9){
    python[bodyID].SetPos(python[bodyID-1].GetPos()+=glm::vec3(0.0f,0.0f,1.0f));
    python[bodyID].SetDir(6);
    bodyID++;
  }
  //case 3: from left
  if(python[bodyID-1].GetOldDir()==9 && python[0].GetDir()==9){
    python[bodyID].SetPos(python[bodyID-1].GetPos()-=glm::vec3(1.0f,0.0f,0.0f));
    python[bodyID].SetDir(9);
    bodyID++;
  }
  
  //!!FOR WESTSIDE FOOD!!
  
  //case 1 from top
  if(python[bodyID-1].GetOldDir()==7 && python[0].GetDir()==8){
    python[bodyID].SetPos(python[bodyID-1].GetPos()-=glm::vec3(0.0f,0.0f,1.0f));
    python[bodyID].SetDir(7);
    bodyID++;
  }
  //case 2: from bottom
  if(python[bodyID-1].GetOldDir()==6 && python[0].GetDir()==8){
    python[bodyID].SetPos(python[bodyID-1].GetPos()+=glm::vec3(0.0f,0.0f,1.0f));
    python[bodyID].SetDir(6);
    bodyID++;
  }
  //case 3: from right
  if(python[bodyID-1].GetOldDir()==8 && python[0].GetDir()==8){
    python[bodyID].SetPos(python[bodyID-1].GetPos()+=glm::vec3(1.0f,0.0f,0.0f));
    python[bodyID].SetDir(8);
    bodyID++;
    }

  //FOR SOUTH SIDE FOOD!!
  //case 1 from left
  if(python[bodyID-1].GetOldDir() == 9 && python[0].GetDir()==7){
    python[bodyID].SetPos(python[bodyID-1].GetPos()-=glm::vec3(1.0f,0.0f,0.0f));
    python[bodyID].SetDir(9);
    bodyID++;
  }
  //case 2 from right
  if(python[bodyID-1].GetOldDir() == 8 && python[0].GetDir()==7){
    python[bodyID].SetPos(python[bodyID-1].GetPos()+=glm::vec3(1.0f,0.0f,0.0f));
    python[bodyID].SetDir(8);
    bodyID++;
  }
  //from top
  if(python[bodyID-1].GetOldDir() == 7 && python[0].GetDir()==7){
    python[bodyID].SetPos(python[bodyID-1].GetPos()-=glm::vec3(0.0f,0.0f,1.0f));
    python[bodyID].SetDir(7);
    bodyID++;
  }
  
}
//check collision
void Game::CheckCollision(){
  if(python[0].GetPosX() == fruit.GetPosX() && python[0].GetPosZ() == fruit.GetPosZ()){
    //std::cout<<"Collision!"<<std::endl;
    AddBody();
    NewFruitPos();
  }
}
void Game::HandleInput(int val){

  //for python
  if(val == 6){//north
    if(python[0].GetPosZ()<=9 && python[0].GetPosZ()>=0){
      std::cout<<"dir of last : "<<python[bodyID-1].GetDir()<<std::endl;
      if(!python[0].IsCrashed() && python[0].GetDir()!=7){
	python[0].SetDir(6);
	python[0].MoveToDir();
	if(!python[0].IsCrashed()){
	  for(int i=bodyID-1;i>0;i--){
	    python[i].MoveToDir();
	    python[i].SetDir(python[i-1].GetDir());
	  }
	}
      }
    }
  }
  else if(val == 7){//south
    if(python[0].GetPosZ()<=9 && python[0].GetPosZ()>=0){
      std::cout<<"dir of last : "<<python[bodyID-1].GetDir()<<std::endl;
      if(!python[0].IsCrashed() && python[0].GetDir()!=6){
	python[0].SetDir(7);
	python[0].MoveToDir();
	if(!python[0].IsCrashed()){
	  for(int i=bodyID-1;i>0;i--){
	    python[i].MoveToDir();
	    python[i].SetDir(python[i-1].GetDir());
	  }
	}
      }
    }
  }
  else if(val == 8){//west
    if(python[0].GetPosX()<=9 && python[0].GetPosX()>=0){
      std::cout<<"dir of last : "<<python[bodyID-1].GetDir()<<std::endl;
      if(!python[0].IsCrashed() && python[0].GetDir()!=9){
	python[0].SetDir(8);
	python[0].MoveToDir();
	if(!python[0].IsCrashed()){
	  for(int i=bodyID-1;i>0;i--){
	    python[i].MoveToDir();
	    python[i].SetDir(python[i-1].GetDir());
	  }
	}
      }
    }
  }
  else if(val == 9){//east
    if(python[0].GetPosX()<=9 && python[0].GetPosX()>=0){
      std::cout<<"dir of last : "<<python[bodyID-1].GetDir()<<std::endl;
      if(!python[0].IsCrashed() && python[0].GetDir()!=8){
	python[0].SetDir(9);
	python[0].MoveToDir();
	if(!python[0].IsCrashed()){
	  for(int i=bodyID-1;i>0;i--){
	    python[i].MoveToDir();
	    python[i].SetDir(python[i-1].GetDir());
	  }
	}
      }
    }
  }
  camera.HandleInput(val);

}
//update
void Game::Update(glm::vec3 camFront,float fv){
  //check collision
  CheckCollision();
  //handle input
  camera.UpdateCameraFront(camFront,fv); 

  for(int i=0;i<bodyID;i++){
    python[i].Update(camera.GetViewMatrix());
  }
  fruit.Update(camera.GetViewMatrix());
  grid.Update(camera.GetViewMatrix());

  
}

//draw
void Game::Draw(){

  for(int i=0;i<bodyID;i++){
    python[i].Draw();
  }
  fruit.Draw();
  grid.Draw();
 
}

