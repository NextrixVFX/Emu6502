#pragma once

namespace architecture
{
	class c_cpu
	{
		// past zeropage
		static constexpr u16 m_stack_base{ 0x0100 };

		// cpu structs
		bus::registers_t m_registry{};
		bus::c_memory m_memory{}; // ram
		c_opcodes m_opcodes{};

		void initialize()
		{
			m_opcodes.initialize(&m_registry, &m_memory);

			struct zero_page
			{
				std::array<u8, 256> m_data{};
			} _zero_page;

			// zero out the zeropage
			m_memory.write(0x0000, _zero_page.m_data);

			// reserved page
			constexpr u16 resv_start{ 0xFFFA }; // (0xFFFA -> 0xFFFF)
			u16 nmi_handler = 0x0000; // replace with address of nmi handler
			u16 power_on_reset = 0x0000; // replace with power on reset location
			u16 interrupt_request_handler = 0x0000; // replace with the interrupt request handler address

			// write all the reserved handlers
			m_memory.write(resv_start, nmi_handler);					// 0xFFFA
			m_memory.write(resv_start + 0x2, power_on_reset);				// 0xFFFC
			m_memory.write(resv_start + 0x4, interrupt_request_handler);	// 0xFFFE

			// initialize the stack pointer
			m_registry.sp = 0xFF;
		}

	public:
		c_cpu()
		{
			initialize();
		}

		void push_stack(u8 value)
		{
			m_memory.write(m_stack_base + m_registry.sp, value);
			--m_registry.sp;
		}

		u8 pop_stack()
		{
			++m_registry.sp;
			return m_memory.read(m_stack_base + m_registry.sp);
			
		}
	};
}