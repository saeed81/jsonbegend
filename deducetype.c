#include<stdio.h>
#include<stdlib.h>

#define Arraycount(a) (sizeof(a) / sizeof(a[0]))
#define StringArraycount(a) ((sizeof(a) / sizeof(a[0])) - 1)

int isdotnumeric (char c){
  int isnum = 0;
  char dotnumeric[] = ".0123456789";
  for (int i=0;i<=10;++i){
    if (c== dotnumeric[i]) isnum = 1;
  }
  return isnum;
}

int ishasonedot (char *str){
  if (str == NULL) return 0;
  char *tmp = str;
  int ncount = 0;
  int ir = 0;
  while(*tmp != '\0'){
    if (*tmp == '.') ncount++;
    tmp++;
  }
  ir = (ncount == 1) ? 1 : 0;
  return ir;
}

int isFloat(char *str){
  if (str == NULL) return 0;
  char *tmp = str, *tmp1 = NULL;
  int ir = 0;
  int inot = 0;
  if (ishasonedot(tmp)){
    if (*tmp == '+' || *tmp == '-'){
      if (*(tmp +1) != '\0' && isdotnumeric(*(tmp+1))){
	tmp1 = tmp + 1;
	while (*tmp1 != '\0' ){
	  if (isdotnumeric(*tmp1) && *tmp1 != 'f' && *tmp1 != 'F' && *tmp1 != 'e' && *tmp1 != 'E' ){
	      ir += 1;
	  }
	  if(!isdotnumeric(*tmp1) && *tmp1 != 'f' && *tmp1 != 'F' && *tmp1 != 'e' && *tmp1 != 'E' ){
	    inot += 1;
	  }
	  tmp1++;
	}
      }
      if (ir >= 1 && inot == 0){
	return 1;
      }
      else {
	return 0;
      }
    }
  }
  tmp = str;
  ir = 0;
  inot = 0;
  if (ishasonedot(tmp)){
    if (*tmp != '+' && *tmp != '-' && *tmp != '\0' && isdotnumeric(*tmp)){
      while (*tmp != '\0'){
	if (isdotnumeric(*tmp) && *tmp != 'f' && *tmp != 'F' && *tmp != 'e' && *tmp != 'E' ){
	  ir += 1;
	}
	if(!isdotnumeric(*tmp) && *tmp != 'f' && *tmp != 'F' && *tmp != 'e' && *tmp != 'E' ){
	  inot += 1;
	}
	tmp++;
      }
      if (ir >= 1 && inot == 0){
	return 1;
      }
      else {
	return 0;
      }
    }
  }
  return 0;
}
  
int main(void){
  char *str1 = "-.2";
  char *str2 = ".12";
  char *str3 = "1.2e0";
  char *str4 = "1.0f";
  char *str5 = "-1.0f";
  char *str6 = "-1.cf";
  
  printf("is float %d\n",isFloat(str1));
  printf("is float %d\n",isFloat(str2));
  printf("is float %d\n",isFloat(str3));
  printf("is float %d\n",isFloat(str4));
  printf("is float %d\n",isFloat(str5));
  printf("is float %d\n",isFloat(str6));
  return 0;
  char numeric[] = "0123456789"; 
  int isnotfloat = 1;
  char *tmp = str1, *tmp1 = NULL;

  if (ishasonedot(tmp)){
    if (*tmp == '+' || *tmp == '-'){
      if (*(tmp +1) != '\0' && isdotnumeric(*(tmp+1))){
	tmp1 = tmp + 1;
	while (*tmp1 != '\0' ){
	  for (int i=0; i < StringArraycount(numeric);++i){
	    if (*tmp1 == numeric[i] && *tmp1 != '.' && *tmp1 != 'f' && *tmp1 != 'F' && *tmp1 != 'e' && *tmp1 != 'E' ) isnotfloat = 0;
	  }
	  tmp1++;
	}
      }
    }
  }
  printf("is float %c\n" ,(isnotfloat == 1) ? 'N' : 'Y');
  tmp = str2;
  isnotfloat = 1;
  if (ishasonedot(tmp)){
    if (*tmp != '+' && *tmp != '-' && *tmp != '\0' && isdotnumeric(*tmp)){
      while (*tmp != '\0'){
	for (int i=0; i < StringArraycount(numeric);++i){
	  if (*tmp == numeric[i] && *tmp != '.' && *tmp != 'f' && *tmp != 'F' && *tmp != 'e' && *tmp != 'E' ) isnotfloat = 0;
	}
	tmp++;
      }
    }
  }
  printf("is float %c\n" ,(isnotfloat == 1) ? 'N' : 'Y');
  printf("%f\n" ,+2.);
    
  return 0;
}
      
  
