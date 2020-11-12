#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "index.h"

typedef struct {
  int key;
  int n_ptrs;
  long *ptrs;
} irecord;

struct index_{
  int type;
  int n_rec;
  irecord **list;
  char *filename;
};

/* ------------ A U X I L I A R Y (I N T E R N A L)     F U N C T I O N S ------------------- */
int mycmp(const void *kptr, const void *e) {
  /*
  irecord *rec = *((irecord **) e);
  if (key < rec->key)
    return -1;
  else if (key > rec->key)
    return 1;
  else
    return 0;
  */
  return 0;
}

/* Returns the position in the file of the first record of the index */
long index_first_pos(index_t *idx){
  if(idx == NULL){
    printf("Fatal error. Index-Aux1-1.\n");
    exit(1);
  }
  return sizeof(int) + sizeof(type_t);
}
/*--------------------------------------------------------------------------------------------*/


/* ------------- M A I N (E X T E R N A L)     F U N C T I O N S ---------------------------- */
/*
   Creates a file for saving an empty index. The index is initialized
   to be of the specific type (in the basic version this is always INT)
   and to contain 0 entries.
 */
int index_create(type_t type, char *path){
  FILE *f=NULL;
  int n_initial_records = 0; /* At the beggining, we have 0 records */

  if(path == NULL){
    printf("Fatal Error. Index-F1-1.\n.");
    exit(1);
  }

  f = (FILE *) fopen(path, "w");
  if(f == NULL){
    printf("Fatal Error. Index-F1-2.\n");
    exit(1);
  }
  
  fwrite(&type, sizeof(type_t), 1, f); /* Writing the type of the index */
  fwrite(&n_initial_records, sizeof(int), 1, f); /* Writing the number of records (actually 0) */

  fclose(f);

  return 0;
}

/*
   Opens a previously created index: reads the contents of the index
   in an index_t structure that it allocates, and returns a pointer to
   it (or NULL if the files doesn't exist or there is an error).

   NOTE: the index is stored in memory, so you can open and close the
   file in this function. However, when you are asked to save the
   index, you will not be given the path name again, so you must store
   in the structure either the FILE * (and in this case you must keep
   the file open) or the path (and in this case you will open the file
   again).
 */
index_t* index_open(char* path){
  index_t *idx=NULL;
  FILE *f=NULL;
  int i, j;

  if(path == NULL){
    printf("Fatal Error. Index-F2-1.\n");
    exit(1);
  }

  idx = (index_t *) malloc(sizeof(index_t));
  if(idx == NULL){
    printf("Fatal Error. Index_F2-2.\n");
    exit(1);
  }

  f = (FILE *) fopen(path, "r+");
  if(f == NULL){
    free(idx);
    printf("Fatal Error. Index-F2-3.\n");
    exit(1);
  }
  
  fread(&(idx->type), sizeof(int), 1, f);
  fread(&(idx->n_rec), sizeof(int), 1, f);

  idx->list = (irecord **) malloc(idx->n_rec * sizeof(irecord *));
  if(idx->list == NULL){
    free(idx);
    fclose(f);
    printf("Fatal Error. Index-F2-4.\n");
    exit(1);
  }

  for(i = 0; i<idx->n_rec; i++){ /*Allocating and the reading the whole index (it is in the file) */
    idx->list[i] = (irecord *) malloc(sizeof(irecord)); /* Allocating memory for each record */
    if(idx->list[i] == NULL){ /* Error */
      printf("Fatal Error. Index-F2-5.\n");
      for(j=i-1; j>=0; j--){
        free(idx->list[j]);
      }
      free(idx->list);
      free(idx);
      fclose(f);
      exit(1);
    }

    fread(&(idx->list[i]->key), sizeof(int), 1, f); /* Reading the key */
    fread(&(idx->list[i]->n_ptrs), sizeof(int), 1, f); /* Reading the number of positions linked to this key */

    idx->list[i]->ptrs = (long *) malloc(idx->list[i]->n_ptrs * sizeof(long)); /* Allocating memory for the array of positions */
    if(idx->list[i]->ptrs == NULL){ /* Error */
      printf("Fatal Error. Index-F2-6.\n");
      for(j=i-1; j>=0; j--){
        free(idx->list[j]->ptrs);
        free(idx->list[j]);
      }
        free(idx->list);
        free(idx);
        fclose(f);
        exit(1);
    }

    for(j = 0; j < (idx->list[i]->n_ptrs); j++){ /* Reading the positions */
      fread(&(idx->list[i]->ptrs[j]), sizeof(long), 1, f);
    }
  }

  idx->filename = path;

  fclose(f);

  return idx;
}

/*
   Saves the current state of index in the file it came from. See the
   NOTE to index_open.
*/
int index_save(index_t *idx){
  FILE *f=NULL;
  int i, j;

  if(idx==NULL){ /* Error */
    printf("Fatal Error. Index-F3-1.\n");
    exit(1);
  }

  f = (FILE*) fopen(idx->filename, "w"); /* We open it with "w" mode because we have to save all the changes done */
  if(f==NULL){ /* Error */
    printf("Fatal Error. Index-F3-2.\n");
    exit(1);
  }
  
  fwrite(&(idx->type), sizeof(int), 1, f);
  fwrite(&(idx->n_rec), sizeof(int), 1, f);
  
  for(i=0; i<idx->n_rec; i++){
    fwrite(&(idx->list[i]->key), sizeof(int), 1, f);
    fwrite(&(idx->list[i]->n_ptrs), sizeof(int), 1, f);
    
    for(j=0; j<(idx->list[i]->n_ptrs); j++){
      fwrite(&(idx->list[i]->ptrs[j]), sizeof(long), 1, f);
    }
  }
  fclose(f);

  return 0;
}


