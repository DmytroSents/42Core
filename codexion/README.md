

	https://www.youtube.com/watch?v=VSkvwzqo-Pk&t=178s

--{Exampe}[MyStruct] If I create multiple threads, how do I know current id?
--explain in simple words, NoCode. How time to burnout should work? How to implement dongle cooldow corretly (when it start and how to check for it)?
--according to the subject schduler does: take one guy ->pthread_create(id, routine, print) THAN It does pthread_join. Is it correct? (less than four sentences)
--what to do if pthread_create or mutex_wait or cond_wait fails in the middle of a program? Should I use those func-s infide if foo() < 0? Should I free_all() and terminate then?
>>Short version: yes, you should treat failures from pthread_create, pthread_mutex_lock, pthread_cond_wait, etc. as serious errors. In most programs the right response is:
*Check the return value.
*If it’s non‑zero, log/print the error, clean up, and exit (or at least shut down that subsystem cleanly).