#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 4096

int main(int argc, char *argv[])
{
    char *fname;
    struct stat sb;
    long long fsize, bcount, i;
    FILE *file;
    char buf[BUFSIZE];

   if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

   fname = argv[1];
   if (stat(fname, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    fsize = (long long) sb.st_size;
    printf("fsize = %lld\n", fsize);

    for (i = 0; i < BUFSIZE; i++) {
      buf[i] = 0;
    }
    bcount = (fsize + BUFSIZE - 1) / BUFSIZE;

    file = fopen(fname, "r+");
    for (i = 0; i < bcount; i++) {
      fwrite(buf, BUFSIZE, 1, file);
    }
    fclose(file);
}
