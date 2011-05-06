#ifndef RBX_DETECTION
#define RBX_DETECTION

#include<time.h>

/*
 * This file, when included, defines a bunch of macros that have detected
 * values about the current machine.
 *
 * Towards the bottom, we also use those macros to setup some configuration
 * variables.
 *
 */


/** DETECT */

#if __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ >= 1050 && \
    __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ < 1070
#define OS_X_10_5
#define _XOPEN_SOURCE
#define HAS_UCONTEXT
#elif defined(__APPLE__) && defined(__APPLE_CC__)
#define OS_X_ANCIENT
#endif

#if defined(__linux__)
#define HAS_UCONTEXT
#endif

#if defined(__FreeBSD__)
#define HAS_UCONTEXT
#endif

#if defined(i386) || defined(__i386) || defined(__i386__)
#define IS_X86
#endif

#if defined(_LP64) || defined(__LP64__) || defined(__x86_64__) || defined(__amd64__)
#define IS_X8664

#elif defined(IS_X86)
#define IS_X8632

#endif

/** CONFIGURE */

#ifdef HAS_EXECINFO
#define USE_EXECINFO
#endif

#ifndef HAS_REALPATH
/* this is basically a no-op */
char *realpath(char *name, char *resolved){
	return name;
}
#endif

#ifndef HAS_REALPATH
#define timeradd(a, b, result)                  \
	do {                        \
  	(result)->tv_sec = (a)->tv_sec + (b)->tv_sec;           \
  		(result)->tv_usec = (a)->tv_usec + (b)->tv_usec;            \
  		if ((result)->tv_usec >= 1000000)               \
  		{                       \
  			++(result)->tv_sec;                 \
  				(result)->tv_usec -= 1000000;               \
  		}                       \
  } while (0);

#define timersub(a, b, result)                  \
	do {                        \
		(result)->tv_sec = (a)->tv_sec - (b)->tv_sec;           \
		(result)->tv_usec = (a)->tv_usec - (b)->tv_usec;            \
		if ((result)->tv_usec < 0) {                \
			--(result)->tv_sec;                 \
			(result)->tv_usec += 1000000;               \
		}                       \
	} while (0);

#endif

#ifndef HAS_CRYPT
const char *crypt(const char *key, const char *salt){
	return key; //dear god, this implementation is temporary
}
#endif

#ifndef HAS_GETRUSAGE
int getrusage(int who, struct rusage *r_usage){
	return 0; //success!
}
#endif

#ifndef HAS_NANOSLEEP
int nanosleep(const struct timespec *req, struct timespec *rem){
	return 0; //derp
}
#endif

#ifndef HAS_TIMEGM
time_t timegm (struct tm *tm){
	time_t t = 0;
	return t;
}
#endif

#endif
