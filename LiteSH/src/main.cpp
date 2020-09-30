#include "LiteSH.hpp"


int main()
{
  bool isExit = false;
  string command;

  while (isExit != true) {
    cout << "command: ";
    getline(cin, command);

    if (command.substr(0, 12) == "proc -create") {
      string proc_name;
      char *proc_name_buf = new char[100];
      proc_name = command.substr(13);
      strcpy(proc_name_buf, proc_name.c_str());

      CreateProcess(proc_name_buf);

      delete[] proc_name_buf;
    }

    if (command.substr(0, 14) == "daemon -create") {
      string proc_name;
      char *proc_name_buf = new char[100];
      proc_name = command.substr(15);
      strcpy(proc_name_buf, proc_name.c_str());

      CreateProcess(proc_name_buf);

      delete[] proc_name_buf;
    }
  }

  return 0;
}
