#include "bluetooth_ctrl.h"

static int fp;
void bluetooth_init()
{
	//这里犯了个错误，fp前面又用int fp这样申明了一下，导致这里的fp成了局部变量，全局的fp没有被赋值。
	fp=open("/dev/rfcomm0",O_RDWR|O_NOCTTY);
	printf("fp %d\n",fp);
	if(fp < 0)
	{
		printf("no bluetooth controller connect\n");
		return;
	}
	tcflush(fp,TCIOFLUSH); 

}

pthread_t p_bt;

void *p_bluetooth_ctrl(void *args)
{
	struct pollfd fdset;
	uint8_t val[2];
	int n;
	printf("bt thread\n");
	
	while(1){	
		n=read(fp,val,2);
		printf("read %d %c\n",n,val[0]);
		switch(val[0])
		{
			case 'A':	//forward
				Flag_Qian=1,Flag_Hou=0,Flag_Left=0,Flag_Right=0;
				break;
			case 'B':
			case 'C':	//right
			case 'D':
				Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=1;
				break;
			case 'E':	//back
				Flag_Qian=0,Flag_Hou=1,Flag_Left=0,Flag_Right=0;
				break;
			case 'F':	//left
			case 'G':	//left		
			case 'H':	//left
				Flag_Qian=0,Flag_Hou=0,Flag_Left=1,Flag_Right=0;
				break;
			case 'X':
				Flag_sudu=1;
				break;
			case 'Y':
				Flag_sudu=2;
				break;
			case 'Z':	//stop
			default:
				Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;
				break;
		}
	}
	return 0;
	
}

void bt_ready_to_get_cmd()
{
	if(fp>0)
	{
		int err;
		err=pthread_create(&p_bt,NULL,p_bluetooth_ctrl,NULL);
		printf("err %d\n",err);
		if(err !=0)
		{
			printf("create p_bt failed\n");
			
		}
	}
}