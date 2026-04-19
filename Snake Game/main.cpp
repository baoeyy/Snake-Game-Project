#include <iostream>
#include <vector>
#include <conio.h> // For _kbhit() and _getch()
#include <windows.h> // For Sleep()
using namespace std;

// Global Variables (To be managed by the Architect)
bool gameOver;
const int width = 67;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

// Tail Data (For the Growth Specialist - Week 8 Arrays/Vectors)
vector<int> tailX, tailY; //xy values for snake tail
int nTail = 0;

// XY Coords
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    // UI Designer: Implement the nested loops to draw the map, snake, and fruit
    system("cls"); // Clears the console

    // Example: Top Wall
    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }
    cout << endl;

    // Logic for middle rows, snake head ('O'), and tail ('o') goes here...
    for (int i = 0; i < height ; i++) {
        for (int j = 0; j <= width ; j++) {
            // walls
            if (j == 0 || j == width) {
                cout << "#";
            }
            //snake head
            if (i == y && j == x) {
                cout << "\033[32m" << "O" << "\033[0m";
            }
            //apple
            else if (i == fruitY && j == fruitX) {
                cout << "\033[31m" << "a" << "\033[0m";
            }
            //snake tail
            else {
                bool tail = false;
                for (int k = 1; k < nTail; k++) {
                    if (tailX[k] == j
                        && tailY[k] == i) {
                        cout << "\033[32m" << "o" << "\033[0m";
                        tail = true;
                        }
                }
                //whitespace
                if (!tail)
                    cout << " ";
            }
        }
        cout << endl;
    }

    //bottom walls
    for (int i = 0; i < width +2; i++) {
        cout << "#";
    }
    cout << endl;

    //score count
    cout << "Score: " << score << endl;
}

void Input() {
    // Physics Lead: Handle key presses (W, A, S, D)
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
            case 'x': gameOver = true; break;
        }
    }
}

void Logic() {
    // Architect & Growth Specialist:
    // 1. Update tail positions (shifting coordinates in the vector)
    if (nTail == 0) {
        nTail = nTail + 1;
    }
    tailX.push_back(x);
    tailY.push_back(y);
    tailX.at(0) = x;
    tailY.at(0) = y;
    int tailPosX1 = tailX.at(0);
    int tailPosY1 = tailY.at(0);
    int tailPosX2, tailPosY2;
    tailX.resize(nTail+1);
    tailY.resize(nTail+1);

    for (int i = 1; i < nTail; i++) {
        tailPosX2 = tailX.at(i);
        tailPosY2 = tailY.at(i);
        tailX.at(i) = tailPosX1;
        tailY.at(i) = tailPosY1;
        tailPosX1 = tailPosX2;
        tailPosY1 = tailPosY2;
    }

    // 2. Update head position based on 'dir'
    switch (dir) {
        case LEFT:
            x = x - 1;
            break;
        case RIGHT:
            x = x + 1;
            break;
        case UP:
            y = y - 1;
            break;
        case DOWN:
            y = y + 1;
            break;
    }

    // 3. Check for collisions (Wall or Self)
    //wall
    if ((x >= width || x < 0) || (y >= height || y < 0)) {
        gameOver = true;
    }
    //self
    for (int i = 1; i < nTail; i++) {
        if (tailX.at(i) == x && tailY.at(i) == y) {
            gameOver = true;
        }
    }

    // 4. Check if fruit is eaten (if x == fruitX && y == fruitY)
    if (x == fruitX && y == fruitY) {
        score = score + 1;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail = nTail + 1;
    }

}

//Aloysius Cabral, MSCI-271
int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // Controls game speed
    }
    return 0;
}