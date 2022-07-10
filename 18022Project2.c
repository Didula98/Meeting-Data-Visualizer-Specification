/*    CO222     PROJECT 02     E/18/022       AMARASINGHE D.I.    */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 80

//##################-DECLARING STRUCT DATA-#################
typedef struct _ {

  char name[50];
  int participant;
  int time;
  int meeting;
  int order;
  struct _ *next;

}data_t;

//###################-DECLARING FUNCTIONS-####################

int number_check(char *);
int sort_data(data_t *, int);
int max_len_of_name(data_t *, int);
int len_of_data(data_t *, int);
void bar_ptint(data_t *, int, int);





//########################-main-###########################
int main(int argc, char ** argv) {

  //these int values are used to check arguments
  int t = 0, m = 0, p = 0, s = 0, l = 0, f = 1;

  int limit = 0, numofFiles = 0;
  char arr[1000][100]; //to store file names 

//check whether no of arguments are grater than 1 
  if(argc > 1){
    for(int i = 1; i < argc; i++){

      if(argv[i][0] == '-'){
        if(strcmp(argv[i],"-t") == 0){
          t = 1; //for -t 

        }else if(strcmp(argv[i],"-p") == 0){
          p = 1; //for -p

        }else if(strcmp(argv[i],"-m") == 0){
          m = 1; //for -m

        }else if(strcmp(argv[i],"--scaled") == 0){
          s = 1; //for -scaled

        }else if(strcmp(argv[i],"-l") == 0){

          //for -l
          if(argc == i+1){
            //when -l is last argument
            printf("Not enough options for [-l]\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", argv[0]);
            return 0;
          }

          //to check argument after -l
          limit = number_check(argv[i+1]);
          
          if(limit == -1){
            //when enter negative value
            printf("Invalid option(negative) for [-l]\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", argv[0]);
            return 0;

          }else if(limit == -2){
            //for other wrong argument after -l
            printf("Invalid options for [-l]\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", argv[0]);
            return 0;

          }else if(limit == 0){ //if value is 0 
            return 0;

          }else{ //else update l value to 1
            l = 1;
          }
        
          i++; //increasing i value to avoid checking the argument after -l again 
    

        }else{
          
          //if there are other than acceptable tags
          printf("Invalid option [%s]\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", argv[i], argv[0]);
          return 0;

        }
      
      }else{
        //if argument doesn't contain "-" in the beginning store them in arr 
        strcpy(arr[numofFiles], argv[i]);
        numofFiles++; //count files
      }

    }

  }else{

    //if only one argument 
    printf("No input files were given\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", argv[0]);
    return 0;
  }


  


  if(t+m+p > 1){
    //if user enter more than one tag
    printf("Cannot plot multiple parameters in same graph.\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", argv[0]);
    return 0;

  }else{
    //no input files
    if(numofFiles == 0){
      printf("No input files were given\nusage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", argv[0]);
      return 0; 

    }

    //if there are arguments other than tags check them
    for(int i = 0; i < numofFiles; i++){

      FILE* fp = fopen(arr[i], "r");

      if(!fp){
        //if wrong file name
        int k = strlen(arr[i])-1;
        if((arr[i][k] == 'v' && arr[i][k-1] == 's' && arr[i][k-2] == 'c' && arr[i][k-3] == '.') || (arr[i][k] == '.' && arr[i][k-1] == 'v' && arr[i][k-2] == 's' && arr[i][k-3] == 'c' && arr[i][k-4] == '.')){
  
          printf("Cannot open one or more given files\n");
          return 0;

        }else{
            //if file is not .csv file
          printf("Only .csv files should be given as inputs.\n");
          return 0;
        }

        f = 0; //update f as 0
          
      }
    }
  }

  
  if(t==0 && m == 0 && p == 0 && f == 1){
   m = 1; //default plotting parameter
  }




  //---------------------------file------------------------

//if file can open
  if(f == 1){ 
    
    int size = 0;
    data_t *newPerson, *temp;
    
    data_t *head = (data_t*) malloc(sizeof(data_t)); //first node
    data_t *tail = (data_t*) malloc(sizeof(data_t)); //last node
    head ->next = NULL;
    tail ->next = NULL;
    
    
    
    FILE * fp;

    for(int i = 0; i < numofFiles; i++){

      fp = fopen(arr[i], "r"); //read .csv file
      char buff[1024];
      int row = 0, field_count = 0; 


      while(fgets(buff, 1024, fp)){

        newPerson = head;
        char *field = strtok(buff, ",");
        temp = (data_t*) malloc(sizeof(data_t));
        field_count = 0;
        row++;  


        while(field){

          if(field_count == 0){
            strcpy(temp ->name, field); //name
          }

          if(field_count == 1){
            temp ->participant = atoi(field);  //number of participent 
          }

          if(field_count == 2){
            int time = (field[0] - 48)*60 + (field[2] - 48)*10 + (field[3] - 48);
            temp ->time = time; //time duration
          }

          field = strtok(NULL, ",");
          field_count++;
        }



        size++; //count no of lines
        temp ->order = size; //order of lines
        temp ->next = NULL;
    

        while(newPerson ->next != NULL){
          newPerson = newPerson ->next;
        }

        newPerson ->next = temp;
      
      }

      fclose(fp);
    }


    //if file doesn't contain any data lines
    if(size == 0){
      printf("No data to process\n");
      return 0;
    }


    newPerson = head;
    while(newPerson ->next != NULL){
      newPerson = newPerson ->next;
    }
    newPerson ->next = tail; // add tail node to the created list
    


  //---------calculating sum of same person data and remove duplicates-----------------
  


    for(data_t *ptr1 = head ->next; ptr1 ->next!= NULL; ptr1 = ptr1 ->next){
  
      int p = 0;
      (ptr1 ->meeting) = 1;
  
      for(data_t *ptr2 = head ->next; ptr2 ->next!= NULL; ptr2 = ptr2 ->next){
        
        
       
        if(strcmp(ptr1 ->name, ptr2 ->name) == 0 && ptr1 != ptr2){
          size--;
          data_t *ptr4 = head;

          while(ptr4 != ptr2){
            p++;
            ptr4 = ptr4 ->next;
          }
         
         //sum of each data of each person
          (ptr1 ->participant) += (ptr2 ->participant);
          (ptr1 ->time) += (ptr2 ->time);
          (ptr1 ->meeting) += 1;

          ptr4 = head;

          while(p != 1){
            ptr4 = ptr4 ->next;
            p--;
          }

          //update next 
          ptr4 ->next = ptr2 ->next;
   
          free(ptr2); //free memory of duplicates
 
          p =0;


        }


      }

    }

   
  

  //calculating total lines of graph
    if(l == 1){

      if(limit>size){
        limit = size*4;

      }else{
        limit = limit*4;
      }

    }else if(size > 10){
      limit = 40;

    }else{
      limit = size*4;
    }


    //make some particular values for scaled parameters and non scaled parameters
    int barType;

    if(s==1){
      if(m==1){
        barType = 4;

      }else if(p == 1){
        barType = 5;

      }else if(t == 1){
        barType = 6;
      } 

    }else{
      if(m==1){
        barType = 1;

      }else if(p == 1){
        barType = 2;

      }else if(t == 1){
        barType = 3;

      }
    }



    bar_ptint(head, barType, limit);

  }


  return 0;
}









