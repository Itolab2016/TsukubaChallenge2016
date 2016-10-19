#include <stdio.h>

main(){
  short s;
  long l;
  int  i;
  long long ll;
  unsigned char* dummy_ptr;

  dummy_ptr=(unsigned char*)(&l);


  printf("short %d\n",sizeof(s));
  printf("long %d\n",sizeof(l));
  printf("int %d\n",sizeof(i));
  printf("long long %d\n",sizeof(ll));


}
