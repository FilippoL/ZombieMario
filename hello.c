//
//! \file hello_demo.c
//!   Screen-entry text demo
//! \date 160228 - 20080416
//! \author cearn
//
// === NOTES ===

#include <stdio.h>
#include <tonc.h>
#include <math.h>
#include <string.h>
#include "map1.h"
#include "map2.h"
#include "map3.h"
#include "map4.h"
#include "map5.h"
#include "map6.h"
#include "map7.h"
#include "map8.h"
#include "map9.h"
#include "map10.h"
#include "map11.h"
#include "map12.h"
#include "map13.h"
#include "map14.h"
#include "hello.h"
#include "mario.h"
#include "heart.h"
#include "marioCollision.h"
#include "whole_map.h"

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer;

void init();		//**************INITIALIZE
void input();		//**************HANDLE KEY INPUT
void obj_set();		//**************SETT ATTRIBUTES
void update();		//**************UPDATE STUFF
void Sprario();		//**************SPRITE FUNCTION
void display();		//**************DISPLAY STUFF
void makeEnemy();	//**************
void EvilMario();	//**************SPRITE FUNCTION
void liveinit();	//**************SPRITE FUNCTION
void displaylife();	//**************LIVES AND LIVES COUNTER
	
int gamestate=0;										
float p_posx=100, p_posy=110; //POSITION PLAYER O THE SCREEN
float p_gposx= 256, p_gposy= 200; //GLOBAL VISION OF PLAYER
int speed = 2;
int gravity;

int maxjump = 33;//****************TOP HIGH
int groundlvl = 110;//*************GROUND LEVEL

int background_x;//****************
int background_y;
int mapsize;//*********************MAP AND COLL MAP SIZE

int n;
int numb = 5;

int roof;

float axellerate=0;
float axellerate2=0.1;

#define NUMB_LIVES 6 
Live lives[NUMB_LIVES];

#define NUM_ENEMIES 1
Enemy enemies[NUM_ENEMIES];

///*********
int e; 
int l;


int point = 0;
char punteggio[100];

int minusthis = 1;
float x = 90;
float menuspeed = 1.5;

double h = 5;

int i;
float maxx = 110;
bool isjumping = false;
bool onground = true;
bool goingup ;
bool collision(int collx, int colly);//***COLLISION FUNC
bool iscolliding;//***********************^^RETURNS THI BOOL
bool checked;//****************************STATIC VAR
bool released = false;

bool plusone = false;
OBJ_ATTR *mariosprite= &obj_buffer[1];			//BUFFERING MARIO
u32 tid=0,pb=0;								//SETTING TILES ID AND PALLET-BANK


void init()
{
	background_x= p_gposx - p_posx;///**********************INITIALIZE BACKGROUND VARIABLE
	background_y= p_gposy - p_posy;//***************WE DOTN WANT THE HIDEN SPRITES TO APPEAR
	 
	 
	
	makeEnemy();
	
	for (l = 0; l < numb + 1; l++)
	{
	
	lives[l].missing = false;
	
	} lives[numb].missing = true;
	

	memcpy(&tile_mem[4][4],UntitledTiles,UntitledTilesLen);				//STORING IN VIDEO MEMORY
	memcpy(pal_obj_mem,UntitledPal,UntitledPalLen);
	
	
	memcpy(&tile_mem[4][0],marioTiles,marioTilesLen);				//STORING IN VIDEO MEMORY
	memcpy(pal_obj_mem,marioPal,marioPalLen);	

	obj_set_attr(mariosprite, 												//ATTRIBUTES OF CHARACTER
		ATTR0_SQUARE,			
		ATTR1_SIZE_16,				
		ATTR2_PALBANK(pb) | tid);	

	obj_set_pos(mariosprite,10, 10);				
	
}

int main()
{
	
	memcpy(&tile_mem[1][0],map1Tiles,map1TilesLen);							//STORING IN VIDEO MEMORY
	memcpy(pal_bg_mem,map1Pal,map1PalLen);          							//STORING IN VIDEO MEMORY
	
	REG_BG1CNT= BG_CBB(1) | BG_SBB(29) | BG_4BPP | BG_REG_64x32;	
	
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D;
	
	oam_init(obj_buffer,128);
	tte_init_se(0, BG_CBB(0)|BG_SBB(31),0,CLR_GREEN,14,NULL,NULL);
	

	tte_write("#{es}");											//CLEAR THE SCREEN

	init();
	
	

	
	for(;;)													//LOOP IT
	{
			vid_vsync();   
			input();
			update();
			display();
		
			displaylife();
		
			
			REG_BG1HOFS= background_x ;		 //SETTING BACKGROUND POSITION X
			REG_BG1VOFS= background_y ;			//SETTING BACKGROUND POSITION Y
		 
			obj_set();

	}
	return 0;
}

