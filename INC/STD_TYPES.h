
#ifndef _STD_TYPES_H
#define _STD_TYPES_H
// Defining  NULL

#define NULL   ((void *) 0)

typedef char * pstring;
typedef char  string;

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;
typedef unsigned long long int u64;

typedef signed char s8;
typedef signed short int s16;
typedef signed long  int s32;
typedef long long int s64;

typedef float  f32;
typedef double f64;

typedef unsigned char * pu8;
typedef signed char * ps8;
typedef unsigned short int * pu16;
typedef signed short int * ps16;
typedef unsigned int * pu32;
typedef signed int * ps32;
typedef unsigned long long int * pu64;
typedef signed long long int * ps64;
typedef float * pf32;
typedef double * pf64;
typedef long double * pf128;




#define OK 						255
#define NULL_POINTER            0



#define ADC_TIMEOUT 50000
#define ADC_SYNC_TIMEOUT_STATE  5
#define ADC_INVALID_CHANNEL_STATE 4
#define ADC_INVALID_RESOLUTION_STATE 3
#define ADC_BUSY_STATE 6

#define BUSY	2
#define IDLE	1








#endif
