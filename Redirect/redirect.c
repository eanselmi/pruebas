#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
  int ch;
  int fd = stripNewlines();

  while(read(fd, &ch, 1) == 1){
    write(1, &ch, 1);
  }

  return 0;
}

int stripNewlines(){
  int fd[2];
  int ch;
  pipe(fd);

  if(!fork()){
    close(fd[0]);

    while(read(0, &ch, 1) == 1){
      if(ch == '\n'){ continue; }
      write(fd[1], &ch, 1);
    }

    exit(0);
  }else{
    close(fd[1]);
    return fd[0];
  }
}