void displaylife()
{
	for (l = 0; l < numb; l++)
	{	
		if (lives[l].missing == false)
		{
			lives[l].heartsprite = &obj_buffer[15+l];
			lives[l].tid2 = 4;
			lives[l].pb2 = 0;
			lives[l].x = 10*l;
			lives[l].y = 0;
			
			
				obj_set_attr(lives[l].heartsprite, 												//ATTRIBUTES OF CHARACTER
			ATTR0_SQUARE,			
			ATTR1_SIZE_16,				
			ATTR2_PALBANK(lives[l].pb2) | lives[l].tid2);

			lives[l].x = lives[l].x + 20;	

			if (iscolliding == true && lives[l+1].missing == true)
						
						{obj_set_attr(lives[l].heartsprite, 
							ATTR0_SQUARE|ATTR0_HIDE,				// Square, regular sprite
							ATTR1_SIZE_16,					// 64x64p, 
							ATTR2_PALBANK(lives[l].pb2) | lives[l].tid2);
							lives[l].missing = true;
							l = numb; 
							}
			
		}
	}
	
	
}

void makeEnemy()
{

	 
	for (e = 0; e < NUM_ENEMIES; e++)
	
	{
		enemies[e].sprite = &obj_buffer[2];
		enemies[e].e_gx = enemies[e].ex - background_x;
		enemies[e].e_gy = enemies[e].ey - background_y;
		enemies[e].enemyspeed = 0.5;
		enemies[e].ex = 0; //+ 25*e;
		enemies[e].ey = p_posy + 16;
		enemies[e].e_gx = 256;// + 25*e;
		enemies[e].e_gy = p_gposy;
		enemies[e].max_x = 400;
		enemies[e].min_x = 50;
	
	
		enemies[e].tid1 = 0;
		enemies[e].pb1 = 2;
	
			
		obj_set_attr(enemies[e].sprite, 												//ATTRIBUTES OF CHARACTER
		ATTR0_SQUARE,			
		ATTR1_SIZE_16,				
		ATTR2_PALBANK(enemies[e].pb1) | enemies[e].tid1);	
	}
}




void moveEnemy()
{
	for (e = 0; e < NUM_ENEMIES; e++)
	{		
			if (point >= 1 && point < 3)
			{
			enemies[e].enemyspeed = 0.75;
			}
			if (point >= 3 && point <4)
			{
			enemies[e].enemyspeed = 1;
			}
			if (point >= 4 && point <6)
			{
			enemies[e].enemyspeed = 1.25;
			}
			
				
			if (enemies[e].ex > p_posx)
			{ enemies[e].ex -= enemies[e].enemyspeed;
			enemies[e].e_gx -= enemies[e].enemyspeed;}
			
			if (enemies[e].ex < p_posx)
			{ enemies[e].ex += enemies[e].enemyspeed;
			enemies[e].e_gx += enemies[e].enemyspeed;}
			
			if (enemies[e].ey > p_posy)
			{ enemies[e].ey -= enemies[e].enemyspeed;
			enemies[e].e_gy -= enemies[e].enemyspeed; }
			
			if (enemies[e].ey < p_posy)
			{ enemies[e].ey += enemies[e].enemyspeed;
			enemies[e].e_gy += enemies[e].enemyspeed;}

	
			
			
			
		
		
		if 	(p_posx  >= enemies[e].ex && p_posx  <= (enemies[e].ex + 16) && p_posy +16 >= enemies[e].ey)//&& p_posy < enemies[e].ey)// && p_posy >= enemies[e].ey && p_posy <= (enemies[e].ey + 16))
			{		
					iscolliding= true;
					
					for (int f = 0; f < 100; f++)
					{
						enemies[e].ex -=2;
					}
						
			}
			
		else	{iscolliding= false;}
			
			
			
				
		 if (enemies[e].ex +16 > p_posx && enemies[e].ex +16 < p_posx + 16 && enemies[e].ey -5 <= p_posy + 20 )//&& p_posy < enemies[e].ey + 16)
			{
				for (int f = 0; f < 100; f++)
						{
							enemies[e].ex -=2;
						}
				plusone = true;
			}
		else {plusone = false;}
			
	}

}

