#include "LiteSH.hpp"


void about()
{
  cout << "\t\t**********LiteSH**********" << endl;
  cout << endl;
  cout << "Using this utility you can easily create processes and daemons," << endl;
  cout << "receive signals from external programs and the operating system" << endl;
  cout << "and also send signals to other processes" << endl << endl;
  cout <<  "Authors: Semyon Karulev, Vladislav Mamonov, Roman Suksin" << endl << endl;

  ifstream signals("signals.txt");
  string SigName;

  cout << "Available signal numbers: " << endl;
  cout << "---------------------------" << endl;

  for (int i = 1; getline(signals, SigName); i++) {
    cout << "\E[36m" << i << " - ";
    cout << "\E[39m";
    cout << SigName << endl;
  }

  signals.close();
}


int main()
{
  pid_t server_pid = net_proc();
  bool isExit = false;

  cout << "Print 'CreateProcess' to create process" << endl;
  cout << "Print 'CreateDaemon' to create daemon" << endl;
  cout << "Print 'SendSignal' to send signal to the process" << endl;
  cout << "Print 'RecvSignal' to receive signal" << endl;
  cout << "Print 'FileManager' to start FileManager" << endl;
  cout << "Print 'about' to learn about project" << endl;
  cout << "Print 'exit' to close program" << endl << endl;

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
        about();
        break;

      case 7:
        isExit = true;
        break;
    }
  }

  SendSignal(server_pid, SIGKILL);  // завершаем работу сервера
  return 0;
}
