#include<reg51.h>
#include<intrins.h>
#include<stdlib.h>
#define N 3

sbit D0 = P0^0;
sbit D1 = P0^1;
sbit D2 = P0^2;
sbit D3 = P0^3;
sbit D4 = P0^4;
sbit D5 = P0^5;
sbit D6 = P0^6;
sbit D7 = P0^7;	//74hc573

sbit ADDR0 = P2^0;
sbit ADDR1 = P2^1;
sbit ADDR2 = P2^2;	//74hc138

sbit DS0 = P2^5;	
sbit SHCP = P2^3;	
sbit STCP = P2^4;	//74hc595

sbit Light_Con = P1^5;	//µÆ×Ü¿ª¹Ø

void performance();
void Timer0Init(void);
void Delay1ms();
void Delay1ms();

unsigned char dat_P0[24] = {0};
unsigned char InrpRand;
unsigned int cnt;
void main()	//2ms@22.1184MHz
{
	unsigned char i = 0;
	Timer0Init();
	EA = 1;
	ET0 = 1;
	while(1)
	{
		TR0 = 1;
		for(i=0;i<24;i++)
		{
			dat_P0[i] = rand() % 256;
		}
	}
	
}

int interuptTimer0() interrupt 1
{
	static unsigned int i = 0;
	TR0 = 0;
	TL0 = 0xCD;		//??????
	TH0 = 0xD4;		//??????
	cnt++;
	if(cnt>=8)
	{
		cnt = 0;
	}
	InrpRand = rand() % 8;
	Light_Con = 1;
	switch (InrpRand)
    {
	    case 0: ADDR2=0; ADDR1=0; ADDR0=0; i++; performance(); break;
	    case 1: ADDR2=0; ADDR1=0; ADDR0=1; i++; performance(); break;
	    case 2: ADDR2=0; ADDR1=1; ADDR0=0; i++; performance(); break;
	    case 3: ADDR2=0; ADDR1=1; ADDR0=1; i++; performance(); break;
	    case 4: ADDR2=1; ADDR1=0; ADDR0=0; i++; performance(); break;
			case 5: ADDR2=1; ADDR1=0; ADDR0=1; i++; performance(); break;
			case 6: ADDR2=1; ADDR1=1; ADDR0=0; i++; performance(); break;
	    case 7: ADDR2=1; ADDR1=1; ADDR0=1; i=0; performance(); break; 
	    default: break;
    }
}
void Timer0Init(void)		//2??@22.1184MHz
{
	AUXR |= 0x80;		//?????1T??
	TMOD &= 0xF0;		//???????
	TMOD |= 0x01;		//???????
	TL0 = 0x33;		//??????
	TH0 = 0x53;		//??????
	TF0 = 0;		//??TF0??
	TR0 = 1;		//???0????
}
void performance()
{
	unsigned int dat = 0x01;
	unsigned int i;
	unsigned char n=0;
	bit datds0;
	
	for(i=0;i<24;i++)
	{
		SHCP = 0;
		STCP = 0;
		datds0 = dat &0x01;
		DS0 = datds0;
		SHCP = 1;
		STCP = 1;
		dat>>=1;
		P0 = dat_P0[i];
}
	Light_Con = 0;

	

}
void Delay1ms()		//@22.1184MHz
{
	unsigned char i, j;

	i = 22;
	j = 128;
	do
	{
		while (--j);
	} while (--i);
}

