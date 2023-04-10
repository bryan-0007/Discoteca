#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <stdarg.h> // biblioteca para ter numa função, número indeterminado de parâmetros do mesmo tipo; Exemplo: function(char var, ...)
#include <semaphore.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/sem.h>


// Sockets --------------------------------------------------------------------------------
#define SOCKET_NAME "/tmp/DemoSocket"
#define BUFFER_SIZE 128 // tamanho maximo que a buffer pode transportar
//---------------------------------------------------------------------
#define FILENAME_SIZE 2048
#define MAX_LINE 100

#define MAX_LENGTH 1000
#define MAX_SIZE 100
#define SHM_KEY 0x1234

pthread_mutex_t mutex;

//--------------------------------------------------------------

//-------------------------------------------Como o cliente é constituido--------------------------------

//------------------------------------------------------------------------------------------ // funcao com o objetivo de retirar apenas parte do que queremos de uma string que esta dentro de um array

//--------------------------------------------------------------O que cada evento faz ------------------------
//evento 1 -> flag 
//evento 9 -> quando a thread acaba sai da discoteca
//evento 10 -> quando o tempo acaba a thread saiem
//evento 2 -> quando a thread entra na fila da zona A 
//evento 3 -> quando a thread entra na zona A 
//evento 4 -> quando a thread sai da zona A 
//evento 5 -> quando a thread entra na fila da zona B 
//evento 6 -> quando a thread entra na zona B
//evento 7 -> quando a thread sai da zona B 
//evento 8 ->quando a thread desiste de estar na fila zona A
//evento 11 -> quando a thread desiste de estar na fila zona B 
//evento 12 -> evento que nao consegue entrar na Zona B porque nao é VIP
//evento 13 -> quando a thread entra na fila da zona C
//evento 14 -> quando a thread entra na zona C
//evento 15 -> quando a thread sai da zona C
//evento 16 -> quando a thread entra na fila da zona D
//evento 17 -> quando a thread desiste de estar na fila zona D
//evento 18 -> quando a thread entra na zona D
//evento 19 -> quando a thread sai da zona D
//evento 20 -> quando a thread está a consumir um hambúrguer na zona D
//evento 21 -> quando a thread já consumiu o hambúrguer na zona D
//evento 22 -> quando a thread produtor está a produzir um hambúrguer na zona D
//evento 23 -> quando a thread produtor já produziu o hambúrguer na zona D
//evento 24 -> estatistica
//evento 25 -> Cliente chega no Disco
//evento 26 -> Cliente sai Zona D, porque não tem dinheiro suficiente

#endif