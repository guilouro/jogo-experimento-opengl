
//-------------------------------------------------------------------------------------

#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include "resources/glTexture.h"

using namespace std;

glTexture *textureManager; //ponteiro para a textura


// variaveis de apoio
int numeroDaPeca = 0,
    relogio      = 0;


// variaveis de movimento e posição
float dx    = 1,
      dy    = -80.0,
      MoveX = -100,
      dx2   = 25.0;
      
float mesaPcPosX      = 75,
      cocaPosX        = 180,
      objTetoPosX     = 330,
      cocaPos2X       = 420,
      objTetoPos2X    = 580,
      lixoPosX        = 645,
      mesaChefePosX   = 720;

//vetores de posição      
float lixoX[4],
      lixoY[4],
      coca[4],
      persoX[4],
      persoY[4],
      cocaX[4],
      cocaY[4],
      coca2X[4],
      coca2Y[4],
      objTetoX[4],
      objTetoY[4],
      objTeto2X[4],
      objTeto2Y[4];
      

//ESCALA
float objTetoScaleX = 0.8,
      objTetoScaleY = 1.25;


bool jogar       = true,
     dica1       = false,
     jogando     = false,
     perdeu      = false,
     ganhou      = false,
     perdeuTempo = false;


//-------------------------------------------------------------------------------------

void atualizaColisao( void )
{
    // PERSONAGEM XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
     
    persoX[0] = 0;
    persoX[1] = 0;
    persoX[2] = 50;
    persoX[3] = 50;
        
    persoY[0] = 0  + dy;
    persoY[1] = 50 + dy;
    persoY[2] = 50 + dy;
    persoY[3] = 0  + dy;
    
    //maquida de coca 1 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    
    cocaX[0]  = (0        + (cocaPosX-20)) + MoveX;
    cocaX[1]  = (0        + (cocaPosX-20)) + MoveX;
    cocaX[2]  = (50 * 2.0 + (cocaPosX+20)) + MoveX;
    cocaX[3]  = (50 * 2.0 + (cocaPosX+20)) + MoveX;
    
    cocaY[0]  = 0;
    cocaY[1]  = 50*1.5;
    cocaY[2]  = 50*1.5;
    cocaY[3]  = 0;
    
    //maquida de coca 2 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    
    coca2X[0]  = (0      + (cocaPos2X-20)) + MoveX;
    coca2X[1]  = (0      + (cocaPos2X-20)) + MoveX;
    coca2X[2]  = (50*2.0 + (cocaPos2X+20)) + MoveX;
    coca2X[3]  = (50*2.0 + (cocaPos2X+20)) + MoveX;
    
    coca2Y[0]  = 0;
    coca2Y[1]  = 50*1.5;
    coca2Y[2]  = 50*1.5;
    coca2Y[3]  = 0;
    
    // OBJETO TETO XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    
    objTetoX[0] = (0        + (objTetoPosX - 20)) + MoveX;
    objTetoX[1] = (0        + (objTetoPosX - 20)) + MoveX;
    objTetoX[2] = (50 * 0.5 + (objTetoPosX + 20)) + MoveX;
    objTetoX[3] = (50 * 0.5 + (objTetoPosX + 20)) + MoveX;
    
    // OBJETO TETO 2 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    
    objTeto2X[0] = (0        + (objTetoPos2X - 20)) + MoveX;
    objTeto2X[1] = (0        + (objTetoPos2X - 20)) + MoveX;
    objTeto2X[2] = (50 * 0.5 + (objTetoPos2X + 20)) + MoveX;
    objTeto2X[3] = (50 * 0.5 + (objTetoPos2X + 20)) + MoveX;
    
    //LIXEIRA XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    
    lixoX[0]  = (0      + (lixoPosX-20)) + MoveX;
    lixoX[1]  = (0      + (lixoPosX-20)) + MoveX;
    lixoX[2]  = (50*0.4 + (lixoPosX+20)) + MoveX;
    lixoX[3]  = (50*0.4 + (lixoPosX+20)) + MoveX;
    
    lixoY[0]  = 0;
    lixoY[1]  = 50*1.5;
    lixoY[2]  = 50*1.5;
    lixoY[3]  = 0;
}

