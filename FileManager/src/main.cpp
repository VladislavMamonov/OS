#include "FManager.hpp"


void about()
{
  cout << "\t\t**********File manager**********" << endl;
  cout << endl;
  cout << "Using this utility you can easily manage your files, find out their size and directory size" << endl;
  cout <<  "Authors: Semyon Karulev, Vladislav Mamonov, Roman Suksin" << endl;
}


int main()
{
  bool isExit = false;

  cout << "Press 1 to display files in directory" << endl;
  cout << "Press 2 to copy file" << endl;
  cout << "Press 3 to move file" << endl;
  cout << "Press 4 to remove file" << endl;
  cout << "Press 5 to get file size" << endl;
  cout << "Press 6 to get directory size" << endl;
  cout << "Press 7 to display procfs processes" << endl;
  cout << "Press 8 to learn about project" << endl;
  cout << "Press any key to exit" << endl << endl;


  while (isExit != true)
  {
    int selection;
    cout << "\n\n" << "selection: ";
    cin >> selection;

    switch (selection) {
      case 1: {
        char *src = new char;
        cout << "path to directory: ";
        cin >> src;

        if (print_dir(src) == 1)
          cout << "unknown path" << endl;

        delete src;
        break;
      }

      case 2: {
        char *src = new char;
        char *dst = new char;
        cout << "path to file: ";
        cin >> src;
        cout << "copy to: ";
        cin >> dst;

        if (copy_file(src, dst) == 1)
          cout << "unknown file/path" << endl;

        delete src;
        delete dst;
        break;
      }

      case 3: {
        char *src = new char;
        char *dst = new char;
        cout << "path to file: ";
        cin >> src;
        cout << "move to: ";
        cin >> dst;

        if (mv_file(src, dst) == 1)
          cout << "unknown file/path" << endl;

        delete src;
        delete dst;
        break;
      }

      case 4: {
        char *src = new char;
        cout << "path to file: ";
        cin >> src;

        if (remove_file(src) == 1)
          cout << "unknown file" << endl;

        delete src;
        break;
      }

      case 5: {
        char *src = new char;
        cout << "path to file: ";
        cin >> src;
        off_t file_size = GetFileSize(src);

        if (file_size == -1) {
          cout << "unknown file" << endl;
          delete src;
          break;
        }

        cout << "size of file: " << file_size << endl;

        delete src;
        break;
      }

      case 6: {
        char *src = new char;
        cout << "path to directory: ";
        cin >> src;
        off_t DirSize = GetDirSize(src);

        if (DirSize == -1) {
          cout << "unknown directory" << endl;
          delete src;
          break;
        }

        cout << "size of directory: " << DirSize << endl;

        delete src;
        break;
      }

      case 7:
        print_processes();
        break;

      case 8:
        about();
        break;

      default:
        isExit = true;
        break;
    }
  }

  return 0;
}
