#include "LiteSH.hpp"


int CreateProcess(char *ProcName)
{
  int rv;
  char *arg[] = {ProcName, 0};

  switch (fork()) {
    case -1:
      perror("fork");
      return 1;
    case 0:
      execv(arg[0], arg);
    default:
      wait(&rv);
  }

  return 0;
}


int CreateDaemon(char *ProcName)
{
  int rv;
  char *arg[] = {ProcName, 0};

  switch (fork()) {
    case -1:
      perror("fork");
      return 1;
    case 0:
      setsid();
      chdir("/");
      fclose(stdin);
      fclose(stdout);
      fclose(stderr);
      execv(arg[0], arg);
      exit(0);
    default:
      wait(&rv);
  }

  return 0;
}
