
//{{BLOCK(map1)

//======================================================================
//
//	map1, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 37 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 1184 + 2048 = 3744
//
//	Time-stamp: 2016-03-16, 20:30:33
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MAP1_H
#define GRIT_MAP1_H

#define map1TilesLen 1184
extern const unsigned short map1Tiles[592];

#define map1MapLen 2048
extern const unsigned short map1Map[1024];

#define map1PalLen 512
extern const unsigned short map1Pal[256];

#endif // GRIT_MAP1_H

//}}BLOCK(map1)
