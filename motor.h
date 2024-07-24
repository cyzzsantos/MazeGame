//
// Created by nuno on 26/10/23.
//

#ifndef SO_MOTOR_H
#define SO_MOTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/prctl.h>
#include <wait.h>

#define MAX_USERS 5
#define MAX_BOTS 10
#define MAX_BOULDERS 50
#define NUM_LEVELS 3
#define MAX_MOVINBBLOCKS 5
#define HEIGHT 16
#define WIDTH 40
#define INSCRICAO "60"
#define NPLAYERS "2"
#define DURACAO "60"
#define DECREMENTO "10"
#define SIZE 100
#define SINGLE_INSTANCE_LOCK "./tmp/sil.lock"

struct Jogador {
    int id;
    int x;
    int y;
    int score;
    char nome[];
};

int getInscricao();
int getNplayers();
int getDuracao();
int getDecremento();
int argumentsCounter(char command[]);
int executeCommand(char command[]);
void error(char errorMessage[]);
void map();
void users();
void kick(char command[]);
void bots();
void bmov();
void rbm();
void begin();
void end();
void testbot(char command[]);
void sendMessage(char command[]);

#endif //SO_MOTOR_H
