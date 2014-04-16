#ifndef AL_COMPAT_H
#define AL_COMPAT_H

#include "AL/al.h"

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef DWORD althread_key_t;
int althread_key_create(althread_key_t *key, void (*callback)(void*));
int althread_key_delete(althread_key_t key);
void *althread_getspecific(althread_key_t key);
int althread_setspecific(althread_key_t key, void *val);

typedef LONG althread_once_t;
#define ALTHREAD_ONCE_INIT 0
void althread_once(althread_once_t *once, void (*callback)(void));

inline int alsched_yield(void)
{ SwitchToThread(); return 0; }

WCHAR *strdupW(const WCHAR *str);

/* Opens a file with standard I/O. The filename is expected to be UTF-8. */
FILE *al_fopen(const char *fname, const char *mode);

#define HAVE_DYNLOAD 1

#else

#include <pthread.h>

ALuint timeGetTime(void);
void Sleep(ALuint t);

#define althread_key_t pthread_key_t
#define althread_key_create pthread_key_create
#define althread_key_delete pthread_key_delete
#define althread_getspecific pthread_getspecific
#define althread_setspecific pthread_setspecific

#define althread_once_t pthread_once_t
#define ALTHREAD_ONCE_INIT PTHREAD_ONCE_INIT
#define althread_once pthread_once

#define alsched_yield sched_yield

#define al_fopen(_n, _m) fopen((_n), (_m))

#if defined(HAVE_DLFCN_H) && !defined(IN_IDE_PARSER)
#define HAVE_DYNLOAD 1
#endif

#endif

#ifdef HAVE_DYNLOAD
void *LoadLib(const char *name);
void CloseLib(void *handle);
void *GetSymbol(void *handle, const char *name);
#endif

#endif /* AL_COMPAT_H */
