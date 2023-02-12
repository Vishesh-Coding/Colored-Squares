#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<stdio.h>
#include<math.h>

#define ScWidth 1400
#define ScHeight 700
#define OpWidth 400

using namespace std;

// Player Variables
double px, py, pa = 0;
int pSize = 20, pStep = 100, pcolor = LIGHTRED;

// Blocks Variables
int size = 250;
int x = 250;
int y = 100;
int x2 = x+size;
int y2 = y;
int x3 = x;
int y3 = y+size;
int x4 = x+size;
int y4 = y+size;
 
// Other Variables
int colors[4] = {LIGHTRED, LIGHTBLUE, LIGHTMAGENTA, LIGHTGREEN};
int timer = 0;
char option, txtScore[5];
int score = 0;	

static double d2r(double degree)
{
    double pi = 3.14159265359;
    return (degree * (pi / 180));
}
static double r2d(double radian)
{
    double pi = 3.14159265359;
    return (radian * 180 / pi);
}

// Draw Colored Blocks
void drawBoxes(){
	setcolor(LIGHTRED);
	setfillstyle(1,LIGHTRED);
	bar(x,y,x+size,y+size);
	
	setcolor(LIGHTBLUE);
	setfillstyle(1,LIGHTBLUE);
	bar(x2,y2,x2+size,y2+size);
	
	setcolor(LIGHTMAGENTA);
	setfillstyle(1,LIGHTMAGENTA);
	bar(x3,y3,x3+size,y3+size);
	
	setcolor(LIGHTGREEN);
	setfillstyle(1,LIGHTGREEN);
	bar(x4,y4,x4+size,y4+size);
}

// Function to check if player ball collides with any block
int playerCollision(){
	
	// Red Block Collision
	if( px >= x && px <= x+size ){
		if( py >= y && py <= y+size ){ 
			if( pcolor == colors[0] ) // if colors match
				return 1;
			else // if colors does not match
				return 0;
		}
	}
	
	// Blue Block Collision
	if( px >= x2 && px <= x2+size ){
		if( py >= y2 && py <= y2+size ){ 
			if( pcolor == colors[1] ) // if colors match
				return 1;
			else // if colors does not match
				return 0;
		}
	}
	
	// Magenta Block Collision
	if( px >= x3 && px <= x3+size ){
		if( py >= y3 && py <= y3+size ){ 
			if( pcolor == colors[2] ) // if colors match
				return 1;
			else // if colors does not match
				return 0;
		}
	}
	
	// Green Block Collision
	if( px >= x4 && px <= x4+size ){
		if( py >= y4 && py <= y4+size ){ 
			if( pcolor == colors[3] ) // if colors match
				return 1;
			else // if colors does not match
				return 0;
		}
	}
	return 0;	
}

void GameOver(){
	cleardevice(); // clear screen
	
	setcolor(WHITE);
	// Print Game Over Text
	settextstyle(4,0,9);
	outtextxy(300,300,"Game Over");

	settextstyle(4,0,2);
	outtextxy(500,420,"Press any key to restart...");
	getch();
	score = 0; // reset score
} 

int main(){
	// for making sure random number generation
	srand((unsigned) time(0));
	
	int gd = DETECT, gm, err, tmp;
	initgraph( & gd, & gm, "C:\\tc\\bgi");
 
	int i=0;
	py = i; // initial ball position
	timer = 250; // for changing ball color
	while(1){
		
		
		setcolor(WHITE);
		//draw board
		rectangle(0,0,ScWidth-OpWidth,ScHeight);
		rectangle(ScWidth-OpWidth,0,ScWidth,ScHeight);
		
		// print score
		// itoa function converts number to character array
		settextstyle(4,0,9);
		if( score<10 )
			outtextxy(ScWidth-270, 250, itoa(score,txtScore,10));
		else if( score>=10 )
			outtextxy(ScWidth-320, 250, itoa(score,txtScore,10));
		
		settextstyle(4,0,1);
		outtextxy(ScWidth-375, 500, "Controls: "); 
		outtextxy(ScWidth-300, 550, "Spacebar"); 
		
		// drawing colored boxes
		drawBoxes();
		
		setcolor(WHITE); 
		circle(500, 350, 100); // draw white outline
		
		if( kbhit()){
			option = getch();
			if(option == 32){
				
				if( playerCollision() == 1 ){ // if player hit right block
					score++;
				}else{ // if player hit wrong block
					GameOver();
				}
				
			}
		}
		// for circular ball movement 
		px = -1*sin(d2r(i))*90;
		py = -1*cos(d2r(i))*90; 
		
		// Drawing player
		setcolor(WHITE);
		setfillstyle(1, pcolor);
		px += 500;
		py += 350;
		fillellipse(px, py, pSize, pSize);
		
		i+=10; // incrementing angle for ball movement
		if( i > 360) // if angle > 360 then reset angle to 0
			i = 0;
		
		if( i == timer ){ // if angle reaches timer time
			pcolor = colors[rand()%4]; // choose random color for ball
			timer = 10 * (15 + rand()%20); // generate new random time
		}
		
		delay(50);
		cleardevice();
	}
	
	getch();
	closegraph();
}
