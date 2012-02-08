/**********************************************************************
 *
 * inetbase.h - basic interface of socket operation
 *
 * for more information, please see the readme file
 *
 **********************************************************************/

#ifndef __INETBASE_H__
#define __INETBASE_H__


/*-------------------------------------------------------------------*/
/* C99 Compatible                                                    */
/*-------------------------------------------------------------------*/
#ifdef _POSIX_C_SOURCE
#if _POSIX_C_SOURCE < 200112L
#undef _POSIX_C_SOURCE
#endif
#endif

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

#ifdef _GNU_SOURCE
#undef _GNU_SOURCE
#endif

#ifdef _BSD_SOURCE
#undef _BSD_SOURCE
#endif

#ifdef __BSD_VISIBLE
#undef __BSD_VISIBLE
#endif

#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define __BSD_VISIBLE 1


/*-------------------------------------------------------------------*/
/* Unix Platform                                                     */
/*-------------------------------------------------------------------*/
#if defined(__unix) || defined(unix) || defined(__MACH__)
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#ifndef __unix
#define __unix
#endif

#if defined(__MACH__) && (!defined(_SOCKLEN_T)) && (!defined(HAVE_SOCKLEN))
typedef int socklen_t;
#endif

#include <errno.h>

#define IESOCKET		-1
#define IEAGAIN			EAGAIN

/*-------------------------------------------------------------------*/
/* Windows Platform                                                  */
/*-------------------------------------------------------------------*/
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#if ((!defined(_M_PPC)) && (!defined(_M_PPC_BE)) && (!defined(_XBOX)))
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif
#ifndef WIN32_LEAN_AND_MEAN  
#define WIN32_LEAN_AND_MEAN  
#endif
#include <windows.h>
#include <winsock2.h>
#else
#ifndef _XBOX
#define _XBOX
#endif
#include <xtl.h>
#include <winsockx.h>
#endif

#include <errno.h>

#define IESOCKET		SOCKET_ERROR
#define IEAGAIN			WSAEWOULDBLOCK

#ifndef _WIN32
#define _WIN32
#endif

typedef int socklen_t;
typedef SOCKET Socket;

#ifndef EWOULDBLOCK
#define EWOULDBLOCK             WSAEWOULDBLOCK
#endif
#ifndef EAGAIN
#define EAGAIN                  WSAEWOULDBLOCK
#endif
#ifndef EINPROGRESS
#define EINPROGRESS             WSAEINPROGRESS
#endif
#ifndef EALREADY
#define EALREADY                WSAEALREADY
#endif
#ifndef ENOTSOCK
#define ENOTSOCK                WSAENOTSOCK
#endif
#ifndef EDESTADDRREQ
#define EDESTADDRREQ            WSAEDESTADDRREQ
#endif
#ifndef EMSGSIZE
#define EMSGSIZE                WSAEMSGSIZE
#endif 
#ifndef EPROTOTYPE
#define EPROTOTYPE              WSAEPROTOTYPE
#endif
#ifndef ENOPROTOOPT
#define ENOPROTOOPT             WSAENOPROTOOPT
#endif
#ifndef EPROTONOSUPPORT
#define EPROTONOSUPPORT         WSAEPROTONOSUPPORT
#endif
#ifndef ESOCKTNOSUPPORT
#define ESOCKTNOSUPPORT         WSAESOCKTNOSUPPORT
#endif
#ifndef EOPNOTSUPP
#define EOPNOTSUPP              WSAEOPNOTSUPP
#endif
#ifndef EPFNOSUPPORT
#define EPFNOSUPPORT            WSAEPFNOSUPPORT
#endif
#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT            WSAEAFNOSUPPORT
#endif
#ifndef EADDRINUSE
#define EADDRINUSE              WSAEADDRINUSE
#endif
#ifndef EADDRNOTAVAIL
#define EADDRNOTAVAIL           WSAEADDRNOTAVAIL
#endif

