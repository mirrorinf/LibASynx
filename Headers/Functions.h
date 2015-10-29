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

/* The internal header file of the function definitions */

#ifndef _LIBASYNX_HEADER_FUNCTIONS
#define _LIBASYNX_HEADER_FUNCTIONS

#include <Block.h>
#include "BlockNames.h"
#include "DataStructure.h"

/* Create a new ASynxContext object
 *
 * Parameters:
 *     numberOfThreads : an unsigned 32-bit integer for the number of threads
 *
 * Returns:
 *     It returns the created context if the operation was successful and NULL if any error occured */
ASynxContext *NewASynxContext(unsigned long numberOfThreads);

/* Regist a function to the context
 *
 * Parameters:
 *     context : the context in which to regist the function
 *     identifier : a string identifies the function
 *     invoke : the block that invokes the function
 *     inputSize : the size of the input
 *
 * Returns:
 *     It returns 1 if the registration was successful and -1 if any error occured */
int ASynxFunctionRegist(ASynxContext *context, const char *identifier, VoidBlockWithVoidPtrInput invoke, size_t inputSize);

/* Call a function in async mode
 *
 * Parameters:
 *     context : ASynxContext to call the function in
 *     queue : a string that identifies the queue to which to be submitted
 *     identifier : a string that identifies the function to be called
 *     input : a generic pointer to the input of the function
 *
 * Returns:
 *     It returns 1 if the function call was successfully submitted to the queue and -1 if any error occured */
int ASynxFunctionCallASync(ASynxContext *context, const char *queue, const char *identifier, void *input);

/* Call a function in sync mode
 *
 * Parameters:
 *     context : ASynxContext to call the function in
 *     queue : a string that identifies the queue to which to be submitted
 *     identifier : a string that identifies the function to be called
 *     input : a generic pointer to the input of the function
 *
 * Returns:
 *     It returns 1 if the function call was successfully submitted to the queue and successfully exited. If any error occured, it will return -1 */
int ASynxFunctionCallSync(ASynxContext *context, const char *queue, const char *identifier, void *input);

/* Add a new queue to a context
 *
 * Parameters:
 *     context : ASynxContext to which the queue is added
 *     identifier : The string that identifies the queue
 *     flag : the flag that describes the queue(only 0 supported yet)
 *
 * Returns:
 *     1 if the addition was successful and -1 if any error occured */
int ASynxAddNewQueue(ASynxContext *context, const char *identifier, unsigned int flag);

#endif
