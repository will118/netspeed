#import "netspeed.c" // for performance

int main(int argc, char *argv[]) {
  if (argc == 2) {
    struct interface_stats stats = interface_bytes_transferred(argv[1]);
    printf(
      "ibytes: %llu obytes: %llu usec: %llu\n",
      stats.ibytes, stats.obytes, stats.time_usec
    );
    return 0;
  }
  printf("usage: netspeed <interface_name>\n");
  exit(1);
}
