/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** init_client
*/

#include "client.h"

client_t *init_client(char *ip_addr, int port)
{
    client_t *client = malloc(sizeof(client_t));

    client->ip_addr = ip_addr;
    client->port = port;

    // init client addr
    client->addr.sin_family = AF_INET;
    client->addr.sin_addr.s_addr = htonl(ip_addr);
    client->addr.sin_port = htons(port);

    return client;
}
