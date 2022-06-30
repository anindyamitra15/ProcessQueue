#include "ProcessQueue.h"

ProcessQueue::ProcessQueue()
{
    clear();
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
inline unsigned long ProcessQueue::size()
{
    DEBUG_SERIAL.println("size()");
    return __queue__.size();
}

/**
 * @brief pushes a process (function to the queue)
 * TODO: apply MAX_SIZE Protection
 * @param value
 */
void ProcessQueue::push(void_function func_ptr)
{
    DEBUG_SERIAL.println("push()");
    __queue__.push(func_ptr);
}

/**
 * @brief executes the function popped
 * from the queue
 */
void ProcessQueue::pop()
{
    DEBUG_SERIAL.println("pop()");
    void_function temp = __queue__.pop();
    if (temp == NULL || temp == 0x0)
        DEBUG_SERIAL.println("NULL reference in function");
    else
        temp();
}

/**
 * @brief Process Queue event loop function
 * put it inside while(1) or void loop()
 */
void ProcessQueue::loop()
{
    if (!isEmpty())
    {
        pop();
    }
}

/**
 * @brief clears the entire queue
 * (use with caution!)
 */
inline void ProcessQueue::clear()
{
    DEBUG_SERIAL.println("clear()");
    __queue__.reset();
}

/**
 * @brief returns the function pointer of
 * the function at the front of the queue
 * without modifying the queue
 *
 * @return void_function
 */
inline void_function ProcessQueue::front()
{
    return __queue__.peek();
}

/**
 * @brief return the function pointer of
 * the function at the rear of the queue
 * without modifying the queue
 *
 * @return void_function
 */
inline void_function ProcessQueue::rear()
{
    return __queue__.peek_rear();
}

/**
 * @brief boolean to check if queue is empty
 *
 * @return true, if queue empty
 * @return false, if queue has some functions
 */
inline bool ProcessQueue::isEmpty()
{
    return __queue__.isEmpty();
}

/**
 * @brief boolean to check if queue is full
 *
 * @return true, if queue full
 * @return false, if queue has some space
 */
inline bool ProcessQueue::isFull()
{
    return __queue__.isFull();
}
