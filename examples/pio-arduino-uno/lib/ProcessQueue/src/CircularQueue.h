#ifndef __CircularQueue_H__
#define __CircularQueue_H__

#include "Arduino.h"
#define DETAIL_STRING_LEN 20
#define QUEUE_SIZE 3U // FINITE SIZE

template <typename T>
class CircularQueue
{
public:
    CircularQueue()
    {
        __front = -1;
        __rear = -1;
        __queue_array[QUEUE_SIZE] = {0};
    }

    /**
     * @brief enqueues an element to the queue array
     *
     * @param element
     * @return true, if successful
     * @return false, if overflow
     */
    bool push(T element)
    {
        if (isFull())
            return false;

        if (__front < 0 && __rear < 0)
        {
            __front = 0;
            __rear = 0;
            __queue_array[__rear] = element;
        }
        else
        {
            __rear = (__rear + 1) % QUEUE_SIZE;
            __queue_array[__rear] = element;
        }
        return true;
    }

    /**
     * @brief pops the front queue element and returns it to the caller
     *
     * @return variable of type T which is popped
     */
    T pop()
    {
        long temp_index;

        if (__front < 0 && __rear < 0)
            return NULL;

        if (__front == __rear)
        {
            temp_index = __front; // holding the index temporarily
            // just resetting the heads
            __front = -1;
            __rear = -1;
            return __queue_array[temp_index];
        }
        else
        {
            temp_index = __front; // holding the index temporarily
            __front = (__front + 1) % QUEUE_SIZE;
            return __queue_array[temp_index];
        }
    }

    /**
     * @brief silently reset the queue without modifying the elements
     * basically resetting the front and rear heads
     */
    void reset()
    {
        __front = -1;
        __rear = -1;
    }

    /**
     * @brief returns the reference without popping
     *
     * @return variable of type specified
     */
    T peek()
    {
        return __queue_array[__front];
    }

    /**
     * @brief returns the reference from the rear without modifying queue
     *
     * @return variable of type specified
     */
    T peek_rear()
    {
        return __queue_array[__rear];
    }

    /**
     * @brief boolean to show if the queue is empty
     *
     * @return true, if queue is empty
     * @return false, if queue has some element
     */
    bool isEmpty()
    {
        return (__front < 0 && __rear < 0);
    }

    /**
     * @brief boolean to show if the queue is Full
     *
     * @return true, if queue is full
     * @return false, if queue has space
     */
    bool isFull()
    {
        return ((__rear + 1) % QUEUE_SIZE == __front);
    }

/**
 * @brief returns the size of the active queue
 * 
 * @return unsigned int 
 */
    unsigned long size()
    {
        if (isEmpty())
            return 0;
        else if (__rear >= __front)
            return __rear - __front + 1;
        else
            return QUEUE_SIZE - __front + __rear;
    }

private:
    T __queue_array[QUEUE_SIZE];
    long __front;
    long __rear;
};

#endif