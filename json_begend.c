#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

typedef enum TTYPE {JSON_ARRAY = 1<<0, JSON_OBJECT = 1<<2, JSON_STRING = 1<<3, JSON_INT = 1<<4, JSON_FLOAT = 1 <<5, JSON_BOOL = 1 << 6, JSON_NULL = 1 << 7, JSON_UNDEF = 1 <<8,}TYPE; 

int isnull(char *beg, char *end){
  if (beg == NULL || end == NULL) return 0;
  int len = 0;
  char *tmp = beg;
  while(tmp <= end){
    len++;
    tmp++;
  }
  if (len != 4) return 0;
  tmp = beg;
  if (*tmp == 'n' && *(tmp+1) == 'u'  && *(tmp+2) == 'l' && *(tmp+3) == 'l'){
    return 1;
  }
  return 0;
}
int isbool(char *beg, char *end){
  if (beg == NULL || end == NULL) return 0;
  int len = 0;
  char *tmp = beg;
  if (*tmp != 't' && *tmp != 'f'){
    return 0;
  }
  while(tmp <= end){
    len++;
    tmp++;
  }
  tmp = beg;
  if (*tmp == 't' && len != 4) return 0;
  if (*tmp == 'f' && len != 5) return 0;
  if (*tmp == 't') {
    if (*(tmp+1) == 'r' && *(tmp+2) == 'u'  && *(tmp+3) == 'e'){
      return 1;
    }
  }
  if (*tmp == 'f') {
    if (*(tmp+1) == 'a' && *(tmp+2) == 'l'  && *(tmp+3) == 's' && *(tmp+4) == 'e'){
      return 1;
    }
  }
  return 0;
}
int isdotnumeric (char c){
  int isnum = 0;
  char dotnumeric[] = ".0123456789";
  for (int i=0;i<=10;++i){
    if (c== dotnumeric[i]) isnum = 1;
  }
  return isnum;
}

int ishasonedot (char *beg, char *end){
  if (beg == NULL || end == NULL) return 0;
  char *tmp = beg;
  int ncount = 0;
  int ir = 0;
  while(tmp <= end){
    if (*tmp == '.') ncount++;
    tmp++;
  }
  ir = (ncount == 1) ? 1 : 0;
  return ir;
}
int ishasdot (char *beg, char *end){
  if (beg == NULL || end == NULL) return 0;
  char *tmp = beg;
  int ncount = 0;
  int ir = 0;
  while(tmp <=end){
    if (*tmp == '.') ncount++;
    tmp++;
  }
  ir = (ncount >= 1) ? 1 : 0;
  return ir;
}

int isNumeric(char c){
  return ( (c>= '0') && (c <= '9'));
}


