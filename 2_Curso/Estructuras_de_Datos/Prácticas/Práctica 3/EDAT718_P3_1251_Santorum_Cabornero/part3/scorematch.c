#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "table.h"
#include "type.h"

#define NCOLS 4

int main(int argc, char **argv){
  table_t *tb=NULL;
  index_t *idx=NULL;
  void **buff=NULL;
  long pos1, pos2;
  long *array=NULL;
  int i, n, j, score;

  if(argc != 2){
    printf("Incorrect input parameters.\nPlease check them.\n");
    return EXIT_FAILURE;
  }

  buff = (void **) malloc(NCOLS * sizeof(void *));
  if(buff==NULL) return EXIT_FAILURE;

  tb = table_open("table.txt");
  if(tb==NULL){
    free(buff);
    printf("Error at opening the table at table.txt.\n");
    exit(1);
  }

  index_create(STR, "scorematch.txt");
  idx = index_open("scorematch.txt");
  if(idx==NULL){
    free(buff);
    table_close(tb);
    printf("Error opening the index.\n");
    return -1;
  }

  pos1 = table_first_pos(tb);

  while(1){
    pos2 = table_read_record(tb, pos1);
    if(pos2 == -1){
      break;
    }

    for(i=0; i<table_ncols(tb); i++){
      buff[i] = table_column_get(tb, i);
    }

    index_put(idx, buff[1], pos1);

    pos1 = pos2;
  }
  index_save(idx);
  index_close(idx);

  idx = index_open("scorematch.txt");
  if(idx==NULL){
    free(buff);
    table_close(tb);
    printf("Error opening the index 2.\n");
    return -1;
  }

  array = index_get(idx, argv[1], &n);
  if(array==NULL){
    free(buff);
    table_close(tb);
    index_close(idx);
    printf("Error getting the array of positions.\n");
    printf("Please check that the title introduced is in the table.\n");
    printf("Title not found.\n");
    return -1;
  }

  for(i=0; i<n; i++){
    table_read_record(tb, array[i]);

    for(j=0; j<table_ncols(tb); j++){
      buff[j] = table_column_get(tb, j);
    }
    score = *((int *) buff[2]);

    pos1 = table_first_pos(tb);
    printf("Title books with score %d:\n", score);
    while(1){
      pos1 = table_read_record(tb, pos1);
      if(pos1 == -1){
        break;
      }

      for(j=0; j<table_ncols(tb); j++){
        buff[j] = table_column_get(tb, j);
      }

      if(score == *((int *)buff[2])){
        printf("%s\n", (char *) buff[1]);
      }
    }
  }

  index_close(idx);
  table_close(tb);
  free(array);
  free(buff);

  return EXIT_SUCCESS;
}
