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
  int socket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  in_addr_t target_ip = inet_addr("192.168.1.100");
  // handle_err(target_ip == INADDR_NONE,"bad target_ip\n");

  struct sockaddr_in target_addr = {
      .sin_family = AF_INET,
      .sin_addr.s_addr = target_ip,
      .sin_port = htons(9090)};

  int n = 100;
  int cnt = 0;
  while (n--)
  {
    char msg[] = "Hello World!";
    sendto(socket_, msg, sizeof(msg), 0, (struct sockaddr *)&target_addr,
           sizeof(target_addr));
    cnt++;
    // struct sockaddr_in my_addr;
    // socklen_t my_addr_len = sizeof(my_addr);
    // getsockname(socket_, (struct sockaddr *)&my_addr, &my_addr_len);
    printf("已发送:%d \t本机ip:%s\t目标ip:%s\n", cnt, "", inet_ntoa(target_addr.sin_addr));
  }
}
