#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int goto_exit(int *requests, int exit_val){
  /*
    free requests and exit
  */
  free(requests);
  exit(exit_val);
}

int has_read(int permission_val){
  /*
    if permission is > 3 that means it has read permission
  */
  if (permission_val > 3){
    return 1;
  }
  return 0;
}

int has_write(int permission_val){
  /*
    if permission value is 2,3,6,7, it has write permission
  */
  if (permission_val != 1 || permission_val != 4 || permission_val != 5){
    return 1;
  }
  return 0;
}

int has_execute(int permission_val){
  /*
    if the last bit is 1 it has execute, so checking for odd values
  */
  if (permission_val % 2 == 1){
    return 1;
  }
  return 0;
}

int is_same_group(char **argv_list, char *group, int count){
    /*
      see if the group of object is in list of initiators group
    */
    for (int i = 6; i < count; i++){
      if (!strcmp(group, argv_list[i])) return 1;
    }
    return 0;
}

int has_permission(int *requests, int permission_val){
  /*
  check if the permission value given has read, write and execute 
  */

  if (requests[0] == 1){
    if (!has_read(permission_val)) goto_exit(requests, 1);
  }
  if (requests[1] == 1){
    if (!has_write(permission_val)) goto_exit(requests, 1);
  }
  if (requests[2] == 1){
    if (!has_execute(permission_val)) goto_exit(requests, 1);
  }

}

long int check_permission_validity(char *permission){
  /*
    check if the provided permission string is valid or not
  */
  long int object_permission;
  char *end;

  object_permission = strtol(permission, &end, 10);
  if (end == permission || *end != '\0'){
    fprintf(stderr, "Not a valid value\n");
    exit(2);
  }
  else if ( object_permission > 777 || object_permission < 0 ){
    fprintf(stderr, "Not a valid permission value\n");
    exit(2);
  }
  return object_permission;
}


int *check_requests_validity(char *input_requests){
  /*
  this function is to check if the provided requests 
  contains only r,w or x
  */
  int *requests = malloc(3 * sizeof(int));
  int length;

  if (requests == NULL){
    fprintf(stderr, "Memory allocation error\n");
    exit(2);
  }

  length = strlen(input_requests);

  for (int i = 0; i < length; i++){
    if (input_requests[i] == 'r'){
      requests[0] = 1;
    }
    else if (input_requests[i] == 'w'){
      requests[1] = 1;
    }
    else if (input_requests[i] == 'x'){
      requests[2] = 1;
    }
    else{
      fprintf(stderr, "Invalid Value\n");
      goto_exit(requests, 2);
    }
  }

  return requests;
  
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


    int owner_object_permission = object_permission / 100;
    int group_object_permission = ( object_permission - owner_object_permission * 100 ) /10;
    int other_object_permission = object_permission % 10;

    char *owner = argv[2];
    char *group = argv[3];
    char *input_requests = argv[4];
    int *requests = check_requests_validity(input_requests);
    char *initiator = argv[5];

    //first check if owner and initiator are same
    if (!strcmp(owner, initiator)){
      has_permission(requests, owner_object_permission);
    }

    else if (is_same_group(argv, group, argc)){
      has_permission(requests, group_object_permission);
    }

    else{
      has_permission(requests, other_object_permission);
    }

    free(requests);
  }

}