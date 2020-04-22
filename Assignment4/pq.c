/*
 * This file contains the implementation of a priority queue.
 *
 * You must complete the implementations of these functions:
 *   pq_insert()
 *   pq_first()
 *   pq_remove_first()
 */

#include <stdlib.h>
#include <assert.h>

#include "dynarray.h"
#include "pq.h"

// This is the initial capacity that will be allocated for the heap.
#define INITIAL_HEAP_CAPACITY 16

/*
 * This is the definition of the structure we will use to represent the
 * priority queue.  It contains only a dynamic array, which will be used to
 * store the heap underlying the priority queue.
 */
struct pq {
  struct dynarray* heap;
};


/*
 * This is an auxiliary structure that we'll use to represent a single element
 * in the priority queue.  It contains two fields:
 *
 *   priority - the priority value assigned to the item
 *   item - the pointer to the data item represented by this element
 *
 * Both of these will come directly from the corresponding values passed to
 * pq_insert().
 */
struct pq_elem {
  int priority;
  void* item;
};


/*
 * This function allocates and initializes a new priority queue.
 *
 * You should not modify this function.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
  assert(pq);
  pq->heap = dynarray_create(INITIAL_HEAP_CAPACITY);
  return pq;
}


/*
 * This function frees the memory associated with a priority queue.
 *
 * You should not modify this function.
 */
void pq_free(struct pq* pq) {
  assert(pq);
  while (!pq_isempty(pq)) {
    pq_remove_first(pq);
  }
  dynarray_free(pq->heap);
  free(pq);
}

/*
 * This function returns 1 if the given priority queue is empty or 0
 * otherwise.
 *
 * You should not modify this function.
 */
int pq_isempty(struct pq* pq) {
  assert(pq);
  return dynarray_size(pq->heap) == 0;
}


/*
 * This function inserts a new item with a specified priority into a priority
 * queue.
 *
 * You should complete the implementation of this function.  The first part
 * is done for, where a new element is created to be placed into the dynamic
 * array underlying the priority queue.
 */
void pq_insert(struct pq* pq, void* item, int priority) {
  assert(pq);

  struct pq_elem * element = malloc(sizeof(struct pq_elem ));
  element->priority = priority;
  element->item = item;

 //printf("%s","This is the size: " );// testing
 //printf("%d\n",dynarray_size(pq->heap) );// testing
 printf("%s\n", " " );
 int current = dynarray_size(pq->heap);

  dynarray_insert(pq->heap, -1, element);

  //int current = dynarray_size(pq->heap);
  int parent = (current-1)/2;
  struct pq_elem *temp2 = dynarray_get(pq->heap, parent);

  while (element->priority < temp2->priority){
    dynarray_set(pq->heap, current, temp2);
    dynarray_set(pq->heap, parent, element);
    current = parent;
    parent = (current-1)/2;
    temp2 = dynarray_get(pq->heap, parent);
    //printf("%s\n","I made it here" );
  }

/*
  int c = dynarray_size(pq->heap);//for testing
  for( int i =0 ; i < c; i++){// for testing
    struct pq_elem *tmp = dynarray_get(pq->heap, i);// for teseting
    printf("%d\n",tmp->priority );// for testing
  }//for testing*/


  /*
   * Restore the heap so that it has the property that every node's priority
   * value is less than the priority values of its children.  This can be
   * done by "percolating" the newly added element up in the heap array.  To
   * perform the percolation, you will have to compare the priority values of
   * the struct pq_elems in the heap array (i.e. by comparing the
   * elem->priority values).
   */

}


/*
 * This function returns the first (highest-priority) item from a priority
 * queue without removing it.
 *
 * You should complete the implementation of this function.
 */
void* pq_first(struct pq* pq) {
  assert(pq);
  assert(dynarray_size(pq->heap) > 0);

  return dynarray_get(pq->heap,0);
}


void percolate_heap(struct pq* pq, int max, int pos)
{
  int leftIdx = pos*2 +1;
  int rightIdx = pos*2+2;
  int small_index;

  if (rightIdx < max) {
    struct pq_elem *left_element = dynarray_get(pq->heap,leftIdx);
    struct pq_elem *righ_element = dynarray_get(pq->heap, rightIdx);

    if (left_element->priority < righ_element->priority) {
      small_index = leftIdx;
    }else{
      small_index = rightIdx;
    }
    struct pq_elem * smaller_element = dynarray_get(pq->heap, small_index);
    struct pq_elem * current_element = dynarray_get(pq->heap, pos);
      if (smaller_element->priority < current_element->priority) {
        struct pq* temp3 = dynarray_get(pq->heap, small_index);
        dynarray_set(pq->heap, small_index, dynarray_get(pq->heap, pos));
        dynarray_set(pq->heap, pos, temp3);
        percolate_heap(pq, max,small_index);
      }
    }
    else if (leftIdx < max ) {
      if (dynarray_get(pq->heap, leftIdx) < dynarray_get(pq->heap, pos)) {
        struct pq* temp4 = dynarray_get(pq->heap, leftIdx);
        dynarray_set(pq->heap, leftIdx, dynarray_get(pq->heap, pos));
        dynarray_set(pq->heap, pos, temp4);
      }
    }

}


/*
 * This function removes the first (highest-priority) element from a priority
 * queue and returns its value.
 *
 * You should complete this function
 */
void* pq_remove_first(struct pq* pq) {
  assert(pq);
  assert(dynarray_size(pq->heap) > 0);
  struct pq_elem *first_elem = dynarray_get(pq->heap, 0);

  int l =  dynarray_size(pq->heap);
  int last_index = l-1;
  dynarray_set(pq->heap,0, dynarray_get(pq->heap,last_index));
  dynarray_remove(pq->heap, last_index);

  percolate_heap(pq, last_index, 0);

  if (first_elem != 0) {
    return first_elem;
  }
  return;



  /*
   * Determine what index in the heap array corresponds to the highest-priority
   * element (i.e. the one with the lowest priority value), and store the
   * value there in first_elem.
   */

  /*
   * Replace the highest-priority element with the appropriate one from within
   * the heap array.  Remove that replacement element from the array after
   * copying its value to the location of the old highest-priority element..
   */

  /*
   * Restore the heap so that it has the property that every node's priority
   * value is less than the priority values of its children.  This can be
   * done by "percolating" the element that replaced the highest-priority
   * element down in the heap array.  To perform the percolation, you will
   * have to compare the priority values of the struct pq_elems in the heap
   * array (i.e. by comparing the elem->priority values).  It may be helpful
   * to write a helper function to accomplish this percolation down.
   */

  /*
   * Return the extracted item, if the element taken out of the priority
   * queue is not NULL
   */
}
