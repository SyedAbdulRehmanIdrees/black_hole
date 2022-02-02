#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

const int gridSize = 5;
char objects[gridSize][gridSize] = {
    {'-', '#', '-', '-', '#'},
    {'#', '-', '-', '#', '-'},
    {'-', '-', '#', '-', '#'},
    {'#', '-', '-', '#', '-'},
    {'#', '#', '-', '#', '-'}
};
bool gravity = false;
bool blackHole = false;

void printBoard();
void setGravity(bool);
void setBlackHole(bool);
void tickTime(int);
void tickOnce();
void tickOnceBlackHole();

int main(){
    printBoard();
    setGravity(true);
    setBlackHole(true);

    while(true){
        system("clear");
        tickTime(1);
        printBoard();
        usleep(200000);
    }
}

void setGravity(bool val){
    gravity = val;
}

void setBlackHole(bool val){
    blackHole = val;
}

void tickTime(int times){
    if(!gravity) return;

    if(!blackHole){
        for(int i = 0; i < times; i++){
            tickOnce();
        }
    }
    else {
        for(int i = 0; i < times; i++){
            tickOnceBlackHole();
        }
    }
}

void tickOnce(){
    for(int x = gridSize - 1; x > 0; x--){
        for(int y = 0; y < gridSize; y++){
            if(objects[x][y] == '-' && objects[x - 1][y] == '#'){
                objects[x][y] = '#';
                objects[x - 1][y] = '-';
            }
        }
    }
}

void tickOnceBlackHole(){
    char tmp[gridSize] = {};

    int x = gridSize - 1;
    for(int y = 0; y < gridSize; y++){
        tmp[y] = objects[x][y];
    }

    for(int x = gridSize - 1; x > 0; x--){
        for(int y = 0; y < gridSize; y++){
            objects[x][y] = objects[x - 1][y];
        }
    }

    x = 0;
    for(int y = 0; y < gridSize; y++){
        objects[x][y] = tmp[y];
    }
}

void printBoard(){

    cout << "┌";
    for(int i = 0; i < gridSize - 1; i++){
        cout << "───┬";
    }

    cout << "───┐" << endl;
    for(int i = 0; i < gridSize; i++){
        cout << "│";
        for(int j = 0; j < gridSize; j++){
            cout << " " << objects[i][j] << " │";
        }
        cout << endl;


        if(i != gridSize - 1){
            cout << "├";
            for(int j = 0; j < gridSize - 1; j++){
                cout << "───┼";
            }
            cout << "───┤" << endl;
        }
    }

    cout << "└";
    for(int i = 0; i < gridSize - 1; i++){
        cout << "───┴";
    }

    cout << "───┘" << endl;
}