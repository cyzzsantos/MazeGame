//
// Created by nuno on 26/10/23.
//

#include "motor.h"

void error(char errorMessage[]) {
    printf("[ERROR] %s\n", errorMessage);
}

int getInscricao() {
    if(getenv("INSCRICAO") == NULL) {
        setenv("INSCRICAO", INSCRICAO, 1);
        return atoi(INSCRICAO);
    }

    return (int) strtol(getenv("INSCRICAO"), NULL, 10);;
}

int getNplayers() {
    if(getenv("NPLAYERS") == NULL) {
        setenv("NPLAYERS", NPLAYERS, 1);
        return atoi(NPLAYERS);
    }

    return (int) strtol(getenv("NPLAYERS"), NULL, 10);;
}

int getDuracao() {
    if(getenv("DURACAO") == NULL) {
        setenv("DURACAO", DURACAO, 1);
        return atoi(DURACAO);
    }

    return (int) strtol(getenv("DURACAO"), NULL, 10);;
}

int getDecremento() {
    if(getenv("DECREMENTO") == NULL) {
        setenv("DECREMENTO", DECREMENTO, 1);
        return atoi(DECREMENTO);
    }

    return (int) strtol(getenv("DECREMENTO"), NULL, 10);;
}

void map() {
    FILE *fp;
    char ch;
    fp = fopen("map.txt", "r");
    if (fp == NULL) {
        error("Could not open map.txt");
        return;
    }
    while ((ch = fgetc(fp)) != EOF)
        printf("%c", ch);
    fclose(fp);
    printf("\n\n");
}

void users() {

}

void kick(char command[]) {
    // TODO
}

void bots() {

}

void bmov() {

}

void rbm() {

}

void begin() {

}

void end() {
    printf("Ending motor and bots...\n");
    pid_t parent_pid = getpgid(getpid());
    kill(-parent_pid, SIGINT);
    error("Failed to end motor and bots");
}

void testbot(char command[]) {

    char* interval;
    char* duration;
    char tmp[SIZE];
    char buf[SIZE];
    int filedes[2];
    pid_t pid;

    strcpy(tmp, command);
    interval = strtok(tmp, " ");
    interval = strtok(NULL, " ");

    strcpy(tmp, command);
    duration = strtok(tmp, " ");
    duration = strtok(NULL, " ");
    duration = strtok(NULL, " ");

    if(pipe(filedes) == -1) {
        error("Could not create pipe");
        return;
    }

    pid = fork();
    if(pid == -1) {
        error("Could not fork");
        return;
    }

    if(pid == 0) {
        while(dup2(filedes[1], STDOUT_FILENO) == -1 && errno == EINTR) {}
        close(filedes[0]);
        close(filedes[1]);
        execl("./bot", "./bot", interval, duration, NULL);
        error("Could not execute bot");
        exit(1);
    }
    close(filedes[1]);

    while(1) {
        memset(buf, 0, sizeof(buf));
        ssize_t bytes = read(filedes[0], buf, sizeof(bytes));
        if(bytes == -1 && errno == EINTR)
            continue;

        if(bytes == -1) {
            error("Could not read from pipe");
            return;
        }

        if(bytes == 0)
            break;

        printf("RECEBI: %s", buf);
    }
    close(filedes[0]);
    wait(0);
}

void sendMessage(char command[]) {
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

    printf("Message sent to %s\n", target);
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

int executeCommand(char command[]) {
    char commandName[SIZE];
    int numArgs = argumentsCounter(command);
    int pipe;

    strcpy(commandName, command);
    strtok(commandName, " ");

    if(strcmp(commandName, "users") == 0) {
        if(numArgs != 0) {
            printf("Invalid arguments for command 'users'\nCorrenct syntax: 'users'\n");
            return 1;
        }
        users();
        return 1;
    }

    if(strcmp(commandName, "kick") == 0) {
        if(numArgs != 1) {
            printf("Invalid arguments for command 'kick'\nCorrenct syntax: 'kick <username>'\n");
            return 1;
        }
        kick(command);
        return 1;
    }

    if(strcmp(commandName, "bots") == 0) {
        if(numArgs != 0) {
            printf("Invalid arguments for command 'bots'\nCorrenct syntax: 'bots'\n");
            return 1;
        }
        bots();
        return 1;
    }

    if(strcmp(commandName, "bmov") == 0) {
        if(numArgs != 0) {
            printf("Invalid arguments for command 'bmov'\nCorrenct syntax: 'bmov'\n");
            return 1;
        }
        bmov();
        return 1;
    }

    if(strcmp(commandName, "rbm") == 0) {
        if(numArgs != 0) {
            printf("Invalid arguments for command 'rbm'\nCorrenct syntax: 'rbm'\n");
            return 1;
        }
        rbm();
        return 1;
    }

    if(strcmp(commandName, "begin") == 0) {
        if(numArgs != 0) {
            printf("Invalid arguments for command 'begin'\nCorrenct syntax: 'begin'\n");
            return 1;
        }
        begin();
        return 1;
    }

    if(strcmp(commandName, "end") == 0) {
        if(numArgs != 0) {
            printf("Invalid arguments for command 'end'\nCorrenct syntax: 'end'\n");
            return 1;
        }
        end();
        exit(0); // temp
        return 1;
    }

    if(strcmp(commandName, "message") == 0) {
        if(numArgs != 2) {
            printf("Invalid arguments for command 'message'\nCorrect syntax: 'message <target> <message>'\n");
            return 1;
        }
        sendMessage(command);
        return 1;
    }

    if(strcmp(commandName, "test_bot") == 0) {
        if(numArgs != 2) {
            printf("Invalid arguments for command 'test_bot'\nCorrect syntax: 'test_bot <interval> <duration>\n");
            return 1;
        }

        pipe = fork();
        if(pipe == 0) {
            testbot(command);
        }
        return 1;
    }

    if (strcmp(commandName, "help") == 0) {
        printf("Available commands: users, kick, bots, bmov, rbm, begin, end, message, test_bot\n");
        return 1;
    }

    printf("Unknown command: %s\n", commandName);
    return 1;
}

int main(int argc, char* argv[]) {
    int inscricao = getInscricao();
    int nplayers = getNplayers();
    int duracao = getDuracao();
    int decremento = getDecremento();

    int lockfile = open(SINGLE_INSTANCE_LOCK, O_CREAT | O_RDWR, 0666);
    char command[SIZE];

    if(lockfile == -1)
    {
        error("Could not create or open lock file");
        return 1;
    }
    if(flock(lockfile, LOCK_EX | LOCK_NB) == -1)
    {
        error("Another instance is already running");
        close(lockfile);
        return 1;
    }

    map();

    while(1) {
        printf(">> ");
        fgets(command, SIZE, stdin);
        command[strlen(command) - 1] = '\0';

        executeCommand(command);
    }

    flock(lockfile, LOCK_UN);
    close(lockfile);

    return 0;
}