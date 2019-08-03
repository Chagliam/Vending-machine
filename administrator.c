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
	time(&t);//获取Unix时间戳
	lt = localtime(&t);//转为时间结构
	FILE *fp;
	fp = fopen("sold.dat", "a+");
	if (!fp)
	{
		puts("文件出错!");
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
		printf("文件读写错误！");
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
	printf("\n请输入管理员密码： ");
	scanf("%s", password);
	while (strcmp(password, "123456") != 0)
	{
		count--;
		printf("\n密码错误!你还有%d次机会\n", count);
		if (count == 0)
			break;
		printf("\n请输入管理员密码： ");
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
				printf("\n贩卖机里还有%.2f元\n", money);
				do {
					printf("\n请输入要取出的钱     ");
					scanf("%f", &choice);

					if (choice >= money/2)
						printf("请取少一点\n");
				} while (choice >= money/2);
				money = money - choice;
				write_money(money);
				printf("\n按回车键继续\n");
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
		printf("\n1- 补货； 2检查过期商品；3-检查销量低商品； 4-显示售出； 5-取钱    ");
		rewind(stdin);
		if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5))
			printf("\n请输入一个1~5的整数!\n");
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
			printf("\n需要补货的商品：%s, 剩余数量：%d\n", goods[i].name, goods[i].amout);
			flag = 1;
		}
	}

	if (flag != 0)
	{
		do {
			puts("\n确定补货？（1-是 ， 0-否） ");
			rewind(stdin);
			if (scanf("%d", &option) != 1 || (option != 0 && option != 1))
				printf("\n请输入1或0!!");
		} while (option != 0 && option != 1);

		if (option == 1)
		{
			for (i = 0; i < SIZE; i++)
			{
				if (goods[i].amout <= 2)
					goods[i].amout = 10;
			}
			puts("补货完成");
		}
	}
	else
		puts("\n没有需要补货的商品\n");
	printf("\n按回车键继续\n");
	getchar();
	getchar();
}

//4.2.1
void addnew(int choice, products goods[])
{
	printf("请输入你要重新上架的商品:(属性 数量 名称 价格 过期时间年 月 日)\n\n");
	scanf("%d %d %s %f %d %d %d %d %d", &goods[choice].kind, &goods[choice].amout, goods[choice].name,
		&goods[choice].price, &goods[choice].date[0], &goods[choice].date[1], &goods[choice].date[2]);
}

//4.3
void pick_outdate(products goods[])
{
	int i, flag = 0;
	time_t t;
	struct tm * lt;
	time(&t);//获取Unix时间戳
	lt = localtime(&t);//转为时间结构
	//商品过期则重新补货
	for (i = 0; i < SIZE; i++){
		if (goods[i].date[0] < lt->tm_year + 1900){
			printf("%s商品已过期，已自动补货\n", goods[i].name);
			goods[i].amout = 10;
			goods[i].date[0]++;
			flag = 1;
			break;
		}
		else if (goods[i].date[0] == lt->tm_year + 1900 && goods[i].date[1] < lt->tm_mon + 1){
			printf("%s商品已过期，已自动补货\n", goods[i].name);
			goods[i].amout = 10;
			goods[i].date[0]++;
			flag = 1;
			break;
		}
		else if (goods[i].date[0] == lt->tm_year + 1900 && goods[i].date[1] == lt->tm_mon + 1 && goods[i].date[2] < lt->tm_mday){
			printf("%s商品已过期，已自动补货\n", goods[i].name);
			goods[i].amout = 10;
			goods[i].date[0]++;
			flag = 1;
			break;
		}
	}

	if (flag == 0)
		printf("无过期商品\n");
	printf("\n按回车键继续\n");
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
		if (goods[i].sold / count < 0.00714)//平均每种商品选到的概率*0.2,远小于平均值
		{
			puts("此商品销量过低，若不是新品，建议更换商品");
			puts("0-取消，1-更换");
			do {
				scanf("%d", &option);
				if (option != 0 && option != 1)
				{
					puts("请输入1或0");
					puts("0-取消，1-更换");
				}
			} while (option != 0 && option != 1);
			if (option == 1)
				addnew(i, goods);
		}
	}
	else
		printf("销售数据不足以计算，请过段时间再来看\n");
	printf("\n按回车键继续\n");
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
		puts("文件出错!");
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
		puts("文件出错!");
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

	//sold链表的写入
	head = (sold *)malloc(sizeof(sold));
	if (head == NULL)
		exit(1);
	head->next = NULL;
	s = head;
	if ((fpsold = fopen("sold.dat", "r")) == NULL) {
		printf("销售文件打开失败！！\n");
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

	//提示记录过多是否清空
	if (flag > 200)
	{
		printf("\n销售记录过多，是否清空？<1-是， 0-否>       ");
		scanf("%d", &option);
		if (option == 1)
		{
			if ((fpsold = fopen("sold.dat", "w")) == NULL) {
				printf("销售文件打开失败！！\n");
				return;
			}
			fclose(fpsold);
		}
	}

	//sold显示
	q = head->next;
	printf("商品编号  商品名称\t商品价格 \t商品购买日期\n");
	while (q != NULL) {
		printf("%d \t%8s \t%.2f  \t\t%d /%d /%d\n", q->num, q->name, q->price, q->date[0], q->date[1], q->date[2]);
		q = q->next;
	}
	printf("\n需要查找请输入 1, 需要按销量排序输出 2，按其他键退出：     ");
	scanf("%d", &choice);

	//按销量排序
	if (choice == 2)
	{
		//goods链表的写入
		start = (products *)malloc(sizeof(products));
		if (start == NULL)
			exit(1);
		start->next = NULL;
		pre = start;
		if ((fpgoods = fopen("goods.dat", "r")) == NULL) {
			printf("销售文件打开失败！！\n");
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

		//链表的bubblesort
		end = NULL;
		//从链表头开始将较小值往后移动
		while (start->next != end)
		{
			for (pre = start, cur = pre->next, next = cur->next; next != end; pre = pre->next, cur = cur->next, next = next->next)
			{
				//相邻的节点比较
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
		printf("\n商品编号  商品名称\t商品价格 \t商品销量\n");
		while (pre != NULL) {

			printf("%d \t%8s \t%.2f  \t\t%d\n", pre->num, pre->name, pre->price, pre->sold);
			pre = pre->next;
		}
	}
	
	//查找
	if (choice == 1)
	{
		//查找
		printf("\n请输入查找商品的编号:      ");
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
				printf("\n未找到\n");
		}
	} 
	printf("\n按回车键继续\n");
	getchar();
	getchar();
}
