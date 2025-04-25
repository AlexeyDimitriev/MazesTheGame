#include <windows.h>
#include <time.h>
#include "operators.cpp"
#include "kruskalGenerator.cpp"
#include "dfsGenerator.cpp"
#include "bfsPath.cpp"

void AutoWalkthrough(Coords &player, Coords &wayOut, std::vector<std::vector<Cell>> &maze, int regime) {
    std::vector<Coords> path = GetPath(player, wayOut, maze);
    int pathLen = path.size();
    for(int i = 0; i < pathLen; ++i) {
        std::system("cls");
        player = path[i];
        if(regime == 0) {
            printMaze(maze, player, wayOut);
        } else if(regime == 1) {
            printDarkMaze(maze, player, wayOut);
        }
        Sleep(400);
    }

    return;
}

int PlayerMove(Coords &player, std::vector<std::vector<Cell>> &maze) {
    while(true) {
        if(GetAsyncKeyState(87) && 0x8000 && !maze[player.y + UP.y][player.x + UP.x].type) {
            player = player + UP;
            break;
        } else if(GetAsyncKeyState(83) && 0x8000 && !maze[player.y + DOWN.y][player.x + DOWN.x].type) {
            player = player + DOWN;
            break;
        } else if(GetAsyncKeyState(65) && 0x8000 && !maze[player.y + LEFT.y][player.x + LEFT.x].type) {
            player = player + LEFT;
            break;
        } else if(GetAsyncKeyState(68) && 0x8000 && !maze[player.y + RIGHT.y][player.x + RIGHT.x].type) {
            player = player + RIGHT;
            break;
        } else if(GetAsyncKeyState(79) && 0x8000) {
            return 1;
        } else if(GetAsyncKeyState(80) && 0x8000) {
            return 2;
        }
    }
    
    Sleep(250);
    return 0;
}

void InGame(int regime, int generateCode) {
    bool inGame = true;
    bool win = false;
    int mazeHeight, mazeWidth;
    time_t startTime, endTime; 
    Coords player(1, 1);

    bool inputting = true;
    while(inputting) {
        std::system("cls");
        std::cout << "Please, enter width and height of maze: ";
        
        if(!(std::cin >> mazeHeight >> mazeWidth)) {
            std::cout << "Something went wrong.";
            Sleep(1000);
            inGame = false;
            inputting = false;
            continue;
        }

        if(mazeHeight % 2 == 0 || mazeWidth % 2 == 0) {
            std::cout << "Width and height of maze should be odd numbers.";
            Sleep(1000);
            continue;
        }

        if(mazeHeight < 5 || mazeWidth < 5) {
            std::cout << "Width and height of maze should be more or equal than 5.";
            Sleep(1000);
            continue;
        }

        inputting = false;
    }

    if(inGame == false) {
        return;
    }

    Coords wayOut(mazeWidth - 2, mazeHeight - 2);
    std::vector<std::vector<Cell>> maze;
    if(generateCode == 0) {
        maze = GenerateMazeByKruskalAlgo(mazeHeight, mazeWidth);
    } else if(generateCode == 1) {
        maze = GenerateMazeByDfs(mazeHeight, mazeWidth);
    }

    time(&startTime);
    while(inGame) {
        Sleep(250);
        std::system("cls");

        if(regime == 0) {
            printMaze(maze, player, wayOut);
        } else if(regime == 1) {
            printDarkMaze(maze, player, wayOut);
        }
        
        int moveInd = PlayerMove(player, maze);

        if(moveInd == 1) {
            inGame = false;
            break;
        } else if(moveInd == 2) {
            AutoWalkthrough(player, wayOut, maze, regime);
            inGame = false;
            break;
        }

        if(player == wayOut) {
            inGame = false;
            win = true;
        }
    }

    if(win) {
        std::system("cls");
        std::cout << "You win!\n";
        time(&endTime);
        std::cout << "\nTotal time: " << (int)(endTime - startTime) << " seconds.\n";
        Sleep(1000);
    }

    return;
}