//#########################-CHECK LIMIT OF DATA-##############################

int number_check(char *arr){
  int flag = 0;

  if(arr[0] == '-'){
    for(int i = strlen(arr) - 1; i > 0; i--){
      if(arr[i] - 48 >= 10 || arr[i] - 48 < 0){
        flag = -2; //contain other characters 
        break;

      }else{
        flag = -1; //contain negative value
      }
    }

    if(arr[1] == '0' && strlen(arr) == 2){
            flag = 0; //if user enter zero program should be terminate withot printing anything
    }



  }else{

    for(int i = strlen(arr) - 1; i >= 0; i--){
      if(arr[i] - 48 < 10 && arr[i] - 48 >= 0){
        flag = 1; //if all are numbers flag is updates as 1

      }else{
        flag = -2;
        break;

      }
    }

    if(flag == 1){
      flag = atoi(arr); //if characters in array are numbers then take value 
    }

  }

  return flag;
}












//################-CHECK MAXIMUM NAME LENGTH IN GIVEN DATA LIST-###################
int max_len_of_name(data_t *head, int limit){

  int max_len = strlen(head ->next ->name); //initially maximum length of name is first one
  int i = limit/4;
  data_t *ptr1 = head ->next;
  while(i != 0){
    ptr1 = ptr1 ->next;
    i--;
  }

  for(data_t *ptr = head ->next; ptr != ptr1; ptr = ptr ->next){
    if(max_len < strlen(ptr ->name)){
      max_len = strlen(ptr ->name); //if there are name length that exceed length of first name max_len is updates as longer name length
    }
  }


  return max_len;

}








