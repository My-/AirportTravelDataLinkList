#ifndef HASHSET
#define HASHSET

#include "../data/data.h"
#include "../node/node.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean
// #include <string.h>     // string

#define MAX_BUCKETS 1000

struct hashset {
    int * buckets;
    int size;
    struct hashset_type * _it;
};

struct hashset_type {
    bool (*add)(struct hashset *this, struct data *data);
    bool (*contains)(struct hashset *this, struct data *data);
    bool (*isEmpty)(struct hashset *this);
    bool (*remove)(struct hashsset *this, struct data *data);
    int (*size)(struct hashset *this);
} HashSet;

#endif
