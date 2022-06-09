/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** run_client
*/

#include "client.h"

static char **my_malloc_words(char const *str, char **table, char c)
{
    int i = 0;
    int nb_words = 0;

    while (str[i] == c)
        i++;
    while (str[i]) {
        i++;
        if (str[i] == c || str[i] == '\0') {
            nb_words++;
            while (str[i] == c)
                i++;
        }
    }
    table = malloc(sizeof(char*) * (nb_words + 1));
    table[nb_words] = 0;
    return (table);
}

static char **my_malloc_words_letter(char const *str, char **table, char c)
{
    int i = 0;
    int x = 0;
    int nb_wrd_let = 1;

    while (str[i] == c)
        i++;
    while (str[i]) {
        i++;
        if (str[i] == c || str[i] == '\0') {
            table[x] = malloc(sizeof(char) * (nb_wrd_let + 1));
            x++;
            nb_wrd_let = 0;
            while (str[i] == c)
                i++;
        }
        nb_wrd_let++;
    }
    return (table);
}

static char **my_concat_string(char const *str, char **table, char c)
{
    int i = 0;
    int x = 0;
    int y = 0;

    while (str[i] == c)
        i++;
    while (str[i]) {
        table[x][y] = str[i];
        y++;
        i++;
        if (str[i] == c || str[i] == '\0') {
            table[x][y] = '\0';
            x++;
            y = 0;
            while (str[i] == c)
                i++;
        }
    }
    return (table);
}

char **my_strsplit(char const *s, char c)
{
    char **table = NULL;

    if (s && c) {
        table = my_malloc_words(s, table, c);
        table = my_malloc_words_letter(s, table, c);
        table = my_concat_string(s, table, c);
    }
    return (table);
}

void send_msg(int fd)
{
    char buffer[256];

    bzero(buffer, sizeof(buffer));
    read(0, buffer, sizeof(buffer));
    send(fd, buffer, sizeof(buffer), 0);
}

void receive_msg(int fd)
{
    char buffer[256];
    char **args;

    bzero(buffer, sizeof(buffer));
    recv(fd, &buffer, sizeof(buffer), 0);
    args = my_strsplit(buffer, ' ');
    
}

void run_client(client_t *client)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in localaddr;
    fd_set fds;

    connect(sockfd, (struct sockaddr*)&client->addr, sizeof(client->addr));
    while (1) {
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        FD_SET(sockfd, &fds);
        select(sockfd + 1, &fds, NULL, NULL, NULL);
        if (FD_ISSET(STDIN_FILENO, &fds))
            send_msg(sockfd);
        else if (FD_ISSET(sockfd, &fds))
            receive_msg(sockfd);
    }
    close(sockfd);
    return;
}