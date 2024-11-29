#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
/*
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
    int memorySize;                    // ���ڴ��С
    vector<Block> memoryBlocks;        // �ڴ����
    vector<Process> processes;         // �ѷ���Ľ���

    // �ڴ��������ַ����
    void mergeFreeBlocks() {
        // ����ʼ��ַ����
        sort(memoryBlocks.begin(), memoryBlocks.end(), [](const Block& a, const Block& b) {
            return a.start < b.start;
            });

        // �ϲ����ڵĿ��п�
        for (int i = 0; i < memoryBlocks.size() - 1; ++i) {
            if (memoryBlocks[i].isFree && memoryBlocks[i + 1].isFree) {
                memoryBlocks[i].size += memoryBlocks[i + 1].size;  // �ϲ���С
                memoryBlocks.erase(memoryBlocks.begin() + i + 1);  // ɾ����һ����
                --i; // ���ϲ���Ŀ��Ƿ񻹿��Լ����ϲ�
            }
        }
    }


public:
    MemoryManager(int size) : memorySize(size) {
        memoryBlocks.push_back({ 0, size, true }); // ��ʼ�������ڴ�Ϊ����
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
        case 1: // ������Ӧ��
            for (int i = 0; i < memoryBlocks.size(); ++i) {
                if (memoryBlocks[i].isFree && memoryBlocks[i].size >= size) {
                    index = i;
                    break;
                }
            }
            break;
        case 2: // �����Ӧ��
            for (int i = 0; i < memoryBlocks.size(); ++i) {
                if (memoryBlocks[i].isFree && memoryBlocks[i].size >= size) {
                    if (index == -1 || memoryBlocks[i].size < memoryBlocks[index].size) {
                        index = i;
                    }
                }
            }
            break;
        case 3: // ���Ӧ��
            for (int i = 0; i < memoryBlocks.size(); ++i) {
                if (memoryBlocks[i].isFree && memoryBlocks[i].size >= size) {
                    if (index == -1 || memoryBlocks[i].size > memoryBlocks[index].size) {
                        index = i;
                    }
                }
            }
            break;
        default: cout << "��Чѡ�������ѡ��" << endl;
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

            cout << "���� " << pid << " ����ɹ�����С: " << size << endl;
        }
        else {
            cout << "���� " << pid << " ����ʧ�ܣ��ڴ治�㡣" << endl;
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
            cout << "���� " << pid << " ���ճɹ���" << endl;
        }
        else {
            cout << "���� " << pid << " ����ʧ�ܣ�δ�ҵ���" << endl;
        }
    }

    void displayMemory() {
        cout << "��ǰ�ڴ�״̬��" << endl;
        cout << setw(10) << "��ʼ��ַ" << setw(10) << "��С" << setw(10) << "״̬" << endl;

        for (const auto& block : memoryBlocks) {
            cout << setw(10) << block.start << setw(10) << block.size
                << setw(10) << (block.isFree ? "����" : "��ռ��") << endl;
        }

        cout << "�ѷ���Ľ��̣�" << endl;
        cout << setw(10) << "����ID" << setw(10) << "��ʼ��ַ" << setw(10) << "��С" << endl;

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

    cout << "���������ڴ��С: ";
    cin >> totalMemory;

    MemoryManager manager(totalMemory);

    while (true) {
        cout << "\n1. �����ڴ�\n2. �����ڴ�\n3. ��ʾ�ڴ�״̬\n4. ����\n0. �˳�\n��ѡ�����: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "���������ID: ";
            cin >> pid;
            cout << "�������ڴ��С: ";
            cin >> size;
            cout << "��ѡ����䷽ʽ (1: ������Ӧ, 2: �����Ӧ, 3: ���Ӧ): ";
            cin >> method;
            if (manager.isPidExists(pid)) {
                cout << "����id�Ѵ��ڣ������·���" << endl;
                break;
            }
            manager.allocate(pid, size, method);
            break;
        case 2:
            cout << "��������յĽ���ID: ";
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
            cout << "��Чѡ�������ѡ��" << endl;
        }
    }
}
*/

/*
���ڴ��С: 200

��������:
1. ������� (ID: 1, ��С: 50, �������: 1)
2. ������� (ID: 2, ��С: 70, �������: 2)
3. ������� (ID: 3, ��С: 30, �������: 3)
4. ��ʾ�ڴ�״̬
5. ���ս��� (ID: 2)
6. ��ʾ�ڴ�״̬
7. ������� (ID: 4, ��С: 20, �������: 1)
8. ������� (ID: 5, ��С: 40, �������: 2)
9. ��ʾ�ڴ�״̬
10. ���ս��� (ID: 1)
11. ���ս��� (ID: 3)
12. ��ʾ�ڴ�״̬
13. ������� (ID: 6, ��С: 100, �������: 3)
14. ��ʾ�ڴ�״̬

*/