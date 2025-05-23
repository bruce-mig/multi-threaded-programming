/*
 * =====================================================================================
 *
 *       Filename:  network_utils.h
 *
 *    Description: This file is an interface for Network Utils
 *
 *        Version:  1.0
 *        Created:  20/04/2025 22:03:57 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BRUCE MIGERI (), bmigeri@gmail.com
 *
 *
 * =====================================================================================
 */

#ifndef __NETWORK_UTILS__
#define __NETWORK_UTILS__

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <memory.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_PACKET_BUFFER_SIZE 1024

typedef void (*recv_fn_cb)(char *,    /* msg recvd */
                           uint32_t,  /* recvd msg size */
                           char *,    /* Sender's IP address */
                           uint32_t); /* Sender's Port number */

pthread_t *udp_server_create_and_start(char *ip_addr, uint32_t udp_port_no,
                                       recv_fn_cb recv_fn);

int send_udp_msg(char *dest_ip_addr, uint32_t udp_port_no, char *msg,
                 uint32_t msg_size);

/* General Nw utilities */
char *network_covert_ip_n_to_p(uint32_t ip_addr, char *output_buffer);

uint32_t network_covert_ip_p_to_n(char *ip_addr);

#endif /* __NETWORK_UTILS__  */
