#include<iostream>
#include<vector>
#include<conio.h>
#include<thread>
#include<chrono>
#include<random>
#include<iomanip>

using namespace std;

int snakeX = 1;
int snakeY = 1;
int snakePrevX;
int snakePrevY;
bool alive = 1;
char head = '0';
int speed = 110;

vector<char> body(1, 'o');
vector<int> bodyX = {0};
vector<int> bodyY = {1};

string grid[16][16];

char input;
char direction = 'd';

int foodX = 8;
int foodY = 8;

char inputFunc();
void restart();

void displayMainMenu(){
    cout << "Press Any Key to Start" << endl;
    cout << "Press 1 to Exit:" << endl;
}

void moveBody(){
    for(int i = bodyX.size() - 1; i > 0; i--){
        bodyX[i] = bodyX[i - 1];
        bodyY[i] = bodyY[i - 1];
    }

    bodyX[0] = snakePrevX;
    bodyY[0] = snakePrevY;
}

void displayGrid(){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){

            if(i == snakeY && j == snakeX)
                cout << head << " ";

            else if(i == foodY && j == foodX)
                cout << "* ";

            else{
                int k;

                for(k = 0; k < bodyX.size(); k++){
                    if(i == bodyY[k] && j == bodyX[k]){
                        cout << body[k] << " ";
                        break;
                    }
                }

                if(k == bodyX.size())
                    cout << grid[i][j] << ". ";
            }
        }
        cout << endl;
    }
}

int startGame(){

    system("cls");

    while(alive == 1){

        // food spawning
        
	        
        if(snakeY == foodY && snakeX == foodX){
	        bool onBody = true;
			while (onBody) {
	        	
		        srand(time(0));
		        foodX = rand() % 16;
		        foodY = rand() % 16;
				bool broken = false;
		        for(int z = 0; z < bodyY.size(); z++){
		        	if(bodyX[z] == foodX && bodyY[z] == foodY){
		        		broken = true;
		        		break;
					}
				}
				if (!broken) {
					onBody = false;	
				}
			}
	        
	        // size increase
			body.push_back('o');
			bodyX.push_back(bodyX.back());
			bodyY.push_back(bodyY.back());
			if(body.size() < 17){
				speed -= 5;
			}
			
			
		}
        // movement
        if(_kbhit()){

            char input = _getch();

            snakePrevX = snakeX;
            snakePrevY = snakeY;

            switch(input){

                case 'w':
                	if(direction != 'd'){
	                    snakeY--;
	                    direction = 'u';
	                    moveBody();
					}
                    break;

                case 'a':
                	if(direction != 'r'){
	                    snakeX--;
	                    direction = 'l';
	                    moveBody();
					}
                    break;

                case 's':
                	if(direction != 'u'){
	                    snakeY++;
	                    direction = 'd';
	                    moveBody();
					}
                    break;

                case 'd':
                	if(direction != 'l'){
	                    snakeX++;
	                    direction = 'r';
	                    moveBody();
					}
                    break;
            }
        }
        else{

            snakePrevX = snakeX;
            snakePrevY = snakeY;

            switch(direction){

                case 'u':
                	if(direction != 'd')
                    snakeY--;
                    break;

                case 'l':
                	if(direction != 'r')
                    snakeX--;
                    break;

                case 'd':
                	if(direction != 'u')
                    snakeY++;
                    break;

                case 'r':
                	if(direction != 'l')
                    snakeX++;
                    break;
            }

            moveBody();
        }

        // checks
        if(snakeX < 0 || snakeX > 15 || snakeY < 0 || snakeY > 15){
            alive = 0;
        }
        for(int z = 0; z < bodyY.size(); z++){
	        if(bodyX[z] == snakeX && bodyY[z] == snakeY){
	        		alive = 0;
			}
		}
		cout << setw(18) << "Score: " << body.size() << endl;
        displayGrid();

        this_thread::sleep_for(chrono::milliseconds(speed));
        system("cls");
    }
    
    // ending screen
	
    cout << "\tGame Over :(" << endl;
    cout << "\tFinal Score: " << body.size() << endl;
    cout << "\tEnter R to Restart" << endl;
	cout << "\tEnter E to Quit: ";
	this_thread::sleep_for(chrono::milliseconds(1000));
    restart();
    
}
void restart(){
	char restartChoice = 'f';
    while(restartChoice != 'e' && restartChoice != 'r'){
    	 restartChoice = _getch();
		if(restartChoice == 'r'){
	    	alive = 1;
	    	snakeX = 1;
			snakeY = 1;
			speed = 110;
			body.clear();
			bodyX.clear();
			bodyY.clear();
			vector<char> body = {'o'};
			vector<int> bodyX = {0};
			vector<int> bodyY = {1};
			direction = 'd';
			foodX = 8;
			foodY = 8;
	
			startGame();
			break;
		}
		else if(restartChoice == 'e'){
			break;
		}
	}
}

int main(){

    cout << setw(18) << "Snake" << endl << endl;

    displayMainMenu();

    char choice = _getch();

    if(choice != '1'){
        startGame();
    }
    else{
        return 0;
    }
}
