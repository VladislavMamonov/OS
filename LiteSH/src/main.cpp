#include "LiteSH.hpp"


int main()
{
  pid_t server_pid = net_proc();
  bool isExit = false;

  char *error;
  void *handle = dlopen("/home/vladislav/OS/LiteSH/lib/libabout.so", RTLD_LAZY);
  if (!handle) {
    fputs (dlerror(), stderr);
    return 1;
  }

  void *p_func = dlsym(handle, "commands_guide");

  if ((error = dlerror()) != NULL) {
    fprintf (stderr, "%s\n", error);
    return 1;
  }

  // void *commands_guide();
  // commands_guide();

  while (isExit != true)
  {
    int selection = 0;
    char *command = new char[100];

    cout << endl << endl;
    cout << "command to server: ";
    cin >> command;
    cout << endl << endl;

    cout << "--------------------------" << endl;
    selection = NetWorking_client(command);
    cout << "--------------------------" << endl << endl;

    switch (selection) {
      case 1: {
        char *ProcName = new char[100];
        cout << "process name: ";
        cin >> ProcName;

        if (CreateProcess(ProcName) == 1)
          cout << "failed to create process" << endl;

        delete [] ProcName;
        break;
      }

      case 2: {
        char *ProcName = new char[100];
        cout << "process name: ";
        cin >> ProcName;

        if (CreateDaemon(ProcName) == 1)
          cout << "failed to create daemon" << endl;

        delete [] ProcName;
        break;
      }

      case 3: {
        pid_t pid, signum;
        cout << "pid: ";
        cin >> pid;
        cout << "signal to send: ";
        cin >> signum;

        if (SendSignal(pid, signum) == 1)
          cout << "failed to send signal";

        break;
      }

      case 4: {
        int signum;
        cout << "signal to receive: ";
        cin >> signum;

        if (RecvSignal(signum) == 1)
          cout << "failed to receive signal";

        break;
      }

      case 5:
        CreateProcess("/home/vladislav/OS/FileManager/bin/File_Manager"); //поменять на свой
        break;

      case 6:
        //about();
        break;

      case 7:
        isExit = true;
        break;
    }
  }

  SendSignal(server_pid, SIGKILL);  // завершаем работу сервера
  dlclose(handle);
  return 0;
}
