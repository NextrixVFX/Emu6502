#include <fstream>
#include <chrono>
#include <format>
#include <iostream>
#include <mutex>
#include <string_view>
#include <array>
#include <memory>
#include <utility>
#include <concepts>
#include <span>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

#include <workspace/utility/logger.hxx>
using namespace utility;

#include <workspace/core/handlers/nmi.hxx>
#include <workspace/core/handlers/power.hxx>
#include <workspace/core/handlers/interrupt.hxx>

#include <workspace/core/bus/registry.hxx>
#include <workspace/core/bus/memory.hxx>

#include <workspace/core/architecture/opcodes.hxx>
#include <workspace/core/architecture/cpu.hxx>