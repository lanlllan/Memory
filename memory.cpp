
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
	case 1:// 最先适应法
		for (int i = 0; i < memoryBlocks.size(); ++i) {
			if (memoryBlocks[i].isFree && memoryBlocks[i].size >= size) {
				index = i;
				break;
			}
		}
		break;
	case 2:// 最佳适应法
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
	case 3:// 最坏适应法
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
		cout << "无效选项，请重新选择！" << endl;
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
	cout << "当前内存状态：" << endl;
	cout << setw(20) << "起始地址" << setw(20) << "大小" << setw(20) << "状态" << endl;

	for (const auto& block : memoryBlocks) {
		cout << setw(20) << block.start << setw(20) << block.size
			<< setw(20) << (block.isFree ? "空闲" : "已占用") << endl;
	}

	cout << "已分配的进程：" << endl;
	cout << setw(20) << "进程ID" << setw(20) << "起始地址" << setw(20) << "大小" << endl;

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
			memoryBlocks[i].size += memoryBlocks[i + 1].size;  // 合并大小
			memoryBlocks.erase(memoryBlocks.begin() + i + 1);  // 删除后一个块
			--i; // 检查合并后的块是否还可以继续合并
		}
	}
	 
}
