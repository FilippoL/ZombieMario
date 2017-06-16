
#include <stdio.h>
#include <tonc.h>
#include <string.h>

typedef struct {

	float ex;
	float ey;
	float e_gx;
	float e_gy;
	int start_x;
	int start_y;
	int max_x;
	int max_y;
	int min_x;
	int min_y;
	int respawn_count;
	
	
	float enemyspeed;
	
	OBJ_ATTR * sprite;
	
	u32 tid1;
	u32 pb1;
	
	bool enemy_dead;
	bool enemy_faceright;
	bool respawning;

} Enemy;

typedef struct {

	int x;
	int y;

	bool missing;
	
	
	OBJ_ATTR * heartsprite;
	
	u32 tid2;
	u32 pb2;

} Live;