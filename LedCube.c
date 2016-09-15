#include<reg51.h>
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
void Timer1Init(void);
void Change();

unsigned int dat_P0[8][3] = {
	0xDB, 0xB6, 0x6D,	//red
	0x49, 0x92, 0x24,	//yellow
	0xB6, 0x6D, 0xDB, //blue
	0x6D, 0xDB, 0xB6, //green
	0x24, 0x49, 0x92, //cyan-blue
	0x92, 0x24, 0x49, //purple
	0x00, 0x00, 0x00	//white
};
static unsigned int cnt1 = 0, cnt = 0;
static unsigned char n=0,m = 0;

void main()	//2ms@22.1184MHz
{
	Timer0Init();
  Timer1Init();
	EA = 1;
	ET0 = 1;
	ET1 = 1;
	while(1)
	{
		TR0 = 1;
	}
}

int interuptTimer0() interrupt 1
{
	static unsigned int i = 0;
	TL0 = 0x9A;		//??????
	TH0 = 0xA9;		//??????
	TR0 = 0;
	cnt++;
	switch (i)
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
int interruptTimer1() interrupt 3
{
	
	TL1 = 0x66;		//??????
	TH1 = 0x7E;		//??????
	cnt++;
	if(cnt >= 1000)
	{
		cnt = 0;
		m++;
		if(m>=8)
		{
			m = 0;
		}
	}
	
}
void Timer0Init(void)		//2??@22.1184MHz
{
	AUXR |= 0x80;		//?????1T??
	TMOD &= 0xF0;		//???????
	TMOD |= 0x01;		//???????
	TL0 = 0x66;		//??????
	TH0 = 0x7E;		//??????
	TF0 = 0;		//??TF0??	
}
void Timer1Init(void)		//1??@22.1184MHz
{
	AUXR |= 0x40;		//?????1T??
	TMOD &= 0x0F;		//???????
	TMOD |= 0x10;		//???????
	TL1 = 0x66;		//??????
	TH1 = 0x7E;		//??????
	TF1 = 0;		//??TF1??
	TR1 = 1;		//???1????
}
void performance()
{
	unsigned int i;
	
	for(i=0;i<24;i++)
	{	
		SHCP = 0;
		STCP = 0;		
		DS0 = i==0?1:0;
		SHCP = 1;
		STCP = 1;
		if(n >= 3)
		{
			n = 0;
		}
		P0 = dat_P0[m][n];
		n++;
	}
	Light_Con = 0;
	Delay1ms();
	Light_Con = 1;
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