//-------------------------------------------------------------------------------------
void imagem( void )
{
    // Criação do arquivo que irá gerenciar as texturas
    textureManager = new glTexture();
    
    // Estabelece o número de texturas que será utilizado
    textureManager->SetNumberOfTextures(16);
    
    // Cria as texturas
    textureManager->CreateTexture( "images/bgFase1.jpg", 0 );
    textureManager->CreateTexture( "images/nerd.jpg", 1 );
    textureManager->CreateTexture( "images/coca.jpg", 2 );
    textureManager->CreateTexture( "images/tela1.jpg", 3 );
    textureManager->CreateTexture( "images/dica1.jpg", 4 );
    textureManager->CreateTexture( "images/perdeu.jpg", 5 );
    textureManager->CreateTexture( "images/ganhou.jpg", 6 );
    textureManager->CreateTexture( "images/lustre.jpg", 7 );
    textureManager->CreateTexture( "images/pc1.jpg", 8 );
    textureManager->CreateTexture( "images/pc2.jpg", 9 );
    textureManager->CreateTexture( "images/lixoCheio.jpg", 10 );
    textureManager->CreateTexture( "images/lixoVazio.jpg", 11 );
    textureManager->CreateTexture( "images/perdeu2.jpg", 12 );
    textureManager->CreateTexture( "images/hd.jpg", 13 );
    textureManager->CreateTexture( "images/cd.jpg", 14 );
    textureManager->CreateTexture( "images/regra.jpg", 15 );
}
//---------------------------------------------------------------------------------------
void acaoPeca( void )
{            
     if((persoX[0] > cocaX[0] && persoX[0] < cocaX[3])){   numeroDaPeca = 1; }
     if((persoX[0] > coca2X[0] && persoX[0] < coca2X[3])){ numeroDaPeca = 2; }
     if((persoX[0] > lixoX[0] && persoX[0] < lixoX[3])){   numeroDaPeca = 3; }
     
     if(MoveX == -100 && numeroDaPeca != 0)
     {
          if(numeroDaPeca == 3)
          {
             ganhou = true;
          }else{ 
             perdeu = true;
          }
     }
     glutPostRedisplay();
}
//-------------------------------------------------------------------------------------

void reseta( void )
{
     numeroDaPeca = 0;
     relogio = 0;
     jogando = false;
}

//-------------------------------------------------------------------------------------
void keyboard( unsigned char key, int x, int y )
{
     
     switch(key)
     {
        case 27: //ESC
             exit(0); 
             break;
        
        case 13: //ENTER
             dica1   = false;
             jogando = true;
             break;
             
        case 105:
        case 73:
        case 106: // (J)
        case 74:
        case 49:
             jogar = false;
             dica1 = true;
             ganhou = false;
             perdeu = false;
             perdeuTempo = false;
             break;
             
        case 32: //ESPAÇO
             acaoPeca();
             break;             
     }
     
    printf("%d", key);    
    glutPostRedisplay();    
}

