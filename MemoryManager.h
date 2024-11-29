
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>


using namespace std;

struct Block {
    int start;      // ��ʼ��ַ
    int size;       // ��С
    bool isFree;    // �Ƿ����
};

struct Process {
    int id;         // ���� ID
    int size;       // �����ڴ��С
    int start;      // ��ʼ��ַ
};

class MemoryManager {
private:
    vector<Block> memoryBlocks; //�����ڴ��
    vector<Process> processes;  //�ѷ������
    int pid;                         //����ID������
    int memSize;                     //�ڴ��С

    void sortMem();
    void mergeMemory();
public:
    MemoryManager(int size);
    bool allocate(int size, int method);
    void display();
    int getPid();
    bool deallocate(int pid);
};
