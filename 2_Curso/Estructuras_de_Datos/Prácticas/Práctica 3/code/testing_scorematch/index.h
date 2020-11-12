/* INDEX MODULE */
/* INDEX STRUCTURE FOR STORING AND RETRIEVING KEY-POSITIONS PAIRS EFFICENTLY IN MEMORY */
#ifndef INDEX_H
#define INDEX_H

#include "type.h"

typedef struct index_ index_t;

/*
   Creates a file for saving an empty index. The index is initialized
   to be of the specific type (in the basic version this is always INT)
   and to contain 0 entries.
 */
int index_create(type_t type, char *path);

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
index_t* index_open(char* path);

/*
   Saves the current state of index in the file it came from. See the
   NOTE to index_open.
*/
int index_save(index_t* index);


/*
   Puts a pair key-position in the index. Note that the key may be
   present in the index or not... you must manage both situation. Also
   remember that the index must be kept ordered at all times.
*/
int index_put(index_t *index, void *key, long pos);

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
long* index_get(index_t *index, void *key, int* nposs);

/*
   Closes the index by freeing the allocated resources
*/
void index_close(index_t *index);

#endif
