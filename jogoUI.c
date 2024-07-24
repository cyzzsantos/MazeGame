//
// Created by nuno on 26/10/23.
//

#include "jogoUI.h"

void exitRequest() {

}

void spectator() {

}

void players() {

}

bool login(char username[]) {
    return true;
}

void sendMessage(char command[], struct Windows mapas) {
    char* target;
    char* message;
    char tmp[SIZE];

    strcpy(tmp, command);
    target = strtok(tmp, " ");
    target = strtok(NULL, " ");

    strcpy(tmp, command);
    message = strtok(tmp, " ");
    message = strtok(NULL, " ");
    message = strtok(NULL, " ");

    wprintw(mapas.middleWindow, "Message sent to %s\n", target);
}

int argumentsCounter(char command[]) {
    int count = 0;
    char* token;
    char tmp[SIZE];

    strcpy(tmp, command);

    token = strtok(tmp, " ");
    while(token != NULL) {
        count++;
        token = strtok(NULL, " ");
    }

    return count - 1;
}

int executeCommand(char command[], struct Windows mapas) {
    char commandName[SIZE];
    int numArgs = argumentsCounter(command);

    strcpy(commandName, command);
    strtok(commandName, " ");

    if(strcmp(commandName, "players") == 0) {
        if(numArgs != 0) {
            wprintw(mapas.middleWindow, "Invalid arguments for command 'players'\nCorrenct syntax: 'players'\n");
            return 1;
        }
        players();
        return 1;
    }

    if(strcmp(commandName, "msg") == 0) {
        if(numArgs != 2) {
            wprintw(mapas.middleWindow, "Invalid arguments for command 'msg'\nCorrect syntax: 'msg <target> <message>\n");
            return 1;
        }
        sendMessage(command, mapas);
        return 1;
    }

    if(strcmp(commandName, "exit") == 0) {
        if(numArgs != 0) {
            mvwprintw(mapas.middleWindow, 2, 1, "Invalid arguments for command 'exit'\nCorrect syntax: 'exit'\n");
            return 1;
        }
        exitRequest();
        return 0;
    }

    if (strcmp(commandName, "help") == 0) {
        wprintw(mapas.middleWindow, "Available commands: players, msg, exit\n");
        return 1;
    }

    wprintw(mapas.middleWindow, "Unknown command: %s\n", commandName);
    return 1;
}

void drawMap(WINDOW* window) {
    keypad(window, TRUE);
    wclear(window);
    wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');

    refresh();
    wrefresh(window);
}

void endWindows(struct Windows mapas) {
    wclear(mapas.topWindow);
    wrefresh(mapas.topWindow);
    delwin(mapas.topWindow);
    wclear(mapas.middleWindow);
    wrefresh(mapas.middleWindow);
    delwin(mapas.middleWindow);
    wclear(mapas.bottomWindow);
    wrefresh(mapas.bottomWindow);
    delwin(mapas.bottomWindow);
    endwin();
}

int main(int argc, char* argv[]) {
    char command[SIZE];
    struct Windows mapas;
    struct Jogador jogador;

    initscr();
    echo();
    attrset(A_DIM);

    WINDOW *janelaTopo = newwin(HEIGHT, WIDTH, 3, 1);
    WINDOW *janelaMeio = newwin(3, 82, HEIGHT + 4, 1);
    WINDOW *janelaBaixo = newwin(3, 82, HEIGHT + 8, 1);

    mapas.topWindow = janelaTopo;
    mapas.middleWindow = janelaMeio;
    mapas.bottomWindow = janelaBaixo;

    drawMap(mapas.topWindow);

    if(argc != 2)
    {
        wprintw(mapas.middleWindow, "Invalid authentication\nSyntax: ./jogoUI <username>\n");
        endWindows(mapas);
        return 0;
    }
    else {
        strcpy(jogador.nome, argv[1]);
        wprintw(mapas.middleWindow, "Welcome %s\n", jogador.nome);
    }

    if(!login(argv[1]))
    {
        spectator();
        return 0;
    }

    while(1) {
        /*printf(">> ");
        fgets(command, SIZE, stdin);
        command[strlen(command) - 1] = '\0';*/

        wprintw(mapas.bottomWindow, ">> ");
        wgetstr(mapas.bottomWindow, command);
        wclear(mapas.middleWindow);
        wclear(mapas.bottomWindow);

        if(!executeCommand(command, mapas))
            break;

        refresh();
        wrefresh(mapas.bottomWindow);
        wrefresh(mapas.middleWindow);
        wrefresh(mapas.topWindow);
    }

    endWindows(mapas);

    return 0;
}
