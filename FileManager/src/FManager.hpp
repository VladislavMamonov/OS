#pragma once
#include <iostream>
#include <cstring>
#include <dirent.h>

using namespace std;


int64_t GetFileSize(FILE *fd);

int copy_file(char *src, char *dst);
int mv_file(char *src, char *dst);
int remove_file(char *src);
int print_dir(char *src);
