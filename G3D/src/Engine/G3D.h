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

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#define internal static
#define local_persist static
#define global_variable static