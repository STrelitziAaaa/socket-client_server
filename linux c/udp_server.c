#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define handle_err(expr, msg) \
  if (expr)                   \
  {                           \
    perror(msg);              \
    exit(EXIT_FAILURE);       \
  }

int main(int argc, char **argv)
{
  int ls_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  struct sockaddr_in ls_addr = {
      .sin_family = AF_INET,
      .sin_addr.s_addr = htonl(INADDR_ANY), //htonl(INADDR_ANY);
      .sin_port = htons(9090)};
  // memset(&ls_addr, 0, sizeof(ls_addr));

  bind(ls_socket, (struct sockaddr *)&ls_addr, sizeof(ls_addr));

  char buf[1024] = {0};
  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);
  int cnt = 0;
  while (1)
  {
    int n = recvfrom(ls_socket, buf, sizeof(buf), 0,
                     (struct sockaddr *)&client_addr,
                     &client_addr_len);
    handle_err(n <= 0, "receive from socket : ERROR");

    printf("Receive msg: %s \t 本机ip:%s \tclient ip:%s\n", buf, "", inet_ntoa(client_addr.sin_addr));
    cnt++;
    printf("收到信息数:%d\n", cnt);
  }
}
