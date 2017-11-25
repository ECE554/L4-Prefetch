#include <stdlib.h>

/*
    Baseline:
        DL1 Accesses: 4247
        DL1 Misses: 345
    
    With 1st Loop:
        DL1 Accesses:  4257
        DL1 Misses: 347
    
    With 2ndst Loop:
        DL1 Accesses:  4267
        DL1 Misses: 347
*/

int main() {
    long* array;
    int it;

    long* a;
    long* b;
    long* c;
    long* d;
    long* e;
    long* f;
    long* g;
    long* h;
    long* i;
    long* j;
       
    array = (long*) malloc(10 * sizeof(long));

    a = array;
    b = array + 1;
    c = array + 2;
    h = array + 7;
    i = array + 8;
    j = array + 9;
    d = array + 3;
    e = array + 4;
    f = array + 5;
    g = array + 6; //Have to jumble the order so a, b, c and h, i, j are not in the cache

    //Only 2 misses
    // for(it = 0; it < 1; it++) {
    //     *a = it;
    //     *b = it;
    //     *c = it;
    //     *d = it;
    //     *e = it;
    //     *f = it;
    //     *g = it;
    //     *h = it;
    //     *i = it;
    //     *j = it;
    // }

    // // // 10 misses
    for(it = 0; it < 1; it++) {
        *j = it;
        *i = it;
        *h = it;
        *g = it;
        *f = it;
        *e = it;
        *d = it;
        *c = it;
        *b = it;
        *a = it;
    }

	return 0;
}