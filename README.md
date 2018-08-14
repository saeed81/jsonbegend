# jsonbegend 
**jsonbegend** is a  **JSON** parser in C language. The goal of this parser is to be easy to be used, with a minimal number of function calls. 

It has two main function calls:

1-json_load("jsonfile")

2-getvalue(a series of keys which ends with NULL)

So basically you can get the value by calling two above function. 

jsonbeged is a single file library and it can be easily integrated to the project. There is no need to dynamically allocate memory except for loading the file. However, this can be avoided by using the static or global array that holds the content of file. 

