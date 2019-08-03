#pragma once
#ifndef _FUNCTION_H
#define _FUNCTION_H
#define SIZE 28

typedef struct product
{
	int num;
	int kind;
	int amout;
	int sold;
	char name[20];
	float price;
	int date[3];
	struct product *next;
}products;

typedef struct solditem {
	int num;
	char name[20];
	float price;
	int date[3];
	struct solditem *next;
}sold;

//float soldmoney1 = 0;

void read_goods_list(products goods[]);//用于完成所有商品数据的输入
void output_product(products goods[]);//用于完成所有商品信息的展示
int purchase_process(products goods[]);//用于进行购买流程
int select_product(products goods[]);//用于完成用户对商品的选择，展示该商品详细信息
int payment(int choice, products goods[]);//用于二维码支付及现金找零和收入的记录
void modify_list(int choice, products goods[]);//用于修改销售后的商品清单文件
void write_sold_list(int choice, products goods[]);//用于记录每一次销售情况形成日志
void refresh_goods_list(products goods[]);//用于更新商品信息存进文件夹
void administration(products goods[]);//用于管理员管理系统
int menu();//打印管理员菜单
void supplement(int choice, products goods[]);//用于对货物售空后的补给
void addnew(int choice, products goods[]);//用于删除过期或销量不好后新添一种商品
void pick_outdate(products goods[]);//用于检查过期商品并提醒给管理员重新补货
void pick_lowsold(products goods[]);//用于检查销量低的商品并提醒给管理员换货
void intelli_recommend(int choice, products goods[]);
void manage_sold_list();//用于显示已卖出商品
void write_money(float soldmoeny1);//用于写入现金收入
float read_money();//用于读出现金收入

#endif