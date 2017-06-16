
//{{BLOCK(map2)

//======================================================================
//
//	map2, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 37 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 1184 + 2048 = 3744
//
//	Time-stamp: 2016-03-16, 20:31:08
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MAP2_H
#define GRIT_MAP2_H

#define map2TilesLen 1184
extern const unsigned short map2Tiles[592];

#define map2MapLen 2048
extern const unsigned short map2Map[1024];

#define map2PalLen 512
extern const unsigned short map2Pal[256];

#endif // GRIT_MAP2_H

//}}BLOCK(map2)
