#pragma once

// #define MEMORY_DBG

namespace bus
{
	// 6502 expects a little-endian format (smallest byte first written)
	class c_memory
	{
		std::array<u8, 65536> m_ram{};

	public:
		template<std::integral T>
		void write(u16 addr, T value)
		{
			for (size_t offset{}; offset < sizeof(T); ++offset)
			{
				u8 off_value =
					static_cast<u8>((value >> (offset * 8)) & 0xFF);

				#ifdef MEMORY_DBG
					g_logger.debug(
						"MEM",
						"write [{:#06x}] = {:#04x}",
						static_cast<u16>(addr + offset),
						off_value
					);
				#endif

				m_ram[addr + offset] = off_value;
			}
		}

		template<size_t N>
		void write(u16 addr, const std::array<u8, N>& data)
		{
			for (size_t offset{}; offset < N; ++offset)
			{
				#ifdef MEMORY_DBG
					g_logger.debug(
						"MEM",
						"write [{:#06x}] = {:#04x}",
						static_cast<u16>(addr + offset),
						data[offset]
					);
				#endif

				m_ram[addr + offset] = data[offset];
			}
		}

		void write(u16 addr, std::span<const u8> data)
		{
			for (size_t offset{}; offset < data.size(); ++offset)
			{
				m_ram[addr + offset] = data[offset];
			}
		}

		u8 read(u16 addr) const
		{
			return m_ram[addr];
		}
	};
}