
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>


using namespace std;

struct Block {
    int start;      // 起始地址
    int size;       // 大小
    bool isFree;    // 是否空闲
};

struct Process {
    int id;         // 进程 ID
    int size;       // 所需内存大小
    int start;      // 起始地址
};

class MemoryManager {
private:
    vector<Block> memoryBlocks; //所有内存块
    vector<Process> processes;  //已分配进程
    int pid;                         //进程ID计数器
    int memSize;                     //内存大小

    void sortMem();
    void mergeMemory();
public:
    MemoryManager(int size);
    bool allocate(int size, int method);
    void display();
    int getPid();
    bool deallocate(int pid);
};
