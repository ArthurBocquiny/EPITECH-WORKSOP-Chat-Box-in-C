/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** init_server
*/

#include "server.h"

server_t *init_server(char *ip_addr, int port)
{
    server_t *server = malloc(sizeof(server_t));

    server->ip_addr = ip_addr;
    server->port = port;

    // init socket
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    // init server addr
    server->addr.sin_family = AF_INET;
    server->addr.sin_addr.s_addr = htonl(ip_addr);
    server->addr.sin_port = htons(port);
    // bind
    bind(server->socket, (struct sockaddr*)&server->addr, sizeof(server->addr));
    // listen
    if (listen(server->socket, SOMAXCONN) == -1)
        exit(84);
    return server;
}