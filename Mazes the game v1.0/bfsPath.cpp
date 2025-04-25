#include <queue>
#include "operators.cpp"

std::vector<Coords> GetPath(Coords &player, Coords &wayOut, std::vector<std::vector<Cell>> &maze) {
    int mazeHeight = maze.size();
    int mazeWidth = maze[0].size();
    std::vector<std::vector<bool>> visited(mazeHeight, std::vector<bool>(mazeWidth, false));
    std::vector<std::vector<Coords>> parent(mazeHeight, std::vector<Coords>(mazeWidth, Coords(-1, -1)));
    std::queue<Coords> que;

    que.push(player);
    visited[player.y][player.x] = true;
    parent[player.y][player.x] = player;
    while(!que.empty()) {
        Coords node = que.front();
        que.pop();
        if(!maze[node.y + UP.y][node.x + UP.x].type && !visited[node.y + UP.y][node.x + UP.x]) {
            visited[node.y + UP.y][node.x + UP.x] = true;
            parent[node.y + UP.y][node.x + UP.x] = node;
            que.push(node + UP);
        }
        if(!maze[node.y + DOWN.y][node.x + DOWN.x].type && !visited[node.y + DOWN.y][node.x + DOWN.x]) {
            visited[node.y + DOWN.y][node.x + DOWN.x] = true;
            parent[node.y + DOWN.y][node.x + DOWN.x] = node;
            que.push(node + DOWN);
        }
        if(!maze[node.y + LEFT.y][node.x + LEFT.x].type && !visited[node.y + LEFT.y][node.x + LEFT.x]) {
            visited[node.y + LEFT.y][node.x + LEFT.x] = true;
            parent[node.y + LEFT.y][node.x + LEFT.x] = node;
            que.push(node + LEFT);
        }
        if(!maze[node.y + RIGHT.y][node.x + RIGHT.x].type && !visited[node.y + RIGHT.y][node.x + RIGHT.x]) {
            visited[node.y + RIGHT.y][node.x + RIGHT.x] = true;
            parent[node.y + RIGHT.y][node.x + RIGHT.x] = node;
            que.push(node + RIGHT);
        }
    }

    std::vector<Coords> path;
    Coords node = wayOut;
    while(node != player) {
        path.push_back(node);
        node = parent[node.y][node.x];
    }
    path.push_back(player);
    path = ReverseVector(path);
    return path;
}