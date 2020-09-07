#pragma once
#include "Lists.h"
namespace hashTC
{
	struct Object
	{
		int size; // размер таблицы
		int(*FunKey)(void*); //Функция получения ключа
		listx::Object* Hash; // указатель типа Object пространства имен listx (список)

		Object(int Size, int(*f)(void*)) //конструктор
		{
			size = Size;
			FunKey = f;
			Hash = new listx::Object[Size]; // создание массива Object из size - 1 

		};
		int hashFunction(void* data);
		bool insert(void* data);
		listx::Element* search(void* data);
		bool deleteByData(void* data);
		void Scan();
	};
	Object create(int size, int(*f)(void*));
}