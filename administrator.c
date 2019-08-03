#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#include<time.h>
#include"function.h"

//3.3
void modify_list(int choice, products goods[])
{
	goods[choice].amout--;
	goods[choice].sold++;
	write_sold_list(choice, goods);
	refresh_goods_list(goods);
}

//3.3.1
void write_sold_list(int choice, products goods[])
{
	time_t t;
	struct tm * lt;
	time(&t);//��ȡUnixʱ���
	lt = localtime(&t);//תΪʱ��ṹ
	FILE *fp;
	fp = fopen("sold.dat", "a+");
	if (!fp)
	{
		puts("�ļ�����!");
		exit(1);
	}

	fprintf(fp, "%d %s      %.2f %d %d %d\n", goods[choice].num, goods[choice].name, goods[choice].price, lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday);
	fclose(fp);

}

//3.3.2
void refresh_goods_list(products goods[])
{
	FILE *fp;
	int i;
	fp = fopen("goods.dat", "w+");
	if (!fp)
	{
		printf("�ļ���д����");
		exit(1);
	}
	for (i = 0; i < SIZE; i++)
	{
		fprintf(fp, "%d %d %d %s %.2f %d %d %d %d \n", goods[i].kind, goods[i].amout, goods[i].sold,
			goods[i].name, goods[i].price, goods[i].date[0], goods[i].date[1], goods[i].date[2], goods[i].num);
	}
	fclose(fp);
}

//4
void administration(products goods[])
{
	char password[60];
	int option, count = 3;
	float money;
	float choice;
	printf("\n���������Ա���룺 ");
	scanf("%s", password);
	while (strcmp(password, "123456") != 0)
	{
		count--;
		printf("\n�������!�㻹��%d�λ���\n", count);
		if (count == 0)
			break;
		printf("\n���������Ա���룺 ");
		scanf("%s", password);
	}
	if (count == 0)
		exit(1);
	else
	{
		if (strcmp(password, "123456") == 0)
		{
			option = menu();
			switch (option)
			{
			case 1: supplement(option, goods);
				refresh_goods_list(goods);
				break;
			case 2:pick_outdate(goods);
				refresh_goods_list(goods);
				break;
			case 3:pick_lowsold(goods);
				refresh_goods_list(goods);
				break;
			case 4:manage_sold_list();
				refresh_goods_list(goods);
				break;
			case 5:money = read_money();
				printf("\n�������ﻹ��%.2fԪ\n", money);
				do {
					printf("\n������Ҫȡ����Ǯ     ");
					scanf("%f", &choice);

					if (choice >= money/2)
						printf("��ȡ��һ��\n");
				} while (choice >= money/2);
				money = money - choice;
				write_money(money);
				printf("\n���س�������\n");
				getchar();
				getchar();
			}
		}
	}
	
}

//4.1
int menu()
{
	int choice;
	do {
		printf("\n1- ������ 2��������Ʒ��3-�����������Ʒ�� 4-��ʾ�۳��� 5-ȡǮ    ");
		rewind(stdin);
		if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5))
			printf("\n������һ��1~5������!\n");
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5);
	return choice;
}

//4.2
void supplement(int choice, products goods[])
{
	int i;
	int option;
	int flag = 0;
	for (i = 0; i < SIZE; i++)
	{
		if (goods[i].amout <= 2)
		{
			printf("\n��Ҫ��������Ʒ��%s, ʣ��������%d\n", goods[i].name, goods[i].amout);
			flag = 1;
		}
	}

	if (flag != 0)
	{
		do {
			puts("\nȷ����������1-�� �� 0-�� ");
			rewind(stdin);
			if (scanf("%d", &option) != 1 || (option != 0 && option != 1))
				printf("\n������1��0!!");
		} while (option != 0 && option != 1);

		if (option == 1)
		{
			for (i = 0; i < SIZE; i++)
			{
				if (goods[i].amout <= 2)
					goods[i].amout = 10;
			}
			puts("�������");
		}
	}
	else
		puts("\nû����Ҫ��������Ʒ\n");
	printf("\n���س�������\n");
	getchar();
	getchar();
}

