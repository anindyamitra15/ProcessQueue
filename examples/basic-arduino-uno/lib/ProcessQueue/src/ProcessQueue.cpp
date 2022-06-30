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
    if (__active_procs >= MAX_PROCS)
    {
        DEBUG_SERIAL.println("Overflow");
        return;
    }
    if (_rear == NULL)
    {
        _rear = (struct Node *)malloc(sizeof(struct Node));
        _rear->func_ptr = func_ptr;
        _rear->next = NULL;
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
    if (isEmpty())
    {
        DEBUG_SERIAL.println("Underflow");
        return;
    }

    if (_front != NULL)
    {
        __temp = _front;
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
}

/**
 * @brief clears the entire queue (use with caution!)
 *
 */
void ProcessQueue::clear()
{ // FIXME: clear should silently pop and not call the function
    DEBUG_SERIAL.println("clear()");
    while (_front != NULL)
    {
        __temp = _front;
        _front = _front->next;
        free(__temp);
    }
}

void_function ProcessQueue::front()
{
    return _front->func_ptr;
}

void_function ProcessQueue::rear()
{
    return _rear->func_ptr;
}

bool ProcessQueue::isEmpty()
{
    return (_front == NULL);
}

bool ProcessQueue::isFull()
{
    // TODO: change impl
    return (__active_procs == MAX_PROCS);
}