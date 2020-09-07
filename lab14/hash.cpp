#include <stdio.h>
#include "Hash.h"
#include <iostream>
int HashFunction(int key, int size, int p)    //Хеш-функция (модульная 9 вариант)
{
	return key % size;
}
int HashFunctionU(int key, int size, int p) // метод универсального хеширования (14 вариант)
{
	int h, a = 31415, b = 27183;
	for (h = 0; key != 0; key--, a = a * b % (size - 1))
		h = (a * h + key) % size;
	return (h < 0) ? (h + size) : h;
}
//-------------------------------
int Next_hash(int hash, int size, int p) //Следующий индекс массива (1 вариант квадратичный шаг)
{
	hash = (hash + 5 * p + 3 * p * p) % size;
	//hash=(hash+p)%size;//10 variant
	return  hash;
}
//-------------------------------
Object create(int size, int(*getkey)(void*)) //Созание хэш таблицы
{
	return *(new Object(size, getkey));
}
//-------------------------------
Object::Object(int size, int(*getkey)(void*))//конструктор хэш таблицы
{
	N = 0;
	this->size = size; //макимальный размер
	this->getKey = getkey; // функция взятия ключа
	this->data = new void* [size]; //массив структур 
	for (int i = 0; i < size; ++i)
		data[i] = NULL;
}
//-------------------------------
bool Object::insert(void* d) //вставка элементов в таблицу
{
	bool b = false;
	if (N != size)
		for (int i = 0, t = getKey(d), j = HashFunction(t, size, 0); // хеширование ключа
			i != size && !b;  j = Next_hash(j, size, ++i)) // пока i > максимального размера; j следующий индекс в соответствии с хешом 
			if (data[j] == NULL || data[j] == DEL)
			{
				data[j] = d;
				N++;
				b = true;
			}
	return b;
}
//-------------------------------
int Object::searchInd(int key) //Поиск по ключу
{
	int t = -1;
	bool b = false;
	if (N != 0)
		for (int i = 0, j = HashFunction(key, size, 0); data[j] != NULL && i != size && !b; j = HashFunction(key, size, ++i)) // хеширование ключа 
			if (data[j] != DEL)
				if (getKey(data[j]) == key)
				{
					t = j; b = true;
				}
	return t; //возврат индекса массива в котором совпал ключ
}
//-------------------------------
void* Object::search(int key) // Поиск по ключу
{
	int t = searchInd(key);
	return(t >= 0) ? (data[t]) : (NULL); //если элемент удален вернем null 
}
//-------------------------------
void* Object::deleteByKey(int key) // формальное Удаление элемента по ключу 
{
	int i = searchInd(key);
	void* t = data[i];
	if (t != NULL)
	{
		data[i] = DEL; // DEL = -1 знак "удаления"
		N--;
	}
	return t;
}
//-------------------------------
bool Object::deleteByValue(void* d) // Удаление по значению
{
	return(deleteByKey(getKey(d)) != NULL);
}
//-------------------------------
void Object::scan(void(*f)(void*)) // Вывод таблицы
{
	for (int i = 0; i < this->size; i++)
	{
		std::cout << " Элемент" << i;
		if ((this->data)[i] == NULL) // Не заполнен
			std::cout << "  пусто" << std::endl;
		else
			if ((this->data)[i] == DEL) // Удален
				std::cout << "  удален" << std::endl;
			else
				f((this->data)[i]); //Вызов функции вывода ААА
	}
}