#ifndef ENETDOWN
#define ENETDOWN                WSAENETDOWN
#endif
#ifndef ENETUNREACH
#define ENETUNREACH             WSAENETUNREACH
#endif
#ifndef ENETRESET
#define ENETRESET               WSAENETRESET
#endif
#ifndef ECONNABORTED
#define ECONNABORTED            WSAECONNABORTED
#endif
#ifndef ECONNRESET
#define ECONNRESET              WSAECONNRESET
#endif
#ifndef ENOBUFS
#define ENOBUFS                 WSAENOBUFS
#endif
#ifndef EISCONN
#define EISCONN                 WSAEISCONN
#endif
#ifndef ENOTCONN
#define ENOTCONN                WSAENOTCONN
#endif
#ifndef ESHUTDOWN
#define ESHUTDOWN               WSAESHUTDOWN
#endif
#ifndef ETOOMANYREFS
#define ETOOMANYREFS            WSAETOOMANYREFS
#endif
#ifndef ETIMEDOUT
#define ETIMEDOUT               WSAETIMEDOUT
#endif
#ifndef ECONNREFUSED
#define ECONNREFUSED            WSAECONNREFUSED
#endif
#ifndef ELOOP
#define ELOOP                   WSAELOOP
#endif
#ifndef EHOSTDOWN
#define EHOSTDOWN               WSAEHOSTDOWN
#endif
#ifndef EHOSTUNREACH
#define EHOSTUNREACH            WSAEHOSTUNREACH
#endif
#define EPROCLIM                WSAEPROCLIM
#define EUSERS                  WSAEUSERS
#define EDQUOT                  WSAEDQUOT
#define ESTALE                  WSAESTALE
#define EREMOTE                 WSAEREMOTE

#else
#error Unknow platform, only support unix and win32
#endif

#ifndef EINVAL
#define EINVAL          22
#endif

#ifdef IHAVE_CONFIG_H
#include "config.h"
#endif

#if defined(i386) || defined(__i386__) || defined(__i386) || \
	defined(_M_IX86) || defined(_X86_) || defined(__THW_INTEL)
	#ifndef __i386__
	#define __i386__
	#endif
#endif

#if (defined(__MACH__) && defined(__APPLE__)) || defined(__MACOS__)
	#ifndef __imac__
	#define __imac__
	#endif
#endif

/* check ICLOCK_TYPE_REALTIME for using pthread_condattr_setclock */
#if defined(__CYGWIN__)
	#define ICLOCK_TYPE_REALTIME
#endif


/*===================================================================*/
/* 32BIT INTEGER DEFINITION                                          */
/*===================================================================*/
#ifndef __INTEGER_32_BITS__
#define __INTEGER_32_BITS__
#if defined(_WIN64) || defined(WIN64) || defined(__amd64__) || \
	defined(__x86_64) || defined(__x86_64__) || defined(_M_IA64) || \
	defined(_M_AMD64)
	typedef unsigned int ISTDUINT32;
	typedef int ISTDINT32;
#elif defined(_WIN32) || defined(WIN32) || defined(__i386__) || \
	defined(__i386) || defined(_M_X86)
	typedef unsigned long ISTDUINT32;
	typedef long ISTDINT32;
#elif defined(__MACOS__)
	typedef UInt32 ISTDUINT32;
	typedef SInt32 ISTDINT32;
#elif defined(__APPLE__) && defined(__MACH__)
	#include <sys/types.h>
	typedef u_int32_t ISTDUINT32;
	typedef int32_t ISTDINT32;
#elif defined(__BEOS__)
	#include <sys/inttypes.h>
	typedef u_int32_t ISTDUINT32;
	typedef int32_t ISTDINT32;
#elif (defined(_MSC_VER) || defined(__BORLANDC__)) && (!defined(__MSDOS__))
	typedef unsigned __int32 ISTDUINT32;
	typedef __int32 ISTDINT32;
#elif defined(__GNUC__)
	#include <stdint.h>
	typedef uint32_t ISTDUINT32;
	typedef int32_t ISTDINT32;
#else 
	typedef unsigned long ISTDUINT32; 
	typedef long ISTDINT32;
#endif
#endif


/*===================================================================*/
/* Global Macro Definition                                           */
/*===================================================================*/
#define ISOCK_NOBLOCK	1		/* flag - non-block       */
#define ISOCK_REUSEADDR	2		/* flag - reuse address   */
#define ISOCK_NODELAY	3		/* flag - no delay        */
#define ISOCK_NOPUSH	4		/* flag - no push         */

#define ISOCK_ERECV		1		/* event - recv           */
#define ISOCK_ESEND		2		/* event - send           */
#define ISOCK_ERROR		4		/* event - error          */

#if (defined(__BORLANDC__) || defined(__WATCOMC__))
#pragma warn -8002  
#pragma warn -8004  
#pragma warn -8008  
#pragma warn -8012
#pragma warn -8027
#pragma warn -8057  
#pragma warn -8066 
#endif

