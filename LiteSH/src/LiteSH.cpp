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
      cout << "pid: " << getpid() << endl;
      cout << "ppid: " << getppid() << endl;
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
      cout << "pid: " << getpid() << endl;
      cout << "ppid: " << getppid() << endl;
      chdir("/");
      fclose(stdin);
      fclose(stdout);
      fclose(stderr);
      execv(arg[0], arg);
      //exit(0);
    default:
      wait(&rv);
  }

  return 0;
}


int SendMssg(const char *ProcName, const char *mssg)
{
  key_t ipckey;
  int mq_id;

  struct { long type; char text[100]; } mymsg;
  ipckey = ftok(ProcName, 42);
  cout << "my key is " << ipckey << endl;

  mq_id = msgget(ipckey, IPC_CREAT | 0666);
  cout << "message identifier is " << mq_id << endl;

  memset(mymsg.text, 0, 100);
  strcpy(mymsg.text, mssg);
  mymsg.type = 1;
  msgsnd(mq_id, &mymsg, sizeof(mymsg), 0);

  return 0;
}


int RecvMssg(const char *ProcName)
{
  key_t ipckey;
  int mq_id;

  struct { long type; char text[100]; } mymsg;
  int received;

  ipckey = ftok(ProcName, 42);
  cout << "My key is " << ipckey << endl;

  /* Подключение к очереди */
  mq_id = msgget(ipckey, 0);
  cout << "Message identifier is " << mq_id << endl;

  /* Считывание сообщения */
  received = msgrcv(mq_id, &mymsg, sizeof(mymsg), 0, 0);
  cout << mymsg.text << "(" << received << ")" << endl;

  return 1;
}


void sighandler(int signo)
{
  cout << "Signal received successfully" << endl;
}


int SendSignal(pid_t pid, int signum)
{
  if (kill(pid, signum) == -1)
    return 1;

  return 0;
}


int RecvSignal(int signum)
{
  if (signal(signum, sighandler) == SIG_ERR)
    return 1;

  return 0;
}
