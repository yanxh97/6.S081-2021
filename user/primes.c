#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  // first process fork and write 2-35 to pipe
  // non-first process fork read from read pipe and write to write pipe
  int p[2];
  int pid;
  pipe(p);
  pid = fork();
  if (pid != 0){
    // write to the pipe from 2 to 35, ending with a 0
    close(p[0]);
    for (int i=2; i<=35 ;i++){
      write(p[1], &i, 4);
    }
    int last = 0;
    write(p[1], &last, 4);

    int status;
    wait(&status);
    exit(0);
  }
  //else{
  //  close(p[1]);
  //  read(p[0], &pid, 4);
  //  printf("prime %d\n", pid);
   // exit(0);
  //}
  while (1){
    int primenumber;
    close(p[1]);
    read(p[0], &primenumber, 4);
    if (primenumber == 0){
    	exit(0);
    }
    printf("prime %d\n", primenumber);

    int p2[2];
    pipe(p2);
    pid = fork();
    if (pid == 0){
      p[0] = p2[0];
      p[1] = p2[1];
    }
    else{
      int number = primenumber;
      close(p2[0]);
      while (number != 0){
        read(p[0], &number, 4);
	if (number == 0 || number % primenumber != 0){
	  write(p2[1], &number, 4);
	}
      }
      int status;
      wait(&status);
      exit(0);
    }

  }

}