#ifndef ICLOCKS_PER_SEC
#ifdef CLK_TCK
#define ICLOCKS_PER_SEC CLK_TCK
#else
#define ICLOCKS_PER_SEC 1000000
#endif
#endif

#ifndef __IINT8_DEFINED
#define __IINT8_DEFINED
typedef char IINT8;
#endif

#ifndef __IUINT8_DEFINED
#define __IUINT8_DEFINED
typedef unsigned char IUINT8;
#endif

#ifndef __IUINT16_DEFINED
#define __IUINT16_DEFINED
typedef unsigned short IUINT16;
#endif

#ifndef __IINT16_DEFINED
#define __IINT16_DEFINED
typedef short IINT16;
#endif

#ifndef __IINT32_DEFINED
#define __IINT32_DEFINED
typedef ISTDINT32 IINT32;
#endif

#ifndef __IUINT32_DEFINED
#define __IUINT32_DEFINED
typedef ISTDUINT32 IUINT32;
#endif

#ifndef __IINT64_DEFINED
#define __IINT64_DEFINED
#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef __int64 IINT64;
#else
typedef long long IINT64;
#endif
#endif

#ifndef __IUINT64_DEFINED
#define __IUINT64_DEFINED
#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef unsigned __int64 IUINT64;
#else
typedef unsigned long long IUINT64;
#endif
#endif


/*====================================================================*/
/* IULONG/ILONG (ensure sizeof(iulong) == sizeof(void*))              */
/*====================================================================*/
#ifndef __IULONG_DEFINED
#define __IULONG_DEFINED
#if defined(WIN64) || defined(_WIN64)		/* LLP64 mode */
#ifdef _MSC_VER
typedef unsigned __int64 iulong;
typedef __int64 ilong;
#else										/* LP64 or 32/16 mode */
typedef unsigned long long iulong;
typedef long long ilong;
#endif
#else
typedef unsigned long iulong;
typedef long ilong;
#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif


/*===================================================================*/
/* Cross-Platform Time Interface                                     */
/*===================================================================*/

/* sleep in millisecond */
void isleep(unsigned long millisecond);

/* get system time of day */
void itimeofday(long *sec, long *usec);

/* get clock in millisecond */
unsigned long iclock(void);

/* get clock in millisecond 64 */
IINT64 iclock64(void);

/* global millisecond clock value, updated by itimeofday */
volatile extern IINT64 itimeclock;


/*===================================================================*/
/* Cross-Platform Threading Interface                                */
/*===================================================================*/

/* thread entry */
typedef void (*ITHREADPROC)(void *);

/* create thread */
int ithread_create(ilong *id, ITHREADPROC fun, const void *attr, void *args);

/* exit thread */
void ithread_exit(long retval);

/* join thread */
int ithread_join(ilong id);

/* detach thread */
int ithread_detach(ilong id);

/* kill thread */
int ithread_kill(ilong id);


/*===================================================================*/
/* Cross-Platform Mutex Interface                                    */
/*===================================================================*/
#ifndef IMUTEX_TYPE

#if (defined(WIN32) || defined(_WIN32))
#if ((!defined(_M_PPC)) && (!defined(_M_PPC_BE)) && (!defined(_XBOX)))
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif
#ifndef WIN32_LEAN_AND_MEAN  
#define WIN32_LEAN_AND_MEAN  
#endif
#include <windows.h>
#else
#ifndef _XBOX
#define _XBOX
#endif
#include <xtl.h>
#endif

#define IMUTEX_TYPE			CRITICAL_SECTION
#define IMUTEX_INIT(m)		InitializeCriticalSection((CRITICAL_SECTION*)(m))
#define IMUTEX_DESTROY(m)	DeleteCriticalSection((CRITICAL_SECTION*)(m))
#define IMUTEX_LOCK(m)		EnterCriticalSection((CRITICAL_SECTION*)(m))
#define IMUTEX_UNLOCK(m)	LeaveCriticalSection((CRITICAL_SECTION*)(m))

#elif defined(__unix) || defined(unix) || defined(__MACH__)
#include <unistd.h>
#include <pthread.h>
#define IMUTEX_TYPE			pthread_mutex_t
#define IMUTEX_INIT(m)		pthread_mutex_init((pthread_mutex_t*)(m), 0)
#define IMUTEX_DESTROY(m)	pthread_mutex_destroy((pthread_mutex_t*)(m))
#define IMUTEX_LOCK(m)		pthread_mutex_lock((pthread_mutex_t*)(m))
#define IMUTEX_UNLOCK(m)	pthread_mutex_unlock((pthread_mutex_t*)(m))

