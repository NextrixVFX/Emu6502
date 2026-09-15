#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <stack>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

#include <workspace/core/handlers/nmi.hxx>
#include <workspace/core/handlers/power.hxx>
#include <workspace/core/handlers/interrupt.hxx>

#include <workspace/core/architecture/registry.hxx>
#include <workspace/core/architecture/memory.hxx>
#include <workspace/core/architecture/cpu.hxx>