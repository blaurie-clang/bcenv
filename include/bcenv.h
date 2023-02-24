#ifndef BCENV_BCENV_H
#define BCENV_BCENV_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

/**
 * bcenv will be a program meant for loading up the environment
 * It'll read a provided file, or it'll read (and cache) environment variables.
 *
 * In general, the file will take precedent over the environment
 */

struct bcenv_pair {
	char *key;
	char *value;
};

struct bcenv_cache {
	struct bcenv_pair *cache;
	size_t capacity;
	size_t count;
};

/**
 * for now the cache will simply be a basic array list.
 * @param cache
 */
static void private_bcenv_cache_init(struct bcenv_cache *cache) {
	cache->capacity = 0;
	cache->count = 0;
	cache->cache = malloc(sizeof(struct bcenv_cache) * 20);
	if (cache->cache == NULL) {
		cache->capacity = 0;
		cache->count = 0;
	}
}

static void private_bcenv_cache_add(struct bcenv_cache *cache, const struct bcenv_pair pair) {
	struct bcenv_pair *p = cache->cache;
	size_t cap = cache->capacity;
	size_t count = cache->count;

	if (count >= cap) {
		//todo grow
	}

	while (p->key) {
		p++;
	}
	*p = pair;
}

static void private_bcenv_cache_get(struct bcenv_cache *cache, const char *key) {
	
}


struct bcenv {
	struct bcenv_cache file_cache;
	struct bcenv_cache env_cache;
};

/**
 * high level interface
 */
int bcenv_init(struct bcenv *env) {
	//todo: initialize the bcenv struct
}
int bcenv_initf(struct bcenv *env, const char *const filename) {
	//todo: initialize, open and read an env file
}
int bcenv_initfd(struct bcenv *env, FILE *fp) {
	//todo: initialize, read a provided file to memory
}
int bcenv_loadf(struct bcenv *env, const char *const filename) {
	//todo: on an initialized bcenv, open and load an file to memory
}
int bcenv_loadfd(struct bcenv *env, FILE *fp) {
	//todo: on an initialized bcenv, load a provided file to memory
}
int bcenv_add(struct bcenv *env, const char * const key, const char *const value) {
	//todo: add a variable to the file loaded memory cache
}
char *bcenv_get(struct bcenv *env, const char *const key) {
	//todo: check the file loaded memory cache for a key, return the associated value
	//		if the file cache doesn't have it, check the environment variable memory cache
	//		if the environment variable memory cache doesn't have it, check the environment
}



#endif //BCENV_BCENV_H
