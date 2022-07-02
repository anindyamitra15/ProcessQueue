# ProcessQueue

This is a library which implements process queue for Arduino.

Basically, we can push function (signature **"void(void)"** ) pointers to the queue. In the loop() function of the arduino sketch, we have to put the loop() method of this (ProcessQueue) class which pops and calls the functions present in the queue till the queue becomes empty.  

The size of the queue, i.e., the maximum number of processes in the queue, can be modified by setting this macro in the arduino sketch:
```
#define MAX_PROCS 30U
```
Here MAX_PROCS is set to 30 (U is the unsigned integer suffix). So, the queue can hold a maximum of 30 function pointers as per the example.
MAX_PROCS is by default set to a size of 10.

## Warning!
Keep the queue size limited based on the available RAM in your microcontroller.

## Class

- **ProcessQueue:**
Only this library is needed to be included to add all the functionalities of this library.
- **CircularQueue:**
This is not necessary to be included. This class is just to keep the queue functionalities separate from the main class i.e., ProcessQueue. However, if the user wants to create a circular queue of finite size and can specify the type using templates, they can include this explicitly.

## Methods in ProcessQueue

- push - pushes a function pointer into the queue
- pop - pops the function pointer at the front of the queue and calls that function.
- clear - silently resets the queue head.
- size - returns the active queue size.
- loop - automates the pop functionality to call all the functions in the queue one by one from the void loop().
- front - returns the function pointer from the front of the queue.
- rear -  returns the function pointer from the back of the queue.
- isEmpty - returns true if the queue is empty.
- isFull - returns true if the queue is full.

## To Do
- More examples for various other boards


