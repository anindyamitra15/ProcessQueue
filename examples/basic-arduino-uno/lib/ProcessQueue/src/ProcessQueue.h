/**
 * @file ProcessQueue.h
 * @author Anindya Kanti Mitra (@anindyamitra15)
 * @brief This is a Library for handling Process Queues using the arduino loop()
 * Main purpose of this implementation is to get rid of kernel panics caused by interrupts.
 * Usecase: an interrupt service routine enqueues a process and the loop dequeues and runs the process keeping the ISR free.
 * @version 0.1 (takes only void(void) functions)
 * @date 2022-06-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __ProcessQueue_H__
#define __ProcessQueue_H__

#include "Arduino.h"

// Maximum number of processes you want to enqueue in the process queue just for safety, system is dynamic
#define MAX_PROCS 100U
#define DEBUG_SERIAL Serial

typedef void(* void_function)(void);

// Node structure
struct Node
{
    void_function func_ptr;
    struct Node *next;
};

class ProcessQueue
{
private:
    unsigned long __active_procs;
    struct Node *_front = NULL;
    struct Node *_rear = NULL;
    struct Node *__temp = NULL;

public:
    ProcessQueue();
    ~ProcessQueue();
    unsigned long size();
    void push(void_function);
    void pop(void);
    void front();
    void rear();
    void clear(void);
    bool isEmpty();
    bool isFull();
};

#endif