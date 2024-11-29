#include "MemoryManager.h"

int main() {
	int totalMemory, choice, pid, size, method;

	cout << "���������ڴ��С: ";
	cin >> totalMemory;

	MemoryManager manager(totalMemory);

	while (true) {
		cout << "\n1. �����ڴ�\n2. �����ڴ�\n3. ��ʾ�ڴ�״̬\n4. ����\n0. �˳�\n��ѡ�����: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "�������ڴ��С: ";
			cin >> size;
			cout << "��ѡ����䷽ʽ (1: ������Ӧ, 2: �����Ӧ, 3: ���Ӧ): ";
			cin >> method;
			if (method > 3 || method < 1) {
				cout << "ѡ�񲻴���" << endl;
			}
			if (manager.allocate(size, method)) {
				cout << "���� " <<manager.getPid() << " ����ɹ�����С: " << size << endl;
			}
			else {
				cout << "���� " << manager.getPid() << " ����ʧ�ܣ��ڴ治�㡣" << endl;
			}
			break;
		case 2:
			cout << "��������յĽ���ID: ";
			cin >> pid;
			if (manager.deallocate(pid)) {
				cout << "���� " << pid << " ���ճɹ���" << endl;
			}
			else {
				cout << "���� " << pid << " ����ʧ�ܣ�δ�ҵ���" << endl;
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
			cout << "��Чѡ�������ѡ��" << endl;
			break;
		}
	}
}