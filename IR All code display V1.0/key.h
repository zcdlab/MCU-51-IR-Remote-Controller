int key ()
{
sbit key0 =P1^0;
sbit key1 =P1^1;
sbit key2 =P1^2;
sbit key3 =P1^3;
sbit key4 =P1^4;
sbit key5 =P1^5;
sbit key6 =P1^6;
sbit key7 =P1^7;
if(key0==0);return 0;
if(key1==0);return 1;
if(key2==0);return 2;
if(key3==0);return 3;
if(key4==0);return 4;
if(key5==0);return 5;
if(key6==0);return 6;
if(key7==0);return 7;
}