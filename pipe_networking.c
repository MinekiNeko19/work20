#include "pipe_networking.h"

/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  // int from_client = 0;

  mkfifo(WKP,0644);
  printf("0. server creates WKP\n");

  int from_client = open(WKP, O_RDONLY);
  char sp[sizeof(ACK)];
  read(from_client, sp, sizeof(ACK));
  printf("4. server recieves from client through WKP: %s\n", sp);
  remove(WKP);

  *to_client = open(ACK, O_WRONLY);
  write(*to_client,"from server",10);
  printf("5. server sent response to client\n");

  char final[10];
  read(from_client, final, 10);
  printf("7. final message from client: %s\n", final);

  return from_client;
}

/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  // int from_server = 0;

  mkfifo(ACK,0644);
  printf("1. client creates secret pipe\n");

  *to_server = open(WKP, O_WRONLY);
  write(*to_server, ACK, sizeof(ACK));
  printf("2. client sends name of SP to server\n");

  int from_server = open(ACK, O_RDONLY);
  printf("3. client waiting for response\n");
  
  char sc[11];
  read(from_server, sc, 11);
  printf("6. client got from server: %s\n", sc);
  remove(ACK);

  write(*to_server, "from clie\n",10);
    return from_server;
}