#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  int from_client = 0;

  mkfifo(WKP,0644);
  printf("0. server creates WKP\n");

  int ctos = open(WKP, O_RDONLY);
  char sp[sizeof(ACK)];
  read(ctos, sp, sizeof(ACK));
  printf("from client through WKP: %s\n", sp);
  // remove(WKP);

  int stoc = open(ACK, O_WRONLY);

  return from_client;
}

// 0. server creates a well known pipe (WKP) and waits for a connection
// 1. client creates a secret pipe
// 2. client sends SP name to server
// 3. client waits for a response
// 4. server receives client message; removes the WKP
// 5. server sends a response to client
// 6. client gets a response; removes SP
// 7. client sends final response

/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server = 0;

  mkfifo(ACK,0644);
  printf("1. client creates secret pipe\n");

  int ctos = open("WKP", O_WRONLY);
  write(ctos, ACK, sizeof(ACK));
  printf("2. client sends name of SP to server\n");

  return from_server;
}