//-------------------------------------------------------------------------------------
void special( int key, int x, int y )
{
    switch( key )
    {
        case GLUT_KEY_LEFT:
            dx = 1;
            dx2 = 25;
            //move cena
            if(MoveX < (-100)){
                     if((persoX[0] != cocaX[3] || persoY[0] != -80) &&
                        (persoX[0] != coca2X[3] || persoY[0] != -80) &&
                        (persoX[0] != objTetoX[3] || persoY[0] != -65)&&
                        (persoX[0] != objTeto2X[3] || persoY[0] != -65)&&
                        (persoX[0] != lixoX[3] || persoY[0] != -80)) MoveX++;
                     
            }
            cout << "persoX[0]: " << persoX[0] << "  **** cocaX[0]: " << objTetoX[0] << "\n";
            cout << "persoX[1]: " << persoX[1] << "  **** cocaX[1]: " << objTetoX[1] << "\n";
            cout << "persoX[2]: " << persoX[2] << " **** cocaX[2]: " << objTetoX[2] << "\n";
            cout << "persoX[3]: " << persoX[3] << " **** cocaX[3]: " << objTetoX[3] << "\n\n";
            break;
        
        case GLUT_KEY_RIGHT:
            dx = -1;
            dx2 = -25;
            //move cena
            if(MoveX > (-700)){
                     if((persoX[0] != cocaX[0] || persoY[0] != -80)&&
                        (persoX[0] != coca2X[0] || persoY[0] != -80)&&
                        (persoX[0] != objTetoX[0] || persoY[0] != -65)&&
                        (persoX[0] != objTeto2X[0] || persoY[0] != -65)&&
                        (persoX[0] != lixoX[0] || persoY[0] != -80)) MoveX--;
            }
            cout << "persoX[0]: " << persoX[0] << "  **** cocaX[0]: " << objTetoX[0] << "\n";
            cout << "persoX[1]: " << persoX[1] << "  **** cocaX[1]: " << objTetoX[1] << "\n";
            cout << "persoX[2]: " << persoX[2] << " **** cocaX[2]: " << objTetoX[2] << "\n";
            cout << "persoX[3]: " << persoX[3] << " **** cocaX[3]: " << objTetoX[3] << "\n\n";
            break;
        
        case GLUT_KEY_UP:
            if(!(persoX[0] > objTetoX[0] && persoX[0] < objTetoX[3]) &&
               !(persoX[0] > objTeto2X[0] && persoX[0] < objTeto2X[3])) dy = -65;
            break;
        
        case GLUT_KEY_DOWN:
             if(!(persoX[0] > cocaX[0] && persoX[0] < cocaX[3]) && 
             !(persoX[0] > coca2X[0] && persoX[0] < coca2X[3]) &&
             !(persoX[0] > lixoX[0] && persoX[0] < lixoX[3])) dy = -80;                           
            break;
	}
	atualizaColisao();
	glutPostRedisplay();
}    

//-------------------------------------------------------------------------------------
void reshape( GLsizei w, GLsizei h )
{

    glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -100, 100, -100, 100, -1.0, 1.0 );
    
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

//-------------------------------------------------------------------------------------
void pegaImagem( int op )
{
    textureManager->SelectTexture( op ); 
}

//-------------------------------------------------------------------------------------
void desenhaObjeto()
{
    glBegin(GL_QUADS);
        glTexCoord2f(1.0, 1.0); //especifica as coordenadas a ser utilizada pela textura 
        glVertex2f( 0.0, 0.0 );
        glTexCoord2f(1.0, 0.0); 
		glVertex2f( 0.0, 50.0 );   
        glTexCoord2f(0.0, 0.0);     
		glVertex2f( 50.0, 50.0 ); 
        glTexCoord2f(0.0, 1.0);       
		glVertex2f( 50.0, 0.0);
     glEnd();
}    
//-------------------------------------------------------------------------------------
void desenhaTelas()
{
    glBegin(GL_QUADS);
        glTexCoord2f(1.0, 1.0); //especifica as coordenadas a ser utilizada pela textura 
        glVertex2f( -100.0, -100.0 );
        glTexCoord2f(1.0, 0.0); 
		glVertex2f( -100.0, 100.0 );   
        glTexCoord2f(0.0, 0.0);     
		glVertex2f( 100.0, 100.0 ); 
        glTexCoord2f(0.0, 1.0);       
		glVertex2f( 100.0, -100.0);
     glEnd();
}    
//-------------------------------------------------------------------------------------
void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXX FUNDO CENA XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
   
    //PrimeiroFundo
    pegaImagem( 0 );
    glPushMatrix();
        glTranslatef( MoveX, -100, 0.0 );
        glScalef( 4, 4, 1.0 );
        desenhaObjeto();
    glPopMatrix();
    textureManager->DisableTexture();
    
    //segundoFundo
    pegaImagem( 0 );
    glPushMatrix();
        glTranslatef( MoveX+200, -100, 0.0 );
        glScalef( 4, 4, 1.0 );
        desenhaObjeto();
    glPopMatrix();
    textureManager->DisableTexture();
    
    //terceiroFundo
    pegaImagem( 0 );
    glPushMatrix();
        glTranslatef( MoveX+400, -100, 0.0 );
        glScalef( 4, 4, 1.0 );
        desenhaObjeto();
    glPopMatrix();
    textureManager->DisableTexture();
    
    //quartoFundo
    pegaImagem( 0 );
    glPushMatrix();
        glTranslatef( MoveX+600, -100, 0.0 );
        glScalef( 4, 4, 1.0 );
        desenhaObjeto();
    glPopMatrix();
    textureManager->DisableTexture();
    