void input()
{
	if (gamestate == 0)
	{
		if (key_is_down(KEY_FULL))
			{
				gamestate = 1;
			}
	}
	
	if (gamestate == 1)
	{
		if (key_is_down(KEY_UP))
		{
			
			if (isjumping == false)
			{
				isjumping = true;
				goingup = true;
			}
		}
		
		if (key_is_up(KEY_UP))
		{
			
			if (isjumping == true)
			{
				isjumping = false;
				goingup = false;
			}
		}
		
		if (key_is_down(KEY_RIGHT) && !collision(p_gposx + 1, p_gposy)) 
		{
			
				
				p_gposx += 1;
				
		}
			
		
		if (key_is_down(KEY_LEFT) && !collision(p_gposx - 1, p_gposy))	
		{
				
				p_gposx -= 1;
				
				
		}

	}	
	
	if (gamestate == 2)
	{
		if (key_is_down(KEY_FULL))
			{
				gamestate = 0;
			}
	}
		
		
	
	if (gamestate == 3)
	{
		if (key_is_down(KEY_FULL))
			{
				gamestate = 0;
			}
	}
	
}


void update()
{
	//roof = 80;
	
	if (gamestate == 0 ||gamestate == 2 ||gamestate == 3)//*************************THIS SCREEN SCROLLING MENU IS ACTUALLY GOOD FOR CHECKING MAPS
	
	{
		p_gposx+=menuspeed;
		key_poll();
			
		if(p_gposx < 0)
		{menuspeed = -menuspeed;}
			
		if (p_gposx > 3268)
		{menuspeed = -menuspeed;}
	}


	


	 if (gamestate == 1)

	{   
	
		

		if (checked == false)
			{
				p_posx= 100, p_posy= 110; //100
				p_gposx=  256, p_gposy= 200; //180
				for (l = 0; l < numb + 1; l++)
					{
					
					lives[l].missing = false;
					
					} lives[numb].missing = true;
				
				point = 0;
				memset(punteggio, 0, sizeof(punteggio));
				
			}	
			
			
		if (p_posy + 16 > 150)
		{gamestate = 3;}
		
			
		if (plusone == true)
			{
				point +=1;
			}
			
			moveEnemy();
			
			
			key_poll();
			
			
		if (isjumping == true)
			{	
				if (goingup == true)
				{
						if (p_gposy > (groundlvl - maxjump) && !collision(p_gposx, p_gposy -3))
						{
							
								p_gposy -= 2;
								p_posy -= 2;
							
							
							
						}
						
						else {goingup = false; }
				}
				
				else {
						
						if (!collision(p_gposx, p_gposy +1))
						{
						
							p_gposy ++;
							p_posy ++;
							
						}
						
						else {isjumping = false ;}
					}
			}
			
			
			if (!collision(p_gposx, p_gposy +1))
			{
							p_gposy ++;
							p_posy ++;
							
			}
			
			if(p_gposx<128)
			{
				p_gposx=128;
			}
			
			if(p_gposx> 3264)
			{
				gamestate = 2;
			}
			
			if (lives[0].missing == true)
			{gamestate = 3;}
				
				

			
			checked = true;
			sprintf(punteggio, "%d" ,point);
			
	}
	
	
	
	
		
		background_x= p_gposx - p_posx;
		background_y= p_gposy - p_posy;
		
		
	
	
	

}

