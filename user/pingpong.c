#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pipePtoC[2], pipeCtoP[2];
  char buf[64];
  int status; 
  
  pipe(pipePtoC);
  pipe(pipeCtoP);
  int pid = fork();
  if (pid != 0){
    close(pipePtoC[0]);
    close(pipeCtoP[1]);
    write(pipePtoC[1], "a", 1);
    read(pipeCtoP[0], buf, 1);
    printf("%d: received pong\n", getpid());
    wait(&status);
  }
  else{
    close(pipePtoC[1]);
    close(pipeCtoP[0]);
    read(pipePtoC[0], buf, 1);
    printf("%d: received ping\n", getpid());
    write(pipeCtoP[1], "b", 1); 
  }
  exit(0);
}
