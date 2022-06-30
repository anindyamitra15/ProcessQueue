#ifndef __CircularQueue_H__
#define __CircularQueue_H__

#include "Arduino.h"
#define DETAIL_STRING_LEN 20
#define QUEUE_SIZE 3U
#define DEBUG_SERIAL Serial

// struct Node
// {
//     int element;
//     char details[DETAIL_STRING_LEN];
// };

template <typename T>
class CircularQueue
{
public:
    CircularQueue()
    {
        __front = -1;
        __rear = -1;
        __queue[QUEUE_SIZE] = {0};
    }

    ~CircularQueue()
    {
        // not needed here
    }

    /**
     * @brief enqueues an element to the queue array
     *
     * @param element
     */
    void push(T element)
    {
        DEBUG_SERIAL.println("push()");
        if (isFull())
        {
            DEBUG_SERIAL.println("Overflow");
        }
        else if (__front < 0 && __rear < 0)
        {
            __front = 0;
            __rear = 0;
            __queue[__rear] = element;
        }
        else
        {
            __rear = (__rear + 1) % QUEUE_SIZE;
            __queue[__rear] = element;
        }
    }

    /**
     * @brief pops the front queue element and returns it to the caller
     *
     * @return int
     */
    T pop()
    {
        DEBUG_SERIAL.println("pop()");
        T temp;
        if (__front < 0 && __rear < 0)
        {
            DEBUG_SERIAL.println("Underflow");
            temp = 0;
        }
        else if (__front == __rear)
        {
            temp = __queue[__front];
            // just reset the heads
            __front = -1;
            __rear = -1;
        }
        else
        {
            temp = __queue[__front];
            __front = (__front + 1) % QUEUE_SIZE;
        }
        return temp;
    }

    int peek()
    {
        return __queue[__front];
    }

    /**
     * @brief just for debugging, will be removed later
     *
     */
    void display()
    {
        DEBUG_SERIAL.println("display()");
        String im = "front: " + String(__front) + ", rear: " + String(__rear);
        DEBUG_SERIAL.println(im);
        unsigned int i = __front - 1;
        do
        {
            i = (i + 1) % QUEUE_SIZE;
            String ind = String(i) + ": ";
            DEBUG_SERIAL.print(ind);
            DEBUG_SERIAL.println(__queue[i]);
        } while (i != __rear);
    }

    /**
     * @brief returns true if the queue is empty
     *
     * @return true, if queue is empty
     * @return false, if queue has some element
     */
    bool isEmpty()
    {
        return (__front < 0 && __rear < 0);
    }

    bool isFull()
    {
        return ((__rear + 1) % QUEUE_SIZE == __front);
    }

    unsigned int size()
    {
        DEBUG_SERIAL.println("size()");
        if (isEmpty())
            return 0;
        else if (__rear >= __front)
            return __rear - __front + 1;
        else
            return QUEUE_SIZE - __front + __rear;
    }

private:
    unsigned long active_size;
    T __queue[QUEUE_SIZE];
    long __front;
    long __rear;
};

#endif