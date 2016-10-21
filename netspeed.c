#include <sys/sysctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <net/route.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

struct interface_stats {
   unsigned long long ibytes;
   unsigned long long obytes;
   unsigned long long time_usec;
};

const struct interface_stats default_stats = { 0, 0, 0 };

struct interface_stats interface_bytes_transferred(const char *interface_name) {
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
  struct interface_stats stats = default_stats;

  while (next < lim) {
    struct if_msghdr *ifm = (struct if_msghdr *)next;
    next += ifm->ifm_msglen;
    if (ifm->ifm_type == RTM_IFINFO2) {
      struct if_msghdr2 *if2m = (struct if_msghdr2 *)ifm;
      struct sockaddr_dl *sdl = (struct sockaddr_dl *)(if2m + 1);
      struct if_data64 ifd = if2m->ifm_data;
      struct timeval tv;
      if (gettimeofday(&tv, NULL) == 0) {
        if (strncmp(interface_name, sdl->sdl_data, sdl->sdl_nlen) == 0) {
          stats.ibytes = ifd.ifi_ibytes;
          stats.obytes = ifd.ifi_obytes;
          stats.time_usec = (1000000 * tv.tv_sec) + tv.tv_usec;
          break;
        }
      }
    }
  }

  free(buf);

  return stats;
}