#else
#define IMUTEX_TYPE			int
#define IMUTEX_INIT(m)		
#define IMUTEX_DESTROY(m)	
#define IMUTEX_LOCK(m)		
#define IMUTEX_UNLOCK(m)	
#endif

#endif



/*===================================================================*/
/* Cross-Platform Socket Interface                                   */
/*===================================================================*/

/* create socket */
int isocket(int family, int type, int protocol);

/* close socket */
int iclose(int sock);

/* connect to */
int iconnect(int sock, const struct sockaddr *addr);

/* shutdown */
int ishutdown(int sock, int mode);

/* bind */
int ibind(int sock, const struct sockaddr *addr);

/* listen */
int ilisten(int sock, int count);

/* accept */
int iaccept(int sock, struct sockaddr *addr);

/* get errno */
int ierrno(void);

/* send */
int isend(int sock, const void *buf, long size, int mode);

/* receive */
int irecv(int sock, void *buf, long size, int mode);

/* sendto */
int isendto(int sock, const void *buf, long size, int mode, 
	const struct sockaddr *addr);

/* recvfrom */
int irecvfrom(int sock, void *buf, long size, int mode, 
	struct sockaddr *addr);

/* ioctl */
int iioctl(int sock, long cmd, unsigned long *argp);

/* set socket option */
int isetsockopt(int sock, int level, int optname, const char *optval, 
	int optlen);

/* get socket option */
int igetsockopt(int sock, int level, int optname, char *optval, 
	int *optlen);

/* get socket name */
int isockname(int sock, struct sockaddr *addr);

/* get peer name */
int ipeername(int sock, struct sockaddr *addr);


/*===================================================================*/
/* Basic Function Definition                                         */
/*===================================================================*/

/* enable option */
int ienable(int fd, int mode);

/* disable option */
int idisable(int fd, int mode);

/* poll event */
int ipollfd(int sock, int event, long millisec);

/* iselect: fds(fd set), events(mask), revents(received events) */
int iselect(const int *fds, const int *events, int *revents, int count, 
	long millisec, void *workmem);

/* ipollfds: poll many sockets with iselect */
int ipollfds(const int *fds, const int *events, int *revents, int count, 
	long millisec);

/* ikeepalive: tcp keep alive option */
int ikeepalive(int sock, int keepcnt, int keepidle, int keepintvl);

/* send all data */
int isendall(int sock, const void *buf, long size);

/* try to receive all data */
int irecvall(int sock, void *buf, long size);

/* format error string */
char *ierrstr(int errnum, char *msg, int size);

/* get host address */
int igethostaddr(struct in_addr *addrs, int count);

/* setup sockaddr */
struct sockaddr* isockaddr_set(struct sockaddr *a, unsigned long ip, int p);

/* set address of sockaddr */
void isockaddr_set_ip(struct sockaddr *a, unsigned long ip);

/* get address of sockaddr */
unsigned long isockaddr_get_ip(const struct sockaddr *a);

/* set port of sockaddr */
void isockaddr_set_port(struct sockaddr *a, int port);

/* get port of sockaddr */
int isockaddr_get_port(struct sockaddr *a);

/* set family */
void isockaddr_set_family(struct sockaddr *a, int family);

/* get family */
int isockaddr_get_family(struct sockaddr *a);

/* set text to ip */
int isockaddr_set_ip_text(struct sockaddr *a, const char *text);

/* make up address */
struct sockaddr *isockaddr_makeup(struct sockaddr *a, const char *ip, int p);

/* convert address to text */
char *isockaddr_str(const struct sockaddr *a, char *text);

/* compare two addresses */
int isockaddr_cmp(const struct sockaddr *a, const struct sockaddr *b);


/*===================================================================*/
/* Memory Hook Definition                                            */
/*===================================================================*/

/* internal malloc of this module */
void* ikmalloc(size_t size);

/* internal free of this module */
void ikfree(void *ptr);

/* set ikmalloc / ikfree internal implementation */
void ikmset(void *ikmalloc_func, void *ikfree_func);


/*===================================================================*/
/* INLINE COMPATIBLE                                                 */
/*===================================================================*/
#ifndef INLINE
#ifdef __GNUC__

