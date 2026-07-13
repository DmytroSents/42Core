	SOURCE: https://sites.cs.ucsb.edu/~rich/class/cs170/notes/CondVar/index.html



	https://www.youtube.com/watch?v=VSkvwzqo-Pk&t=178s

>>{Example}[MyStruct] If I create multiple threads, how do I know current id?
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