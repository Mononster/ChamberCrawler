#include "controller.h"
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

int main(int argc, char * argv[]){
	
	bool done = false;
	string filename ="";
	//printw(argv[1] );
	//printw(argc );
	if (argc == 2 ){
		filename = argv[1];
	}
	int winState = 0;
	initscr();
	noecho();
	nodelay(stdscr,false);
	keypad(stdscr,TRUE);
	while (!done){
		Controller c;
		clear();
		printw("\n");
		printw("================================================================================\n" );
		printw("Hello, welcome to ChamberCrawler!!\n" );
		printw("Your goal is to reach the final level of the game!\n" );
		printw("Collect as many gold as you can!\n" );
		printw("Now the game begins, please choose your race!\n" );
		printw("================================================================================\n" );
		printw("\n");
		printw("\n");
		printw("Name   :  HP Atk Def Skill\n"  );
		printw("Shade  : 125  25  25  None\n"  );
		printw("Drow   : 150  25  15  all potions have effect magnified by 1.5.\n"  );
		printw("Vamplre:  50  25  25  gains 5HP every ATTACK AND HAS NO MAX HP.\n"  );
		printw("Troll  : 120  25  15  regains 5HP every turn, max 120.\n"  );
		printw("Goblin : 110  15  20  steals 5 gold from every slain enemy.\n"  );
		printw("\n");
		printw("\n");
		printw("'s' for Shade\n" );
		printw("'d' for Drow\n" );
		printw("'t' for Troll\n" );
		printw("'v' for Vamplre\n" );
		printw("'g' for Goblin\n" );
		bool ifwin = c.play(filename,winState);
		if (!ifwin && winState == 1){
			continue;
		}
		nodelay(stdscr,false);
		//refresh();
		if (!ifwin){
			clear();
			printw("Sorry you lost!\n" );
			printw("If you want to run the game again, press 'r', press any other commands to end the program!\n" );		
		}
		int command;
		if (ifwin){
			printw("Do you want to play again? If so , press 'r'");
		}
		command = getch();
		if (command == 'r'){
			continue;
		}
		else{
			return endwin();
		}
	}
}
