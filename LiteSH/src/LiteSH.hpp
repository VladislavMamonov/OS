#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

using namespace std;


int CreateProcess(char *ProcName);
int CreateDaemon(char *ProcName);
int SendMssg();
int RecvMssg();
