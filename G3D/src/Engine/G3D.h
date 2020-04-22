#pragma once
#if 1
	#pragma warning(disable:6011)
	#pragma warning(disable:4244)
	#pragma warning(disable:26812)
#endif

#include <stdint.h>
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

#define internal_func static
#define local_persist static
#define global_variable static

#define G3D_OK 1
#define G3D_ERROR 0