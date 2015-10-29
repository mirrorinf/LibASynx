/*
* Copyright 2015 褚晓敏

* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at

*     http://www.apache.org/licenses/LICENSE-2.0

* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/* This is the internal header file for hash tables.
 * It might be replaced by a implemention in a standard library
 * to gain a better performance. 
 * This is NOT a public interface. It is NOT recommanded to use the 
 * hash table here. */

#ifndef _LIBASYNX_HEADER_HASH_TABLE
#define _LIBASYNX_HEADER_HASH_TABLE

#include "BlockNames.h"
#include <Block.h>

/* The definition of type: HashElement.
 * This is the element of the hash table */
typedef struct HashElement_ {
	void *data;
	void *key;
	struct HashElement_ *next;
} HashElement;

/* The definition of type: HashTable.
 * This is the hash table itself */
typedef struct HashTable_ {
	HashElement *table;
	IntBlockWithTwoVoidPtrInput compare;
	unsigned long tableSize, count;
	UInt32BlockWithVoidPtrInput hash;
	VoidBlockWithVoidPtrInput destroy;
} HashTable;

/* Create a new hash table.
 *
 * Parameters:
 *     tableSize: unsigned 32-bit integer
 *         the size of the new created hash table.
 *     compare: a block with two generic pointers as input and a integer as output
 *         returns 1 if two elements match
 *         returns -1 if not
 *     hash: a block with one generic pointer as input and an unsigned 32-bit integer as output
 *         the hash function for the table
 *     destroy: a block takes a generic pointer and returns no value
 *         this block do the job of destroy the data pointed by a element
 * 
 * Returns:
 *     A pointer to the created table if the creation is successful
 *     NULL if there is no enough memory to create such a table */
HashTable *NewHashTable(unsigned long tableSize, IntBlockWithTwoVoidPtrInput compare, UInt32BlockWithVoidPtrInput hash, VoidBlockWithVoidPtrInput destroy);

/* Destroy a hash table.
 *
 * Parameters:
 *     toBeTrashed: the hash table to be destroyed
 *
 * Returns:
 *     This function deoesn't return any value */
void HashTableDestroy(HashTable *toBeTrashed);

/* Insert a new element to a hash table.
 *
 * Parameters:
 *     self: the hash table to insert the element in
 *     newKey: a generic pointer to the new key
 *     newData: a generic pointer to the new data
 *
 * Returns:
 *     It returns 1 if the insertion succeeds
 *     If there no enough memory to insert the node, return -1
 *
 * Warning:
 *     This function won't check if the element is in the table. */
int HashTableInsert(HashTable *self, void *newKey, void *newData);

/* Look up an element in a hash table.
 *
 * Parameters:
 *     self: the hash table to look up in
 *     key: a generic pointer to the key which is to be looked up
 *
 * Returns:
 *     It returns a generic pointer to the data of the element if the element can be found
 *     If there is no such element in the table, it will return NULL */
void *lookup(HashTable *self, void *key);

#endif
