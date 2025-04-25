#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "operators.cpp"

Coords FindLeader(Coords nodeCoords, std::vector<std::vector<Coords>> &leader) {
    std::vector<Coords> path;
    while(nodeCoords != leader[nodeCoords.y][nodeCoords.x]) {
        path.push_back(nodeCoords);
        nodeCoords = leader[nodeCoords.y][nodeCoords.x];
    }

    for(auto child : path) {
        leader[child.y][child.x] = nodeCoords;
    }

    return nodeCoords;
}

void UniteTrees(Coords node1Coords, Coords node2Coords, std::vector<std::vector<Coords>> &leader, std::vector<std::vector<int>> &depth) {
    node1Coords = FindLeader(node1Coords, leader);
    node2Coords = FindLeader(node2Coords, leader);
    if(depth[node1Coords.y][node1Coords.x] > depth[node2Coords.y][node2Coords.x]) {
        SwapCoords(node1Coords, node2Coords);
    }

    if(depth[node1Coords.y][node1Coords.x] == depth[node2Coords.y][node2Coords.x]) {
        depth[node2Coords.y][node2Coords.x] += 1;
    }
    leader[node1Coords.y][node1Coords.x] = node2Coords;

    return;
}

std::vector<std::vector<Cell>> GenerateMazeByKruskalAlgo(const int mazeHeight, const int mazeWidth) {
    int graphHeight = (mazeHeight - 1) / 2;
    int graphWidth = (mazeWidth - 1) / 2;

    std::vector<std::vector<Cell>> maze(mazeHeight, std::vector<Cell> (mazeWidth));
    std::vector<Edge> edges;
    std::vector<std::vector<Coords>> leader(graphHeight, std::vector<Coords>(graphWidth));
    std::vector<std::vector<int>> depth(graphHeight, std::vector<int>(graphWidth, 1));

    for(int i = 1; i < mazeHeight - 1; i += 2) {
        for(int j = 1; j < mazeWidth - 1; j += 2) {
            maze[i][j].MakeThisRoom();
        }
    }

    for(int i = 1; i < mazeHeight; i += 2) {
        for(int j = 1; j < mazeWidth; j += 2) {
            if(i + 2 < mazeHeight) {
                edges.push_back(Edge(GetGraphCoords(Coords(j, i)), GetGraphCoords(Coords(j, i + 2))));
            }
            if(j + 2 < mazeWidth) {
                edges.push_back(Edge(GetGraphCoords(Coords(j, i)), GetGraphCoords(Coords(j + 2, i))));
            }
        }
    }

    std::random_shuffle(edges.begin(), edges.end());

    for(int i = 0; i < graphHeight; ++i) {
        for(int j = 0; j < graphWidth; ++j) {
            leader[i][j] = Coords(j, i);
        }
    }

    for(auto curEdge : edges) {
        if(FindLeader(curEdge.from, leader) != FindLeader(curEdge.to, leader)) {
            UniteTrees(curEdge.from, curEdge.to, leader, depth);
            MakeRoomBetween(GetMazeCoords(curEdge.from), GetMazeCoords(curEdge.to), maze);
        }
    }

    return maze;
}