//XXXXXXXXXXXXXXXXXXXXXXXXX OBJETOS DA CENA XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    
    //Regras
    pegaImagem( 15 );
    glPushMatrix();
        glTranslatef( 0.0,93.0, 0.0 );
        glScalef( -1, 0.05, 1);
        desenhaTelas();
    glPopMatrix();
    textureManager->DisableTexture();
    

    //Personagem
    pegaImagem( 1 );
    glPushMatrix();
        glTranslatef( dx2,dy, 0.0 );
        glScalef( -dx, 1.8, 1);
        desenhaObjeto();
    glPopMatrix();
    textureManager->DisableTexture();
    
    //Mesa computador
    pegaImagem( 8 );
    glPushMatrix();
        glTranslatef( MoveX + mesaPcPosX, -85, 0.0 );
        glScalef( -1.0, 2, 1.0 );
        desenhaObjeto();
    glPopMatrix(); 
    textureManager->DisableTexture();
    
    //Coca-cola
   pegaImagem( 2 );
    glPushMatrix();
        glTranslatef( MoveX + cocaPosX, -80, 0.0 );
        glScalef( 2.0, 1.3, 1.0 );
        desenhaObjeto();
    glPopMatrix();
    textureManager->DisableTexture();
    
    //Coca-cola 2
    pegaImagem( 2 );
    glPushMatrix();
        glTranslatef( MoveX + cocaPos2X, -80, 0.0 );
        glScalef( 2.0, 1.3, 1.0 );
        desenhaObjeto();
    glPopMatrix();
    textureManager->DisableTexture();
    
    //Objeto Teto
    pegaImagem( 7 );
    glPushMatrix();
        glTranslatef( MoveX + objTetoPosX, 10, 0.0 );
        glScalef( 0.5, 1.8, 1.0 );
        desenhaObjeto();
    glPopMatrix(); 
    textureManager->DisableTexture();
    
     //Objeto Teto 2
    pegaImagem( 7 );
    glPushMatrix();
        glTranslatef( MoveX + objTetoPos2X, 10, 0.0 );
        glScalef( 0.5, 1.8, 1.0 );
        desenhaObjeto();
    glPopMatrix(); 
    textureManager->DisableTexture();
    
    //Mesa CHEFE
    pegaImagem( 9 );
    glPushMatrix();
        glTranslatef( MoveX + mesaChefePosX, -85, 0.0 );
        glScalef( 1.0, 2, 1.0 );
        desenhaObjeto();
    glPopMatrix(); 
    textureManager->DisableTexture();
    
    
