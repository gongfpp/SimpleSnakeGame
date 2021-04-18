#include "stdio.h"
#include "stdlib.h"//包涵rand()函数 
#include "conio.h"//包涵kbhit()函数 
#include "windows.h"//包涵gotoxy ()函数 
#include "time.h"//包涵时间函数time()，用来给rand取时间种子 

const int high=20;
const int width=50 ;
int display[high][width];//地图大小
int head_x,head_y;//蛇头位置
int head_vx,head_vy;//蛇移动速度（主要是取方向） 
int suger_x,suger_y;//糖位置
int lenth;//蛇长度 
bool alive;//还活着么 
//全局变量
 
//本游戏实现了贪吃蛇的基本玩法，
//整形二维数组为基础，蛇的移动和物件的显示均以数组元素的更替实现 
//二维数组作为地图，每个值为物件
//蛇头处数据为1，身体处数据依次以2、3、4···递增  空地为0
//食物处数据为-2,墙为-1（墙可以吃 ，墙的另一边才是死亡判断处，算小彩蛋吧） 
// 示例图 如下   左边为二维数组各元素数据 右边为实际显示 
// 0001000 	  二维数组	 @
// 000200-2   显示为     0   $
// 0003000				 0
// 0004000				 0
//
//  2020/4/16  共计约6小时  NBU 196003408   
 
void gotoxy(int x, int y) {//光标移动，用来刷新画面显示
	COORD pos = {x,y};	//相当于system("cls");但不会造成闪烁
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}
void initialize() { //初始化函数
	srand((unsigned)time(NULL));//时间为种子 为rand取种子
	
	lenth=1; alive=1;
	suger_x=rand() %(width-4)+2;
	suger_y=rand() %(high-4)+2;
	head_x=width/2;head_vx=0;
	head_y=high/2;head_vy=0;
	
	while(head_x==suger_x&&head_y==suger_y)	//避免糖与蛇重叠
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
void show() { 	//画面显示函数
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
	printf("当前得分：%d   ",lenth-1);
}
void update_without() {//赋值显示无关（数据处理有关）的更新
	head_x=head_x+head_vx;
	head_y=head_y+head_vy;
	//蛇头前进 
	if(display[head_y][head_x]>1)	alive=0;//撞自己了 
	if(head_x>=width||head_x<0||head_y>high||head_y<0)	alive=0;
	//冲破束缚的代价 
	
	if(head_x==suger_x&&head_y==suger_y){//甜了自己一口 
		lenth++;//  
		while(display[suger_y][suger_x]!=0){
			suger_x=rand()%(width-2)+1;
			suger_y=rand()%(high-2)+1;
		}
		display[suger_y][suger_x]=-2;
	}
	if(display[head_y][head_x]==-1)
		lenth++;//该死的墙头蛇吃着资本主义的糖 
	
}
void update_with() {//与数组赋值显示有关的更新
	for(int i=0; i<high; i++) {
		for(int j=0; j<width; j++) {
			if(display[i][j]>0&&display[i][j]<=lenth)
				display[i][j]++;//蛇身前进 
			if(head_x==j&&head_y==i)
				display[i][j]=1;// 蛇头前进 
			if(display[i][j]>lenth)
				display[i][j]=0;//蛇尾前进 
			
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
	//你控制的不是头  是头的方向！！ 
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
	 FOREGROUND_INTENSITY | FOREGROUND_RED);//设置文本输出红色 
	printf(" WASTED \a"); //neta自 近10年最佳游戏 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
	 FOREGROUND_INTENSITY);//将文本输出颜色还原 
	Sleep(1000) ;
	system("pause");
}
