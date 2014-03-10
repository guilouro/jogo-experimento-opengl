/*
  Name:        glTexture.h
  Copyright:   Version 0.1.1
  Author:      Rodrigo Luis de Souza da Silva
  Date:        03/11/2008
  Description: Load and store JPEG image as textures
               MUST USE libjpeg to work!
  Updates:
      07/11/2008 - Aspect Ratio option added
*/

#ifndef _GL_TEXTURE_H
#define _GL_TEXTURE_H

#include <string>

class glTexture
{
	public:
      glTexture();
      ~glTexture();
      void  SelectTexture(int );
      void  DisableTexture();
      void  SetNumberOfTextures(int );
      int   GetNumberOfTextures();      
      void  CreateTexture(std::string nome, int id);
      float GetAspectRatio(int);
      void  SetClampModeOn();
      void  SetRepeatModeOn();
      
	protected:
      GLuint *textureID;
      float  *aspectRatio;
      int    numberOfTextures;
      int    wrapMode;  // GL_REPEAT (Default) or GL_CLAMP 
};

#endif
