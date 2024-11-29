#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
/*
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
    int memorySize;                    // 总内存大小
    vector<Block> memoryBlocks;        // 内存分区
    vector<Process> processes;         // 已分配的进程

    // 内存分区按地址排序
    void mergeFreeBlocks() {
        // 按起始地址排序
        sort(memoryBlocks.begin(), memoryBlocks.end(), [](const Block& a, const Block& b) {
            return a.start < b.start;
            });

        // 合并相邻的空闲块
        for (int i = 0; i < memoryBlocks.size() - 1; ++i) {
            if (memoryBlocks[i].isFree && memoryBlocks[i + 1].isFree) {
                memoryBlocks[i].size += memoryBlocks[i + 1].size;  // 合并大小
                memoryBlocks.erase(memoryBlocks.begin() + i + 1);  // 删除后一个块
                --i; // 检查合并后的块是否还可以继续合并
            }
        }
    }


public:
    MemoryManager(int size) : memorySize(size) {
        memoryBlocks.push_back({ 0, size, true }); // 初始化整个内存为空闲
    }

    bool isPidExists(int pid) {
        for (const auto& process : processes) {
            if (process.id == pid) {
                return true;
            }
        }
        return false;
    }

    void allocate(int pid, int size, int method) {
        int index = -1;

        switch (method) {
        case 1: // 最先适应法
            for (int i = 0; i < memoryBlocks.size(); ++i) {
                if (memoryBlocks[i].isFree && memoryBlocks[i].size >= size) {
                    index = i;
                    break;
                }
            }
            break;
        case 2: // 最佳适应法
            for (int i = 0; i < memoryBlocks.size(); ++i) {
                if (memoryBlocks[i].isFree && memoryBlocks[i].size >= size) {
                    if (index == -1 || memoryBlocks[i].size < memoryBlocks[index].size) {
                        index = i;
                    }
                }
            }
            break;
        case 3: // 最坏适应法
            for (int i = 0; i < memoryBlocks.size(); ++i) {
                if (memoryBlocks[i].isFree && memoryBlocks[i].size >= size) {
                    if (index == -1 || memoryBlocks[i].size > memoryBlocks[index].size) {
                        index = i;
                    }
                }
            }
            break;
        default: cout << "无效选项，请重新选择！" << endl;
        }

        if (index != -1) {
            Block& block = memoryBlocks[index];
            processes.push_back({ pid, size, block.start });

            memoryBlocks.push_back({ block.start,size,false });

            block.start += size;
            block.size -= size;

            if (block.size == 0) {
                memoryBlocks.erase(memoryBlocks.begin() + index);
            }
            else {
                block.isFree = true;
            }

            cout << "进程 " << pid << " 分配成功，大小: " << size << endl;
        }
        else {
            cout << "进程 " << pid << " 分配失败，内存不足。" << endl;
        }
    }

    void deallocate(int pid) {
        auto it = find_if(processes.begin(), processes.end(), [pid](Process& p) {
            return p.id == pid;
            });

        if (it != processes.end()) {
            int start = it->start;
            int size = it->size;

            memoryBlocks.push_back({ start, size, true });
            mergeFreeBlocks();

            processes.erase(it);
            cout << "进程 " << pid << " 回收成功。" << endl;
        }
        else {
            cout << "进程 " << pid << " 回收失败，未找到。" << endl;
        }
    }

    void displayMemory() {
        cout << "当前内存状态：" << endl;
        cout << setw(10) << "起始地址" << setw(10) << "大小" << setw(10) << "状态" << endl;

        for (const auto& block : memoryBlocks) {
            cout << setw(10) << block.start << setw(10) << block.size
                << setw(10) << (block.isFree ? "空闲" : "已占用") << endl;
        }

        cout << "已分配的进程：" << endl;
        cout << setw(10) << "进程ID" << setw(10) << "起始地址" << setw(10) << "大小" << endl;

        for (const auto& proc : processes) {
            cout << setw(10) << proc.id << setw(10) << proc.start
                << setw(10) << proc.size << endl;
        }
    }
};
*/

/*
int main() {
    int totalMemory, choice, pid, size, method;

    cout << "请输入总内存大小: ";
    cin >> totalMemory;

    MemoryManager manager(totalMemory);

    while (true) {
        cout << "\n1. 分配内存\n2. 回收内存\n3. 显示内存状态\n4. 清屏\n0. 退出\n请选择操作: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "请输入进程ID: ";
            cin >> pid;
            cout << "请输入内存大小: ";
            cin >> size;
            cout << "请选择分配方式 (1: 最先适应, 2: 最佳适应, 3: 最坏适应): ";
            cin >> method;
            if (manager.isPidExists(pid)) {
                cout << "进程id已存在，请重新分配" << endl;
                break;
            }
            manager.allocate(pid, size, method);
            break;
        case 2:
            cout << "请输入回收的进程ID: ";
            cin >> pid;
            manager.deallocate(pid);
            break;
        case 3:
            manager.displayMemory();
            break;
        case 4:
            system("cls");
            break;
        case 0:
            return 0;
        default:
            cout << "无效选项，请重新选择！" << endl;
        }
    }
}
*/

/*
总内存大小: 200

操作序列:
1. 分配进程 (ID: 1, 大小: 50, 分配策略: 1)
2. 分配进程 (ID: 2, 大小: 70, 分配策略: 2)
3. 分配进程 (ID: 3, 大小: 30, 分配策略: 3)
4. 显示内存状态
5. 回收进程 (ID: 2)
6. 显示内存状态
7. 分配进程 (ID: 4, 大小: 20, 分配策略: 1)
8. 分配进程 (ID: 5, 大小: 40, 分配策略: 2)
9. 显示内存状态
10. 回收进程 (ID: 1)
11. 回收进程 (ID: 3)
12. 显示内存状态
13. 分配进程 (ID: 6, 大小: 100, 分配策略: 3)
14. 显示内存状态

*/