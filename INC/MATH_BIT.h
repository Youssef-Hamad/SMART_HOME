#ifndef MATH_BIT_H
#define MATH_BIT_H

#define SetBit(value,bitnum) (value |= (1<<bitnum))
#define ClearBit(value,bitnum) (value &= ~(1<<bitnum))
#define GetBit(value,bitnum) ((value>>bitnum) & 1)
#define ToggleBit(value,bitnum) (value ^= (1<<bitnum))
#define WriteBit(value,bitnum,bitvalue)	(value=(value & ~(1<<bitnum)) | (bitvalue<<bitnum))


#endif
