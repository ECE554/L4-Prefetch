#include <stdlib.h>

/* 
    Our openended prefetcher remembers the next adress acsessed after an address the last time it was accessed 
    Hence the key to test it is to have repeating sequential accesses of the same memory

    In our config we have only 2 cache lines with 8 blocks wide

    Since we have 4 long variables, it is impossible for all of them to fit in the cache at the same time

    We ran the benchmark twice:

    1. With the TEST code commented out:
        DL1 Accesses:   7050
        DL1 Misses:     3336

    Now because in the for loop the same acsesses always follow eachother,
    we expect to get 4000 more acsesses but only 4 more misses:

    2. With TEST code uncommented:
        DL1 Accesses:   11050
        DL1 Misses:     3341

    Difference:
        DL1 Accesses:   4000
        DL1 Misses:     4

    As expected, we get 4000 acsesses (in the for loop)
    And exactly 4 misses (the first 4 acsesses)

    After that the prefetcher always prefetches the next variable in memory

    **To make sure that our prefetcher is responsible for the improvement, we ran the benchmark with prefetcher = 0 in the config
        Same acsesses, but dl1 misses = 7918, so obvously our prefetcher is doing some work

*/



int main() {
    //Init code
    int i;
    long* a = (long*)malloc(sizeof(long));
    long* b = (long*)malloc(sizeof(long));
    long* c = (long*)malloc(sizeof(long));
    long* d = (long*)malloc(sizeof(long));

    //Seting the wrong order in the prefetcher 
    *a = 20;
    *d = 25;
    *c = 30;
    *b = 40;
    *b = 45;


    //END init code

    
    //TEST code

    //4 reads per loop;
    for (i = 0; i < 1000; i++) {
        *a = i;
        *b = i;
        *c = i;
        *d = i;
    }

    //END TEST code
}

