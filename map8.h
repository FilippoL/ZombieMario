
//{{BLOCK(map8)

//======================================================================
//
//	map8, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 37 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 1184 + 2048 = 3744
//
//	Time-stamp: 2016-04-28, 16:54:37
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MAP8_H
#define GRIT_MAP8_H

#define map8TilesLen 1184
extern const unsigned short map8Tiles[592];

#define map8MapLen 2048
extern const unsigned short map8Map[1024];

#define map8PalLen 512
extern const unsigned short map8Pal[256];

#endif // GRIT_MAP8_H

//}}BLOCK(map8)