//4.2.1
void addnew(int choice, products goods[])
{
	printf("��������Ҫ�����ϼܵ���Ʒ:(���� ���� ���� �۸� ����ʱ���� �� ��)\n\n");
	scanf("%d %d %s %f %d %d %d %d %d", &goods[choice].kind, &goods[choice].amout, goods[choice].name,
		&goods[choice].price, &goods[choice].date[0], &goods[choice].date[1], &goods[choice].date[2]);
}

//4.3
void pick_outdate(products goods[])
{
	int i, flag = 0;
	time_t t;
	struct tm * lt;
	time(&t);//��ȡUnixʱ���
	lt = localtime(&t);//תΪʱ��ṹ
	//��Ʒ���������²���
	for (i = 0; i < SIZE; i++){
		if (goods[i].date[0] < lt->tm_year + 1900){
			printf("%s��Ʒ�ѹ��ڣ����Զ�����\n", goods[i].name);
			goods[i].amout = 10;
			goods[i].date[0]++;
			flag = 1;
			break;
		}
		else if (goods[i].date[0] == lt->tm_year + 1900 && goods[i].date[1] < lt->tm_mon + 1){
			printf("%s��Ʒ�ѹ��ڣ����Զ�����\n", goods[i].name);
			goods[i].amout = 10;
			goods[i].date[0]++;
			flag = 1;
			break;
		}
		else if (goods[i].date[0] == lt->tm_year + 1900 && goods[i].date[1] == lt->tm_mon + 1 && goods[i].date[2] < lt->tm_mday){
			printf("%s��Ʒ�ѹ��ڣ����Զ�����\n", goods[i].name);
			goods[i].amout = 10;
			goods[i].date[0]++;
			flag = 1;
			break;
		}
	}

	if (flag == 0)
		printf("�޹�����Ʒ\n");
	printf("\n���س�������\n");
	getchar();
	getchar();
}

//4.4
void pick_lowsold(products goods[])
{
	int i, count = 0;
	int option;
	for (i = 0; i < SIZE; i++)
	{
		count += goods[i].sold;
	}

	if (count >= 100)
	{
		if (goods[i].sold / count < 0.00714)//ƽ��ÿ����Ʒѡ���ĸ���*0.2,ԶС��ƽ��ֵ
		{
			puts("����Ʒ�������ͣ���������Ʒ�����������Ʒ");
			puts("0-ȡ����1-����");
			do {
				scanf("%d", &option);
				if (option != 0 && option != 1)
				{
					puts("������1��0");
					puts("0-ȡ����1-����");
				}
			} while (option != 0 && option != 1);
			if (option == 1)
				addnew(i, goods);
		}
	}
	else
		printf("�������ݲ����Լ��㣬�����ʱ��������\n");
	printf("\n���س�������\n");
	getchar();
	getchar();
}

//4.5
void write_money(float soldmoney1)
{
	FILE *fp;
	fp = fopen("soldmoney.txt", "w");
	if (!fp)
	{
		puts("�ļ�����!");
		exit(1);
	}
	fprintf(fp, "%.2f\n", soldmoney1);
	fclose(fp);
}

float read_money()
{
	float soldmoney1;
	FILE *fp;
	fp = fopen("soldmoney.txt", "r");
	if (!fp)
	{
		puts("�ļ�����!");
		exit(1);
	}
	fscanf(fp, "%f", &soldmoney1);
	fclose(fp);
	return soldmoney1;
}

