#include <GL/glut.h>
#include <string>
#include <stdio.h>
#include <malloc.h>

#include "glTexture.h"
#include "libjpeg.h" 

//-----------------------------------------------------------
glTexture::glTexture()
{
   this->numberOfTextures = 0;
   this->textureID = NULL;
   this->aspectRatio = NULL;  
   this->wrapMode = GL_REPEAT; 
}

//-----------------------------------------------------------
void  glTexture::SetClampModeOn()
{
   this->wrapMode = GL_CLAMP;   
}

//-----------------------------------------------------------
void  glTexture::SetRepeatModeOn()
{
   this->wrapMode = GL_REPEAT;    
}

//-----------------------------------------------------------
glTexture::~glTexture()
{
   this->numberOfTextures = 0;   
   if(this->textureID)
      delete []this->textureID;
}

//-----------------------------------------------------------
void glTexture::SetNumberOfTextures(int n)
{
   this->numberOfTextures = n;      
   this->textureID        = new GLuint[n];
   this->aspectRatio      = new float[n];   
   
   glEnable ( GL_TEXTURE_2D );
   glGenTextures ( this->numberOfTextures, textureID );   
}

//----------------------------------------------------------- 
float glTexture::GetAspectRatio(int tex)
{
   if(tex >= this->numberOfTextures)
   {
      printf("Error in glTexture::GetAspectRatio(int) : Out of Range access!\"\n\n");
      exit(1);
   }
   return this->aspectRatio[tex];
}

//-----------------------------------------------------------
int glTexture::GetNumberOfTextures()
{
   return this->numberOfTextures;
}

//-----------------------------------------------------------
void glTexture::SelectTexture(int tex)
{
   glEnable ( GL_TEXTURE_2D );
   glBindTexture ( GL_TEXTURE_2D, (GLuint) this->textureID[ tex ] );
}

//-----------------------------------------------------------
void glTexture::DisableTexture()
{
   glDisable(GL_TEXTURE_2D);
}

//-----------------------------------------------------------
void glTexture::CreateTexture(std::string nome, int id)
{
   const char *filename = nome.c_str();
   glBindTexture ( GL_TEXTURE_2D, this->textureID[id] );   
   
   FILE *fd_arquivo =fopen(filename, "rb");
   // Contém as informações do arquivo
   struct  jpeg_decompress_struct cinfo;       
   
   struct  jpeg_error_mgr jerr;                 
   GLubyte *linha;                             
   
   // Conterá a imagem carregada
   GLubyte *image;   
   // Tamanho da Imagem
   int     ImageSize;                          
   
   cinfo.err = jpeg_std_error(&jerr);
   jpeg_create_decompress(&cinfo);
   
   // Abre o arquivo, lê seu cabeçalho
   // e processa a descompressão da mesma    
   jpeg_stdio_src(&cinfo, fd_arquivo);
   jpeg_read_header(&cinfo, TRUE);
   jpeg_start_decompress ( &cinfo );
   
   this->aspectRatio[id] = (float) cinfo.image_width / (float) cinfo.image_height;
   
   ImageSize = cinfo.image_width * cinfo.image_height * 3;    
   image = (GLubyte *) malloc ( ImageSize );
   linha=image;
   
   while ( cinfo.output_scanline < cinfo.output_height )
   {
     linha = image + 3 * cinfo.image_width * cinfo.output_scanline;
     jpeg_read_scanlines ( &cinfo, &linha, 1 );
   }
   
   jpeg_finish_decompress(&cinfo);
   jpeg_destroy_decompress(&cinfo);
   
   //Aplicação de filtros para tratamento da imagem pelo OpenGL
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,this->wrapMode);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,this->wrapMode);
   
   // Efetua a geração da imagem na memória
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cinfo.image_width, cinfo.image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
   
   fclose (fd_arquivo);
   free (image);    
}
