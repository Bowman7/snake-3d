#include"game.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Game::Game(){
  //init texture
  InitTexture();
  fruitShader.Init("f_shader.vert","f_shader.frag");
  gridShader.Init("grid_shader.vert","grid_shader.frag");
  pythonShader.Init("p_shader.vert","p_shader.frag");
  texShader.Init("tx.vert","tex.frag");
  lightShader.Init("light.vert","light.frag");
  
  InitPython(lightShader.GetID());
  python[0].SetID(pythonShader.GetID());
  python[0].SetPos(glm::vec3(1.0f,1.0f,2.0f));
  //python[0].SetColor(glm::vec3(1.0f,0.75f,0.80f));
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

  grid.SetTexture(grass_texture);
  grid.SetID(gridShader.GetID());
  fruit.SetID(fruitShader.GetID());
  //for grid
  grid.InitGrid();
}
//init tex
void Game::InitTexture(){
  //skin texture
  glGenTextures(1,&g_texture);
  glBindTexture(GL_TEXTURE_2D,g_texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  data = stbi_load("Graphics/skin2.jpg",&width,&height,&nrChannels,0);
  
  if(data){
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{
    std::cout<<"Could not load texture"<<std::endl;
  }
  stbi_image_free(data);
  
  //grass texture
  glGenTextures(1,&grass_texture);
  glBindTexture(GL_TEXTURE_2D,grass_texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  data = stbi_load("Graphics/grass3.png",&width,&height,&nrChannels,0);
  
  if(data){
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{
    std::cout<<"Could not load texture"<<std::endl;
  }
  stbi_image_free(data);
  
  
}
Game::~Game(){

}
//init python
void Game::InitPython(unsigned int l_id){
  for(int i=0;i<100;i++){
    python[i].SetID(pythonShader.GetID());
    python[i].SetPos(glm::vec3(0.0f,1.0f,0.0f));
    python[i].SetColor(glm::vec3(0.13f,0.54f,0.13f));
    python[i].SetDir(7);
    python[i].SetTexture(g_texture);
    python[i].SetLightID(l_id);
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
   //FOR SOUTH SIDE FOOD!!
  //case 1(tail->south head->south)
  if(python[bodyID-1].GetOldDir()==7 && python[0].GetDir()==7){
    python[bodyID].SetPos(python[bodyID-1].GetPos()-=glm::vec3(0.0f,0.0f,1.0f));
    python[bodyID].SetDir(7);
    bodyID++;
  }
  //case 2 (tail->east head->south)
  else if(python[bodyID-1].GetOldDir() == 9 && python[0].GetDir()==7){
    python[bodyID].SetPos(python[bodyID-1].GetPos()-=glm::vec3(1.0f,0.0f,0.0f));
    python[bodyID].SetDir(9);
    bodyID++;
  }
  //case 3 (tail->north head->south)
  else if(python[bodyID-1].GetOldDir()==6 && python[0].GetDir()==7){
    python[bodyID].SetPos(python[bodyID-1].GetPos()+=glm::vec3(0.0f,0.0f,1.0f));
    python[bodyID].SetDir(6);
    bodyID++;
  }
  //case 4 (tail->west head->south)
  else if(python[bodyID-1].GetOldDir() == 8 && python[0].GetDir()==7){
    python[bodyID].SetPos(python[bodyID-1].GetPos()+=glm::vec3(1.0f,0.0f,0.0f));
    python[bodyID].SetDir(8);
    bodyID++;
  }
  //----------FOR EASTSIDE FOOD!!
  
  //case 1: (tail->east head->east)
  else if(python[bodyID-1].GetOldDir()==9 && python[0].GetDir()==9){
    python[bodyID].SetPos(python[bodyID-1].GetPos()-=glm::vec3(1.0f,0.0f,0.0f));
    python[bodyID].SetDir(9);
    bodyID++;
  }
  //case 2:(tail->south head->east)
  else if(python[bodyID-1].GetOldDir() == 7 && python[0].GetDir() == 9){
    python[bodyID].SetPos(python[bodyID-1].GetPos()-=glm::vec3(0.0f,0.0f,1.0f));
    python[bodyID].SetDir(7);
    bodyID++;
  }
  //case 3:(tail->north head->east)
  else if(python[bodyID-1].GetOldDir() == 6 && python[0].GetDir() == 9){
    python[bodyID].SetPos(python[bodyID-1].GetPos()+=glm::vec3(0.0f,0.0f,1.0f));
    python[bodyID].SetDir(6);
    bodyID++;
  }
  //case 4:(tail->west head->east)
  else if(python[bodyID-1].GetOldDir()==8 && python[0].GetDir() == 9){
    python[bodyID].SetPos(python[bodyID-1].GetPos()+=glm::vec3(1.0f,0.0f,0.0f));
    python[bodyID].SetDir(8);
    bodyID++;
  }
  
  //------------FOR WESTSIDE FOOD!!
  
  //case 1:(tail->west head->west)
  else if(python[bodyID-1].GetOldDir()==8 && python[0].GetDir()==8){
    python[bodyID].SetPos(python[bodyID-1].GetPos()+=glm::vec3(1.0f,0.0f,0.0f));
    python[bodyID].SetDir(8);
    bodyID++;
  }
  //case 2:(tail->south head->west)
  else if(python[bodyID-1].GetOldDir()==7 && python[0].GetDir()==8){
    python[bodyID].SetPos(python[bodyID-1].GetPos()-=glm::vec3(0.0f,0.0f,1.0f));
    python[bodyID].SetDir(7);
    bodyID++;
  }
  //case 3:(tail->north head->west)
  else if(python[bodyID-1].GetOldDir()==6 && python[0].GetDir()==8){
    python[bodyID].SetPos(python[bodyID-1].GetPos()+=glm::vec3(0.0f,0.0f,1.0f));
    python[bodyID].SetDir(6);
    bodyID++;
  }
  //case 4:(tail->east head->west)
  else if(python[bodyID-1].GetOldDir()==9 && python[0].GetDir()==8){
    python[bodyID].SetPos(python[bodyID-1].GetPos()-=glm::vec3(1.0f,0.0f,0.0f));
    python[bodyID].SetDir(9);
    bodyID++;
    }

  //-----------FOR NORTH FOOD!!
  
  //case 1:(tail->north head->north)
  else if(python[bodyID-1].GetOldDir()==6 && python[0].GetDir()==6){
    python[bodyID].SetPos(python[bodyID-1].GetPos()+=glm::vec3(0.0f,0.0f,1.0f));
    python[bodyID].SetDir(6);
    bodyID++;
  }
  //case 2:(tail->east head->north)
  else if(python[bodyID-1].GetOldDir()==9 && python[0].GetDir()==6){
    python[bodyID].SetPos(python[bodyID-1].GetPos()-=glm::vec3(1.0f,0.0f,0.0f));
    python[bodyID].SetDir(9);
    bodyID++;
  }
  //case 3:(tail->west head->north)
  else if(python[bodyID-1].GetOldDir()==8 && python[0].GetDir()==6){
    python[bodyID].SetPos(python[bodyID-1].GetPos()+=glm::vec3(1.0f,0.0f,0.0f));
    python[bodyID].SetDir(8);
    bodyID++;
  }
  //case 4:(tail->south head->north)
  else if(python[bodyID-1].GetOldDir()==7 && python[0].GetDir()==6){
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
//check for self eating in north

bool Game::n_IsEatingSelf(){
  glm::vec3 temp = python[0].GetPos();
  temp-=glm::vec3(0.0f,0.0f,1.0f);
  for(int i=1;i<100;i++){
    if(temp.x == python[i].GetPosX() && temp.z == python[i].GetPosZ()){
      return true;
    }
  }
  return false;
}
// in south

bool Game::s_IsEatingSelf(){
  glm::vec3 temp = python[0].GetPos();
  temp+=glm::vec3(0.0f,0.0f,1.0f);
  for(int i=1;i<100;i++){
    if(temp.x == python[i].GetPosX() && temp.z == python[i].GetPosZ()){
      return true;
    }
  }
  return false;
}
//in east

bool Game::e_IsEatingSelf(){
  glm::vec3 temp = python[0].GetPos();
  temp+=glm::vec3(1.0f,0.0f,-.0f);
  for(int i=1;i<100;i++){
    if(temp.x == python[i].GetPosX() && temp.z == python[i].GetPosZ()){
      return true;
    }
  }
  return false;
}
//in west

bool Game::w_IsEatingSelf(){
  glm::vec3 temp = python[0].GetPos();
  temp-=glm::vec3(1.0f,0.0f,0.0f);
  for(int i=1;i<100;i++){
    if(temp.x == python[i].GetPosX() && temp.z == python[i].GetPosZ()){
      return true;
    }
  }
  return false;
}
//handle inputs
void Game::HandleInput(int val){

  //for python
  if(val == 6){//north
    if(python[0].GetPosZ()<=9 && python[0].GetPosZ()>=0){
      //std::cout<<"dir of last : "<<python[bodyID-1].GetDir()<<std::endl;
      if(!n_IsEatingSelf()){
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
  }
  else if(val == 7){//south
    if(python[0].GetPosZ()<=9 && python[0].GetPosZ()>=0){
      //std::cout<<"dir of last : "<<python[bodyID-1].GetDir()<<std::endl;
      if(!s_IsEatingSelf()){
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
  }
  else if(val == 8){//west
    if(python[0].GetPosX()<=9 && python[0].GetPosX()>=0){
      //std::cout<<"dir of last : "<<python[bodyID-1].GetDir()<<std::endl;
      if(!w_IsEatingSelf()){
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
  }
  else if(val == 9){//east
    if(python[0].GetPosX()<=9 && python[0].GetPosX()>=0){
      //std::cout<<"dir of last : "<<python[bodyID-1].GetDir()<<std::endl;
      if(!e_IsEatingSelf()){
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
    python[i].SetCameraPos(camera.GetPos());
  }
  fruit.Update(camera.GetViewMatrix());
  fruit.SetCameraPos(camera.GetPos());
  
  grid.Update(camera.GetViewMatrix());
  grid.SetCamPos(camera.GetPos());


  
}

//draw
void Game::Draw(){

  for(int i=0;i<bodyID;i++){
    python[i].Draw();
  }
  fruit.Draw();
  grid.Draw();
  
 
}

