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
  int numbers[10] = {0}; 
  for(int i = 0; i < 9; i++){
    int num = n->sudo[row][i];
    if(num != 0){ 
      if(num < 1 || num > 9) return 0;
      if(numbers[num] > 0) return 0; 
      numbers[num]++;
    }
  }
  return 1;
}

int is_valid_column(Node* n, int column){
  int numbers[10] = {0}; 
  for(int i = 0; i < 9; i++){
    int num = n->sudo[i][column];
    if(num != 0){ 
      if(num < 1 || num > 9) return 0; 
      if(numbers[num] > 0) return 0; 
      numbers[num]++;
    }
  }
  return 1;
}

int is_valid_subgrid(Node* n, int row, int column){
  int numbers[10] = {0}; 
  int startRow = (row/3) * 3;
  int startCol = (column/3) * 3;
  
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      int num = n->sudo[startRow + i][startCol + j];
      if(num != 0){ 
        if(num < 1 || num > 9) return 0; 
        if(numbers[num] > 0) return 0; 
        numbers[num]++;
      }
    }
  }
  return 1;
}

int is_valid(Node* n){
  for(int i = 0; i < 9; i++){
    if(!is_valid_row(n,i)) return 0;
    if(!is_valid_column(n,i)) return 0;

    if (i % 3 == 0) {
      for(int j = 0; j < 3; j++){
        if(!is_valid_subgrid(n,i,j)) return 0;
      }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
    List* list = createList();
    
    int empty_i = -1, empty_j = -1;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(n->sudo[i][j] == 0){
                empty_i = i;
                empty_j = j;
                break;
            }
        }
        if(empty_i != -1) break;
    }
    
    if(empty_i == -1) return list;
    
    for(int num = 1; num <= 9; num++){
        Node* new_node = copy(n);
        new_node->sudo[empty_i][empty_j] = num;
      
        if(is_valid(new_node)){
            pushBack(list, new_node);
        } else {
            free(new_node); 
        }
    }
    
    return list;
}


int is_final(Node* n){
    for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
        if(n->sudo[i][j] == 0) return 0;
      }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont) {
  Stack* S = createStack();
  push(S, initial);
  *cont = 0;

  while (!is_empty(S)) {
    Node* current = top(S);
    pop(S);
    (*cont)++;

    if (is_final(current)) {
      return current;
    }

    List* adj_nodes = get_adj_nodes(current);
    for (Node* adj_node = front(adj_nodes); adj_node != NULL; adj_node = next(adj_nodes))
      push(S, adj_node);

    clean(adj_nodes);
    free(current);
  }

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