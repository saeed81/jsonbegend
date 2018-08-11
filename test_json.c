#include"json_begend.c"

int main(void){
  char *con  = json_load("person.json");
  String str = getvalue(con,"age",NULL);
  stringfullinfo(&str);
  if (con  != NULL)free(con);
  
  return 0;
}

    