//##############-SORT DATA IN GIVEN DATA LIS AND GIVEN PARAMETER-###############
int sort_data(data_t *head, int bartype){

  data_t *temp, *ptr1, *ptr2;
  temp = (data_t*)malloc(sizeof(data_t)); //make temporary memory 
  int sum = 0;

//check each bartype value and sort list
  for(ptr1 = head->next; ptr1 ->next != NULL; ptr1 = ptr1 ->next){
    for(ptr2 = ptr1 ->next; ptr2 ->next != NULL; ptr2 = ptr2 ->next){

      if(bartype == 1 || bartype == 4){

        if(ptr1 ->meeting < ptr2 ->meeting){

          strcpy(temp ->name, ptr1 ->name);
          temp ->time = ptr1 ->time;
          temp ->participant = ptr1 ->participant;
          temp ->meeting = ptr1 ->meeting;
          temp ->order = ptr1 ->order;

          strcpy(ptr1 ->name, ptr2 ->name);
          ptr1 ->time = ptr2 ->time;
          ptr1 ->participant = ptr2 ->participant;
          ptr1 ->meeting = ptr2 ->meeting;
          ptr1 ->order = ptr2 ->order;

          strcpy(ptr2 ->name, temp ->name);
          ptr2 ->time = temp ->time;
          ptr2 ->participant = temp ->participant;
          ptr2 ->meeting = temp ->meeting;
          ptr2 ->order = temp ->order;

        }else if(ptr1 ->meeting == ptr2 ->meeting){

            if(ptr1 ->order > ptr2 ->order){

              strcpy(temp ->name, ptr1 ->name);
              temp ->time = ptr1 ->time;
              temp ->participant = ptr1 ->participant;
              temp ->meeting = ptr1 ->meeting;
              temp ->order = ptr1 ->order;

              strcpy(ptr1 ->name, ptr2 ->name);
              ptr1 ->time = ptr2 ->time;
              ptr1 ->participant = ptr2 ->participant;
              ptr1 ->meeting = ptr2 ->meeting;
              ptr1 ->order = ptr2 ->order;

              strcpy(ptr2 ->name, temp ->name);
              ptr2 ->time = temp ->time;
              ptr2 ->participant = temp ->participant;
              ptr2 ->meeting = temp ->meeting;
              ptr2 ->order = temp ->order;
            }
        }




      }else if(bartype == 2 || bartype == 5){

        if(ptr1 ->participant < ptr2 ->participant){

          strcpy(temp ->name, ptr1 ->name);
          temp ->time = ptr1 ->time;
          temp ->participant = ptr1 ->participant;
          temp ->meeting = ptr1 ->meeting;
          temp ->order = ptr1 ->order;

          strcpy(ptr1 ->name, ptr2 ->name);
          ptr1 ->time = ptr2 ->time;
          ptr1 ->participant = ptr2 ->participant;
          ptr1 ->meeting = ptr2 ->meeting;
          ptr1 ->order = ptr2 ->order;

          strcpy(ptr2 ->name, temp ->name);
          ptr2 ->time = temp ->time;
          ptr2 ->participant = temp ->participant;
          ptr2 ->meeting = temp ->meeting;
          ptr2 ->order = temp ->order;

        }else if(ptr1 ->participant == ptr2 ->participant){

            if(ptr1 ->order > ptr2 ->order){

              strcpy(temp ->name, ptr1 ->name);
              temp ->time = ptr1 ->time;
              temp ->participant = ptr1 ->participant;
              temp ->meeting = ptr1 ->meeting;
              temp ->order = ptr1 ->order;

              strcpy(ptr1 ->name, ptr2 ->name);
              ptr1 ->time = ptr2 ->time;
              ptr1 ->participant = ptr2 ->participant;
              ptr1 ->meeting = ptr2 ->meeting;
              ptr1 ->order = ptr2 ->order;

              strcpy(ptr2 ->name, temp ->name);
              ptr2 ->time = temp ->time;
              ptr2 ->participant = temp ->participant;
              ptr2 ->meeting = temp ->meeting;
              ptr2 ->order = temp ->order;
            }
        }




      }else if(bartype == 3 || bartype == 6){

        if(ptr1 ->time < ptr2 ->time){

          strcpy(temp ->name, ptr1 ->name);
          temp ->time = ptr1 ->time;
          temp ->participant = ptr1 ->participant;
          temp ->meeting = ptr1 ->meeting;
          temp ->order = ptr1 ->order;

          strcpy(ptr1 ->name, ptr2 ->name);
          ptr1 ->time = ptr2 ->time;
          ptr1 ->participant = ptr2 ->participant;
          ptr1 ->meeting = ptr2 ->meeting;
          ptr1 ->order = ptr2 ->order;

          strcpy(ptr2 ->name, temp ->name);
          ptr2 ->time = temp ->time;
          ptr2 ->participant = temp ->participant;
          ptr2 ->meeting = temp ->meeting;
          ptr2 ->order = temp ->order;

        }else if(ptr1 ->time == ptr2 ->time){

            if(ptr1 ->order > ptr2 ->order){

              strcpy(temp ->name, ptr1 ->name);
              temp ->time = ptr1 ->time;
              temp ->participant = ptr1 ->participant;
              temp ->meeting = ptr1 ->meeting;
              temp ->order = ptr1 ->order;

              strcpy(ptr1 ->name, ptr2 ->name);
              ptr1 ->time = ptr2 ->time;
              ptr1 ->participant = ptr2 ->participant;
              ptr1 ->meeting = ptr2 ->meeting;
              ptr1 ->order = ptr2 ->order;

              strcpy(ptr2 ->name, temp ->name);
              ptr2 ->time = temp ->time;
              ptr2 ->participant = temp ->participant;
              ptr2 ->meeting = temp ->meeting;
              ptr2 ->order = temp ->order;
            }
        }

      }
      
    }


  }




  free(temp);

//calculating sum of all data

  if(bartype == 1 || bartype == 2 || bartype == 3){
    for(ptr1 = head->next; ptr1 ->next != NULL; ptr1 = ptr1 ->next){

      switch (bartype) {
        case 1:
          sum += ptr1 ->meeting;
          
          break;
        case 2:
          sum += ptr1 ->participant;
        
          break;
        case 3:
          sum += ptr1 ->time;
        
          break;
                  
      }
    }


  }


  return sum;


}










