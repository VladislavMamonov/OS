#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

using namespace std;


int CreateProcess(char *ProcName);
int CreateDaemon(char *ProcName);
int SendMssg(const char *ProcName, const char *mssg);
int RecvMssg(const char *ProcName);

void sighandler();
int SendSignal(pid_t pid, int signum);
int RecvSignal(int signum);
