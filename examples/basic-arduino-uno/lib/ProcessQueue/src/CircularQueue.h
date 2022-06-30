#ifndef __CircularQueue_H__
#define __CircularQueue_H__

#include "Arduino.h"
#define DETAIL_STRING_LEN 20
#define QUEUE_SIZE 3U
#define DEBUG_SERIAL Serial

struct Node
{
    int element;
    char details[DETAIL_STRING_LEN];
};

class CircularQueue
{
public:
    CircularQueue()
    {
        front = -1;
        rear = -1;
        queue[QUEUE_SIZE] = {0};
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
    void push(int element)
    {
        DEBUG_SERIAL.println("push()");
        if (isFull())
        {
            DEBUG_SERIAL.println("Overflow");
        }
        else if (front < 0 && rear < 0)
        {
            front = 0;
            rear = 0;
            queue[rear] = element;
        }
        else
        {
            rear = (rear + 1) % QUEUE_SIZE;
            queue[rear] = element;
        }
    }

    /**
     * @brief pops the front queue element and returns it to the caller
     *
     * @return int
     */
    int pop()
    {
        DEBUG_SERIAL.println("pop()");
        int temp;
        if (front < 0 && rear < 0)
        {
            DEBUG_SERIAL.println("Underflow");
            temp = 0;
        }
        else if (front == rear)
        {
            temp = queue[front];
            // just reset the heads
            front = -1;
            rear = -1;
        }
        else
        {
            temp = queue[front];
            front = (front + 1) % QUEUE_SIZE;
        }
        return temp;
    }

    int peek()
    {
        return queue[front];
    }

    /**
     * @brief just for debugging, will be removed later
     *
     */
    void display()
    {
        DEBUG_SERIAL.println("display()");
        String im = "front: " + String(front) + ", rear: " + String(rear);
        DEBUG_SERIAL.println(im);
        unsigned int i = front - 1;
        do
        {
            i = (i + 1) % QUEUE_SIZE;
            String ind = String(i) + ": ";
            DEBUG_SERIAL.print(ind);
            DEBUG_SERIAL.println(queue[i]);
        } while (i != rear);
    }

    /**
     * @brief returns true if the queue is empty
     *
     * @return true, if queue is empty
     * @return false, if queue has some element
     */
    bool isEmpty()
    {
        return (front < 0 && rear < 0);
    }

    bool isFull()
    {
        return ((rear + 1) % QUEUE_SIZE == front);
    }

    unsigned int size()
    {
        DEBUG_SERIAL.println("size()");
        if (isEmpty())
            return 0;
        else if (rear >= front)
            return rear - front + 1;
        else
            return QUEUE_SIZE - front + rear;
    }

private:
    unsigned long active_size;
    int queue[QUEUE_SIZE];
    long front;
    long rear;
};

#endif