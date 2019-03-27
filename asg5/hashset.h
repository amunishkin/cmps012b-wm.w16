// $Id: hashset.h,v 1.3 2013-03-14 19:25:38-07 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#ifndef __HASHSET_H__
#define __HASHSET_H__

#include <stdbool.h>

typedef struct hashset hashset;

//
// Create a new hashset with a default number of elements.
//
hashset *new_hashset (void);

//
// Frees the hashset, and the words it points at.
//
void free_hashset (hashset *);

void print_debugf_words(hashset *);

//
// Prints the hashfunction's values: cluster sizes, length of hash, 
// number of elements in the hash table.
//
void print_hashfn(hashset *);

void print_hashfn_full(hashset *);

//
// Inserts a new string into the hashset.
//
void put_hashset (hashset *, char*);

//
// Looks up the string in the hashset and returns true if found,
// false if not found.
//
bool has_hashset (hashset *, char*);

#endif

