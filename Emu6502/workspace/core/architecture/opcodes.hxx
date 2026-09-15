#pragma once

namespace architecture
{
    class c_opcodes
    {
        bus::registers_t* m_registry{};
        bus::c_memory* m_memory{};

        using instruction = void(c_opcodes::*)();
        std::array<instruction, 256> m_instructions{};

    public:
        

        c_opcodes()
        {
            m_instructions.fill(nullptr);
        }

        void nop()
        {
            // NOP
        }

        void initialize(
            bus::registers_t* registry,
            bus::c_memory* memory
        )
        {
            m_registry = registry;
            m_memory = memory;

            m_instructions[0xEA] = &c_opcodes::nop;
        }

        void execute(u8 opcode)
        {
            auto instruction = m_instructions[opcode];

            if (!instruction)
            {
                g_logger.warning("Unknown opcode: {:#04x}", opcode);
                return;
            }

            (this->*instruction)();
        }
    };
}