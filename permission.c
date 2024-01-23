#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int is_same_group(char **argv_list, char *group, int count){
    /*
      see if the group of object is in list of initiators group
    */
    for (int i = 6; i < count; i++){
      if (!strcmp(group, argv_list[i])) return 0;
    }
    return 1;
}

long int check_permission_validity(char *permission){
  /*
    check if the provided permission string is valid or not
  */
  long int object_permission;
  char *end;

  object_permission = strtol(permission, &end, 8);
  if (*end != '\0'){
    fprintf(stderr, "Not a valid value\n");
    exit(2);
  }
  else if ( object_permission > 511 || object_permission < 0 ){
    fprintf(stderr, "Not a valid permission value\n");
    exit(2);
  }
  return object_permission;
}


int check_requests_validity(char *input_requests){
  /*
  this function is to check if the provided requests 
  contains only r,w or x
  */
  int length;
  int result = 0;

  length = strlen(input_requests);

  for (int i = 0; i < length; i++){
    if (input_requests[i] == 'r'){
      result |=  4;
    }
    else if (input_requests[i] == 'w'){
      result |= 2;
    }
    else if (input_requests[i] == 'x'){
      result |= 1;
    }
    else{
      fprintf(stderr, "Invalid Value\n");
      exit(2);
    }
  }

  return result;
  
}

int main(int argc, char **argv){
  //first lets count the no of argumetnts

  if (argc < 6 ){
    fprintf(stderr, "Not enough arguments\n");
    exit(2);
  }
  else{
    //then check if the first string is valid permission
    long int object_permission = check_permission_validity(argv[1]);

    char *owner = argv[2];
    char *group = argv[3];
    char *input_requests = argv[4];
    int   result = check_requests_validity(input_requests);
    char *initiator = argv[5];

    if(!strcmp(owner, initiator)){
      object_permission = object_permission & 448; // 448 is 111000000
      object_permission = object_permission >> 6;
    }
    else if (!is_same_group(argv, group, argc)){
      object_permission  = object_permission & 56; //56 is 111000
      object_permission = object_permission >> 3;
    }
    else{
      object_permission = object_permission & 7;
    }
    if ((object_permission | result) == object_permission) return 0;
    return 1;

  }
}
