#include "MemoryManager.h"

int main() {
	int totalMemory, choice, pid, size, method;

	cout << "请输入总内存大小: ";
	cin >> totalMemory;

	MemoryManager manager(totalMemory);

	while (true) {
		cout << "\n1. 分配内存\n2. 回收内存\n3. 显示内存状态\n4. 清屏\n0. 退出\n请选择操作: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "请输入内存大小: ";
			cin >> size;
			cout << "请选择分配方式 (1: 最先适应, 2: 最佳适应, 3: 最坏适应): ";
			cin >> method;
			if (method > 3 || method < 1) {
				cout << "选择不存在" << endl;
			}
			if (manager.allocate(size, method)) {
				cout << "进程 " <<manager.getPid() << " 分配成功，大小: " << size << endl;
			}
			else {
				cout << "进程 " << manager.getPid() << " 分配失败，内存不足。" << endl;
			}
			break;
		case 2:
			cout << "请输入回收的进程ID: ";
			cin >> pid;
			if (manager.deallocate(pid)) {
				cout << "进程 " << pid << " 回收成功。" << endl;
			}
			else {
				cout << "进程 " << pid << " 回收失败，未找到。" << endl;
			}
			break;
		case 3:
			manager.display();
			break;
		case 4:
			system("cls");
			break;
		case 0:
			return 0;
		default:
			cout << "无效选项，请重新选择！" << endl;
			break;
		}
	}
}