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

void read_goods_list(products goods[]);//�������������Ʒ���ݵ�����
void output_product(products goods[]);//�������������Ʒ��Ϣ��չʾ
int purchase_process(products goods[]);//���ڽ��й�������
int select_product(products goods[]);//��������û�����Ʒ��ѡ��չʾ����Ʒ��ϸ��Ϣ
int payment(int choice, products goods[]);//���ڶ�ά��֧�����ֽ����������ļ�¼
void modify_list(int choice, products goods[]);//�����޸����ۺ����Ʒ�嵥�ļ�
void write_sold_list(int choice, products goods[]);//���ڼ�¼ÿһ����������γ���־
void refresh_goods_list(products goods[]);//���ڸ�����Ʒ��Ϣ����ļ���
void administration(products goods[]);//���ڹ���Ա����ϵͳ
int menu();//��ӡ����Ա�˵�
void supplement(int choice, products goods[]);//���ڶԻ����ۿպ�Ĳ���
void addnew(int choice, products goods[]);//����ɾ�����ڻ��������ú�����һ����Ʒ
void pick_outdate(products goods[]);//���ڼ�������Ʒ�����Ѹ�����Ա���²���
void pick_lowsold(products goods[]);//���ڼ�������͵���Ʒ�����Ѹ�����Ա����
void intelli_recommend(int choice, products goods[]);
void manage_sold_list();//������ʾ��������Ʒ
void write_money(float soldmoeny1);//����д���ֽ�����
float read_money();//���ڶ����ֽ�����

#endif