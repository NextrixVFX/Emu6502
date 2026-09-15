#pragma once

namespace architecture
{
	// ref https://en.wikipedia.org/wiki/MOS_Technology_6502
	enum processor_states_t : u8
	{
		m_carry_flag		= 1 << 0,
		m_zero_flag			= 1 << 1,
		m_interrupt_disable = 1 << 2,
		m_decimal_mode		= 1 << 3,
		m_break_command		= 1 << 4,
		m_unused_flag		= 1 << 5, // unused
		m_overflow_flag		= 1 << 6,
		m_negative_flag		= 1 << 7
	};
	
	// ref: https://6502.org/users/obelisk/6502/registers.html
	struct registers_t
	{
		u16 pc{}; // program counter
		u8 sp{};  // stack ptr (0x00 -> 0xFF) (256 bytes)
		u8 a{};   // accumulator
		u8 x{};   // x index
		u8 y{};   // y index
		u8 p{};   // processor status

		void set_flag(processor_states_t flag)
		{
			p |= flag;
		}

		void clear_flag(processor_states_t flag)
		{
			p &= ~flag;
		}

		bool get_flag(processor_states_t flag) const
		{
			return p & flag;
		}
	};
}