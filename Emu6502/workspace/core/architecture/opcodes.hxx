#pragma once

namespace architecture
{
    enum instr_t : u8
    {
        lda_im = 0xA9,
        nop = 0xEA
    };

    class c_opcodes
    {
        bus::registers_t* m_registry{};
        bus::c_memory* m_memory{};

        // takes in clock cycle
        using instruction = void(c_opcodes::*)(u32&);
        std::array<instruction, 256> m_instructions{};

    public:
        c_opcodes()
        {
            m_instructions.fill(nullptr);
        }

        void lda_im(u32& c)
        {
            u8 value = m_memory->fetch(m_registry->pc, c);
            m_registry->a = value;
            
            if (m_registry->a == 0)
                m_registry->set_flag(bus::processor_states_t::m_zero_flag);

            if ((m_registry->a & 0b10000000) > 0)
                m_registry->set_flag(bus::processor_states_t::m_negative_flag);
        }

        void nop(u32& c)
        {
            return;
        }

        void initialize(
            bus::registers_t* registry,
            bus::c_memory* memory
        )
        {
            m_registry = registry;
            m_memory = memory;

            m_instructions[instr_t::lda_im] = &c_opcodes::lda_im;
            m_instructions[instr_t::nop] = &c_opcodes::nop;
        }

        void execute(u8 opcode, u32& cycles)
        {
            auto instruction = m_instructions[opcode];

            if (!instruction)
            {
                g_logger.warning("Unknown opcode: {:#04x}", opcode);
                return;
            }

            (this->*instruction)(cycles);
        }
    };
}