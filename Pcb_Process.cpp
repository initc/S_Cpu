// Pcb_Process.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Init_pcb_process.h"
#include <stdlib.h>
PCB producer ;//声明生产者 pcb
PCB consumer ;//声明消费者 pcb
int S1;//同步信号量
int S2;//同步信号量
char  array[10];//声明存储空间
int in ,out ;//声明生产者和消费者队列指示器
char pro_c;//生产者即将打印的字符
char con_c;//消费者即将打印的字符

void  init(){//初始化操作
	//初始化信号量  
	//S1,S2表示生产者和消费者对队列的操作许可
	S1=1;
	S2=0;
	//初始化队列
	in =0;
	out=0;
	//初始化PCB
	producer =(PCB) malloc(sizeof(struct PCB_p ));
	consumer=(PCB) malloc(sizeof(struct PCB_p ));
	producer->pcb_name="生产者";
	producer->reason="running";
	producer->debug=0;
	producer->status=PCB_READY;
	consumer->pcb_name="消费者";
	consumer->reason="running";
	consumer->debug=0;
	consumer->status=PCB_WAIT;
	//对生产者的函数进行初始化
	producer->fun_process[0]=P_pcb_pro; //第一步是进行p操作
	producer->fun_process[1]=get;       //获取字符(生产字符)
	producer->fun_process[2]=print_pro; //打印字符
	producer->fun_process[3]=V_pcb_con; //提醒消费者消费

	//对消费者的函数进行初始化
	consumer->fun_process[0]=P_pcb_con; //进行p操作
	consumer->fun_process[1]=put;       //获取字符(消费字符）
	consumer->fun_process[2]=print_con; //打印消费的字符
	consumer->fun_process[3]=V_pcb_pro; //提醒生产者进行生产

};

/*
主函数  此函数相当于cpu  

*/
int _tmain(int argc, _TCHAR* argv[])
{
	init();// 初始化
	int  count ; //一共输入多少字符
	// run为奇数时生产者运行   偶数时消费者运行
	int run=1;
	puts("输入字符进行操作-----列如  10 abcdefghip  注意数字和字符之间一个空格");
    scanf_s("%d",&count);
	getchar();
	int pro_count =count;//生产者最多可以生产的数目
	int con_count=count; //消费者可以最多消费的数目
	bool pro_finish =false;
	bool con_finish =false;
	//  cpu 不断循环执行  当所有字符消耗完时即结束
	while (true){
		
		if(run%2 ==1){
			// 生产者运行
			if(pro_count<=0){
				 // 生产者不能再进行生产
				producer->status=PCB_FINISH;
				if(!pro_finish)
				puts("-------------------生产者生产完成");
				pro_finish=true;
				if(con_finish)
					break;
				run++;
				continue;
			}
		int index = producer->debug; // 获取运行函数
		switch(index){
		case 0:
			if(producer->status==PCB_READY){
			// 当生产已经准备就绪时运行
			producer->fun_process[index]();
			if(producer->status==PCB_RUNNING){
				 //生产者可以运行下一步
				 producer->debug= (producer->debug+1)%4;
			}
		}
			break;
		case 1:
			if(producer->status==PCB_RUNNING){
				//进行生产 并且无论如何都可以进行下一步操作
				
				producer->fun_process[index]();
				producer->debug= (producer->debug+1)%4;
			

			}
			break;
		case 2:
			//进行打印操作 并且无论如何都可以进行下一步操作
				producer->fun_process[index]();
				producer->debug= (producer->debug+1)%4;
			break;
		case 3:
			//进行v操作 提醒消费者消费操作 并且无论如何都可以进行下一步操作
				producer->fun_process[index]();
				producer->debug= (producer->debug+1)%4;
			    pro_count--;
			break;
		}
		
		
		}else {
			// 消费者运行

			if(con_count<=0){
				 //消费者不能再进行生产
				consumer->status=PCB_FINISH;
				if(!con_finish)
				puts("-------------------消费者消费完成");
				con_finish=true;
				if(pro_finish)
					break;  // 生产者和消费者都已经完成  直接结束运行
				run++;
				continue;
			}
		int index = consumer->debug; // 获取运行函数
		switch(index){
		case 0:
			if(consumer->status==PCB_READY){
			// 当消费者已经准备就绪时运行
			consumer->fun_process[index]();
			if(consumer->status==PCB_RUNNING){
				 //消费者可以运行下一步
				consumer->debug= (consumer->debug+1)%4;
			}
		}
			break;
		case 1:
			if(consumer->status==PCB_RUNNING){
				//进行消费  并且无论如何都可以进行下一步操作
				consumer->fun_process[index]();
				consumer->debug= (consumer->debug+1)%4;
				
			}
			break;
		case 2:
			//进行打印操作 并且无论如何都可以进行下一步操作
				consumer->fun_process[index]();
				consumer->debug= (consumer->debug+1)%4;
			break;
		case 3:
			//进行v操作 提醒生产者操作 并且无论如何都可以进行下一步操作
				consumer->fun_process[index]();
				consumer->debug= (consumer->debug+1)%4;
				con_count--;
			break;
		}


		}
		run++;
	}
	puts("-----------模拟cpu完成");
	puts("-----------按回车键退出");
	getchar();
	getchar();
	
	return 0;
}

void P_pcb_pro(){  //对生产者的p操作 判生产者是否可以生产
	S1--;
	if(S1<0){
		producer->status=PCB_WAIT;

	}else {

		producer->status=PCB_RUNNING;//使之运行
	}

}
void V_pcb_con()// v操作  对消费者的v操作
{
	S2++;
	if(S2>0){//说明还有消费者还在等待  提醒一个消费者
		//但是由于目前此程序中只有一个消费
		consumer ->status=PCB_READY; 
	}

}
void P_pcb_con()// p操作  判断消费者是否可以消费
{   

	S2--;
	if(S1<0){
		consumer->status=PCB_WAIT;

	}else {

		consumer->status=PCB_RUNNING;//使之运行
	}


}
void V_pcb_pro()// v操作 对生产者的v操作  提醒生产者进行生产
{
	S1++;
	if(S1>0){
	
		producer ->status=PCB_READY; 
	}

}
/*
从console上获取一个字符存储在array中

*/
void get(){
	//scanf_s("%c",&pro_c);
	pro_c=getchar();

	array[in]=pro_c;
	in =(in+1)%10;
}
/*
从array的数组中获取一个字符  相当于消费者消费一个字符

*/
void put(){
	con_c=array[out];
	out=(out+1)%10;
}
void print_pro(){

	printf("------------生产者生产了 %c \n",pro_c);
}
void print_con(){

	printf("------------消费者消费了 %c \n",con_c);
}
