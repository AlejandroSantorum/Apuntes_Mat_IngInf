#include "type.h"
#include "index.h"
#include <string.h>


int main() {
  int i, n_rec, n_pos, key, n;
  long pos;
  long *array=NULL;
  index_t *idx=NULL;
  
  index_create(INT, "indextest.txt");
  
  idx = index_open("indextest.txt");
  if(idx==NULL){
    printf("Error opening the index.\n");
    return -1;
  }
  
  printf("Introduce the number of keys you want to put into the index ");
  printf("(do not count repetitions): ");
  scanf("%d", &n_rec);
  
  for(i=0; i<n_rec; i++){
    printf("Introduce key number %d: ", i+1);
    scanf("%d", &key);
    printf("Introduce the number of positions associated with this key: ");
    scanf("%d", &n_pos);
    for(int j=0; j<n_pos; j++){
      printf("Introduce position number %d: ", j+1);
      scanf("%ld", &pos);
      index_put(idx, key, pos);
    }
  }
  
  index_save(idx);
  index_close(idx);
  
  idx = index_open("indextest.txt");
  if(idx==NULL){
    printf("Error opening the index 2.\n");
    return -1;
  }
  
  printf("\n\tWE HAVE CLOSED THE INDEX AND OPENED IT AGAIN.\n");
  printf("Now we ask you to introduce a key to get its positions: ");
  scanf("%d", &key);
  
  array = index_get(idx, key, &n);
  printf("\nPositions associated with the key: ");
  for(i=0; i<n; i++){
    printf("%ld ", array[i]);
  }
  
  free(array);
  index_close(idx);
  
  return 0;
}
