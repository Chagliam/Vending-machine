//��ʼ����0�������Աϵͳ������Ϊ12345
//����-1�˳�ϵͳ

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#include<time.h>
#include"function.h"

int main()
{
	int choice = 0;
	products goods[SIZE];
	system("color 0B");
	do {
		read_goods_list(goods);
		output_product(goods);
		if ((choice = purchase_process(goods)) == -1)
		{
			administration(goods);
		}
		Sleep(1000);
		system("cls");
	} while (choice != -2);
}