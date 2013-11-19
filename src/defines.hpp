#ifndef DEFINES_HPP
#define DEFINES_HPP

#define WINDOWTITLE			"Imblockible"
#define LEVELSDIR			"levels/"

// Dimensions
#define WINDOWWIDTH			1280.f
#define WINDOWHEIGHT		600.f
#define VIEWWIDTH			800.f
#define VIEWHEIGHT			600.f

// Scenery
#define FOREGROUNDMARGIN	((WINDOWWIDTH - VIEWWIDTH) / 2)
#define FOREGROUNDPADDING	150.f
#define FLOORSIZE 			3.f

// Cube
#define CUBESIZE 			50.f
#define CUBEPOSITIONX		(3*CUBESIZE)

// Physics
#define SPEED 				650.f
#define JUMPDIST			(6.f * CUBESIZE)
#define JUMPTIME 			(JUMPDIST / SPEED)
#define JUMPHEIGHT 			(2.f * CUBESIZE)
#define PADOFFSET			(0.2f * CUBESIZE)
#define SPHERESKIN			(-0.1f*CUBESIZE)

#endif // DEFINES_HPP
