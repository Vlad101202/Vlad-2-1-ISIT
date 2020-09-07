#include  <stdio.h>
#include "Hash_Twin_Chain.h"
#include <iostream>
using namespace std;
unsigned char rand8[256];
struct AAA
{
	int key;
	char* mas;
	AAA(int k, char* z) //����������� � �����������
	{
		key = k;
		mas = z;
	}
	AAA()//����������� ��� ����������
	{
		key = 0;
		mas = (char*)"";
	}
};
//-------------------------------
int hf(void* d) // ������� ��������� �����	
{
	double A;
	A = (sqrt(5.0f) - 1.0f) / 2.0f;
	std::cout << A;
	AAA* f = (AAA*)d;
	return  f->key * A;
}
int hf1(void* d) // ������� ��������� �����
{
	AAA* f = (AAA*)d;
	unsigned char h = 0;
	char i = 0;
	while (*(f->mas))
	{
		h = rand8[h ^ *(f->mas)++];
		i++;
	}
	f->mas -= i;
	return h;
}
//-------------------------------
void AAA_print(listx::Element* e) // ������� ������ ����� � �������� 
{
	std::cout << ((AAA*)e->data)->key << '-' << ((AAA*)e->data)->mas << " / ";
}
//-------------------------------
int main()
{
	cout << "Pull request" << endl;    //text here 
	srand(NULL);
	setlocale(LC_ALL, "rus");
	int current_size = 7;
	cout << "������� ������ ���-�������" << endl;
	cin >> current_size;
	for (int i = 0; i < 256; i++)
		rand8[i] = rand() % 255;
	hashTC::Object H = hashTC::create(current_size, hf); //�������� ������� 
	int choice; // ���������� ��� ������ 
	int k;
	for (;;)
	{
		cout << endl << "1 - ����� ���-�������" << endl;
		cout << "2 - ���������� ��������" << endl;
		cout << "3 - �������� ��������" << endl;
		cout << "4 - ����� ��������" << endl;
		cout << "0 - �����" << endl;
		cout << "�������� �����" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:  exit(0);
		case 2: {	  AAA* a = new AAA; // ��������� ������
			char* str = new char[20]; //���������� 
			a->key = rand() % 1000 + 1;
			cout << "����� ������: " << a->key << endl;
			cout << "������� ��� ��������" << endl;
			cin >> str;
			a->mas = str;
			H.insert(a); //������� ���������� � ������� 
		}
			  break;
		case 1: H.Scan(); // ������� ������ ������
			break;
		case 3: {	  AAA* b = new AAA;
			cout << "������� ����� ������" << endl;
			cin >> k;
			b->key = k;
			H.deleteByData(b); // ������� �������� 
		}
			  break;
		case 4: AAA * c = new AAA;
			cout << "������� ����� ������" << endl;
			cin >> k;
			c->key = k;
			if (H.search(c) == NULL) //����� �������� 
				cout << "������ �� �������" << endl;
			else
			{
				AAA_print(H.search(c));
				cout << endl;
			}
			break;
		}
	}
	return 0;
}