void display()
{
		if (gamestate == 0)
	{
		tte_set_pos(30, 15);
		tte_write("PRESS ANY KEY TO START");
		tte_set_pos(30, 40);
		tte_write("TRY TO HIT ZOMBIE MARIO");
		tte_set_pos(30, 60);
		tte_write(" FROM ABOVE AND TRY TO");
		tte_set_pos(30, 80);
		tte_write(" STAY ALIVE TILL THE END");
	}
	
	if (gamestate == 1) 
	
	{tte_write("#{es}");
	tte_set_pos(300, 10);
	tte_write("Scores: ");
	tte_set_pos(500, 20);
	tte_write(punteggio);
	
	}
	
	
	if (gamestate == 2)
	{
		tte_write("#{es}");
		tte_set_pos(50, 45);
		tte_write("YOU WON!!");
		p_posx = -16;
		p_posx = -16;
		checked = false;
		
	}
		
		
	
	if (gamestate == 3)
	{
		tte_write("#{es}");
		tte_set_pos(50, 45);
		tte_write("YOU LOST!!");
		p_posx = -16;
		p_posx = -16;
		checked = false;
	}
	
	
		if(p_gposx>0 && p_gposx<(256+p_posx))
		{
		memcpy(&se_mem[29][0],map1Map,map1MapLen);	//adding map1 to vmemory								
		memcpy(&se_mem[30][0],map2Map,map2MapLen); //adding map2 to vmemory
		}
		
		
		if(p_gposx>(256+p_posx)&& p_gposx<(512+p_posx))
		{
		memcpy(&se_mem[30][0],map2Map,map2MapLen);
		memcpy(&se_mem[29][0],map3Map,map3MapLen);
		}
		if(p_gposx>(512+p_posx) && p_gposx<(768+p_posx))
		{
		memcpy(&se_mem[29][0],map3Map,map3MapLen);
		memcpy(&se_mem[30][0],map4Map,map4MapLen);
		}
		if(p_gposx>(768+p_posx) && p_gposx<(1024+p_posx))
		{
		memcpy(&se_mem[30][0],map4Map,map4MapLen);
		memcpy(&se_mem[29][0],map5Map,map5MapLen);
		}
		if(p_gposx>(1024+p_posx) && p_gposx<(1280+p_posx))
		{
		memcpy(&se_mem[29][0],map5Map,map5MapLen);
		memcpy(&se_mem[30][0],map6Map,map6MapLen);
		}
		if(p_gposx>(1280+p_posx) && p_gposx<(1536+p_posx))
		{
		memcpy(&se_mem[30][0],map6Map,map6MapLen);
		memcpy(&se_mem[29][0],map7Map,map7MapLen);
		}
		if(p_gposx>(1536+p_posx) && p_gposx<(1792+p_posx))
		{
		memcpy(&se_mem[29][0],map7Map,map7MapLen);
		memcpy(&se_mem[30][0],map8Map,map8MapLen);
		}
		if(p_gposx>(1792+p_posx) && p_gposx<(2048+p_posx))
		{
		memcpy(&se_mem[30][0],map8Map,map8MapLen);
		memcpy(&se_mem[29][0],map9Map,map9MapLen);
		}
		if(p_gposx>(2048+p_posx) && p_gposx<(2304+p_posx))
		{
		memcpy(&se_mem[29][0],map9Map,map9MapLen);
		memcpy(&se_mem[30][0],map10Map,map10MapLen);
		}
		if(p_gposx>(2304+p_posx) && p_gposx<(2560+p_posx))
		{
		memcpy(&se_mem[30][0],map10Map,map10MapLen);
		memcpy(&se_mem[29][0],map11Map,map11MapLen);
		}
		if(p_gposx>(2560+p_posx) && p_gposx<(2816+p_posx))
		{
		memcpy(&se_mem[29][0],map11Map,map11MapLen);
		memcpy(&se_mem[30][0],map12Map,map12MapLen);
		}
		if(p_gposx>(2816+p_posx) && p_gposx<(3072+p_posx))
		{
		memcpy(&se_mem[30][0],map12Map,map12MapLen);
		memcpy(&se_mem[29][0],map13Map,map13MapLen);
		}
		if(p_gposx>(3072+p_posx) && (p_gposx+p_posx)<mapsize)
		{
		memcpy(&se_mem[29][0],map13Map,map13MapLen);
		memcpy(&se_mem[30][0],map1Map,map1MapLen);
		}
	

}


bool collision(int collx, int colly)
{
	int sprite_x,sprite_y;//**********************************************************NEED THESE FOR LOOPING 
		
	mapsize = 3584;//*********************************************************HOW LONG IS THE MAP
		
		
		for(sprite_x =0; sprite_x<16; sprite_x++)//*************************GENERATE A 16x16px CHECKER
		{
			for(sprite_y =0; sprite_y<16; sprite_y++)//*********************THAT WILL CHECK PX BY PX
			{
				if ((marioCollisionBitmap[sprite_x+sprite_y*16])&&//*********CHECK IT AGAINST SPRITE PX 
					(whole_mapBitmap[(sprite_x+collx)+ (sprite_y+colly)*mapsize]))//**AND COLLMAP
				{
					return true;
				}
			}
		}
		
	return false;
	
}


void obj_set()							//DISPLAY  OBJECTS 
{	if (gamestate == 1)
	{
		Sprario();
		EvilMario();
		liveinit();
		oam_copy(oam_mem,obj_buffer,128);
	}
}

void Sprario()						//SETTING CHARACTER 
{	
	obj_set_pos(mariosprite,p_posx,p_posy);
	
	mariosprite->attr2= ATTR2_BUILD(tid,pb,0); 			
	obj_set_pos(mariosprite,p_posx, p_posy);				
}

void liveinit()
{

	for (l = 0; l < numb; l++)
	{
		
		obj_set_pos(lives[l].heartsprite, lives[l].x, lives[l].y);
		
		lives[l].heartsprite->attr2= ATTR2_BUILD(lives[l].tid2,lives[l].pb2, 0); 			
		obj_set_pos(lives[l].heartsprite,lives[l].x,lives[l].y);
	}
}

void EvilMario()
{
	for (int e = 0; e < NUM_ENEMIES; e++)
	{
		//enemies[e].ex=0;
		obj_set_pos(enemies[e].sprite, enemies[e].ex, enemies[e].ey);
		
		enemies[e].sprite->attr2= ATTR2_BUILD(enemies[e].tid1,enemies[e].pb1, 0); 			
		obj_set_pos(enemies[e].sprite, enemies[e].ex, enemies[e].ey);
	}
}



