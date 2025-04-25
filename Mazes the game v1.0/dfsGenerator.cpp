#pragma once
#include "operators.cpp"

void dfs(Coords node, Coords wayOut, std::vector<std::vector<bool>> &used, std::vector<std::vector<Cell>> &maze) {
    if(node == wayOut) {
        used[wayOut.y][wayOut.x] = true;
        return;
    }

    used[node.y][node.x] = true;

    std::vector<int> waysInds = {0, 1, 2, 3};
    std::random_shuffle(waysInds.begin(), waysInds.end());

    for(int ind : waysInds) {
        Coords neighbour;
        if(ind == 0) {
            neighbour = node + UP;
        } else if(ind == 1) {
            neighbour = node + DOWN;
        } else if(ind == 2) {
            neighbour = node + LEFT;
        } else {
            neighbour = node + RIGHT;
        }

        if(neighbour.x < 0 || neighbour.x >= static_cast<int>(used[0].size()) || neighbour.y < 0 || neighbour.y >= static_cast<int>(used.size()) || used[neighbour.y][neighbour.x]) {
            continue;
        }

        MakeRoomBetween(GetMazeCoords(node), GetMazeCoords(neighbour), maze);

        dfs(neighbour, wayOut, used, maze);
    }

    return;
}

std::vector<std::vector<Cell>> GenerateMazeByDfs(const int mazeHeight, const int mazeWidth) {
    int graphHeight = (mazeHeight - 1) / 2;
    int graphWidth = (mazeWidth - 1) / 2;

    std::vector<std::vector<Cell>> maze(mazeHeight, std::vector<Cell> (mazeWidth));

    for(int i = 1; i < mazeHeight - 1; i += 2) {
        for(int j = 1; j < mazeWidth - 1; j += 2) {
            maze[i][j].MakeThisRoom();
        }
    }

    std::vector<std::vector<bool>> used(graphHeight, std::vector<bool>(graphWidth, false));
    dfs(Coords(0, 0), Coords(graphWidth - 1, graphHeight - 1), used, maze);

    return maze;
}