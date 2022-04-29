/* 
    Name: Rena Zhao
    NetID: ryz215
    GitHub Name: ryzhao123
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int arr[5][5];
int ret [5][5];

void evolution(int r, int c) { //creates the next evolution
  int count = 0; // counts alive neighbors
  if(r > 0) { //ignores top row
    if (arr[r - 1][c] == 1) 
      count++;
    if(c > 0)
      if(arr[r - 1][c - 1] == 1)
        count++;
    if(c < 4)
      if(arr[r - 1][c + 1] == 1)
        count++;
  }
  if(r < 4) { //ignores bottom row
    if (arr[r + 1][c] == 1) 
      count++;
    if(c > 0)
      if(arr[r + 1][c - 1] == 1)
        count++;
    if(c < 4)
      if(arr[r + 1][c + 1] == 1)
        count++;
  }
  if(c > 0) { //ignores left column
    if(arr[r][c - 1] == 1)
      count++;
  }
  if(c < 4) { //ignores right column
    if(arr[r][c + 1] == 1)
      count++;
  } //finished counting alive neighbors
  if(arr[r][c] == 0) { //if originally dead
    if(count == 3) { //alive
      ret[r][c] = 1;
    }
    else {
      ret[r][c] = 0; //dead
    }
  }
  else { //if originally alive
    if(count < 2 || count > 3) { //dead
      ret[r][c] = 0;
    }
    else { //alive
      ret[r][c] = 1;
    }
  }
} 

void copyArray() { //copies ret into arr
  for(int a = 0; a < 5; a++) {
    for(int b = 0; b < 5; b++) {
      arr[a][b] = ret[a][b];
    }
  }
}

int main(int argc, char *argv[]) {
  if(argc != 3) {
    printf("Usage: ./automata N FILENAME");
    exit(-1);
  }
  FILE *file = fopen(argv[2], "r"); //r for read
  if(file == NULL) //checks if there is a file
  {
    printf("error: can't open file");   
    exit(-1);             
  }
  for(int i = 0; i < 5; i++) { //nested loop builds input
    for(int j = 0; j < 5; j++) {
      fscanf(file, "%d", &arr[i][j]);
    }
  }
  fclose(file);
  int gen = atoi(argv[1]); //parses string as int
  for(int count = 1;count <= gen; count++){
    for(int r = 0; r < 5; r++) { //changes alive and dead status for all cells
      for(int c = 0; c < 5; c++) {
        evolution(r, c);
      }
    }
    copyArray();
  }
  char *filename = argv[2]; //returns output in a file
  strncat(filename, ".out", 4);
  FILE *output;
  output = fopen(filename, "w"); //w for write
  for(int r = 0; r < 5; r++) {
    for(int c = 0; c < 5; c++) {
      fprintf(output, "%d ", ret[r][c]);
    }
    fprintf(output, "\n");
  }
  fclose(output);
}
