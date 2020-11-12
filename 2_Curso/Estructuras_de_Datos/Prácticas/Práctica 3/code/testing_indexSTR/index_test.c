#include "type.h"
#include "index.h"
#include <string.h>


int main() {
  int i, n;
  long *array=NULL;
  index_t *idx=NULL;

  index_create(STR, "indextest.txt");

  idx = index_open("indextest.txt");
  if(idx==NULL){
    printf("Error opening the index.\n");
    return -1;
  }

  index_put(idx, "aaaa", 1111);
  index_put(idx, "cccc", 2222);
  index_put(idx, "bbbb", 3333);
  index_put(idx, "aaaa", 4444);
  index_put(idx, "cccc", 5555);
  index_put(idx, "bbbb", 6666);


  index_save(idx);
  index_close(idx);

  idx = index_open("indextest.txt");
  if(idx==NULL){
    printf("Error opening the index 2.\n");
    return -1;
  }

  array = index_get(idx, "bbbb", &n);
  printf("\nPositions associated with the key: ");
  for(i=0; i<n; i++){
    printf("%ld ", array[i]);
  }

  free(array);

  array = index_get(idx, "cccc", &n);
  printf("\nPositions associated with the key: ");
  for(i=0; i<n; i++){
    printf("%ld ", array[i]);
  }

  free(array);
  index_close(idx);

  return 0;
}
