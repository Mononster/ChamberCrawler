/****************** ChamberCrawler3000 ****************  
    Purpose : Final project of CS246, first rpg game in life coding by C++.
    		  Basically, this is a simple vision of roguelike game. More features 
    		  are provided in th DLC vision of CC3K.	
    Returns : 1; if the game ends successfully. 
    Erros   : This program can deal with invalid inputs, if the user tries to break the program
     		  i.e kept entering garbage values, the behaviour of the program is underdetermined.
******************************************************/  

#include "controller.h"
#include <cstdlib>

using namespace std;

int main(int argc, char * argv[]){
	srand(time(NULL));
	bool done = false;
	string filename ="";
	if (argc == 2 ){
		filename = argv[1];
	}
	int winState = 0; // record if user wants to quit or restart the game.
	while (!done){
		Controller c;
		system("clear");
		cout<<endl;
		cout<<"                 ******     *****   *******      **     ** " << endl;
		cout<<"               *****      *****          **      **   **   " << endl;
    	cout<<"              ****       ****            **      ** **     " << endl;
   		cout<<"             ****       ****        *******      ***       " << endl;
     	cout<<"              ****       ****            **      ** **     " << endl;
      	cout<<"               *****      *****          **      **   **   " << endl;
       	cout<<"                 *****      *****   *******      **     ** " << endl;
       	cout<< endl;
		cout << "================================================================================" << endl;
		cout << "|                       Hello, welcome to ChamberCrawler!!                     |" << endl;
		cout << "|               Your goal is to reach the final level of the game!             |" << endl;
		cout << "|                       Collect as many gold as you can!                       |" << endl;
		cout << "|                   Now the game begins, please choose your race!              |" << endl;
		cout << "================================================================================" << endl;
		cout << "                                      CS246 Final Project University of Waterloo" << endl;
		cout << "                                               Publish Date : December 4th, 2015" << endl;
		cout << "                                                       Designed by : Kaiyue Deng" << endl;
		cout << "                                                                     Marvin Zhan" << endl;
		cout << '\n' << '\n' << '\n' ;
		cout << "Name   :  HP Atk Def Skill"  << endl;
		cout << "Shade  : 125  25  25  None"  << endl;
		cout << "Drow   : 150  25  15  all potions have effect magnified by 1.5."  << endl;
		cout << "Vamplre:  50  25  25  gains 5HP every ATTACK AND HAS NO MAX HP."  << endl;
		cout << "Troll  : 120  25  15  regains 5HP every turn, max 120."  << endl;
		cout << "Goblin : 110  15  20  steals 5 gold from every slain enemy."  << endl;
		cout << '\n' << '\n';
		cout << "'s' for Shade" << endl;
		cout << "'d' for Drow" << endl;
		cout << "'t' for Troll" << endl;
		cout << "'v' for Vamplre" << endl;
		cout << "'g' for Goblin" << endl;
		cout << "Which race do you want to choose?           command == ";
		bool ifwin = c.play(filename,winState);
		if (!ifwin && winState == 1){ // if winState = 1, it shows player wants to restart the game.
			winState = 0;
			continue;
		}
		char command;
		if (!ifwin){
			cout << "Sorry you lost!" << endl;
			cout << "If you want to run the game again, press 'r', press any other commands to end the program!" << endl;	
			cin >> command;
			if (command == 'r'){
				continue;
			}
		}
		if (ifwin){
			cin >> command;
			if (command == 'q'){
				return 1;
			}else{
				continue;
			}
		}	
		else{
			return 1;
		}
	}
}
