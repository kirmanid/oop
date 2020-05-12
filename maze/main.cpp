#include "maze.h"

// I could not find a good cross-platform way to capture console keypresses, so I'm using std::getchar() and WASD. Please tell me if you want it changed.
// on the upside, you can input strings of moverments, like "wwsadas"

int main(){
    Maze m (200,50,true);
    m.generateMaze(0, 20);
    m.displayMaze();
    while (true){
        m.makeUserMove();
        m.displayMaze();
        std::cout << "\n\n";
    }
}