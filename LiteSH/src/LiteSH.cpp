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


int SendMssg()
{
  key_t ipckey;
  int mq_id;

  struct { long type; char text[100]; } mymsg;
  ipckey = ftok("/home/vladislav/.bash_history", 42);
  cout << "my key is " << ipckey << endl;

  mq_id = msgget(ipckey, IPC_CREAT | 0666);
  cout << "message identifier is " << mq_id << endl;

  memset(mymsg.text, 0, 100);
  strcpy(mymsg.text, "Hello, world!");
  mymsg.type = 1;
  msgsnd(mq_id, &mymsg, sizeof(mymsg), 0);

  return 0;
}


int RecvMssg()
{
  key_t ipckey;
  int mq_id;

  struct { long type; char text[100]; } mymsg;
  int received;

  ipckey = ftok("/home/vladislav/.bash_history", 42);
  cout << "My key is " << ipckey << endl;

  /* Подключение к очереди */
  mq_id = msgget(ipckey, 0);
  cout << "Message identifier is " << mq_id << endl;

  /* Считывание сообщения */
  received = msgrcv(mq_id, &mymsg, sizeof(mymsg), 0, 0);
  cout << mymsg.text << "(" << received << ")" << endl;

  return 1;
}
