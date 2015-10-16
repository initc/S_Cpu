#ifndef  Init_pcb_process
#define Init_pcb_process

//����pcb��p��v����
/*
����PCB����ʱ��״̬����  
cpu���Լ��ĳ���ͨ��״̬�������Ƿ��������������
*/
enum STATUS {  
	PCB_RUNNING,
	PCB_WAIT,
	PCB_READY,
	PCB_FINISH
};
struct PCB_p {
	char * pcb_name;//���������
	STATUS status;//�����״̬
	char * reason ;//�жϻ���wait��ԭ��
	void (* fun_process [4] )(void ); //ָ��Ҫ����Ĵ�������
	int  debug;//����ָ�������
};
typedef struct PCB_p * PCB;
void P_pcb_pro();// p���� 
void V_pcb_pro();// v����
void P_pcb_con();// p����
void V_pcb_con();// v����
void put();    
void get();
void print_pro();
void print_con();


#endif