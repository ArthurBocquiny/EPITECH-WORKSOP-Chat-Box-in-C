/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** run_server
*/

#include "server.h"

#define MAX_CLIENT 10

void send_message(char *msg, int fd)
{
    char buffer[256];
    int i = 0;

    bzero(buffer, sizeof(buffer));
    while (msg[i]) {
        buffer[i] = msg[i];
        i++;
    }
    buffer[i] = '\0';
    send(fd, &buffer, strlen(buffer), 0);
}

void accept_request(socklen_t len, struct sockaddr_in localaddr, int fd, int **client_socket)
{
    int accept_fd = 0;

    len = sizeof(localaddr);
    if ((accept_fd = accept(fd, (struct sockaddr *)&localaddr, &len)) < 0) {
        puts("error\n");
        exit(84);
    }
    for (int i = 0; i < MAX_CLIENT; i++) {
        if ((*client_socket)[i] == 0) {
            (*client_socket)[i] = accept_fd;
            break;
        }
    }
}

void run_server(server_t *server)
{
    socklen_t len = 0;
    fd_set rset;
    int *client_socket = malloc(sizeof(int) * (MAX_CLIENT + 1));
    int max_sd = 0;
    int sd;
    int check;
    char recv_buf[256];
    cli *info_client = malloc(sizeof(cli) * (MAX_CLIENT));

    len = sizeof(server->addr);
    for (int i = 0; i < MAX_CLIENT; i++)
        client_socket[i] = 0;
    while (1) {
        FD_ZERO(&rset);

        FD_SET(server->socket, &rset);
        max_sd = server->socket;
        for (int i = 0; i < MAX_CLIENT; i++) {
            sd = client_socket[i];

            if (sd > 0)
                FD_SET(sd, &rset);
            if (sd > max_sd)
                max_sd = sd;
        }
        select(max_sd + 1, &rset, NULL, NULL, NULL);
        if (FD_ISSET(server->socket, &rset))
            accept_request(len, server->addr, server->socket, &client_socket);
        for (int i = 0; i < MAX_CLIENT; i++) {
            sd = client_socket[i];

            if (FD_ISSET(sd, &rset)) {
                if ((check = recv(sd, &recv_buf, sizeof(recv_buf), 0)) == 0) {
                    close(sd);
                    client_socket[i] = 0;
                } else {
                    recv_buf[check] = '\0';
                    puts(recv_buf);
                }
                bzero(recv_buf, sizeof(recv_buf));
            }
        }
    }
    close(server->socket);
    return;
}
