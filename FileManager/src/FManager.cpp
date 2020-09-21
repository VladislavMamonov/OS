#include "FManager.hpp"


int copy_file(char *src, char *dst)
{
  FILE *from;
  FILE *to;

  int src_len = 0;
  int file_len = 0;

  for (int i = 0; src[i] != '\0'; i++)    //Длина исходного пути
    src_len++;

  for (int i = src_len; src[i] != '/'; i--)   //Длина перемещаемого файла
    file_len++;

  file_len--;
  char *filename = new char[file_len];

  for (int i = 0, j = src_len - file_len; i < file_len; i++, j++) {   //Извлекаем имя файла из указанного пути
    filename[i] = src[j];
  }

  char copy_to[512];
  strcat(copy_to, dst);
  strcat(copy_to, filename);      //Получем полный путь для создания файла

  if ((from = fopen(src, "r")) == NULL) {
    delete[] filename;
    return 1;
  }

  if ((to = fopen(copy_to, "w")) == NULL) {
    delete[] filename;
    return 1;
  }

  int c;
  while ((c = getc(from)) != EOF)
    putc(c, to);

  fclose(from);
  fclose(to);
  delete[] filename;

  return 0;
}


int mv_file(char *src, char *dst)
{
  if (copy_file(src, dst) == 1)
    return 1;

  if (remove(src) == -1)    //После копирования удаляем исходный файл
    return 1;

  return 0;
}


int remove_file(char *src)
{
  if (remove(src) == -1)
    return 1;

  return 0;
}


int print_dir(char *src)
{
  struct dirent *pDirent;
  DIR *pDir;

  if ((pDir = opendir(src)) == NULL)
    return 1;

  while ((pDirent = readdir(pDir)) != NULL)
    cout << pDirent->d_name << endl;

  closedir(pDir);
  return 0;
}


off_t GetFileSize(char *src)
{
  struct stat buf;
  FILE *fp;

  if ((fp = fopen(src, "r")) == NULL)
    return -1;

  stat(src, &buf);
  return buf.st_size;
}


off_t GetDirSize(char *src)
{
  off_t DirSize = 0;
  struct dirent *pDirent;
  DIR *pDir;

  if ((pDir = opendir(src)) == NULL)
    return -1;

  while ((pDirent = readdir(pDir)) != NULL) {   //Проходимся по директории
    char buf[512];
    memset(buf, 0, sizeof(buf));
    strcat(buf, src);
    strcat(buf, pDirent->d_name);    //В buf хранится полный путь до файла
    DirSize += GetFileSize(buf);     //GetFileSize() для каждого файла
  }

  if (DirSize < 0)
    return -1;

  closedir(pDir);
  return DirSize;
}


void print_processes()
{
  struct dirent *pDirent;
  DIR *pDir;

  pDir = opendir("/proc/");
  cout << "PID\t" << "Name" << endl;
  cout << "--------------" << endl;

  while ((pDirent = readdir(pDir)) != NULL) {   //Проходимся по директории
    if (isdigit(pDirent->d_name[0]) != 0) {
      char proc_path[100] = "/proc/";
      strcat(proc_path, pDirent->d_name);
      strcat(proc_path, "/status");            //Формируем путь к процессу
      FILE *proc_info = fopen(proc_path, "r");

      char *proc_name = new char;
      char *temp = new char;

      fscanf(proc_info, "%s%s", temp, proc_name);     //Извлекаем из файла "status" название процесса
      cout << pDirent->d_name << "\t" << proc_name << endl;

      // delete proc_name;
      // delete temp;
      fclose(proc_info);
    }
  }

  closedir(pDir);
}
