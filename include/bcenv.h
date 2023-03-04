#ifndef BCENV_BCENV_H
#define BCENV_BCENV_H

#include <string.h>
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
	const char *key;
	const char *value;
};

struct bcenv_cache {
	struct bcenv_pair *cache;
	size_t capacity;
	size_t count;
};

/**
 * for now the cache will simply be a basic array list. Probably should be a map.
 * @param cache
 */
static void private_bcenv_cache_init(struct bcenv_cache *cache) {
	cache->capacity = 0;
	cache->count = 0;
	cache->cache = calloc(sizeof(struct bcenv_cache) * 20);
	if (cache->cache == NULL) {
		cache->capacity = 0;
		cache->count = 0;
	}
}

static void private_bcenv_cache_free(struct bcenv_cache *cache) {
	cache->capacity = 0;
	cache->count = 0;
	free(cache->cache);
	cache->cache = NULL;
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

static char *private_bcenv_cache_get(struct bcenv_cache *cache, const char *key) {
	struct bcenv_pair *p = cache->cache;
	size_t count = cache->count;

	for (size_t i = 0; i < count; i++) {
		if (strcmp(key, p[i].key) == 0) {
			return p[i].value;
		}
	}

	return NULL;
}


struct bcenv {
	struct bcenv_cache file_cache;
	struct bcenv_cache env_cache;
};

/**
 * high level interface
 */
int bcenv_loadf(struct bcenv *env, const char *const filename) {
	//todo: on an initialized bcenv, open and load an file to memory
}

int bcenv_loadfd(struct bcenv *env, FILE *fp) {
	//todo: on an initialized bcenv, load a provided file to memory
}

int bcenv_init(struct bcenv *env) {

	private_bcenv_cache_init(&(env->env_cache));
	if (env->env_cache.cache == NULL) {
		return 0;
	}

	private_bcenv_cache_init(&(env->file_cache));
	if (env->file_cache.cache == NULL) {
		private_bcenv_cache_free(&(env->env_cache));
		return 0;
	}

	return 1;
}

int bcenv_initf(struct bcenv *env, const char *const filename) {
	if (!bcenv_init(env)) {
		return 0;
	}

	return bcenv_loadf(env, filename);
}

int bcenv_initfd(struct bcenv *env, FILE *fp) {
	if (!bcenv_init(env)) {
		return 0;
	}

	return bcenv_loadfd(env, fp);
}

/**
 * Add the key value pair to the bcenv. If a key already exists, nothing happens.
 * @param env
 * @param key
 * @param value
 * @return
 */
int bcenv_add(struct bcenv *env, const char * const key, const char *const value) {
	if (!private_bcenv_cache_get(&(env->file_cache), key)) {
		struct bcenv_pair pair = {
				.key = key,
				.value = value
		};
		private_bcenv_cache_add(&(env->file_cache), pair);

		return 1;
	}

	return 0;
}
char *bcenv_get(struct bcenv *env, const char *const key) {
	//todo: check the file loaded memory cache for a key, return the associated value
	//		if the file cache doesn't have it, check the environment variable memory cache
	//		if the environment variable memory cache doesn't have it, check the environment


	//man getenv() -- returns a point to an environment variables value, or null if it doesn't exist.
	// according to man pages, getenv *could* be used to modify environment, or also, the location that is returned
	//may be static, meaning multiple calls would change the value.
	//So when we cache the value, we will create a copy of it.
}



#endif //BCENV_BCENV_H
