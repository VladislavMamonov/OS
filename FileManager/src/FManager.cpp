#include "FManager.hpp"


int64_t GetFileSize(FILE *fd)
{
  int64_t _file_size = 0;

  if (fd == NULL) {
    _file_size = -1;
    return 1;
  }
  else {
    while(getc(fd) != EOF) _file_size++;
    fclose(fd);
  }

  return _file_size;
}


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
  strcat(copy_to, filename);

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
