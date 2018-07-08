#include "gba.h"
#include "screenmode.h"
#include "KEYPAD.h"
#include "GFX.h"
#include "main_char.h" //header file created by pcx2gba


u16* paletteMem = (u16*)0x5000000;	//PalMemory is 256 16 bit BGR values starting at 0x5000000
u16* videoBuffer;
void drawPlayer(int tankx, int tanky, int direction);	// draws the tank on the screen


int main(void)
{
	SetMode(MODE_4 | BG2_ENABLE ); //set mode 4

	EraseScreen();
	int player_x, player_y;
	player_x = 100;
	player_y = 100;
	int x;
	while(1) {
		volatile unsigned char *ioram = (unsigned char *)0x04000000;
		ioram[0] = 0x03; // Use video mode 3 (in BG2, a 16bpp bitmap in VRAM)
		ioram[1] = 0x04; // Enable BG2 (BG0 = 1, BG1 = 2, BG2 = 4, ...)
		// set the palette
		for(x = 0; x < 256; x++)
			paletteMem[x] = man_palette[x];	//loop through and store the palette from your pict 
										//palette into video palette mem 

		drawPlayer(player_x, player_y, 0);
		

		

		// Wait forever
		while(1);
	}
	return 0;
}


void drawPlayer(int px, int py, int dir) {
	int x, y;
	// draw the tank
	for(y = 0; y < player_height; y++)
		for (x = 0; x < (player_width/2); x++)
			PlotPixelTransparent(x+px, y+py, playerData[y*(player_width/2)+x]);
}