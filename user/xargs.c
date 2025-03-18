#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int
main(int argc, char *argv[])
{
  if (argc <= 1){
    printf("Usage xargs cmd [parms ...].");
    exit(1);
  }
  char *myArgv[MAXARG];
  for (int i=0; i<argc-1; i++)
    myArgv[i] = argv[i+1];
  
  int finished = 0;
  // hopefully the previous program would not 
  // generate line longer than 512 bytes
  char buf[512];
  char *p;
  while (finished == 0){
    p = buf;
    *p = 0;
    // deal with text\n\0 , text\0 , \n (no text) cases 
    while (read(0, p, 1) != 0 && *p != '\n'){
      p++;
    }
    // \n (notext) case
    if (*p == '\n' && p == buf){
      continue;
    }
    // text\n\0 case
    if (*p != '\n' && p == buf){
      break;
    }
    // text\0 case
    if (*p != '\n')
      finished = 1;
    *p = 0;

    myArgv[argc-1] = buf;
    if (argc < MAXARG)
      myArgv[argc] = 0;
    int pid = fork();
    if (pid == 0){
      exec(myArgv[0], myArgv);
      printf("error exec %s", myArgv[0]);
      exit(1);
    }
    else{
      int status;
      wait(&status);
    }
  }

  exit(0);
}