int isFloat(char *beg, char *end){
  if (beg == NULL || end == NULL)  return 0;
  char *tmp = beg, *tmp1 = NULL;
  int ir = 0;
  int inot = 0;
  int onedot = 0;
  onedot = ishasonedot(beg,end);
  if (onedot){
    if (*tmp == '+' || *tmp == '-'){
      if (end == beg) return 0;
      if (((end -beg) == 1) &&  *end == '.') return 0;
      if (isdotnumeric(*(tmp+1))){
	tmp1 = tmp + 1;
	while (tmp1 <=end ){
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
  tmp = beg;
  ir = 0;
  inot = 0;
  if (onedot){
    if (*tmp != '+' && *tmp != '-' && isdotnumeric(*tmp)){
      if (end == beg) return 0;
      while (tmp <= end){
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

int isInt(char *beg, char *end){
  if (beg == NULL || end == NULL) return 0;
  char *tmp = beg, *tmp1 = NULL;
  int ir = 0;
  int dot = 0;
  dot = ishasdot(beg,end);
  if (dot != 0 ) return 0;
  if (*tmp == '+' || *tmp == '-'){
    if (end == beg) return 0;
      if (isNumeric(*(tmp+1))){
	tmp1 = tmp + 1;
	while (tmp1 <= end ){
	  if (!isNumeric(*tmp1)){
	      ir += 1;
	  }
	  tmp1++;
	}
      }
      if (ir != 0){
	return 0;
      }
      else {
	return 1;
      }
  }
  tmp = beg;
  ir = 0;
  if (*tmp != '+' && *tmp != '-' && isNumeric(*tmp)){
    while (tmp <= end){
      if (!isNumeric(*tmp)){
	ir += 1;
      }
      tmp++;
    }
    if ( ir != 0){
      return 0;
    }
    else {
      return 1;
    }
  }
  return 0;
}
int pow10(int n){
  int d = 1;
  if (n > 0){ 
    for (int i=0; i < n;++i) d *= 10;
  }
  return d;
}

float npow10(int n){
  float d = 1.0;
  if (n > 0){ 
    for (int i=0; i < n;++i) d /= 10.0;
  }
  return d;
}

int stoi(char *st){
  int sign = 0;

  int nc=0;
  char *temp = st;

  while (*temp != '\0' ){
    if ( *temp != ' ') nc++;
    temp++;
  }
  nc--;
  int d = 0;
  int c = 1;
  while (*st != '\0'){
    if (*st == '-'){
      c = -1;
      nc--; 
      st++;
      sign += 1;
      if (sign > 1 ) return 0;
    }
    else if (*st == '+'){
      c = 1;
      nc--; 
      st++;
      sign += 1;
      if (sign > 1 ) return 0;
    }
    else if( *st != ' ') {
      d += ((int)(*st - '0')*pow10(nc));
      st++;
      nc--;
    }
    else {
      st++;
    }
  }

  return (c*d);
}

int stoi_bg(char *beg, char *end){
  int sign = 0;
  int nc=0;
  char *temp = beg;
  
  while (temp<=end ){
    if ( *temp != ' ') nc++;
    temp++;
  }
  nc--;
  int d = 0;
  int c = 1;
  char *st = beg;
  while (st<=end ){
    if (*st == '-'){
      c = -1;
      nc--; 
      st++;
      sign += 1;
      if (sign > 1 ) return 0;
    }
    else if (*st == '+'){
      c = 1;
      nc--; 
      st++;
      sign += 1;
      if (sign > 1 ) return 0;
    }
    else if( *st != ' ') {
      d += ((int)(*st - '0')*pow10(nc));
      st++;
      nc--;
    }
    else {
      st++;
    }
  }

  return (c*d);
}

float stof(char *st){
  
  int sign = 0;
  int nc=0;
  char *temp = st;
  char *tint = st;

  while (*temp != '\0'){
    if ( *temp != ' '){
      if (*temp == '.'){
	break;
      }
      else{
	nc++;
      }
    }
    temp++;
  }
  nc--;
  float d = 0.0;
  int c = 1;
  while (*tint != '\0'){
    if (*tint == '-'){
      c = -1;
      nc--; 
      tint++;
      sign += 1;
      if (sign > 1 ) return 0.0;
    }
    else if (*tint == '+'){
      c = 1;
      nc--; 
      tint++;
      sign += 1;
      if (sign > 1 ) return 0.0;
    }
    else if( *tint != ' ') {
      if (*tint == '.') break;
      d += (float)((int)(*tint - '0')*pow10(nc));
      tint++;
      nc--;
    }
    else {
      tint++;
    }
  }

  char *tm = st;

  while (*tm != '\0'){

    if (*tm == '.') break;
    tm++;
  }
  char *tm1 = (++tm);
  nc=0;
  float df = 0.0;
  while (*tm1 != '\0'){
    if ( *tm1 != ' ') {
    nc++; 
    df += (float)((int)(*tm1 - '0')*npow10(nc));
    tm1++;
    }
  }
  
  return (c*(d + df));
}

/* matching.h file is here now */
int istoplevelkey(char *beg, char *end){

  char *tmp = beg;

  char lsymbols[4] = {'{','(','[','\0'};
  char rsymbols[4] = {'}',')',']','\0'};
  int nr[4] = {-1,-1,-1,-1};
  int nl[4] = {-1,-1,-1,-1};
  
 
  for (int i=0; i < 3 ; ++i){
    tmp = beg;
    while (tmp < end){
      if (*tmp == lsymbols[i]){
	nl[i] += 1 ;
      }
      tmp++;
    }
  }
  
  for (int i=0; i < 3 ; ++i){
    tmp = beg;
    while (tmp < end){
      if (*tmp == rsymbols[i]){
	nr[i] += 1 ;
      }
      tmp++;
    }
  }
  
  int iok = 0;

  for (int i= 0; i < 3; ++i){
    if (nr[i] == nl[i] ) iok += 1;
  }
  
  if (iok != 3) return 0;
  
  return 1;
}

int checksymbolbeforeparse(char *str){

  char *tmp = str;

  char lsymbols[4] = {'{','(','[','\0'};
  char rsymbols[4] = {'}',')',']','\0'};
  int nr[4] = {-1,-1,-1,-1};
  int nl[4] = {-1,-1,-1,-1};
  
 
  for (int i=0; i < 3 ; ++i){
    tmp = str;
    while (*tmp != '\0'){
      if (*tmp == lsymbols[i]){
	nl[i] += 1 ;
      }
      tmp++;
    }
  }
  
  for (int i=0; i < 3 ; ++i){
    tmp = str;
    while (*tmp != '\0'){
      if (*tmp == rsymbols[i]){
	nr[i] += 1 ;
      }
      tmp++;
    }
  }
  
  int iok = 0;

  for (int i= 0; i < 3; ++i){
    if (nr[i] == nl[i] ) iok += 1;
  }
  
  if (iok != 3) return 1;
  
  return 0;
}

int checkforquote(char *str){
  
  char *tmp = str;
  int exist = 0;
  if (*tmp == '\"') exist++;
  while (*tmp != '\0'){
    tmp++;
  }
  tmp--;
  if (*tmp == '\"') exist++;
  
  if (exist == 2 ) return 0;
  
  return 1;
}
char *addquote(char *str){
  
  char *tmp = str;
  int len   = 0;
  
  while (*tmp != '\0'){
    tmp++;
    len++;
  }
  char *reg = NULL;
  int n = 0;

  reg = (char *)malloc(len+1+2);
  char *trg = reg;
  *reg = '\"';
  reg++;
  tmp = str;
  while (*tmp != '\0'){
    *reg = *tmp;
    n++;
    tmp++;
    reg++;
  }
  *reg = '\"';
  reg++;
  *reg='\0';
  reg = trg;
    
  trg = reg;
  len = 0;
  while (*trg != '\0'){
    trg++;
    len++;
  }
    
  return reg;
}

void match(char *str, char lsymbol, int *index){

  char rsymbol = '0';
  int element  = 1;
  switch (lsymbol){
  case '{':
    rsymbol = '}';
    break;
  case '(':
    rsymbol = ')';
    break;
  case '[':
    rsymbol = ']';
    break;
  default:
    break;
  }

  int openPose = (element-1);
  int closePose = openPose ;
  int counter  = 1;
  char c = ' ';
  while (counter > 0) {
    c = str[++closePose];
    if (c == lsymbol) {
      counter++;
    }
    else if (c == rsymbol) {
      counter--;
    }
    if (counter == 0) break;
  }
  

  *index = closePose;

  return;

}
/*matching.h ends here*/
/*arrayexplode.c is here */
typedef struct tIndex{
  int findex;
  int lindex;
}Index;

int power10(int n){
 int a = 1;
  while(n--){
    a *= 10;
  }
  return a;
}

int fun(char *c){
  char *tmp = c;
  int len = 0;
  while (*tmp != '\0'){
    len++;
    tmp++;
  }
  int index = 0;
  tmp = c;
  int ncount = 0;

  for (int i = (len-1); i>=0; --i){
    index += (c[i]-'0') * power10(ncount);
    ncount++; 
  }

  return index;
}

char *array_value(char *st, char *cind){
  int len   = 0;
  char *tmp = st;
  if (st == NULL) return NULL;
  while(*tmp != '\0'){
    len++;
    tmp++;
  }
  len++;
  char type = '\0';
  int dicel  = 0;
  int rb     = 0;
  if (st[0] == '['){
    //printf("this is array\n");
    type = 'a';
  }
  match(&st[0], '[', &rb);
  //printf("rb %d\n",rb);
  
  int j = -1;
  if (type == 'a'){
    for (int i=1; i < len; ++i){
      if (st[i] == '{'){
	j = i;
	break;
      }
    }
  }
  if (j > 0){
    dicel = 1;
    for (int i=(j-1); i>0;--i){
      if ((st[i] != ' ') || (st[i] != '\t') || (st[i] != '\r') || (st[i] != '\n') ){
	dicel = 0;
	break;
      }
    }
  }
  int index = -1;
  int icol  = -1;
  int nel   = 0;
  int first = 1;
  int last  = 1;
  int stop = 1;
  char *cout = NULL;
  if (dicel == 1){
    while( j < len && stop){
      icol = 0;
      match(&st[j], '{', &index);
      if (nel == fun(cind)){
	cout = NULL;
	int ncount = 0;
	cout = (char *)malloc(index+2);
	for (int i=j;i<=(j+index);++i){
	  //printf("%c",st[i]);
	  cout[ncount] = st[i];
	  ncount++;
	}
	cout[index+1] = '\0';
	stop = 0;
      }
      //printf("\n");
      for (int i=(j+index+1);i < len;++i){
	if (st[i] == ','){
	  first = j;
	  last = i;
      	  j = i;
	  icol = 1;
	  break;
	}
      }
      nel++;
      if (icol == 0) break;
      for (int i=(j+1);i < len;++i){
	if (st[i] == '{'){
	  j = i;
	  break;
	}
      }
    }
    //printf("number of elements is %d\n",nel);
  }
  index = -1;
  icol  = -1;
  nel   = 0;
  j = 1;
  first = 1;
  last  = 1;
  stop = 1;
  if (dicel == 0 ){
    while( (j < len) && stop){
      icol = 0;
      for (int i=j;i < len;++i){
	if (st[i] == ','){
	  first = j;
	  last = i;
	  j = (i+1);
	  icol = 1;
	  break;
	}
      }
      if (icol == 0 && nel == 0){
	if (nel == fun(cind)){
	  //printf("rb is %d",rb);
	  int ncount = 0;
	  last = rb -1;
	  cout = (char *)malloc(last-first+2);
	  for (int k=first;k <=last;++k){
	    //printf("%c",st[k]);
	    cout[ncount] = st[k];
	    ncount++;
	  }
	  cout[ncount] = '\0';
	  //printf("\n");
	  stop = 0;
	}
      }

      if (icol == 0 && nel > 0){
	first = last +1;
	last = rb -1;
	if (nel == fun(cind)){
	  int ncount = 0;
	  cout = (char *)malloc(last-first+2);
	  for (int k=first;k <= last;++k){
	    //printf("%c",st[k]);
	    cout[ncount] = st[k];
	    ncount++;
	  }
	  cout[ncount] = '\0';
	    //printf("\n");
	  stop = 0;
	}
      }

      if (icol == 1){
	//printf("here3 %d\t %d\n",last,first);
	if (nel == fun(cind)){
	  int ncount = 0;
	  cout = (char *)malloc(last-first+1);
	  for (int k=first;k < last;++k){
	    //printf("%c",st[k]);
	    cout[ncount] = st[k];
	    ncount++;
	  }
	  cout[ncount] = '\0';
	  //printf("\n");
	  stop = 0;
	}
      }
      nel++;
      //printf("j is %d\n",j);
    }
  }

  return cout;

}

Index array_value_pt(char *beg, char *end, char *cind){
  int len   = 0;
  char *tmp = beg;
  while(tmp <= end){
    len++;
    tmp++;
  }
  char type = '\0';
  int dicel  = 0;
  int rb     = 0;
  if (*beg == '['){
    //printf("this is array\n");
    type = 'a';
  }
  match(beg, '[', &rb);
  //printf("rb %d\n",rb);
  int j = -1, i = 1;
  if (type == 'a'){
    for (char *it = (beg+1); it < end; ++it){
      if (*it == '{'){
	j = i;
	break;
	i++;
      }
    }
  }
  if (j > 0){
    dicel = 1;
    for (char *it=(beg+j-1); it> beg;--it){
      if ((*it != ' ') || (*it != '\t') || (*it!= '\r') || (*it != '\n') ){
	dicel = 0;
	break;
      }
    }
  }
  int index = -1;
  int icol  = -1;
  int nel   = 0;
  int first = 1;
  int last  = 1;
  int stop = 1;
  Index indout = {-1,-1};
  if (dicel == 1){
    while( j < (len-1) && stop){
      icol = 0;
      match(beg+j, '{', &index);
      //printf("j is %d and index is \t %c \n",j,st[j+index]);
      if (nel == fun(cind)){
	indout.findex = j;
	indout.lindex = j + index;
	stop = 0;
      }
      //printf("\n");
      for (int i=(j+index+1);i < (len-1);++i){
	if (*(beg+i) == ','){
	  first = j;
	  last = i;
      	  j = i;
	  icol = 1;
	  break;
	}
      }
      nel++;
      if (icol == 0) break;
      for (int i=(j+1);i < (len-1);++i){
	if (*(beg+i) == '{'){
	  j = i;
	  break;
	}
      }
    }
    //printf("number of elements is %d\n",nel);
  }
  index = -1;
  icol  = -1;
  nel   = 0;
  j = 1;
  first = 1;
  last  = 1;
  stop = 1;
  if (dicel == 0 ){
    //printf("we are here dicel =0 len %d \n",len);
    while( (j < (len-1)) && stop){
      icol = 0;
      for (int i=j;i < (len-1);++i){
	if (*(beg+i) == ','){
	  first = j;
	  last = i;
	  j = (i+1);
	  icol = 1;
	  //printf("before break \n");
	  break;
	}
      }
      if (icol == 0 && nel == 0){
	//printf("here1 (icol == 0 && nel == 0) last %d\t first %d\n",last,first);
	if (nel == fun(cind)){
	  indout.findex = first;
	  indout.lindex = last;
	  stop = 0;
	}
      }

      if (icol == 0 && nel > 0){
	first = last +1;
	last = rb -1;
	if (first > last) break;
	//printf("here2 (icol == 0 && nel > 0) last %d\t first %d\n",last,first);
	if (nel == fun(cind)){
	  indout.findex = first;
	  indout.lindex = last;
	  stop = 0;
	}
      }

      if (icol == 1){
	//printf("here3 last %d\t first %d\n",last,first);
	if (nel == fun(cind)){
	  indout.findex = first;
	  indout.lindex = last -1;
	  stop = 0;
	}
      }
      nel++;
    }
    //printf("j is %d\n",j);
  }
  //printf("number of elements is %d\n",nel);
  //printf("indout  %d %d \n",indout.findex,indout.lindex);
  return indout;
}


void array_explode(char *st){
  int len   = 0;
  char *tmp = st;
  if (st == NULL) return;
  while(*tmp != '\0'){
    len++;
    tmp++;
  }
  len++;
  char type = '\0';
  int dicel = 0;
  if (st[0] == '['){
    printf("this is array\n");
    type = 'a';
  }
  int j = -1;
  if (type == 'a'){
    for (int i=1; i < len; ++i){
      if (st[i] == '{'){
	j = i;
	break;
      }
    }
  }
  if (j > 0){
    dicel = 1;
    for (int i=(j-1); i>0;--i){
      if ((st[i] != ' ') || (st[i] != '\t') || (st[i] != '\r') || (st[i] != '\n') ){
	dicel = 0;
	break;
      }
    }
  }
  int index = -1;
  int icol  = -1;
  int nel   = 0;
  if (dicel == 1){
    while( j < len){
      icol = 0;
      match(&st[j], '{', &index);
      //printf("j is %d and index is \t %c \n",j,st[j+index]);
      for (int i=j;i<=(j+index);++i){
	printf("%c",st[i]);
      }
      printf("\n");
      nel++;
      for (int i=(j+index+1);i < len;++i){
	if (st[i] == ','){
	  j = i;
	  icol = 1;
	  break;
	}
      }
      if (icol == 0) break;
      for (int i=(j+1);i < len;++i){
	if (st[i] == '{'){
	  j = i;
	  break;
	}
      }
    }
    printf("number of elements is %d\n",nel);
  }
  index = -1;
  icol  = -1;
  nel   = 0;
  j = 1;
  if (dicel == 0 ){
    while( j < len){
      icol = 0;
      nel++;
      for (int i=j;i < len;++i){
	if (st[i] == ','){
	  j = (i+1);
	  icol = 1;
	  break;
	}
      }
      //printf("j is %d\n",j);
      if (icol == 0) break;
    }
    //printf("number of elements is %d\n",nel);
  }
  //fun("10");
  //printf("%d\n",power10(5));
}
/*array explode ends here*/
typedef struct tString{
  char *beg;
  char *end;
  TYPE type;
}String;

void stringinfo(String *str){
  if ((str->beg != NULL) && (str->end != NULL)){
    printf("Value is = ");
    for (char *it =str->beg; it <= str->end;++it)printf("%c",*it);
    printf("\n");
  }
  return;
}

void stringfullinfo(String *str){
  if ((str->beg != NULL) && (str->end != NULL)){
    switch(str->type){
    case JSON_ARRAY: {
      printf("TYPE is array\n");
    }break;
    case JSON_OBJECT:{
      printf("TYPE is object\n");
    }break;
    case JSON_STRING:{
      printf("TYPE is string \n");
    }break;
    case JSON_FLOAT:{
      printf("TYPE is float \n");
    }break;
    case JSON_INT:{
      printf("TYPE is int  \n");
    }break;
    case JSON_BOOL:{
      printf("TYPE is bool \n");
    }break;
    case JSON_NULL:{
      printf("TYPE is null \n");
    }break;
    case JSON_UNDEF:{
      printf("TYPE is undefined.\n");
    }break;
    }
    printf("Value is = ");
    for (char *it =str->beg; it <= str->end;++it)printf("%c",*it);
    printf("\n");
  }
  return ;
}

int getLen(char *str){
  int len = 0;
  if (str != NULL){
    while(*str != '\0'){
      len++;
      str++;
    }
  }
  return len;
}

void removewhitespace(char *str){
  if (str == NULL)return;
  char *tmp = str;
  int ne =0;
  while(*str != '\0'){
    if ((*str != ' ') && (*str != '\n') && (*str != '\r') && (*str != '\t') && (*str != '\v') && (*str != '\f')){
      *(tmp+ne) = *str;
      ne++;
    }
    str++;
  }
  *(tmp+ne) = '\0';
  str = tmp;
}

void quotetowhitespace(char *str){
  char *tmp = str;
  if (str != NULL){
    while(*tmp != '\0'){
      if (*tmp == '\"'){
        *tmp = ' ';
      }
      tmp++;
    }
  }
}

void writeonscreen(char *str){
  if (str == NULL)return;
  //quotetowhitespace(str);
  //removewhitespace(str);
  if (str != NULL ){
    while (*str != '\0'){
      printf("%c",*str);
      str++;
    }
  }
  printf("\n");
}

int iswhitespace(char c){
  if ( (c == ' ') || (c == '\t') || ( c == '\n') || (c == '\r') || (c == '\t') || (c == '\v') || (c == '\f')){
    return 1;
  }
  
  return 0;
}

TYPE typevalue(char *ar, int findex, int lindex){

  TYPE type = JSON_UNDEF;

  if (ar[findex] == '[' && ar[lindex] == ']'){
    //printf("value is array\n");
    type = JSON_ARRAY;
  }
  else if (ar[findex] == '{' && ar[lindex] == '}'){
    //printf("value is dictionary\n");
    type = JSON_OBJECT;
  }
  else if (isFloat(&ar[findex], &ar[lindex])){
    type = JSON_FLOAT;
  }
  else if (isInt(&ar[findex], &ar[lindex])){
    type = JSON_INT;
  }
  else if (isnull(&ar[findex], &ar[lindex])){
    type = JSON_NULL;
  }
  else if (isbool(&ar[findex], &ar[lindex])){
    type = JSON_BOOL;
  }
  else{
    //printf("value is either string or float");
    type = JSON_STRING;
  }
  
  return type;
}

void findpt(char *reg, int lnr, char *beg, char *end, int *ibeg, int *iend){
  int k = 0;
  int i = 0;
  int ncount = 0;
  int ip = 0;
  //int lnr = getLen(reg);                            
  //char *itp = beg;                                                                                                                                                                                             
  //for (int j=0; j < lns; ++j){                                                                                                                                                                                
  int j = 0;
  j = -1;
  *ibeg = -1;
  *iend = -1;
  for (char *itp =beg; itp <= end; ++itp){
    i = 0;
    j++;
    if (*itp == reg[i]){
      //printf("we found the first instance of the first character at j %d\n",j);
      //printf("we need to find the other characters\n");                                                                                                                                                        
      k  = j;
      char *next = (itp+1);
      ip = i + 1;
      ncount = 1;
      while((*next == reg[ip]) && (reg[ip] != '\0') ){
        next++;
        ip++;
        ncount++;
        k++;
      }
      //printf("ncount is %d\n",ncount);                                                                                                                                                                         
      if (ncount == lnr){
        //printf("we found the first instance\n");
        //printf("first index is at distance %d fron beg pointer and  %c\n",j,*(beg+j));
        //printf("last  index is at distance %d fron beg pointer and  %c\n",k,*(beg+k));
	*ibeg = j;
	*iend = k;
	break;
      }
      else{
        //printf("no instance found we continue searching\n");
      }
    }
  }
  return;
}

int find(char *reg, char *str, int *first, int *last){

  int  lnr = getLen(reg);
  int  lns = getLen(str);
  if ( lnr == 0 || lns == 0) return -1;
  if (lnr > lns) return -1;
  
  int i = 0;
  int ncount = 0;
  int k = 0;
  int result = -1;
  int ip = 0;
  for (int j=0; j < lns; ++j){
    i = 0;
    if (str[j] == reg[i]){
      //printf("we found the first instance of the first character at j %d\n",j);                                                                                                      
      //printf("we need to find the other characters\n");                                                                                                                              
      *first = j;
      k  = j+1;
      ip = i + 1;
      ncount = 1;
      while(str[k] == reg[ip]){
	++k;
	++ip;
	++ncount;
      }
      if (ncount == lnr){
	//printf("we found the first instance\n");                                                                                                                                     
	//printf("index is %d\n",j);                                                                                                                                                   
	result = j;
	*last = (k-1);
	break;
      }
      else{
	//printf("no instance found we continue searching\n");
      }
    }
  }
  return result;
}

int Strcmp(char *s1, char *s2){
  
  int i = 0;
  int ns1 = 0, ns2 = 0;
  char *t1 = s1, *t2 = s2;
  while (*t1 != '\0'){
    ns1++;
    t1++;
  }
  while (*t2 != '\0'){
    ns2++;
    t2++;
  }
  
  if (ns2 != ns1) return i;

  t1 = s1;
  t2 = s2;
  while (*t1 != '\0'){
    if (*t1 != *t2) i = -1;
    t1++;
    t2++;
  }
  if ( i < 0 ) return 0;
  
  return 1;
}
 
char *json_load(char *filename){

  FILE *inp = NULL;

  inp = fopen(filename,"r");

  if (inp == NULL) return NULL;

  fseek(inp,0,SEEK_END);

  long int fs = ftell(inp);

  fseek(inp,0,SEEK_SET);

  char *content = NULL;
  
  content = (char *)malloc((fs+1) * sizeof(char));

  fread(content,1,fs,inp);

  fclose(inp);

  content[fs] = '\0';

  removewhitespace(content);


  if (checksymbolbeforeparse(content) != 0){
    free(content);
    content = NULL;
  }

  return content;
}

String getvalue(char *content, char *key,...){
  String rst = {NULL, NULL,' '};
  if (content == NULL) return rst;
  if (key == NULL) return rst; 
  char *str = content;
  long int fs = 0L;
  while(*str != '\0'){
    fs++;
    str++;
  }
  //fs++;
  va_list vs;
  va_start(vs,key);

  char *quotekey = NULL;
  int dynamic = 0;
  if ( checkforquote(key)) {
    quotekey = addquote(key);
    dynamic = 1;
  }
  else{
    quotekey = key;
  }
  
  int first = -1, last = -1;

  findpt(quotekey,getLen(quotekey),&content[0],&content[fs],&first,&last);
     
  if ( first == (-1) || last == (-1)){
    printf("%s does not exist in the file \n",quotekey);
    return rst;
  }
  //printf("%d \t %d \n",first, last);
  int ffirst = first;
  int llast  =  last;
  int ii     = first;
  int jj     = last;
  //printf("fs is %ld\n",fs);
  while(istoplevelkey(&content[1],&content[ii]) == 0){
    //printf("we are here \n");
    findpt(quotekey,getLen(quotekey),&content[jj+1],&content[fs],&ffirst,&llast);
    if ( ffirst == (-1) || llast == (-1)){
      printf("%s does not exist in the file \n",quotekey);
      return rst;
    }
    //printf("%d\t%d\t%d\t%c \t %c \t %c \n",jj+1,ffirst,llast,content[jj+1], content[jj+1+ffirst], content[jj+1+llast]);
    ii = jj + ffirst + 1;
    jj = jj + llast +  1;
    ffirst = -1;
    llast  = -1;
  }
  //printf("%d \t %d \n",ffirst, llast);
  //printf("%d \t %d \t %c \t %c\n",ii, jj,content[ii+1],content[jj-1]);
  first = ii;
  last  = jj;
  //printf("key=>");
  //for (int i=first;i<=last;++i)printf("%c",content[i]);

  int incol = -1;
  for (int i=(last+1);i < fs;++i){
    if (content[i] == ':'){
      incol = i;
      break;
    }
  }
  
  if (incol == -1)return rst;
  
  int ka = incol, kb = -1, kc = -1;
  int findex = -1;
  int lindex = -1;
  
  if (ka >= 0){
    for (int i=(ka+1); i < fs; ++i){
      if (content[i] == '{' || content[i] == '['){
	kb =  i;
	break;
      }
    }
  }
  //check what is between : and {
  //printf("kb is %d \n",kb);
  if (kb >= 0 ){
    int stop = 0; 
    for (int i=(kb-1); i >(ka) ; --i){
      if (iswhitespace(content[i]) == 0){
	//printf("there is something before {. Now we search for ,\n");
	stop = 1;
	break;
      }
    }
    if (stop){
      for (int i=(ka+1); i < (kb) ; ++i){
	if (content[i] == ','){
	  //printf("we found ,\n");
	  kc = i;
	  break;
	}
      }
      //printf("block 1 value=>\n");
      findex = (ka+1);
      lindex = (kc-1);
      for (int i=(ka+1); i < (kc) ; ++i){
	if (content[i] == '}'){
	  //printf("%c",content[i]);
	  lindex = (i-1);
	  break;
	}
      }
    }
    else{
      char *tmp1 = &content[kb];
      int index = -1;
      if (content[kb] == '{')match(tmp1,  '{', &index);
      if (content[kb] == '[')match(tmp1,  '[', &index);
      //printf("match { is at index %d and kb + index %d\n",index, kb +index);
      //printf("block 2 value=>\n");
      findex = kb;
      lindex = (kb+index);
      for (int i=(kb); i <= (kb+index) ; ++i){
	//printf("%c",content[i]);
      }
    }
  }
  else{
    for (int i=(ka+1); i < fs; ++i){
      if (content[i] == ','){
	kc =  i;
	break;
      }
    }
    if ( kc < 0) {
      //printf("block 3 value=>\n");
      findex = (ka+1);
      lindex = (fs-1-1);
      for (int i=(ka+1); i < (fs-1) ; ++i){
	if (content[i] == '}'){
	  lindex = (i-1);
	  break;
	}
      }
    }
    else{
      //printf("block 4 value=>\n");
      findex = (ka+1);
      lindex = (kc -1);
      for (int i=(ka+1); i < kc ; ++i){
	//printf("%c",content[i]);
      }
    }
  }
  int narg = 1;
  TYPE type = JSON_UNDEF; 
  //printf("\n");
  type = typevalue(content,findex,lindex);

  // we find the second value first value would a key now
  if (dynamic == 1) free(quotekey);
  
  while((key=va_arg(vs,char *)) != NULL){
    dynamic = 0;
    //printf("%c\n",type);
    if (type == JSON_ARRAY){
      //printf("%s\n",key);
      Index index = array_value_pt(&content[findex],&content[lindex],key);
      if ((index.findex == -1) || (index.lindex == -1)){
	rst.beg = NULL;
	rst.end = NULL;
	return rst;
      }
      lindex = findex + index.lindex;
      findex = findex + index.findex;
    }
    else{
    if ( checkforquote(key) ) {
      dynamic = 1;
      quotekey = addquote(key);
    }
    else{
      quotekey = key;
    }
    first = -1, last = -1;
    findpt(quotekey,getLen(quotekey),&content[findex],&content[lindex],&first,&last);
    //find(quotekey,keyt,&first,&last);
    fs = (lindex-findex+1);
    fs = lindex + 1;
    
    if ( first == (-1) || last == (-1)){
      //printf("%s does not exist in the file \n",quotekey);
      printf("%s does not exist in the file \n",quotekey);
      if (dynamic == 1)free(quotekey);
      return rst;
    }
    ffirst = -1;
    llast  = -1;
    ii     = findex + first;
    jj     = findex + last;
    
    if (type == 'd'){
      //printf("fs is %ld\n",fs);
      while(istoplevelkey(&content[findex+1],&content[ii]) == 0){
	//printf("we are here \n");
	//find(quotekey,&keyt[jj+1],&ffirst,&llast);
	findpt(quotekey,getLen(quotekey),&content[jj+1],&content[lindex],&first,&last);
	if ( ffirst == (-1) || llast == (-1)){
	  if (dynamic == 1) free(quotekey);
	  printf("%s is not the top level key and it is inside of another dictionary check the hierarchy of keys again \n",quotekey);
	  return rst;
	}
    //printf("%d\t%d\t%d\t%c \t %c \t %c \n",jj+1,ffirst,llast,content[jj+1], content[jj+1+ffirst], content[jj+1+llast]);
	ii = jj + ffirst + 1;
	jj = jj + llast  + 1;
	ffirst = -1;
	llast  = -1;
      }
    }
  //printf("%d \t %d \n",ffirst, llast);
  //printf("%d \t %d \t %c \t %c\n",ii, jj,content[ii+1],content[jj-1]);
  first = ii;
  last  = jj;
  if (dynamic == 1) free(quotekey);
  //printf("key=>");
  //for (int i=first;i<=last;++i)printf("%c",keyt[i]);

    incol = -1;
    for (int i=(last+1);i < fs;++i){
      if (content[i] == ':'){
	incol = i;
	break;
      }
    }
    if (incol == -1)return rst;
  
    ka = incol, kb = -1, kc = -1;
    findex = -1;
    lindex = -1;
  
    if (ka >= 0){
      for (int i=(ka+1); i < fs; ++i){
	if (content[i] == '{' || content[i] == '['){
	  kb =  i;
	  break;
	}
      }
    }
  //check what is between : and {
  //printf("kb is %d \n",kb);
  
    if (kb >= 0 ){
      int stop = 0; 
      for (int i=(kb-1); i >(ka) ; --i){
	if (iswhitespace(content[i]) == 0){
	//printf("there is something before {. Now we search for ,\n");
	stop = 1;
	break;
      }
    }
    if (stop){
      for (int i=(ka+1); i < (kb) ; ++i){
	if (content[i] == ','){
	  //printf("we found ,\n");
	  kc = i;
	  break;
	}
      }
      //printf("block 1 value=>\n");
      findex = (ka+1);
      lindex = (kc-1);
      for (int i=(ka+1); i < (kc) ; ++i){
	if (content[i] == '}'){
	  //printf("%c",content[i]);
	  lindex = (i-1);
	  break;
	}
      }
    }
    else{
      char *tmp1 = &content[kb];
      int index = -1;
      if (content[kb] == '{')match(tmp1, '{', &index);
      if (content[kb] == '[')match(tmp1, '[', &index);
      //printf("match { is at index %d and kb + index %d\n",index, kb +index);
      //printf("block 2 value=>\n");
      findex = kb;
      lindex = (kb+index);
      for (int i=(kb); i <= (kb+index) ; ++i){
	//printf("%c",keyt[i]);
      }
    }
  }
  else{
    for (int i=(ka+1); i < fs; ++i){
      if (content[i] == ','){
	kc =  i;
	break;
      }
    }
    if ( kc < 0) {
      //printf("block 3 value=>\n");
      findex = (ka+1);
      lindex = (fs-1-1);
      for (int i=(ka+1); i < (fs-1) ; ++i){
	if (content[i] == '}'){
	  lindex = (i-1);
	  break;
	}
      }
    }
    else{
      //printf("block 4 value=>\n");
      findex = (ka+1);
      lindex = (kc -1);
      for (int i=(ka+1); i < kc ; ++i){
	//printf("%c",keyt[i]);
      }
    }
  }
    //printf("\n");
    }
     narg++;
    type = typevalue(content,findex,lindex);
  }
  
  va_end(vs);
  rst.beg = &content[findex];
  rst.end = &content[lindex];
  rst.type = type;
  return rst;
}
/*========================================================================*/
  