//4.6
void manage_sold_list()
{
	int flag = 0, choice = 0,find = 0;
	int option, n;
	FILE *fpsold,*fpgoods;
	products *start, *pre, *cur, *next, *end, *temp;
	sold *head;
	sold *p, *s, *q, *m;

	//sold�����д��
	head = (sold *)malloc(sizeof(sold));
	if (head == NULL)
		exit(1);
	head->next = NULL;
	s = head;
	if ((fpsold = fopen("sold.dat", "r")) == NULL) {
		printf("�����ļ���ʧ�ܣ���\n");
		return;
	}
	printf("\n");
	while (!feof(fpsold)) {
		p = (sold *)malloc(sizeof(sold));
		fscanf(fpsold, "%d %s %f %d %d %d\n", &p->num, &p->name, &p->price, &p->date[0], &p->date[1], &p->date[2]);
		s->next = p;
		s = p;
		flag++;
	}
	s->next = NULL;
	fclose(fpsold);

	//��ʾ��¼�����Ƿ����
	if (flag > 200)
	{
		printf("\n���ۼ�¼���࣬�Ƿ���գ�<1-�ǣ� 0-��>       ");
		scanf("%d", &option);
		if (option == 1)
		{
			if ((fpsold = fopen("sold.dat", "w")) == NULL) {
				printf("�����ļ���ʧ�ܣ���\n");
				return;
			}
			fclose(fpsold);
		}
	}

	//sold��ʾ
	q = head->next;
	printf("��Ʒ���  ��Ʒ����\t��Ʒ�۸� \t��Ʒ��������\n");
	while (q != NULL) {
		printf("%d \t%8s \t%.2f  \t\t%d /%d /%d\n", q->num, q->name, q->price, q->date[0], q->date[1], q->date[2]);
		q = q->next;
	}
	printf("\n��Ҫ���������� 1, ��Ҫ������������� 2�����������˳���     ");
	scanf("%d", &choice);

	//����������
	if (choice == 2)
	{
		//goods�����д��
		start = (products *)malloc(sizeof(products));
		if (start == NULL)
			exit(1);
		start->next = NULL;
		pre = start;
		if ((fpgoods = fopen("goods.dat", "r")) == NULL) {
			printf("�����ļ���ʧ�ܣ���\n");
			return;
		}

		while (!feof(fpgoods)) {
			cur = (products *)malloc(sizeof(products));
			fscanf(fpgoods, "%d %d %d %s %f %d %d %d %d \n", &pre->kind, &pre->amout, &pre->sold,
				pre->name, &pre->price, &pre->date[0], &pre->date[1], &pre->date[2], &pre->num);
			pre->next = cur;
			if (!feof(fpgoods))
				pre = cur;
		}
		pre->next = NULL;
		fclose(fpgoods);

		//�����bubblesort
		end = NULL;
		//������ͷ��ʼ����Сֵ�����ƶ�
		while (start->next != end)
		{
			for (pre = start, cur = pre->next, next = cur->next; next != end; pre = pre->next, cur = cur->next, next = next->next)
			{
				//���ڵĽڵ�Ƚ�
				if (cur->sold < next->sold)
				{
					cur->next = next->next;
					pre->next = next;
					next->next = cur;
					temp = next;
					next = cur;
					cur = temp;
				}
			}
			end = cur;
		}
		pre = start->next;
		printf("\n��Ʒ���  ��Ʒ����\t��Ʒ�۸� \t��Ʒ����\n");
		while (pre != NULL) {

			printf("%d \t%8s \t%.2f  \t\t%d\n", pre->num, pre->name, pre->price, pre->sold);
			pre = pre->next;
		}
	}
	
	//����
	if (choice == 1)
	{
		//����
		printf("\n�����������Ʒ�ı��:      ");
		scanf("%d", &n);
		if (head == NULL)
			exit(1);
		else
		{
			m = head->next;
			while (m != NULL)
			{
				if (n == m->num)
				{
					printf("%d \t%8s \t%.2f\t%d/%d/%d\n", m->num, m->name, m->price, m->date[0], m->date[1], m->date[2]);
					find = 1;
				}
				m = m->next;
			}
			if (find == 0)
				printf("\nδ�ҵ�\n");
		}
	} 
	printf("\n���س�������\n");
	getchar();
	getchar();
}
