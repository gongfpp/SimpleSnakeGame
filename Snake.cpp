#include "stdio.h"
#include "stdlib.h"//����rand()���� 
#include "conio.h"//����kbhit()���� 
#include "windows.h"//����gotoxy ()���� 
#include "time.h"//����ʱ�亯��time()��������randȡʱ������ 

const int high=20;
const int width=50 ;
int display[high][width];//��ͼ��С
int head_x,head_y;//��ͷλ��
int head_vx,head_vy;//���ƶ��ٶȣ���Ҫ��ȡ���� 
int suger_x,suger_y;//��λ��
int lenth;//�߳��� 
bool alive;//������ô 
//ȫ�ֱ���
 
//����Ϸʵ����̰���ߵĻ����淨��
//���ζ�ά����Ϊ�������ߵ��ƶ����������ʾ��������Ԫ�صĸ���ʵ�� 
//��ά������Ϊ��ͼ��ÿ��ֵΪ���
//��ͷ������Ϊ1�����崦����������2��3��4����������  �յ�Ϊ0
//ʳ�ﴦ����Ϊ-2,ǽΪ-1��ǽ���Գ� ��ǽ����һ�߲��������жϴ�����С�ʵ��ɣ� 
// ʾ��ͼ ����   ���Ϊ��ά�����Ԫ������ �ұ�Ϊʵ����ʾ 
// 0001000 	  ��ά����	 @
// 000200-2   ��ʾΪ     0   $
// 0003000				 0
// 0004000				 0
//
//  2020/4/16  ����Լ6Сʱ  NBU 196003408   
 
void gotoxy(int x, int y) {//����ƶ�������ˢ�»�����ʾ
	COORD pos = {x,y};	//�൱��system("cls");�����������˸
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}
void initialize() { //��ʼ������
	srand((unsigned)time(NULL));//ʱ��Ϊ���� Ϊrandȡ����
	
	lenth=1; alive=1;
	suger_x=rand() %(width-4)+2;
	suger_y=rand() %(high-4)+2;
	head_x=width/2;head_vx=0;
	head_y=high/2;head_vy=0;
	
	while(head_x==suger_x&&head_y==suger_y)	//�����������ص�
		head_x=rand()%(width-2)+1,head_y=rand()%(high-2)+1;

	for(int i=0; i<high; i++) {
		for(int j=0; j<width; j++) {
			if(i==0||i==high-1||j==0||j==width-1)
				display[i][j]=-1;
			else if(head_x==j&&head_y==i)
				display[i][j]=1;
			else if(suger_x==j&&suger_y==i)
				display[i][j]=-2;
			else
				display[i][j]=0;
		}
	}
}
void show() { 	//������ʾ����
	gotoxy(0,0);
	//system("cls");
	for(int i=0; i<high; i++) {
		for(int j=0; j<width; j++) {
			if(display[i][j]==-1)
				printf("#");
			else if(display[i][j]==1)
				printf("@");
			else if(display[i][j]>1)
				printf("O");
			else if (display[i][j]==-2)
				printf("$");
			else if(display[i][j]==0)
				printf(" ");
		}
		printf("\n");
	}
	printf("��ǰ�÷֣�%d   ",lenth-1);
}
void update_without() {//��ֵ��ʾ�޹أ����ݴ����йأ��ĸ���
	head_x=head_x+head_vx;
	head_y=head_y+head_vy;
	//��ͷǰ�� 
	if(display[head_y][head_x]>1)	alive=0;//ײ�Լ��� 
	if(head_x>=width||head_x<0||head_y>high||head_y<0)	alive=0;
	//���������Ĵ��� 
	
	if(head_x==suger_x&&head_y==suger_y){//�����Լ�һ�� 
		lenth++;//  
		while(display[suger_y][suger_x]!=0){
			suger_x=rand()%(width-2)+1;
			suger_y=rand()%(high-2)+1;
		}
		display[suger_y][suger_x]=-2;
	}
	if(display[head_y][head_x]==-1)
		lenth++;//������ǽͷ�߳����ʱ�������� 
	
}
void update_with() {//�����鸳ֵ��ʾ�йصĸ���
	for(int i=0; i<high; i++) {
		for(int j=0; j<width; j++) {
			if(display[i][j]>0&&display[i][j]<=lenth)
				display[i][j]++;//����ǰ�� 
			if(head_x==j&&head_y==i)
				display[i][j]=1;// ��ͷǰ�� 
			if(display[i][j]>lenth)
				display[i][j]=0;//��βǰ�� 
			
		}
	}
}

void operate() {
	if(kbhit()) {
		int input=getch();
		switch (input) {
			case 'a':head_vx=-1;head_vy=0;break;
			case 's':head_vy=1;head_vx=0;break;
			case 'w':head_vy=-1;head_vx=0;break;
			case 'd':head_vx=1;head_vy=0;break;
		}
	}
	//����ƵĲ���ͷ  ��ͷ�ķ��򣡣� 
}
int main() {
	initialize();
	while(alive) {
		show(); 
		operate();
		update_without();
		update_with();
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
	 FOREGROUND_INTENSITY | FOREGROUND_RED);//�����ı������ɫ 
	printf(" WASTED \a"); //neta�� ��10�������Ϸ 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
	 FOREGROUND_INTENSITY);//���ı������ɫ��ԭ 
	Sleep(1000) ;
	system("pause");
}
