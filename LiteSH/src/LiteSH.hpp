#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;


int CreateProcess(char *ProcName);
int CreateDaemon(char *ProcName);
