// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#ifndef __INSSORT_H__
#define __INSSORT_H__

// NAME
//    inssort ADT
//
// DESCRIPTION
//    A simple ADT that permits the use of a generic sorter.
//    Here it is used for double and string (char *) data types.

int doublecmp(const void *, const void *);

int strstrcmp(const void *, const void *);

void inssort(void *base, size_t nelem, size_t size, 
             int (*compar) (const void *, const void *));
   // Precond:  base holds all the data to be sorted.
   // Postcond: sorted data in base.

#endif