/*
   Puts a pair key-position in the index. Note that the key may be
   present in the index or not... you must manage both situation. Also
   remember that the index must be kept ordered at all times.
*/
int index_put(index_t *idx, int key, long pos){
  int i;
  int F, L, Fp, Lp; /* first, last, first of pointers' array & last of pointers' array*/
  int M, Mp; /* mid & mid of pointers' array*/
  irecord *ir=NULL;

  if(idx==NULL){
    printf("Fatal Error. Index-F4-1.\n");
    exit(1);
  }

  F = 0;
  L = idx->n_rec - 1;

  while(F <= L){
    M = (F+L)/2;

    if(idx->list[M]->key == key){ /* We found the key so it was already in the index */
      idx->list[M]->ptrs = (long *) realloc(idx->list[M]->ptrs, (idx->list[M]->n_ptrs + 1) * sizeof(long)); /* We just need to put the new position */
      if(idx->list[M]->ptrs == NULL){ /* Error */
        printf("Fatal Error. Index-F4-2.\n");
        exit(1);
      }
      
      Fp = 0;
      Lp = idx->list[M]->n_ptrs - 1;
      
      while(Fp <= Lp){ /* Searching in the array of positions for the place where our new position has to be put */
        Mp = (Fp+Lp)/2;
        
        if(idx->list[M]->ptrs[Mp] == pos){ /* If the position we want to insert it´s already in the array we return a warning */
          printf("WARNING. The position you want to put it´s already saved.\n");
          return -1;
        }
        else if(pos < idx->list[M]->ptrs[Mp]){
          Lp = Mp - 1;
        }
        else{
          Fp = Mp + 1;
        }
      }
      for(i = (idx->list[M]->n_ptrs - 1); i>Fp; i--){ /* Moving the greater the positions to let the space for the new one */
        idx->list[M]->ptrs[i] = idx->list[M]->ptrs[i-1];
      }
      idx->list[M]->ptrs[Fp] = pos;
      (idx->list[M]->n_ptrs)++;
      return 0;
    }
    
    else if(key < idx->list[M]->key){
      L = M-1;
    }
    else{
      F = M+1;
    }
  }
  
  /* If the key is not founded, we insert a new record with this key */
  /* Allocating memory for the new irecord */
  ir = (irecord *) malloc(sizeof(irecord));
  if(ir == NULL){ /* Error */
    printf("Fatal Error. Index-F4-3.\n");
    exit(1);
  }
  
  ir->ptrs = (long *) malloc(sizeof(long));
  if(ir->ptrs == NULL){
    free(ir);
    printf("Fatal Error. Index-F4-4.\n");
    exit(1);
  }
  ir->key = key;
  ir->ptrs[0] = pos;
  ir->n_ptrs = 1;
  
  /* Reallocating the memory of irecords, because we need another one */
  idx->list = (irecord **) realloc(idx->list, (idx->n_rec + 1) * sizeof(irecord *));
  if(idx->list == NULL){ /* Error */
    free(ir->ptrs);
    free(ir);
    printf("Fatal Error. Index-F4-5.\n");
    exit(1);
  }
  idx->n_rec++;
  
  for(i = (idx->n_rec - 1); i>F; i--){
    idx->list[i] = idx->list[i-1];
  }
  idx->list[F] = ir;

  return 0;
}

/*
   Retrieves all the positions associated with the key in the index.

   NOTE: the parameter nposs is not an array of integers: it is
   actually an integer variable that is passed by reference. In it you
   must store the number of elements in the array that you return,
   that is, the number of positions associated to the key. The call
   will be something like this:

   int n
   long **poss = index_get(index, key, &n);

   for (int i=0; i<n; i++) {
       Do something with poss[i]
   }

   ANOTHER NOTE: remember that the search for the key MUST BE DONE
   using binary search.
*/
long* index_get(index_t *idx, int key, int *nposs){
  int i;
  int F, L; /* first and last */
  int M; /* mid */
  long *array=NULL;
  
  
  if(idx==NULL){
    printf("Fatal Error. Index-F5-1.\n");
    exit(1);
  }
  
  F = 0;
  L = idx->n_rec - 1;
  
  while(F <= L){
    M = (F+L)/2;

    if(idx->list[M]->key == key){
      array = (long *) malloc((idx->list[M]->n_ptrs) * sizeof(long)); 
      if(array == NULL){ /* Error */
        printf("Fatal Error. Index-F5-2.\n");
        exit(1);
      }
      for(i=0; i<(idx->list[M]->n_ptrs); i++){ /* We create a copy to avoid to change the index in the main program */
        array[i] = idx->list[M]->ptrs[i];
      }
      *nposs = idx->list[M]->n_ptrs;
      return array;
    }
    else if(key < idx->list[M]->key){
      L = M-1;
    }
    else{
      F = M+1;
    }
  }
  
  return NULL;
}


/*
   Closes the index by freeing the allocated resources
*/
void index_close(index_t *idx){
  int i;

  if(idx==NULL){
    printf("Fatal Error. Index-F7-1.\n");
    exit(1);
  }
  
  if(idx->list != NULL){
    for(i=0; i<idx->n_rec; i++){
      if(idx->list[i] != NULL){
        if(idx->list[i]->ptrs != NULL){
          free(idx->list[i]->ptrs);
        }
        free(idx->list[i]);
      }
    }
    free(idx->list);
  }
  free(idx);
}
