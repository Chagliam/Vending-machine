#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#include<time.h>
#include"function.h"

//1
void read_goods_list(products goods[])
{
	FILE *fp;
	int i;
	fp = fopen("goods.dat", "rb+");
	if (!fp)
	{
		printf("�ļ�����");
		exit(1);
	}
	for (i = 0; i < SIZE; i++)
	{
		fscanf(fp, "%d %d %d %s %f %d %d %d %d\n", &goods[i].kind, &goods[i].amout, &goods[i].sold,
			goods[i].name, &goods[i].price, &goods[i].date[0], &goods[i].date[1], &goods[i].date[2], &goods[i].num);
	}
	fclose(fp);
}

//2
void output_product(products goods[])
{
	int i;
	puts("\t\t\t\t     WELCOME!");
	printf("\t=================================================================\n\t");
	for (i = 0; i < SIZE; i++)
	{
		printf("|%4d\t%-8s\t%.2f\t", goods[i].num, goods[i].name, goods[i].price);
		printf("|");
		if (i % 2 != 0)
			printf("\n\n\t");
	}
	printf("\n");
}

//3
int purchase_process(products goods[])
{
	int choice;
	choice = select_product(goods);
	if (choice == -1)//���������ϵͳ
		return -1;
	else if (choice == -2)//�˳�ϵͳ
		return -2;
	else if (choice == -3)//ѡ����Ʒ�󲻹���
		return -3;
	else if (payment(choice, goods) == 0)//��������
	{
		modify_list(choice,goods);
	}
	return 0;
}

//3.1
int select_product(products goods[])
{
	int choice = -1;
	int option = 0;
	
	//�����Ʒ���
	do {
		printf("�������Ʒ���(1~28)��  ");
		rewind(stdin);
		if (scanf("%d", &choice) != 1)
		{
			printf("\n������һ��1~28������!\n\n");
		}
		else if ((choice < 1 || choice>28) && choice != 0 && choice != -1)
			printf("\n������һ��1~28������!\n\n");
		else if (choice == 0)
			return -1;
		else if (choice == -1)
			return -2;
	} while (choice < 1 || choice>28&&choice != 0 && choice != -1);
	choice--;
	if (goods[choice].amout == 0)
	{
		intelli_recommend(choice, goods);
		printf("\n���س�������");
		getchar();
		getchar();
		
		return -3;
		//select_product(goods);
	}
	else {
		printf("\n��Ʒ���ƣ�%4s\t   ��Ʒ�۸�%.2f\n\nȷ������(1-�ǣ�2-��)    ", goods[choice].name, goods[choice].price);
			
		//ȷ���Ƿ���
		do {
			rewind(stdin);
			if (scanf("%d", &option) != 1)
			{
				printf("������1��2!\n\n");
			}
			if (option != 1 && option != 2)
				printf("������1��2!\n\n");
		} while (option != 1 && option != 2);
		printf("\n");
	}
	if (option == 2)
			choice = -3;
	return choice;
}

//3.2
int payment(int choice, products goods[])
{
	float soldmoney1 = 0;
	int option;
	float money;
	float readmoney;
	//ѡ��֧����ʽ
	do {
		printf("1-΢��֧��\t2-֧����֧��\t3-�ֽ�֧��\n");
		printf("\n��ѡ��֧����ʽ��  ");
		rewind(stdin);
		if (scanf("%d", &option) != 1)
		{
			printf("\n������һ��1~3������!\n\n");
		}
		if (option < 1 || option>3)
			printf("\n������һ��1~3������!\n\n");
	} while (option < 1 || option>3);
	
	//����
	switch (option)
	{
	case 1: printf("\n��ɨ���ά�루�������������\n\n");
		printf("\t\t\t*****  ******  **  *****\n");
		printf("\t\t\t***** ***  *** *** *****\n");
		printf("\t\t\t*****    *** ****  *****\n");
		printf("\t\t\t  *** *** **** ** **  **\n");
		printf("\t\t\t*  *** **  *  * ****  **\n");
		printf("\t\t\t  ******      ******   *\n");
		printf("\t\t\t  *  * *******   ** ** *\n");
		printf("\t\t\t  **     ***  ** *****  \n");
		printf("\t\t\t*****    **** **    *   \n");
		printf("\t\t\t****** ** * * ** **** **\n");
		printf("\t\t\t*****    ***** ***  ****\n\n\n");
		getchar();
		Sleep(2000);
		printf("֧���ɹ���\n");
		break;
	case 2: printf("\n��ɨ���ά�루�������������\n");
		printf("\t\t\t*****  ******  **  *****\n");
		printf("\t\t\t***** ***  *** *** *****\n");
		printf("\t\t\t*****    *** ****  *****\n");
		printf("\t\t\t  *** *** **** ** **  **\n");
		printf("\t\t\t*  *** **  *  * ****  **\n");
		printf("\t\t\t  ******      ******   *\n");
		printf("\t\t\t  *  * *******   ** ** *\n");
		printf("\t\t\t  **     ***  ** *****  \n");
		printf("\t\t\t*****    **** **    *   \n");
		printf("\t\t\t****** ** * * ** **** **\n");
		printf("\t\t\t*****    ***** ***  ****\n\n");
		getchar();
		Sleep(2000);
		printf("֧���ɹ���\n");
		break;
	case 3: printf("\n��������Ͷ���ֽ����");
		do {
			rewind(stdin);
			if (scanf("%f", &money) != 1)
			{
				
				printf("\n������1~100֮�����:  ");
			}
			else if (money < 0 || money > 100)
				printf("\n������1~100֮�����   ");
				
		} while (money < 0 || money > 100);
		if (money < goods[choice].price)
		{
			printf("֧��ʧ�ܣ�Ǯ����\n");
			printf("���պ�����%.2f��Ǯ\n",money);
			return 1;
		}
		else
		{
			printf("֧���ɹ���\n");
			readmoney = read_money();
			soldmoney1 = goods[choice].price + readmoney+ soldmoney1;
			
			if (money == goods[choice].price)
				printf("������\n");
			printf("���պ�������Ǯ��һ��%.2fԪ\n", money - goods[choice].price);
			write_money(soldmoney1);
		}
	}
	printf("\n���س�������\n");
	getchar();
	return 0;
}

//5
void intelli_recommend(int choice, products goods[])
{
	int i;
	if (goods[choice].amout == 0)
	{
		puts("\n��Ʒ���ۿգ����ǻ�������ͬ����Ʒ:");
		for (i = 0; i < SIZE; i++)
		{
			if (goods[i].kind == goods[choice].kind&&goods[i].amout > 0)
			{
				if (i != choice)
				{
					printf("��ţ�%d\t���ƣ�%s\t�۸�%.2f\n",goods[i].num, goods[i].name,goods[i].price);
				}
			}
		}
	}
	printf("\n");
}
