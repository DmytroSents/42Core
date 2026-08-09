	SOURCE: https://sites.cs.ucsb.edu/~rich/class/cs170/notes/CondVar/index.html
	https://en.wikipedia.org/wiki/Tree_(abstract_data_type)
	https://en.wikipedia.org/wiki/Binary_tree
	https://www.geeksforgeeks.org/dsa/binary-heap/
	https://www.techiedelight.com/queue-implementation-cpp/
	https://visualgo.net/en/heap?utm_source=chatgpt.com


	https://www.youtube.com/watch?v=VSkvwzqo-Pk&t=178s

>>{Example}[MyStruct's] If I create multiple threads, how do I know current id?
>>explain in simple words, NoCode. How time to burnout should work? How to implement dongle cooldow corretly (when it start and how to check for it)?
>>according to the subject schduler does: take one guy ->pthread_create(id, routine, print) THAN It does pthread_join. Is it correct? (less than four sentences)
>>what to do if pthread_create or mutex_wait or cond_wait fails in the middle of a program? Should I use those func-s infide if foo() < 0? Should I free_all() and terminate then?
--Short version: yes, you should treat failures from pthread_create, pthread_mutex_lock, pthread_cond_wait, etc. as serious errors. In most programs the right response is:
*Check the return value.
*If it’s non‑zero, log/print the error, clean up, and exit (or at least shut down that subsystem cleanly).
>>if I've used pthread_mutex_init and one of the allocations failed along the way, should I destroy all previosly created mutex or just free() an array[mutex] (was previously malloc() on heap)?
>>If I have if (pthread_create(&p->coders[i].thread, NULL, &routine, &p->coders[i])) return (-1); --should I join them before exit() or not?
>>Does an attempt to lock already locke mutex will cause a bug on undef-behavior?
--This is exactly how mutexes are meant to be used. Trying to lock an already locked mutex does not cause undefined behavior
>>answer in one word: is a pointer to a function here: -mandatory; -good_fit; -not;
--Good fit.
>>[answer with one word]. Is it -possible; -feasible; -reasonable; [choose one of the options] -to make scheduler and entire project simply useng mutexes and never pthread_cond_t var;?


A queue follows the FIFO principle; It is my C implementation of class Queue
from C++ std::queue, using a fixed-size circular array. Approximate source code example:	https://www.techiedelight.com/queue-implementation-cpp/
The implementation uses dynamic memory allocation but has a fixed maximum capacity defined when the queue is created [coders_num].If the queue becomes full, insertion is rejected; if it is empty, removal is rejected.
Store rear as the index of the next free slot, not the last occupied slot.
For the EDF common approach is to use std::priority_queue like this 
https://www.codewithc.com/implementing-real-time-scheduling-algorithms-in-c/
https://www.geeksforgeeks.org/dsa/binary-heap/
https://en.wikipedia.org/wiki/Binary_heap
So I had to implement some methods myself

