#include <iostream>
#include <vector>
#include <windows.h>
#include "gameplay.cpp"

int menuPos = 0;
int chooseRegimePos = 0;
int chooseAlgoPos = 0;

int menuSize = 2;
std::vector<std::string> menuAsset = {
    "New game",
    "Exit game"
};

int chooseRegimeSize = 3;
std::vector<std::string> chooseRegimeAsset = {
    "Basic mode",
    "Dark maze",
    "Back"
};

int chooseAlgoSize = 3;
std::vector<std::string> chooseAlgoAsset = {
    "Kruskal algorithm",
    "Dfs algorithm",
    "Back"
};

void InChooseAlgoMenu(int regime) {
    Sleep(250);
    bool inChooseAlgoMenu = true;
    while(inChooseAlgoMenu) {
        std::system("cls");
        for(int i = 0; i < chooseAlgoSize; ++i) {
            std::cout << chooseAlgoAsset[i];
            if(i == chooseAlgoPos) {
                std::cout << " <";
            }
            std::cout << '\n';
        }

        if(GetAsyncKeyState(87) && 0x8000 && chooseAlgoPos > 0) {
            chooseAlgoPos--;
        } else if(GetAsyncKeyState(83) && 0x8000 && chooseAlgoPos < chooseAlgoSize - 1) {
            chooseAlgoPos++;
        } else if(GetAsyncKeyState(69) && 0x8000) {
            if(chooseAlgoPos == 0) {
                InGame(regime, 0);
            } else if(chooseAlgoPos == 1) {
                InGame(regime, 1);
            }
            inChooseAlgoMenu = false;
        }
        Sleep(250);
    }
}

void InChooseRegimeMenu() {
    Sleep(250);
    bool inChooseRegimeMenu = true;
    while(inChooseRegimeMenu) {
        std::system("cls");
        for(int i = 0; i < chooseRegimeSize; ++i) {
            std::cout << chooseRegimeAsset[i];
            if(i == chooseRegimePos) {
                std::cout << " <";
            }
            std::cout << '\n';
        }

        if(GetAsyncKeyState(87) && 0x8000 && chooseRegimePos > 0) {
            chooseRegimePos--;
        } else if(GetAsyncKeyState(83) && 0x8000 && chooseRegimePos < chooseRegimeSize - 1) {
            chooseRegimePos++;
        } else if(GetAsyncKeyState(69) && 0x8000) {
            if(chooseRegimePos == 0) {
                chooseAlgoPos = 0;
                InChooseAlgoMenu(0);
            } else if(chooseRegimePos == 1) {
                chooseAlgoPos = 0;
                InChooseAlgoMenu(1);
            }
            inChooseRegimeMenu = false;
        }
        Sleep(250);
    }
}

void InMenu() {
    Sleep(250);
    bool inMenu = true;
    while(inMenu) {
        std::system("cls");
        for(int i = 0; i < menuSize; ++i) {
            std::cout << menuAsset[i];
            if(i == menuPos) {
                std::cout << " <";
            }
            std::cout << '\n';
        }

        if(GetAsyncKeyState(87) && 0x8000 && menuPos > 0) {
            menuPos--;
        } else if(GetAsyncKeyState(83) && 0x8000 && menuPos < menuSize - 1) {
            menuPos++;
        } else if(GetAsyncKeyState(69) && 0x8000) {
            if(menuPos == 0) {
                chooseRegimePos = 0;
                InChooseRegimeMenu();
                menuPos = 0;
            } else if(menuPos == 1) {
                inMenu = false;
            }
        }
        Sleep(250);
    }
}