#pragma once

namespace architecture
{
	// 6502 expects a little-endian format (smallest byte first written)
	class c_memory
	{
		std::array<u8, 65536> m_ram{};

	public:
		void write(u16 addr, u8 value)
		{
			m_ram[addr] = value;
		}

		template<typename t = u64>
		void write(u16 addr, t value)
		{
			for (size_t offset{}; offset < sizeof(t); ++offset)
			{
				m_ram[addr + offset] = static_cast<u8>((value >> (offset * 8)) & 0xFF);
			}
		}

		u8 read(u16 addr) const
		{
			return m_ram[addr];
		}
	};
}