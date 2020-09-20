#pragma once
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

using namespace std;


int copy_file(char *src, char *dst);
int mv_file(char *src, char *dst);
int remove_file(char *src);
int print_dir(char *src);

off_t GetFileSize(char *src);
off_t GetDirSize(char *src);
