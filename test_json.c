#include"json_begend.c"

int main(void){
  char *con  = json_load("person.json");
  String str = getvalue(con,"languages","programming","0",NULL);
  dumpstring(&str,1);
  if (con  != NULL)free(con);
  
  return 0;
}

    
