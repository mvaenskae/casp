#include <inttypes.h>
#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

/**
 * This is the API description for your hashtable data-structure
 * that you'll need to implement in C.
 * The table maps strings to arbitrary data, described as a void* in C.
 * An equivalent type in Java would be declared as Hashtable<String, Object>.
 *
 * You will have to implement all the hash_* functions declared
 * in this header file. You are allowed to change/update the
 * struct definitions for hash_table and hash_elem if you need to,
 * but you should not change the API of the function declarations.
 */

// A user provided function that is able to correctly dispose stored
// hash table values
typedef void (* hash_data_free_fn)(void *);

struct hash_elem; // Forward declaration

/**
 * The hash table structure itself.
 */
struct hash_table {
    // number of buckets in the table.
    int num_buckets;

    // pointer to the buckets.
    struct hash_elem** buckets;

    // function that knows how to free inserted data resources
    hash_data_free_fn data_free;
};

/*
 * Structure of a hash table element.
 */
struct hash_elem {
    // Key of the element
    const char* key;
    // Data entry
    void* data;

    // Pointer that points to next hash_elem in case of collisions
    struct hash_elem* next;

    // Extra fields
    struct hash_elem* prev;
    size_t hash;
};

/**
 * Creates a new hash table.
 * @param  t The pointer is either set to the new allocated hash table or NULL in case of an error.
 * @param  f User provided function that frees deleted hash table entries. Can be NULL.
 */
void  hash_create(struct hash_table **t, hash_data_free_fn f)
{
    // WÄT?!
}

/**
 * Releases the entire hash table, including all its entries properly.
 * @param  t The hash table to dispose.
 */
void  hash_release(struct hash_table *t)
{
    for (int i = 0; i < (*t).num_buckets; ++i) {
        struct hash_elem *cur = NULL;
        for (cur = *((*t).buckets + i); cur != NULL; cur = (*cur).next) {
            //free
        }
    }

/**
 * Inserts a key/value pair into the hash-table.
 * @param  t    Insert into this hash-table.
 * @param  key  Corresponding key to insert, if the key already exists, overwrite and free old data.
 * @param  data Data for corresponding key.
 */
void  hash_insert(struct hash_table *t, const char* key, void *data);
{
    size_t hash = hash_value(*t, *key);
    struct hash_elem *new_elem = (struct hash_elem *) malloc(sizeof(struct hash_elem));
    struct hash_elem *elem = find_elem(*t, *key);
    if (elem == NULL) {
        struct hash_elem *last = find_last(*t, hash);
        find_last(*t, *key);
        (*new_elem).key = key;
        (*new_elem).data = data;
        (*new_elem).hash = hash;
        (*new_elem).next = NULL;
        (*new_elem).prev = last;
        if (last != NULL) {
            (*last).next = new_elem;
        } else {
            *((*t).buckets + hash) = new_elem;
        }
    } else if ((*new_elem).key == (*elem).key) {
        free((*elem).data);
        (*elem).data = data;
    }
}

/**
 * Finds an element in the hash-table.
 * @param t   Hash-table to find element in.
 * @param key Key of the corresponding element.
 * @returns Corresponding data entry or NULL in case the key does not exist.
 */
// DONE
void* hash_find(struct hash_table *t, const char* key)
{
    struct hash_elem *current;
    *current = find_elem(*t, *key);
    
    if (current == NULL) {
        return NULL;
    }
    return (*current).data;
}

/**
 * Deletes an element in the hash-table. This function should also call the
 * registered function to free the data.
 * @param  t   Hash table to delete from.
 * @param  key Key to delete. Does nothing if key does not exist.
 */
//DONE
void  hash_delete(struct hash_table *t, const char* key)
{
    struct hash_elem *current, *parent;
    *current = find_elem(*t, *key);
    if (current == NULL) {
        return;
    }
    parent = (*current).prev;

    if (parent == NULL) {
        *((*t).buckets + (*current).hash) = (*current).next;
    } else {
        (*parent).next = (*current).next;
    }
    free((char *) (*current).key);
    free((*current).data);
    free(*current);
}

/*
 ** This function finds the correct bucket to be hashing the key into.
 ** @param  t   Hash table to hash into
 ** @param  key Key to hash
 ** @return     Bucket number in which to put the key
 */
//DONE
size_t hash_value(struct hash_table *t, const char* key)
{
    const size_t mers_prime = 31;
    size_t len = 0;
    for(; *(key + len) != '\0'; ++len){};
    
    size_t hash = 0;
    for (int i = 0; i < len; ++i) {
        hash = (mers_prime * hash + *(key + i)) % (*t).num_buckets;
    }
    return hash;
}

/*
 ** Function which iterates over the bucket in which key should be found.
 ** @param  t   Hash table to check for the key
 ** @param  key Key for which to search
 ** @return     If the key is found return a pointer to it, else return NULL;
 */
//DONE
struct hash_elem *find_elem(struct hash_table *t, const char* key)
{
    size_t bucket = hash_value(*t, *key);
    struct hash_elem *cur = NULL;
    for (cur = *((*t).buckets + bucket); cur != NULL && (*cur).key != key; cur = (*cur).next) {};
    return cur;
}

/*
 ** Function which iterates over a bucket and returns the last element.
 ** @param  t       Hash table to work in
 ** @param  bucket  Bucket identifier
 ** @return         If there exists a key in the bucket, return a pointer to
 **                 the last, else return NULL.
 */
struct hash_elem *find_last(struct hash_table *t, const size_t bucket)
{
    struct hash_elem *cur = NULL;
    for (cur *((*t).buckets + bucket); cur != NULL && (*cur).next != NULL; cur = (*cur).next) {};
    return cur;
}

#endif
