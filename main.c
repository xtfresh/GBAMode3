#include "parkour.h"


typedef unsigned short u16;
#define MODE3 3
#define BG2_ENABLE (1<<10)
#define REG_DISPCNT *(u16*) 0x4000000
#define RGB(r,g,b) ( (r) | (g)<<5) | (b<<10)
#define OFFSET(r,c,nc) ((r)*(nc)+(c))
u16 *videoBuffer = (u16*) 0x6000000;



void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);

int main(){
	REG_DISPCNT = MODE3 | BG2_ENABLE;
	int i = 0;
	for(int r = 0; r<PARKOUR_HEIGHT; r++){
		for(int c = 0; c < PARKOUR_WIDTH; c++){
		     	setPixel(r,c,parkour[i]);
			i++;
		}    	
	}

	
	while(1);
	return 0;
}

void setPixel(int r, int c, u16 color){
	               
	videoBuffer[OFFSET(r,c,240)] = color;
}
 
void drawRect(int r, int c, int width, int height, u16 color){
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			setPixel(j+r,i+c,color);	
		}	
	}
} 

void drawHollowRect(int r, int c, int width, int height, u16 color){
	for(int i = r; i < height+r; i++){
		setPixel(i,c,color);
		setPixel(i, c+width-1, color);
	}
	for(int i = c; i < width+c; i++){
		setPixel(r,i,color);
		setPixel(r+height-1, i, color);
			
	}

}





