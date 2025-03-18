#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc == 1)
    printf("ab\n\ncd\n");
  if (argc > 1)
    printf("ab\ncd");

  exit(0);
}
