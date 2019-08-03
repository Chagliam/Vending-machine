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
		printf("文件出错！");
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
	if (choice == -1)//进入管理者系统
		return -1;
	else if (choice == -2)//退出系统
		return -2;
	else if (choice == -3)//选择商品后不购买
		return -3;
	else if (payment(choice, goods) == 0)//正常购买
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
	
	//输入产品编号
	do {
		printf("请输入产品编号(1~28)：  ");
		rewind(stdin);
		if (scanf("%d", &choice) != 1)
		{
			printf("\n请输入一个1~28的整数!\n\n");
		}
		else if ((choice < 1 || choice>28) && choice != 0 && choice != -1)
			printf("\n请输入一个1~28的整数!\n\n");
		else if (choice == 0)
			return -1;
		else if (choice == -1)
			return -2;
	} while (choice < 1 || choice>28&&choice != 0 && choice != -1);
	choice--;
	if (goods[choice].amout == 0)
	{
		intelli_recommend(choice, goods);
		printf("\n按回车键返回");
		getchar();
		getchar();
		
		return -3;
		//select_product(goods);
	}
	else {
		printf("\n商品名称：%4s\t   商品价格：%.2f\n\n确定购买？(1-是，2-否)    ", goods[choice].name, goods[choice].price);
			
		//确定是否购买
		do {
			rewind(stdin);
			if (scanf("%d", &option) != 1)
			{
				printf("请输入1或2!\n\n");
			}
			if (option != 1 && option != 2)
				printf("请输入1或2!\n\n");
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
	//选择支付方式
	do {
		printf("1-微信支付\t2-支付宝支付\t3-现金支付\n");
		printf("\n请选择支付方式：  ");
		rewind(stdin);
		if (scanf("%d", &option) != 1)
		{
			printf("\n请输入一个1~3的整数!\n\n");
		}
		if (option < 1 || option>3)
			printf("\n请输入一个1~3的整数!\n\n");
	} while (option < 1 || option>3);
	
	//结账
	switch (option)
	{
	case 1: printf("\n请扫描二维码（按任意键继续）\n\n");
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
		printf("支付成功！\n");
		break;
	case 2: printf("\n请扫描二维码（按任意键继续）\n");
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
		printf("支付成功！\n");
		break;
	case 3: printf("\n请输入你投入的纸币面额：");
		do {
			rewind(stdin);
			if (scanf("%f", &money) != 1)
			{
				
				printf("\n请输入1~100之间的数:  ");
			}
			else if (money < 0 || money > 100)
				printf("\n请输入1~100之间的数   ");
				
		} while (money < 0 || money > 100);
		if (money < goods[choice].price)
		{
			printf("支付失败！钱不够\n");
			printf("请收好您的%.2f块钱\n",money);
			return 1;
		}
		else
		{
			printf("支付成功！\n");
			readmoney = read_money();
			soldmoney1 = goods[choice].price + readmoney+ soldmoney1;
			
			if (money == goods[choice].price)
				printf("请慢走\n");
			printf("请收好您的零钱，一共%.2f元\n", money - goods[choice].price);
			write_money(soldmoney1);
		}
	}
	printf("\n按回车键继续\n");
	getchar();
	return 0;
}

//5
void intelli_recommend(int choice, products goods[])
{
	int i;
	if (goods[choice].amout == 0)
	{
		puts("\n商品已售空，我们还有以下同类商品:");
		for (i = 0; i < SIZE; i++)
		{
			if (goods[i].kind == goods[choice].kind&&goods[i].amout > 0)
			{
				if (i != choice)
				{
					printf("编号：%d\t名称：%s\t价格：%.2f\n",goods[i].num, goods[i].name,goods[i].price);
				}
			}
		}
	}
	printf("\n");
}
