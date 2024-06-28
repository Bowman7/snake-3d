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
  loadingShader.Init("screen.vert","screen.frag");
  endLoadingShader.Init("screen.vert","screen.frag");
  //for text
  textShader.Init("text.vert","text.frag");
  
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
  //laoding screen
  loading.SetTexture(l_texture);
  loading.SetID(loadingShader.GetID());
  //gameover screen
  endLoading.SetTexture(el_texture);
  endLoading.SetID(endLoadingShader.GetID());
  //for grid
  grid.InitGrid();
  //for text
  text.SetID(textShader.GetID());

}
Game::~Game(){
  
}
//reset game
void Game::Reset(){
  gameOver = false;
  bodyID = 0;
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
  //loading screen texture
  //texture
  glGenTextures(1,&l_texture);
  glBindTexture(GL_TEXTURE_2D,l_texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  stbi_set_flip_vertically_on_load(true);  
  data = stbi_load("Graphics/background0.png",&width,&height,&nrChannels,0);
  if(data){
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{
     std::cout<<"Could not load texture"<<std::endl;
  }
  stbi_image_free(data);

  //game over texure
  glGenTextures(1,&el_texture);
  glBindTexture(GL_TEXTURE_2D,el_texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  stbi_set_flip_vertically_on_load(true);  
  data = stbi_load("Graphics/background-1.png",&width,&height,&nrChannels,0);
  if(data){
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{
     std::cout<<"Could not load texture"<<std::endl;
  }
  stbi_image_free(data);
  
  
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
    python[i].ResetCrashed();
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
    PlayBite();
    AddBody();
    NewFruitPos();
    speed += 0.01;
  }
}
//check for self eating in north

bool Game::n_IsEatingSelf(){
  glm::vec3 temp = python[0].GetPos();
  temp-=glm::vec3(0.0f,0.0f,1.0f);
  for(int i=2;i<bodyID;i++){
    if(temp.x == python[i].GetPosX() && temp.z == python[i].GetPosZ()){
      gameOver = true;
      return true;
    }
  }
  return false;
}
// in south

bool Game::s_IsEatingSelf(){
  glm::vec3 temp = python[0].GetPos();
  temp+=glm::vec3(0.0f,0.0f,1.0f);
  for(int i=2;i<bodyID;i++){
    if(temp.x == python[i].GetPosX() && temp.z == python[i].GetPosZ()){
      gameOver = true;
      return true;
    }
  }
  return false;
}
//in east

bool Game::e_IsEatingSelf(){
  glm::vec3 temp = python[0].GetPos();
  temp+=glm::vec3(1.0f,0.0f,-.0f);
  for(int i=2;i<bodyID;i++){
    if(temp.x == python[i].GetPosX() && temp.z == python[i].GetPosZ()){
      gameOver = true;
      return true;
    }
  }
  return false;
}
//in west

bool Game::w_IsEatingSelf(){
  glm::vec3 temp = python[0].GetPos();
  temp-=glm::vec3(1.0f,0.0f,0.0f);
  for(int i=2;i<bodyID;i++){
    if(temp.x == python[i].GetPosX() && temp.z == python[i].GetPosZ()){
      gameOver = true;
      return true;
    }
  }
  return false;
}
//handle inputs
void Game::HandleInput(int val){
  //for python
  if(python[0].IsCrashed()){
    gameOver = true;
  }
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
//time step
bool Game::EventTriggered(double Time){
  double currentTime = glfwGetTime();
  if(currentTime - lastUpdatedTime >= Time){
    lastUpdatedTime = currentTime;
    return true;
  }
  return false;
}
//update
void Game::Update(glm::vec3 camFront,float fv){
  if(EventTriggered(speed)){
    if(python[0].IsCrashed()){
      gameOver = true;
    }
    //north
    if(python[0].GetDir() == 6){
      if(!n_IsEatingSelf()){
	python[0].SetDir(6);
	python[0].MoveToDir();
	for(int i =bodyID-1;i>0;i--){
	  python[i].MoveToDir();
	  python[i].SetDir(python[i-1].GetDir());
	}
      }
    }
    //south
    else if(python[0].GetDir()==7){
      if(!s_IsEatingSelf()){
	python[0].SetDir(7);
	python[0].MoveToDir();
	for(int i =bodyID-1;i>0;i--){
	  python[i].MoveToDir();
	  python[i].SetDir(python[i-1].GetDir());
	}
      }
    }
    //west
    else if(python[0].GetDir() == 8){
      if(!w_IsEatingSelf()){
	python[0].SetDir(8);
	python[0].MoveToDir();
	for(int i =bodyID-1;i>0;i--){
	  python[i].MoveToDir();
	  python[i].SetDir(python[i-1].GetDir());
	}
      }
    }
    //east
    else if(python[0].GetDir() == 9){
      if(!e_IsEatingSelf()){
	python[0].SetDir(9);
	python[0].MoveToDir();
	for(int i =bodyID-1;i>0;i--){
	  python[i].MoveToDir();
	  python[i].SetDir(python[i-1].GetDir());
	}
      }
    }
  }
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
  //draw text
 
  for(int i=0;i<bodyID;i++){
    python[i].Draw();
  }
  fruit.Draw();
  grid.Draw();
  text.RenderText("This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
  text.RenderText("(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
}
//draw loading
void Game::DrawLoading(){
  loading.Draw();
}
//draw gameover
void Game::DrawGameOver(){
  endLoading.Draw();
}

