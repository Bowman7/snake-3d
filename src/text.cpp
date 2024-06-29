#include"../include/text.hpp"

Text::Text(){
  if(FT_Init_FreeType(&ft)){
    std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
  }

  if(FT_New_Face(ft,"Fonts/boxy.TTF",0,&face)){
    std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl; 
  }
  FT_Set_Pixel_Sizes(face,0,48);


  //store all ASCII characters
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);

  for(unsigned char c=0;c<128;c++){
    //load character glyph
    if(FT_Load_Char(face,c,FT_LOAD_RENDER)){
      std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
      continue;
    }
    //generate texture
    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,
		 face->glyph->bitmap.width,
		 face->glyph->bitmap.rows,
		 0,GL_RED,GL_UNSIGNED_BYTE,
		 face->glyph->bitmap.buffer);
    //texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //store chracter

    Character character={
      texture,
      glm::ivec2(face->glyph->bitmap.width,face->glyph->bitmap.rows),
      glm::ivec2(face->glyph->bitmap_left,face->glyph->bitmap_top),
      face->glyph->advance.x
    };

    Characters.insert(std::pair<char,Character>(c,character));
  }
  //done
  FT_Done_Face(face);
  FT_Done_FreeType(ft);

  //vaos and vbo
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(float)*6*4,NULL,GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,4*sizeof(float),0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER,0);
  glBindVertexArray(0);
  
}
//render text

void Text::RenderText(std::string text,float x,float y,float scale,glm::vec3 color){
  //std::cout<<"Rendering ext"<<std::endl;
  glUseProgram(ID);
  glm::mat4 projection = glm::ortho(0.0f,1080.0f,0.0f,720.0f);
  setMat4("projection",projection,ID);
  glUniform3f(glGetUniformLocation(ID,"textColor"),color.x,color.y,color.z);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);
  //iterate through all chars
  std::string::const_iterator c;
  for(c =text.begin();c!=text.end();c++){
    Character ch = Characters[*c];

    float xpos = x+ch.Bearing.x*scale;
    float ypos = y-(ch.Size.y - ch.Bearing.y)*scale;

    float w = ch.Size.x * scale;
    float h = ch.Size.y * scale;

    //update VBO for each char
    float vertices[6][4]={
      {xpos, ypos+h ,0.0f,0.0f},
      {xpos, ypos,0.0f,1.0f},
      {xpos+w,ypos,1.0f,1.0f},

      {xpos,ypos+h,0.0f,0.0f},
      { xpos+w,ypos,1.0f,1.0f},
      { xpos+w,ypos+h,1.0f,0.0f}
      
    };
    //render gylph texture over quad
    glBindTexture(GL_TEXTURE_2D,ch.TextureID);
    //up content in vbo
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    //redner quad
    glDrawArrays(GL_TRIANGLES,0,6);
    x+=(ch.Advance>>6)*scale;
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D,0);
}
