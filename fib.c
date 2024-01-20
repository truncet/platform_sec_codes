/*
This is a very simple program
I didn't use getopt.h as the conditions were simple. 
So just used argv and argc value to manipulate output.
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int showusage();

int showusage(){
  fprintf(stderr, "USAGE: fib [outfile]\n");
  return 0;
}

int main(int argc, char **argv){
  int n = 10;
  int a = 1;
  int b = 1;
  int c;

  if (argc > 3){
    showusage();
    exit(1);
  }
  else if (argc == 3){
    if (!strcmp(argv[1], "--")){
      freopen(argv[2], "w", stdout);
    }
    else{
      showusage();
      exit(1);
    }
  }
  else if (argc == 2){
    if (!strcmp(argv[1], "-")){
      freopen("/dev/stdout", "w", stdout);
    }
    else{
      freopen(argv[1], "w", stdout);
    }
  }
  fprintf(stdout, "Fibonacci Numbers\n");
  for (int i = 0; i < n; i++){
    fprintf(stdout, "%d\n", a);
    c = a + b;
    a = b;
    b = c;
  }
  fclose(stdout);
  return 0;
}
