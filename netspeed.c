#include <sys/sysctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <net/route.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void interface_bytes_transferred(char *interface_name) {
  int mib[] = {
    CTL_NET,
    PF_ROUTE,
    0,
    0,
    NET_RT_IFLIST2,
    0
  };

  size_t len;

  if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
    exit(1);
  }

  char *buf = malloc(len);

  if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
    exit(1);
  }

  char *next = buf;
  char *lim = buf + len;

  while (next < lim) {
    struct if_msghdr *ifm = (struct if_msghdr *)next;
    next += ifm->ifm_msglen;
    if (ifm->ifm_type == RTM_IFINFO2) {
      struct if_msghdr2 *if2m = (struct if_msghdr2 *)ifm;
      struct sockaddr_dl *sdl = (struct sockaddr_dl *)(if2m + 1);
      struct if_data64 ifd = if2m->ifm_data;
      if (strncmp(interface_name, sdl->sdl_data, sdl->sdl_nlen) == 0) {
        printf("ibytes: %llu\nobytes: %llu\n", ifd.ifi_ibytes, ifd.ifi_obytes);
      }
    }
  }

  free(buf);
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    interface_bytes_transferred(argv[1]);
  } else {
    printf("usage: ./netspeed <interface_name>\n");
    exit(1);
  }
  return 0;
}
