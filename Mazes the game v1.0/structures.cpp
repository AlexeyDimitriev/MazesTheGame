#include <iostream>

struct Cell {
    bool type = true; //0 -- room, 1 -- wall

    explicit Cell() : type(true) {};
    explicit Cell(bool isWall) : type(isWall) {};

    void MakeThisRoom() {
        type = 0;
        return;
    };

    void MakeThisWall() {
        type = 1;
        return;
    };
};

struct Coords {
    int x;
    int y;

    explicit Coords() : x(0), y(0) {};
    explicit Coords(int X, int Y) : x(X), y(Y) {};

    bool operator == (const Coords& c2) {
        return (x == c2.x) && (y == c2.y);
    };

    bool operator != (const Coords& c2) {
        return (x != c2.x) || (y != c2.y);
    };

    Coords operator + (const Coords& c2) {
        return Coords(x + c2.x, y + c2.y);
    }

    void Print() {
        std::cout << '(' << x << ", " << y << ')';
        return;
    };
};

struct Edge {
    Coords from;
    Coords to;

    explicit Edge() : from(Coords(0, 0)), to(Coords(0, 0)) {};
    explicit Edge(Coords From, Coords To) : from(From), to(To) {};

    void Print() {
        std::cout << '{';
        from.Print();
        std::cout << ", ";
        to.Print();
        std::cout << '}';
        return;
    };
};