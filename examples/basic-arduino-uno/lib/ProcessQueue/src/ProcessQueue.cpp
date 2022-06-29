#include "ProcessQueue.h"

ProcessQueue::ProcessQueue()
{
    __active_procs = 0;
}

ProcessQueue::~ProcessQueue()
{
    clear();
}

/**
 * @brief returns the active size of the queue
 *
 * @return unsigned long
 */
unsigned long ProcessQueue::size()
{
    DEBUG_SERIAL.println("size()");
    return __active_procs;
}

/**
 * @brief pushes a process (function to the queue)
 * TODO: apply MAX_SIZE Protection
 * @param value
 */
void ProcessQueue::push(void_function func_ptr)
{
    DEBUG_SERIAL.println("push()");
    if (_rear == NULL)
    {
        _rear = (struct Node *)malloc(sizeof(struct Node));
        _rear->next = NULL;
        _rear->func_ptr = func_ptr;
        _front = _rear;
    }
    else
    {
        __temp = (struct Node *)malloc(sizeof(struct Node));
        _rear->next = __temp;
        __temp->func_ptr = func_ptr;
        __temp->next = NULL;
        _rear = __temp;
    }
    // _rear->func_ptr();
    __active_procs++;
}

/**
 * @brief returns a function pointer to the caller
 *
 * @return function pointer
 */
void ProcessQueue::pop()
{
    DEBUG_SERIAL.println("pop()");
    __temp = _front;
    if (_front == NULL)
    {
        // handle underflow condition
        // return 0;
        return;
    }
    else
    {
        if (__temp->next != NULL) // if exists
        {
            __temp = __temp->next;
            // TODO: _front->func_ptr();
            _front->func_ptr();
            // free the allocated memory in _front
            free(_front);
            _front = __temp;
        }
        else
        {
            // TODO: _front->func_ptr();
            _front->func_ptr();
            free(_front);
            _front = NULL;
            _rear = NULL;
        }
    }
    __active_procs--;
    // return 0;
}

/**
 * @brief clears the entire queue (use with caution!)
 *
 */
void ProcessQueue::clear()
{
    DEBUG_SERIAL.println("clear()");
    for (unsigned long i = 0; i <= __active_procs; i++)
    {
        pop();
    }
}

void ProcessQueue::front()
{
    _front->func_ptr();
}

void ProcessQueue::rear()
{
    _rear->func_ptr();
}