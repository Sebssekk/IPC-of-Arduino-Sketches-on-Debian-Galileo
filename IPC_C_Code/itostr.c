void itostr(int num,char* num_char)
{
  char dict[]={'0','1','2','3','4','5','6','7','8','9'};
  int i=0,x=0;
  char num_char1[10];
  while(num)
  {
    x=num%10;
    num_char1[i]=dict[x];
    num/=10;
    i+=1;
  }
  for (int e=0;e<i;e++)
  {
    num_char[e]=num_char1[i-1-e];
  }
}
