#ifndef  Init_pcb_process
#define Init_pcb_process

//定义pcb和p和v操作
/*
定义PCB运行时的状态变量  
cpu（自己的程序）通过状态来决定是否来运行这个程序
*/
enum STATUS {  
	PCB_RUNNING,
	PCB_WAIT,
	PCB_READY,
	PCB_FINISH
};
struct PCB_p {
	char * pcb_name;//程序的名字
	STATUS status;//程序的状态
	char * reason ;//中断或者wait的原因
	void (* fun_process [4] )(void ); //指向要处理的代码数据
	int  debug;//程序指令计数器
};
typedef struct PCB_p * PCB;
void P_pcb_pro();// p操作 
void V_pcb_pro();// v操作
void P_pcb_con();// p操作
void V_pcb_con();// v操作
void put();    
void get();
void print_pro();
void print_con();


#endif