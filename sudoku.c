#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid_row(Node* n, int row){
  int i,j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if(n->sudo[row][i]==n->sudo[row][j] && i!=j) return 0;
    }
  }
  return 1;
}

int is_valid_column(Node* n, int column){
  int i,j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if(n->sudo[i][column]==n->sudo[j][column] && i!=j) return 0;
    }
  } 
  return 1;
}

int is_valid_subgrid(Node* n, int row, int column){
  int i,j;
  int numbers[9] = {0,0,0,0,0,0,0,0,0};
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      numbers[n->sudo[row+i][column+j]-1]++;
    }
  }

  for(i=0;i<9;i++){
    if(numbers[i]>1) return 0;
  }
  return 1;
}

int is_valid(Node* n){
  int i,j;
  for(i=0;i<9;i++){
    if(is_valid_row(n,i)==0) return 0;
    if(is_valid_column(n,i)==0) return 0;
    if(is_valid_subgrid(n,i/3,i%3)==0) return 0;
  }
  return 1;
}


List* get_adj_nodes(Node* n){
    List* list = createList();

    int i,j;
    int flag = 0;
    for(i=0;i<9;i++){
      for(j=0;j<9;j++){
        if(n->sudo[i][j]==0)
          {
            flag = 1;
            break;
          }
      }
      if(flag == 1) break;
    }

    if(flag == 0) return list;

    for(int k=0;k<9;k++){
      Node* new_node = copy(n);
      new_node->sudo[i][j] = k+1;
      pushBack(list, new_node);
    }

    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/