//#############-LENGTH MAXIMUM VALUE OF GIVEN LIST AND PARAMETER-##############
int len_of_data(data_t *head, int bartype){

  int len = 0, temp;
  sort_data(head, bartype);

  if(bartype == 4 || bartype == 1){

    temp = head ->next ->meeting;
    while(temp != 0){
      temp /= 10;
      len++;
    }

  }else if(bartype == 5 || bartype == 2){

    temp = head ->next ->participant;
    while(temp != 0){
      temp /= 10;
      len++;
    }

  }else if(bartype == 6 || bartype == 3){
    
    temp = head ->next ->time;
    while(temp != 0){
      temp /= 10;
      len++;
    }
  }

  return len;

}

















//########################-PRINT GRAPH-##########################
void bar_ptint(data_t *head, int bartype, int limit){

  printf("\n");

  int sum, position, temp, temp1, l;
  char *s = head ->next ->name;

  sum = sort_data(head,bartype);
  temp1 = len_of_data(head, bartype);
  l = max_len_of_name(head, limit);



  switch (bartype) {
    case 1:
      temp = head ->next ->meeting; 
      break;

    case 2:
      temp = head ->next ->participant;
      break;

    case 3:
      temp = head ->next ->time;
      break;

    case 4:
      temp = head ->next ->meeting;
      break;

    case 5:
      temp = head ->next ->participant;
      break;

    case 6:
      temp = head ->next ->time;
      break;
            
  }


  data_t *ptr = head ->next;

  for(int i = 1; i < limit+1; i++){
 
//-------------------------non-scaled meeting bars---------------------------

    if(bartype == 1){

      if(i%4 != 0){
        if(i%2 == 0){
          if(strlen(s) != l){
            printf(" %s", s);
            for(int k = 1; k <= l-strlen(s)+1; k++){
              printf(" ");
            }
            printf("\u2502");
            for(position = 0; position < temp*(SIZE-l-3-temp1)/sum ; position++){
              printf("\u2591");
            }

            printf("%i",ptr ->meeting);

          }else if(strlen(s) == l){
            printf(" %s \u2502", s);
            for(position = 0; position < temp*(SIZE-l-3-temp1)/sum ; position++){
              printf("\u2591");
            }

            printf("%i",ptr ->meeting);
          }          
        }else if(i%2 != 0){
          for(int k = 1; k <= l+2; k++){
            printf(" ");
          }
          printf("\u2502");
          for(position = 0; position < temp*(SIZE-l-3-temp1)/sum ; position++){
            printf("\u2591");
          }        

        }
            
      }else{
        for(int k = 1; k <= l+2; k++){
          printf(" ");
        }
        printf("\u2502");

        int p = i/4;
        ptr = head ->next;
        while(p != 0){
          ptr = ptr ->next;
          p--;
        }
        temp = ptr ->meeting;
        s = ptr ->name;
      }


//-------------------------non-scaled participant bars---------------------------

    }else if(bartype == 2){
      if(i%4 != 0){
        if(i%2 == 0){
          if(strlen(s) != l){
            printf(" %s", s);
            for(int k = 1; k <= l-strlen(s)+1; k++){
              printf(" ");
            }
            printf("\u2502");
            for(position = 0; position < temp*(SIZE-l-3-temp1)/sum ; position++){
              printf("\u2591");
            }

            printf("%i",ptr ->participant);

          }else if(strlen(s) == l){
            printf(" %s \u2502", s);
            for(position = 0; position < temp*(SIZE-l-3-temp1)/sum ; position++){
              printf("\u2591");
            }

            printf("%i",ptr ->participant);
          }          
        }else if(i%2 != 0){
          for(int k = 1; k <= l+2; k++){
            printf(" ");
          }
          printf("\u2502");
          for(position = 0; position < temp*(SIZE-l-3-temp1)/sum ; position++){
            printf("\u2591");
          }        

        }
            
      }else{
        for(int k = 1; k <= l+2; k++){
          printf(" ");
        }
        printf("\u2502");

        int p = i/4;
        ptr = head ->next;
        while(p != 0){
          ptr = ptr ->next;
          p--;
        }
        temp = ptr ->participant;
        s = ptr ->name;
      }
//----------------------------non-scaled time bars------------------------------

    }else if(bartype == 3){
      if(i%4 != 0){
        if(i%2 == 0){
          if(strlen(s) != l){
            printf(" %s", s);
            for(int k = 1; k <= l-strlen(s)+1; k++){
              printf(" ");
            }
            printf("\u2502");
            for(position = 0; position < temp*(SIZE-l-3-temp1)/sum ; position++){
              printf("\u2591");
            }

            printf("%i",ptr ->time);

          }else if(strlen(s) == l){
            printf(" %s \u2502", s);
            for(position = 0; position < temp*(SIZE-l-3-temp1)/sum ; position++){
              printf("\u2591");
            }

            printf("%i",ptr ->time);
          }          
        }else if(i%2 != 0){
          for(int k = 1; k <= l+2; k++){
            printf(" ");
          }
          printf("\u2502");
          for(position = 0; position < temp*(SIZE-l-3-temp1)/sum ; position++){
            printf("\u2591");
          }        

        }
            
      }else{
        for(int k = 1; k <= l+2; k++){
          printf(" ");
        }
        printf("\u2502");

        int p = i/4;
        ptr = head ->next;
        while(p != 0){
          ptr = ptr ->next;
          p--;
        }
        temp = ptr ->time;
        s = ptr ->name;
      }

//----------------------------scaled meeting bars---------------------------------

    }else if(bartype == 4){

      if(i%4 != 0){
        if(i%2 == 0){
          if(strlen(s) != l){
            printf(" %s", s);
            for(int k = 1; k <= l-strlen(s)+1; k++){
              printf(" ");
            }
            printf("\u2502");
            for(position = 0; position < temp*(SIZE-l-3-temp1)/head ->next ->meeting; position++){
              printf("\u2591");
            }

            printf("%i",ptr ->meeting);

          }else if(strlen(s) == l){
            printf(" %s \u2502", s);
            for(position = 0; position < temp*(SIZE-l-3-temp1)/head ->next ->meeting; position++){
              printf("\u2591");
            }

            printf("%i",ptr ->meeting);
          }          
        }else if(i%2 != 0){
          for(int k = 1; k <= l+2; k++){
            printf(" ");
          }
          printf("\u2502");
          for(position = 0; position < temp*(SIZE-l-3-temp1)/head ->next ->meeting; position++){
            printf("\u2591");
          }        

        }
            
      }else{
        for(int k = 1; k <= l+2; k++){
          printf(" ");
        }
        printf("\u2502");

        int p = i/4;
        ptr = head ->next;
        while(p != 0){
          ptr = ptr ->next;
          p--;
        }
        temp = ptr ->meeting;
        s = ptr ->name;
      }



//---------------------------scaled participant bars------------------------------
        
    }else if(bartype == 5){
      if(i%4 != 0){
        if(i%2 == 0){
          if(strlen(s) != l){
            printf(" %s", s);
            for(int k = 1; k <= l-strlen(s)+1; k++){
              printf(" ");
            }
            printf("\u2502");
            for(position = 0; position < temp*(SIZE-l-3-temp1)/head ->next ->participant; position++){
              printf("\u2591");
            }

            printf("%i",ptr ->participant);

          }else if(strlen(s) == l){
            printf(" %s \u2502", s);
            for(position = 0; position < temp*(SIZE-l-3-temp1)/head ->next ->participant; position++){
              printf("\u2591");
            }

            printf("%i",ptr ->participant);
          }          
        }else if(i%2 != 0){
          for(int k = 1; k <= l+2; k++){
            printf(" ");
          }
          printf("\u2502");
          for(position = 0; position < temp*(SIZE-l-3-temp1)/head ->next ->participant; position++){
            printf("\u2591");
          }        

        }
            
      }else{
        for(int k = 1; k <= l+2; k++){
          printf(" ");
        }
        printf("\u2502");

        int p = i/4;
        ptr = head ->next;
        while(p != 0){
          ptr = ptr ->next;
          p--;
        }
        temp = ptr ->participant;
        s = ptr ->name;
      }

//------------------------------scaled time bars-----------------------------------

    }else if(bartype == 6){
      if(i%4 != 0){
        if(i%2 == 0){
          if(strlen(s) != l){
            printf(" %s", s);
            for(int k = 1; k <= l-strlen(s)+1; k++){
              printf(" ");
            }
            printf("\u2502");
            for(position = 0; position < temp*(SIZE-l-3-temp1)/head ->next ->time; position++){
              printf("\u2591");
            }

            printf("%i",ptr ->time);

          }else if(strlen(s) == l){
            printf(" %s \u2502", s);
            for(position = 0; position < temp*(SIZE-l-3-temp1)/head ->next ->time; position++){
              printf("\u2591");
            }

            printf("%i",ptr ->time);
          }          
        }else if(i%2 != 0){
          for(int k = 1; k <= l+2; k++){
            printf(" ");
          }
          printf("\u2502");
          for(position = 0; position < temp*(SIZE-l-3-temp1)/head ->next ->time; position++){
            printf("\u2591");
          }        

        }
            
      }else{
        for(int k = 1; k <= l+2; k++){
          printf(" ");
        }
        printf("\u2502");

        int p = i/4;
        ptr = head ->next;
        while(p != 0){
          ptr = ptr ->next;
          p--;
        }
        temp = ptr ->time;
        s = ptr ->name;
      }
        
    }

    printf("\n");

  }


//------------------------------X axis------------------------------------

  for(int k = 1; k <= l+2; k++){
    printf(" ");
  }

  printf("\u2514");

  for(int i = 0; i < SIZE-l-3; i++){
    printf("\u2500");
  }

  printf("\n");


}