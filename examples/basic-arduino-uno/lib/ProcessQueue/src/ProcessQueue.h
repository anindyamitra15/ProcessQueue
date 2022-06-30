/**
 * @file ProcessQueue.h
 * @author Anindya Kanti Mitra (@anindyamitra15)
 * @brief This is a Library for handling Process Queues using the arduino loop()
 * Main purpose of this implementation is to get rid of kernel panics caused by interrupts.
 * Usecase: an interrupt service routine enqueues a process and the loop dequeues and runs the process keeping the ISR free.
 * @version 1.0 (takes only void(void) functions)
 * @date 2022-06-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __ProcessQueue_H__
#define __ProcessQueue_H__

#include "Arduino.h"
#include "CircularQueue.h"

// Maximum number of processes you want to enqueue in the process queue just for safety, system is dynamic
#define MAX_PROCS 10U
#define DEBUG_SERIAL Serial

#undef QUEUE_SIZE
#define QUEUE_SIZE MAX_PROCS

// void(void) function pointer type
typedef void (*void_function)(void);

class ProcessQueue
{
public:
    ProcessQueue();
    ~ProcessQueue();
    unsigned long size();
    void push(void_function);
    void pop();
    void loop();
    void_function front();
    void_function rear();
    void clear(void);
    bool isEmpty();
    bool isFull();

private:
    CircularQueue<void_function> __queue__;
};

#endif