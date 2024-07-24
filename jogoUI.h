//
// Created by nuno on 26/10/23.
//

#ifndef SO_JOGOUI_H
#define SO_JOGOUI_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>

#define HEIGHT 16
#define WIDTH 40
#define SIZE 100

struct Windows {
    WINDOW* topWindow;
    WINDOW* middleWindow;
    WINDOW* bottomWindow;
};

struct Jogador {
    int id;
    int x;
    int y;
    int score;
    char nome[];
};

bool login(char username[]);
void spectator();
void players();
void sendMessage(char command[], struct Windows mapas);
void exitRequest();
void moveUp();
void moveDown();
void moveLeft();
void moveRight();
void drawMap(WINDOW* window);

int executeCommand(char command[], struct Windows mapas);

#endif //SO_JOGOUI_H
