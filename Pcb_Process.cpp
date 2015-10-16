// Pcb_Process.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Init_pcb_process.h"
#include <stdlib.h>
PCB producer ;//���������� pcb
PCB consumer ;//���������� pcb
int S1;//ͬ���ź���
int S2;//ͬ���ź���
char  array[10];//�����洢�ռ�
int in ,out ;//���������ߺ������߶���ָʾ��
char pro_c;//�����߼�����ӡ���ַ�
char con_c;//�����߼�����ӡ���ַ�

void  init(){//��ʼ������
	//��ʼ���ź���  
	//S1,S2��ʾ�����ߺ������߶Զ��еĲ������
	S1=1;
	S2=0;
	//��ʼ������
	in =0;
	out=0;
	//��ʼ��PCB
	producer =(PCB) malloc(sizeof(struct PCB_p ));
	consumer=(PCB) malloc(sizeof(struct PCB_p ));
	producer->pcb_name="������";
	producer->reason="running";
	producer->debug=0;
	producer->status=PCB_READY;
	consumer->pcb_name="������";
	consumer->reason="running";
	consumer->debug=0;
	consumer->status=PCB_WAIT;
	//�������ߵĺ������г�ʼ��
	producer->fun_process[0]=P_pcb_pro; //��һ���ǽ���p����
	producer->fun_process[1]=get;       //��ȡ�ַ�(�����ַ�)
	producer->fun_process[2]=print_pro; //��ӡ�ַ�
	producer->fun_process[3]=V_pcb_con; //��������������

	//�������ߵĺ������г�ʼ��
	consumer->fun_process[0]=P_pcb_con; //����p����
	consumer->fun_process[1]=put;       //��ȡ�ַ�(�����ַ���
	consumer->fun_process[2]=print_con; //��ӡ���ѵ��ַ�
	consumer->fun_process[3]=V_pcb_pro; //���������߽�������

};

/*
������  �˺����൱��cpu  

*/
int _tmain(int argc, _TCHAR* argv[])
{
	init();// ��ʼ��
	int  count ; //һ����������ַ�
	// runΪ����ʱ����������   ż��ʱ����������
	int run=1;
	puts("�����ַ����в���-----����  10 abcdefghip  ע�����ֺ��ַ�֮��һ���ո�");
    scanf_s("%d",&count);
	getchar();
	int pro_count =count;//��������������������Ŀ
	int con_count=count; //�����߿���������ѵ���Ŀ
	bool pro_finish =false;
	bool con_finish =false;
	//  cpu ����ѭ��ִ��  �������ַ�������ʱ������
	while (true){
		
		if(run%2 ==1){
			// ����������
			if(pro_count<=0){
				 // �����߲����ٽ�������
				producer->status=PCB_FINISH;
				if(!pro_finish)
				puts("-------------------�������������");
				pro_finish=true;
				if(con_finish)
					break;
				run++;
				continue;
			}
		int index = producer->debug; // ��ȡ���к���
		switch(index){
		case 0:
			if(producer->status==PCB_READY){
			// �������Ѿ�׼������ʱ����
			producer->fun_process[index]();
			if(producer->status==PCB_RUNNING){
				 //�����߿���������һ��
				 producer->debug= (producer->debug+1)%4;
			}
		}
			break;
		case 1:
			if(producer->status==PCB_RUNNING){
				//�������� ����������ζ����Խ�����һ������
				
				producer->fun_process[index]();
				producer->debug= (producer->debug+1)%4;
			

			}
			break;
		case 2:
			//���д�ӡ���� ����������ζ����Խ�����һ������
				producer->fun_process[index]();
				producer->debug= (producer->debug+1)%4;
			break;
		case 3:
			//����v���� �������������Ѳ��� ����������ζ����Խ�����һ������
				producer->fun_process[index]();
				producer->debug= (producer->debug+1)%4;
			    pro_count--;
			break;
		}
		
		
		}else {
			// ����������

			if(con_count<=0){
				 //�����߲����ٽ�������
				consumer->status=PCB_FINISH;
				if(!con_finish)
				puts("-------------------�������������");
				con_finish=true;
				if(pro_finish)
					break;  // �����ߺ������߶��Ѿ����  ֱ�ӽ�������
				run++;
				continue;
			}
		int index = consumer->debug; // ��ȡ���к���
		switch(index){
		case 0:
			if(consumer->status==PCB_READY){
			// ���������Ѿ�׼������ʱ����
			consumer->fun_process[index]();
			if(consumer->status==PCB_RUNNING){
				 //�����߿���������һ��
				consumer->debug= (consumer->debug+1)%4;
			}
		}
			break;
		case 1:
			if(consumer->status==PCB_RUNNING){
				//��������  ����������ζ����Խ�����һ������
				consumer->fun_process[index]();
				consumer->debug= (consumer->debug+1)%4;
				
			}
			break;
		case 2:
			//���д�ӡ���� ����������ζ����Խ�����һ������
				consumer->fun_process[index]();
				consumer->debug= (consumer->debug+1)%4;
			break;
		case 3:
			//����v���� ���������߲��� ����������ζ����Խ�����һ������
				consumer->fun_process[index]();
				consumer->debug= (consumer->debug+1)%4;
				con_count--;
			break;
		}


		}
		run++;
	}
	puts("-----------ģ��cpu���");
	puts("-----------���س����˳�");
	getchar();
	getchar();
	
	return 0;
}

void P_pcb_pro(){  //�������ߵ�p���� ���������Ƿ��������
	S1--;
	if(S1<0){
		producer->status=PCB_WAIT;

	}else {

		producer->status=PCB_RUNNING;//ʹ֮����
	}

}
void V_pcb_con()// v����  �������ߵ�v����
{
	S2++;
	if(S2>0){//˵�����������߻��ڵȴ�  ����һ��������
		//��������Ŀǰ�˳�����ֻ��һ������
		consumer ->status=PCB_READY; 
	}

}
void P_pcb_con()// p����  �ж��������Ƿ��������
{   

	S2--;
	if(S1<0){
		consumer->status=PCB_WAIT;

	}else {

		consumer->status=PCB_RUNNING;//ʹ֮����
	}


}
void V_pcb_pro()// v���� �������ߵ�v����  ���������߽�������
{
	S1++;
	if(S1>0){
	
		producer ->status=PCB_READY; 
	}

}
/*
��console�ϻ�ȡһ���ַ��洢��array��

*/
void get(){
	//scanf_s("%c",&pro_c);
	pro_c=getchar();

	array[in]=pro_c;
	in =(in+1)%10;
}
/*
��array�������л�ȡһ���ַ�  �൱������������һ���ַ�

*/
void put(){
	con_c=array[out];
	out=(out+1)%10;
}
void print_pro(){

	printf("------------������������ %c \n",pro_c);
}
void print_con(){

	printf("------------������������ %c \n",con_c);
}