//XXXXXXXXXXXXXXXXXXXXXXXXXXX PEÇAS NA CENA XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

    // CAIXA
    if( numeroDaPeca != 1 )
    {
        pegaImagem( 13 );
        glPushMatrix();
            glTranslatef( MoveX + cocaPosX + 50, -18, 0.0 );
            glScalef( 0.25, 0.25, 1.0 );
            desenhaObjeto();
        glPopMatrix(); 
        textureManager->DisableTexture();
    }

    // CD
    if( numeroDaPeca != 2 )
    {
        pegaImagem( 14 );
        glPushMatrix();
            glTranslatef( MoveX + cocaPos2X + 50, -18, 0.0 );
            glScalef( 0.25, 0.32, 1.0 );
            desenhaObjeto();
        glPopMatrix(); 
        textureManager->DisableTexture();
    }
    
    //Lixeira
    if( numeroDaPeca != 3 )
    {
        pegaImagem( 10 );
        glPushMatrix();
            glTranslatef( MoveX + lixoPosX, -85, 0.0 );
            glScalef( 0.4, 0.5, 1.0 );
            desenhaObjeto();
        glPopMatrix(); 
        textureManager->DisableTexture();
    } else {
        pegaImagem( 11 );
        glPushMatrix();
            glTranslatef( MoveX + lixoPosX, -85, 0.0 );
            glScalef( 0.4, 0.5, 1.0 );
            desenhaObjeto();
        glPopMatrix(); 
        textureManager->DisableTexture();   
    }
    
    //café
    /*if( numeroDaPeca != 4 )
    {
        //pegaImagem( 2 );
        glPushMatrix();
            glTranslatef( MoveX + mesaChefePosX, -85, 0.0 );
            glScalef( 0.4, 0.4, 1.0 );
            desenhaObjeto();
        glPopMatrix(); 
        //textureManager->DisableTexture();
    }*/
    
//XXXXXXXXXXXXXXXXXXXXXXXXXX TELA DE DICAS XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   

    if((!jogar) && (dica1))
    {
        pegaImagem( 4 );
        glPushMatrix();
            glTranslatef( 0, 0, 0.0 );
            glScalef( -1, 1, 1.0 );
            desenhaTelas();
        glPopMatrix(); 
        textureManager->DisableTexture();
    }
    
//XXXXXXXXXXXXXXXXXXXXXXXXXXXX TELA INICIAL XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

    if(jogar)
    {
        pegaImagem( 3 );
        glPushMatrix();
            glTranslatef( 0, 0, 0.0 );
            glScalef( -1, 1, 1.0 );
            desenhaTelas();
        glPopMatrix(); 
        textureManager->DisableTexture();
    }
    
//XXXXXXXXXXXXXXXXXXXXXXXXXXXX TELA GANHOU/PERDEU XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

    if(ganhou)
    {
        pegaImagem( 6 );
        glPushMatrix();
            glTranslatef( 0, 0, 0.0 );
            glScalef( -1, 1, 1.0 );
            desenhaTelas();
        glPopMatrix(); 
        textureManager->DisableTexture();
        reseta();
    }
    
    if(perdeu)
    {
        if(perdeuTempo)
        {
                pegaImagem( 12 );
                glPushMatrix();
                    glTranslatef( 0, 0, 0.0 );
                    glScalef( -1, 1, 1.0 );
                    desenhaTelas();
                glPopMatrix(); 
                textureManager->DisableTexture();
                reseta();
        }
        else
        {
                pegaImagem( 5 );
                glPushMatrix();
                    glTranslatef( 0, 0, 0.0 );
                    glScalef( -1, 1, 1.0 );
                    desenhaTelas();
                glPopMatrix(); 
                textureManager->DisableTexture();
                reseta();
        }
    }

    glutSwapBuffers();
}

//-------------------------------------------------------------------------------------
void Init( void )
{
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    srand(time(NULL));
}
//-------------------------------------------------------------------------------------
void timer( int i )
{
     
    if(jogando) relogio ++;
    
    if(relogio == 90) 
    {
               perdeu = true;
               perdeuTempo = true;
    }
        
    glutPostRedisplay();
    glutTimerFunc( 1000, timer, 1 );
}    
//-------------------------------------------------------------------------------------
int main()
{
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowPosition( 100, 100 );
    glutInitWindowSize( 1000, 700 );
    glutCreateWindow("Jogo Nerd");
    
    glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutSpecialFunc( special );
    glutKeyboardFunc( keyboard );
    
    glutTimerFunc( 60, timer, 1 );
	
    imagem();
    Init();
    
    glutMainLoop();
    return 0;       
}
//-------------------------------------------------------------------------------------

