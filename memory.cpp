
#include "MemoryManager.h"

using namespace std;

MemoryManager::MemoryManager(int size) :memSize(size) {
	memoryBlocks.push_back({0,size,true});
	pid = 1;
}

bool MemoryManager::allocate(int size, int method)
{
	int index = -1;
	switch (method)
	{
	case 1:// ������Ӧ��
		for (int i = 0; i < memoryBlocks.size(); ++i) {
			if (memoryBlocks[i].isFree && memoryBlocks[i].size >= size) {
				index = i;
				break;
			}
		}
		break;
	case 2:// �����Ӧ��
	{
		int tempsize = memSize + 1;
		for (int i = 0; i < memoryBlocks.size(); ++i) {
			if (memoryBlocks[i].isFree && memoryBlocks[i].size >= size) {
				if (memoryBlocks[i].size < tempsize) {
					index = i;
					tempsize = memoryBlocks[i].size;
				}
			}
		}
	}
		break;
	case 3:// ���Ӧ��
	{
		int tempsize = 0;
		for (int i = 0; i < memoryBlocks.size(); ++i) {
			if (memoryBlocks[i].isFree && memoryBlocks[i].size >= size) {
				if (memoryBlocks[i].size > tempsize) {
					index = i;
					tempsize = memoryBlocks[i].size;
				}
			}
		}
	}
		break;
	default:
		cout << "��Чѡ�������ѡ��" << endl;
		break;
	}
	if (index != -1) {
		processes.push_back({ pid,size,memoryBlocks[index].start });
		pid++;
		memoryBlocks.push_back({ memoryBlocks[index].start,size,false});
		memoryBlocks[index].start += size;
		memoryBlocks[index].size -= size;
		if (memoryBlocks[index].size == 0) {
			memoryBlocks.erase(memoryBlocks.begin() + index);
		}


		return true;
	}
	else return false;
}



void MemoryManager::display()
{
	sortMem();
	cout << "��ǰ�ڴ�״̬��" << endl;
	cout << setw(20) << "��ʼ��ַ" << setw(20) << "��С" << setw(20) << "״̬" << endl;

	for (const auto& block : memoryBlocks) {
		cout << setw(20) << block.start << setw(20) << block.size
			<< setw(20) << (block.isFree ? "����" : "��ռ��") << endl;
	}

	cout << "�ѷ���Ľ��̣�" << endl;
	cout << setw(20) << "����ID" << setw(20) << "��ʼ��ַ" << setw(20) << "��С" << endl;

	for (const auto& proc : processes) {
		cout << setw(20) << proc.id << setw(20) << proc.start
			<< setw(20) << proc.size << endl;
	}
}


int MemoryManager::getPid()
{
	return pid-1;
}


void MemoryManager::sortMem()
{
	sort(memoryBlocks.begin(), memoryBlocks.end(), [](const Block& a, const Block& b) {
		return a.start < b.start;
		});
}


bool MemoryManager::deallocate(int pid)
{
	auto it = find_if(processes.begin(), processes.end(), [pid](Process& p) {
		return p.id == pid;
		});
	if (it != processes.end()) {
		int start = it->start;
		int size = it->size;

		processes.erase(it);
		for (int i = 0; i < memoryBlocks.size(); i++) {
			if (memoryBlocks[i].start == start) {
				memoryBlocks.erase(memoryBlocks.begin() + i);
			}
		}
		memoryBlocks.push_back({ start, size, true });
		mergeMemory();
		return true;
	}
	else return false;
}


void MemoryManager::mergeMemory()
{
	sortMem();
	for (int i = 0; i < memoryBlocks.size() - 1; ++i) {
		if (memoryBlocks[i].isFree && memoryBlocks[i + 1].isFree) {
			memoryBlocks[i].size += memoryBlocks[i + 1].size;  // �ϲ���С
			memoryBlocks.erase(memoryBlocks.begin() + i + 1);  // ɾ����һ����
			--i; // ���ϲ���Ŀ��Ƿ񻹿��Լ����ϲ�
		}
	}
	 
}