#if __GNUC_MINOR__ >= 1  && __GNUC_MINOR__ < 4
#define INLINE         __inline__ __attribute__((always_inline))
#else
#define INLINE         __inline__
#endif

#elif (defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__))
#define INLINE __inline
#else
#define INLINE 
#endif
#endif

#ifndef inline
#define inline INLINE
#endif


/*===================================================================*/
/* Simple Assistant Function                                         */
/*===================================================================*/

/* start network */
int inet_init(void);

/* open a binded udp socket */
int inet_open_port(unsigned short port, unsigned long ip, int noblock);

/* set recv buf and send buf */
int inet_set_bufsize(int sock, long recvbuf_size, long sendbuf_size);


/*===================================================================*/
/* Cross-Platform Poll Interface                                     */
/*===================================================================*/
#define IDEVICE_AUTO		0
#define IDEVICE_SELECT		1
#define IDEVICE_POLL		2
#define IDEVICE_KQUEUE		3
#define IDEVICE_WINCP		4
#define IDEVICE_EPOLL		5
#define IDEVICE_DEVPOLL		6
#define IDEVICE_RTSIG		7

#ifndef IPOLL_IN
#define IPOLL_IN	1
#endif

#ifndef IPOLL_OUT
#define IPOLL_OUT	2
#endif

#ifndef IPOLL_ERR
#define IPOLL_ERR	4
#endif

typedef void * ipolld;

/* init poll device */
int ipoll_init(int device);

/* quit poll device */
int ipoll_quit(void);

/* create poll descriptor */
int ipoll_create(ipolld *ipd, int param);

/* delete poll descriptor */
int ipoll_delete(ipolld ipd);

/* add file/socket into poll descriptor */
int ipoll_add(ipolld ipd, int fd, int mask, void *udata);

/* delete file/socket from poll descriptor */
int ipoll_del(ipolld ipd, int fd);

/* set file event mask in a poll descriptor */
int ipoll_set(ipolld ipd, int fd, int mask);

/* wait for events coming */
int ipoll_wait(ipolld ipd, int millisecond);

/* query one event: loop call it until it returns non-zero */
int ipoll_event(ipolld ipd, int *fd, int *event, void **udata);



/*===================================================================*/
/* Condition Variable Cross-Platform Interface                       */
/*===================================================================*/
struct iConditionVariable;
typedef struct iConditionVariable iConditionVariable;

iConditionVariable *iposix_cond_new(void);

void iposix_cond_delete(iConditionVariable *cond);

/* sleep and wait, returns 1 for been waked up, 0 for timeout */
int iposix_cond_sleep_cs_time(iConditionVariable *cond, 
	IMUTEX_TYPE *mutex, unsigned long millisec);

/* sleep and wait, returns 1 for been waked up, 0 for timeout */
int iposix_cond_sleep_cs(iConditionVariable *cond, 
	IMUTEX_TYPE *mutex);

/* wake up one sleeped thread */
void iposix_cond_wake(iConditionVariable *cond);

/* wake up all sleeped thread */
void iposix_cond_wake_all(iConditionVariable *cond);


/*===================================================================*/
/* Event Cross-Platform Interface                                    */
/*===================================================================*/
struct iEventPosix;
typedef struct iEventPosix iEventPosix;

#define IEVENT_INFINITE 0xffffffff

iEventPosix *iposix_event_new(void);

void iposix_event_delete(iEventPosix *event);

/* set signal to 1 */
void iposix_event_set(iEventPosix *event);

/* set signal to 0 */
void iposix_event_reset(iEventPosix *event);

/* sleep until signal is 1(returns 1), or timeout(returns 0) */
int iposix_event_wait(iEventPosix *event, unsigned long millisec);


/*===================================================================*/
/* ReadWriteLock Cross-Platform Interface                            */
/*===================================================================*/
struct iRwLockPosix;
typedef struct iRwLockPosix iRwLockPosix;

iRwLockPosix *iposix_rwlock_new(void);

void iposix_rwlock_delete(iRwLockPosix *rwlock);

void iposix_rwlock_w_lock(iRwLockPosix *rwlock);

void iposix_rwlock_w_unlock(iRwLockPosix *rwlock);

void iposix_rwlock_r_lock(iRwLockPosix *rwlock);

void iposix_rwlock_r_unlock(iRwLockPosix *rwlock);



#ifdef __cplusplus
}
#endif


#endif


