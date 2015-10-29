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

/* The internal header file of ASynx data structures */

#ifndef _LIBASYNX_HEADER_DATA_STRUCTURE
#define _LIBASYNX_HEADER_DATA_STRUCTURE

#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <Block.h>
#include "BlockNames.h"
#include "HashTable.h"

/* The definition of type: ASynxFunction
 * This is the type of function
 * selfSize is for future use */
typedef struct ASynxFunction_ {
	VoidBlockWithVoidPtrInput invoke;
	size_t selfSize, inputSize;
} ASynxFunction;

/* The definition of type: ASynxTask
 * This is the essential building block of the ASynx library.
 * The member flag is for future use */
typedef struct ASynxTask_ {
	char identifier[31];
	void *input;
	unsigned int flag;
	struct ASynxTask_ *next;
} ASynxTask;

/* The definition of type: ASynxError
 * This is for the ASynx error handling system
 * flag:
 *     1<<5 : 1 for critical error
 *     1<<10 : 1 for output a error message */
typedef struct ASynxError_ {
	char *descriptor;
	unsigned int flag;
} ASynxError;

/* The definition of type: ASynxQueue
 * This is for the scheduler
 * flag:
 *     1<<5 : 1 for serial queues(not yet supported)
 *     1<<10 : 1 for priority queues(not yet supported) */
typedef struct ASynxQueue_ {
	ASynxTask *head, *tail;
	unsigned long count;
	unsigned int flag;
} ASynxQueue;

/* The definition of type: ASynxContext
 * This is the container of all the things needed
 * Static variables are not supported yet */
typedef struct ASynxContext_ {
	ASynxError *errors;
	unsigned long numberOfErrors;
	unsigned long numberOfThreads;
	HashTable *functions, *staticVariables, *queues;
}

#endif
