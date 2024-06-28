#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include"game.hpp"
#include"music.cpp"

#define WIDTH 1920
#define HEIGHT 1080


//enum
enum GAMESTATE{
  LOADING =0,
  GAME,
  GAMEOVER
};
GAMESTATE state ;
//yaw and vec3 var frontpos
bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
glm::vec3 cameraFront = glm::vec3(0.0f,0.0f,-1.0f);
float lastX = WIDTH/2.0f;
float lastY = HEIGHT/2.0f;
float fov = 45.0f;
//screen callback
void framebuffer_size_callback(GLFWwindow* window,int width,int height){
  glViewport(0,0,width,height);
}
//scroll callback

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
  fov -=(float)yoffset;
  if(fov < 1.0f){
    fov = 1.0f;
  }
  if(fov >45.0f){
    fov = 45.0f;
  }
}
//mousr callback
void mouse_callback(GLFWwindow* window,double xpos,double ypos){
  if(firstMouse){
    lastX=WIDTH/2.0f;
    lastY = HEIGHT/2.0f;;
    firstMouse = false;
  }
  float xOffset = xpos- lastX;
  float yOffset = ypos - lastY;
  lastX = xpos;
  lastY = ypos;

  const float sensitivity = 0.05f;
  xOffset *=sensitivity;
  yOffset *=sensitivity;
  
  yaw  +=xOffset;
  pitch+=yOffset;

  if(pitch >=89.0f){
    pitch = 89.0f;
  }
  if(pitch<-89.0f){
    pitch = -89.0f;
  }

  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));
  cameraFront = glm::normalize(direction);
  
}
//bools for snake

bool up = false;
bool down = false;
bool left = false;
bool right = false;
//key callback
void myKeyCallbackFunc(GLFWwindow* window, int key, int scancode, int action, int mods){
  if(key == GLFW_KEY_UP && action == GLFW_PRESS){
    up = true;
  }
  if(key == GLFW_KEY_LEFT && action == GLFW_PRESS){
    left = true;
  }
  if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
    right = true;
  }
  if(key == GLFW_KEY_DOWN && action == GLFW_PRESS){
    down = true;
  }
  if(key == GLFW_KEY_ENTER && action == GLFW_PRESS){
    if(state == LOADING){
      state = GAME;
    }
    if(state == GAMEOVER){
      state = LOADING;
    }
  }
}
//input

int processInput(GLFWwindow *window){
  if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
    glfwSetWindowShouldClose(window,true);
    return 0;
  }
  if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS){
    return 1;
  }
  if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS){
    return 2;
  }
  if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS){
    return 3;
  }
  if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS){
    return 4;
  }
  //for snake
  if(up){
    up = false;
    return 6;
  }
  if(down){
    down = false;
    return 7;
  }
  if(left){
    left = false;//wst
    return 8;
  }
  if(right){
    right = false;//est
    return 9;
  }
  return 5;
  
}
//play music

int main(){
  //init glfw and version
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

  //window
  GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"hello window",NULL,NULL);
  if(window == NULL){
    std::cout<<"Failed to create GLFW window"<<std::endl;
    glfwTerminate();
  }

  //callbacks
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window,mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetKeyCallback(window,myKeyCallbackFunc);
  //load glad
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout<<"Failed to initialize GLAD"<<std::endl;
    
  }
  //enable blending mode for text
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  //enable depth test
  glEnable(GL_DEPTH_TEST);
  //inside window mousr
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  //WIREFRAME MODE
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
  //MAIN GAME OBJECT
  Game game;

  Music music;
  bool loading = true;
  bool m_game = false;
  bool m_gameover = false;
  //MAIN LOOP
  while(!glfwWindowShouldClose(window)){
   
    //handle input
    game.HandleInput(processInput(window));
    //update
    game.Update(cameraFront,fov);
    
    switch(state){
    case LOADING:
      {
	if(loading){
	  music.Stop();
	  music.Play();
	  loading = false;
	  m_game = true;
	}
	glClearColor(0.0f,0.5f,0.5f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	game.DrawLoading();
      }
      break;
    case GAME:
      {
	if(m_game){
	  music.Stop();
	  music.PlayGame();
	  m_game= false;
	  m_gameover = true;
	  
	}
	
	if(game.CheckGameOver()){
	  state = GAMEOVER;
	  game.Reset();
	}else{
	  //render
	  glClearColor(0.0f,0.5f,0.5f,1.0f);
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  
	  game.Draw();
	}
	
      }break;
    case GAMEOVER:
      {
	if(m_gameover){
	  music.Stop();
	  music.PlayOver();
	  m_gameover =false;
	  loading = true;
	}
	glClearColor(0.0f,0.5f,0.5f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	game.DrawGameOver();
      }
      break;
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
 
  glfwTerminate();
  return 0;
}
