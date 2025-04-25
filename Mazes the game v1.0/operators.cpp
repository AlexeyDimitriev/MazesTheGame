#pragma once
#include <vector>
#include <algorithm>
#include "structures.cpp"

const Coords UP(0, -1);
const Coords DOWN(0, 1);
const Coords LEFT(-1, 0);
const Coords RIGHT(1, 0);

void SwapCoords(Coords &c1, Coords &c2) {
    Coords c3(c1.x, c1.y);

    c1.x = c2.x;
    c1.y = c2.y;

    c2.x = c3.x;
    c2.y = c3.y;

    return;
}

Coords GetMazeCoords(Coords crds) {
    return Coords(2 * crds.x + 1, 2 * crds.y + 1);
}

Coords GetGraphCoords(Coords crds) {
    return Coords((crds.x - 1) / 2, (crds.y - 1) / 2);
}

void printMaze(std::vector<std::vector<Cell>> maze, Coords player, Coords wayOut) {
    int mazeHeight = maze.size(), mazeWidth = maze[0].size();
    for(int i = 0; i < mazeHeight; ++i) {
        for(int j = 0; j < mazeWidth; ++j) {
            if(i == player.y && j == player.x && !(i == wayOut.y && j == wayOut.x)) {
                std::cout << '*';
            } else if(i == wayOut.y && j == wayOut.x) {
                std::cout << '0';
            } else if(maze[i][j].type == false) {
                std::cout << ' ';
            } else {
                std::cout << '#';
            }
        }
        std::cout << '\n';
    }

    return;
}

void printDarkMaze(std::vector<std::vector<Cell>> maze, Coords player, Coords wayOut) {
    int mazeHeight = maze.size(), mazeWidth = maze[0].size();
    for(int i = 0; i < mazeHeight; ++i) {
        for(int j = 0; j < mazeWidth; ++j) {
            bool isVisible = std::abs(i - player.y) + std::abs(j - player.x) < 3;
            if(i == player.y && j == player.x && !(i == wayOut.y && j == wayOut.x)) {
                std::cout << '*';
            } else if(i == wayOut.y && j == wayOut.x && isVisible) {
                std::cout << '0';
            } else if(maze[i][j].type == false && isVisible) {
                std::cout << ' ';
            } else if(maze[i][j].type == true && isVisible) {
                std::cout << '#';
            } else {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    return;
}

void MakeRoomBetween(Coords room1Coords, Coords room2Coords, std::vector<std::vector<Cell>> &maze) {
    maze[(room1Coords.y + room2Coords.y) / 2][(room1Coords.x + room2Coords.x) / 2].MakeThisRoom();
    return;
}

std::vector<Coords> ReverseVector(std::vector<Coords> v) {
    std::reverse(v.begin(), v.end());
    return v;
}