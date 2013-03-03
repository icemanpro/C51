/*点亮第一个发光二级管*/
#include <reg52.h>
sbit led1=P1^0;
void main()
{
	led1=0;
}