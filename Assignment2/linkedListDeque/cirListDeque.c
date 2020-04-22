// Jose Manuel Lopez Alcala
// CS 261 
// Assignment 2 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "cirListDeque.h"

/* Double Link Struture */
struct DLink {
	TYPE value;/* value of the link */
	struct DLink * next;/* pointer to the next link */
	struct DLink * prev;/* pointer to the previous link */
};

# define TYPE_SENTINEL_VALUE DBL_MAX 


/* ************************************************************************
 Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
 ************************************************************************ */

struct cirListDeque {
	int size;/* number of links in the deque */
	struct DLink *Sentinel;	/* pointer to the sentinel */
};
/* internal functions prototypes */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);



/* ************************************************************************
	Deque Functions
************************************************************************ */

/*
 create a new circular list deque
 
	pre:    none
 	post:	returns pointer to allocated deque q, q->Sentinel is allocated and q->size equals zero
 
 */
struct cirListDeque *createCirListDeque()
{
   struct cirListDeque *q=  malloc(sizeof(struct cirListDeque));
   assert(q!=0);
   q->Sentinel =  malloc(sizeof(struct DLink));
   assert(q->Sentinel != 0);
   q->Sentinel->next = q->Sentinel;
   q->Sentinel->prev = q->Sentinel;
   q->size = 0; 

   return q;
}


/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
   struct DLink * link = malloc(sizeof(struct DLink));
   assert(link != 0);
   link->value = val;
   return link;
}

/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	v		value of the new link to be added after the existing link
	pre:	q is not null
	pre: 	lnk is not null
	pre:	lnk is in the deque 
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v)
{
   assert(q != 0);
   assert(lnk != 0);
   assert(lnk->prev!=0 && lnk->next != 0);//check if this is in deque 
   struct DLink *newLink = _createLink(v);
   assert(newLink != 0);
   newLink->next = lnk->next;
   lnk->next->prev = newLink;
   lnk->next = newLink;
   newLink->prev = lnk;
   q->size ++;
}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val) 
{
   assert(q!=0);
   //This next line should work because the 
   //sentinel's prvious is the last link in the 
   //deque 
   _addLinkAfter(q, q->Sentinel->prev, val);
}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
   {
	 assert(q != 0);
	 //This next line should work because the new link
	 //will be added to the space after the sentinel
	 _addLinkAfter(q, q->Sentinel, val);

      }

      /* Get the value of the front of the deque

	      param: 	q		pointer to the deque
	      pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q) 
{
   assert(q != 0 && (q->Sentinel->next != q->Sentinel));

   return (q->Sentinel->next->value);
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
   assert(q != 0 && (q->Sentinel->prev != q->Sentinel));
   return (q->Sentinel->prev->value);
}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{
   assert(q != 0 && (q->Sentinel->next != q->Sentinel));
   lnk->prev->next = lnk->next;
   lnk->next->prev = lnk->prev;
   free(lnk);
   q->size --;
}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) {
   assert(q != 0 && (q->Sentinel->next != q->Sentinel));
   _removeLink(q, q->Sentinel->next);
}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
   assert(q != 0 && (q->Sentinel->prev != q->Sentinel));
   _removeLink(q, q->Sentinel->prev);
}

/* De-allocate all links of the deque, and the deque itself

	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including Sentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
   for(int i = 0; i < q->size; i++)
   {
      removeFrontCirListDeque(q);
   }
   free(q->Sentinel);
   free(q);
   q = 0; 

}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) {
   assert(q != 0);
   if( q->Sentinel->next == q->Sentinel  )
   {
      return 1;
   }else{
      return 0;
   }

}


/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
   assert(q != NULL  && isEmptyCirListDeque(q) != 1);
   assert(q->Sentinel != 0);
   struct DLink *temp;
   //printf("%s \n", "Here");// for testing
   temp = q->Sentinel->next;
   ///printf("%s \n", "Here");
   for(int i = 0; i < q->size; i++)
   {
      //printf("Here");//for testing 
      printf("%f%c", temp->value, ',');
      temp = temp->next;
   }
   printf("\n");
}

