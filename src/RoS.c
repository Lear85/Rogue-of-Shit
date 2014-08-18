#include <ncurses.h>

//Global variables

int coords[2][2];
/*
Your current and previous position in the world

Add an additional dimension after adding "levels".
	Separated areas will be treated as cross sections of a large 3-dimensional structure.

The first dimension indicates whether the coordinates referred to are current or previous.
	This is used for tracking movement, and updating the screen in locations that you are in.
	0 is previous, 1 is current.

The second dimension is your y and x coordinates on the current area, both current and previous. See above.

The third dimension (not yet implemented) indicates which level you are on.
	To save memory, levels will become unloaded after new levels have been loaded.
	When first implemented, up to 8 levels will remain loaded at a time.
*/

void drawPlayer(){
	mvprintw(coords[0][0],coords[0][1]," ");
	mvprintw(coords[1][0],coords[1][1],"@");
	move(coords[1][0],coords[1][1]);
	//Update for custom tiles

	coords[0][0]=coords[1][0];
	coords[0][1]=coords[1][1]; //Updates previous coordinates

	refresh();
}

void drawRoom(char vert, char horz, char corner1, char corner2, char corner3, char corner4){

	int inc=0;
	int square=15;

	for(inc=0;inc<=square;inc++)
		mvprintw(0,inc,"%c",horz);
	for(inc=0;inc<=square;inc++)
		mvprintw(square,inc,"%c",horz);

	for(inc=0;inc<=square;inc++)
		mvprintw(inc,0,"%c",vert);
	for(inc=0;inc<=square;inc++)
		mvprintw(inc,square,"%c",vert);

	/*
	Corner layout:
	1  2

	3  4
	*/
	mvprintw(0,0,"%c",corner1);
	mvprintw(0,square,"%c",corner2);
	mvprintw(square,0,"%c",corner3);
	mvprintw(square,square,"%c",corner4);

	refresh();
}

char movePlayer(){
	/*
	LIMITATIONS
		SEVERE
			Only works in a preset square room. Implement proper walls and fix this.
			No timeout.
		MODERATE
			Does not support movement between levels. Not important yet.
		MINOR
			Does not support diagonal movement.

		Move this to a TODO list.
	*/

	char direction = getch();
	if(direction=='w'&&coords[1][0]>1){
		coords[1][0]--;
		mvprintw(17,0,"                 ");
	}
	else if(direction=='a'&&coords[1][1]>1){
		coords[1][1]--;
		mvprintw(17,0,"                 ");
	}
	else if(direction=='s'&&coords[1][0]<14){
		coords[1][0]++;
		mvprintw(17,0,"                 ");
	}
	else if(direction=='d'&&coords[1][1]<14){
		coords[1][1]++;
		mvprintw(17,0,"                 ");
	}
	else if(direction=='w'||direction=='a'||direction=='s'||direction=='d')
		mvprintw(17,0,"It's a wall...");

	drawPlayer();
	return(direction);
}

int main(){

	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();

	drawRoom('|','=','/','\\','\\','/');
	mvprintw(17,0,"Press Q to exit.");
	mvprintw(19,0,"WASD to move.");

	//Place the player In the box's corner.
	coords[0][0] = 1;
	coords[0][1] = 1;
	coords[1][0] = 1;
	coords[1][1] = 1;
	drawPlayer();

	char player;
	char first=1;
	while(player!='q'){
		player = movePlayer();
		if(first){
			mvprintw(19,0,"             ");
			first=0;
		}
	}
	mvprintw(coords[1][0],coords[1][1]," ");
	mvprintw(17,0,"End of program.");
	mvprintw(18,0,"Press the any key to exit.");
	getch();
	endwin();
}
