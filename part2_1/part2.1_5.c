/*用定时器0的方式1实现第一个发光管以200ms间隔闪烁，用定时器1的方式1实现数码管前两位59S循环计时。*/
#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit dula=P2^6;
sbit wela=P2^7;
sbit led1=P1^0;
uchar H0=(65536-45872)/256;
uchar L0=(65536-45872)%256;
uchar code table[]={
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};
void delayms(uint);
void display(uchar,uchar);
uchar num,num1,num2,shi,ge;
void main()
{
	TMOD=0x11; // 0001 0001  定时器0和 1 的工作方式为1
	TH0=H0;
	TL0=L0;
	TH1=TH0;
	TL1=TL0;
	
	EA=1; //开总中断
	ET0=1;//开定时器0
	ET1=1;//开定时器1
	TR0=1;//定时器0启动
	TR1=1;//定时器1启动
	
	while (1)
	{
		display(shi,ge);
   }
	
}

void delayms(uint xms)
{
	uint i,j;
	for (i=xms;i>0;i--)
	for (j=110;j>0;j--);
}

void T0_time() interrupt 1  //定时器0
{
	TH0=H0;
	TL0=L0;
	num1++;
	if (num1==4)
	{
		num1=0;
		led1=~led1;
}
}

void T1_time() interrupt 3
{
	TH1=H0;
	TL1=L0;
	num2++;
	if (num2==20)
	{
		num2=0;
		num++;
		if (num==60)
			num=0;
		shi=num/10;
		ge=num%10;
		
  }
}

void display(uchar shi,uchar ge)
{
	dula=1;
	P0=table[shi];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfe;  //1111 1110
	wela=0;
	delayms(5);
	
	
	
	dula=1;
	P0=table[ge];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfd;  //1111 1101
	wela=0;
	delayms(5);
	

	
}
