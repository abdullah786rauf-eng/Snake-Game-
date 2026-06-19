#include<iostream>
#include<vector>
using namespace std;

string grid [16] [16];

void displayMainMenu();
void displayScore();
int takeInput();
void displayGrid();
int spawnFood();
int increaseScore();
void displaySnake();

void displayGrid(){//agr time hua, is me borders add kr dein ge
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < 16; j++){
			grid [i][j] = ".";
		}
	}
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < 16; j++){
			cout << grid [i][j] << " ";
		}
	cout << endl;
	}
}

void displaySnake(){
	
	vector<int> snakeBody;
	snakeBody.push_back(0);	
	grid[0][1] = snakeBody[0];
	
}

int main(){
	displaySnake();
	displayGrid();
}
