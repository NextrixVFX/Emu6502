#pragma once

namespace utility
{
    enum class log_level
    {
        trace,
        debug,
        info,
        warning,
        error,
        fatal
    };

    class c_logger
    {
        std::mutex m_mutex{};

        static constexpr std::string_view level_string(log_level level)
        {
            switch (level)
            {
            case log_level::trace:   return "TRACE";
            case log_level::debug:   return "DEBUG";
            case log_level::info:    return "INFO ";
            case log_level::warning: return "WARN ";
            case log_level::error:   return "ERROR";
            case log_level::fatal:   return "FATAL";
            }

            return "?????";
        }

        static std::string timestamp()
        {
            const auto now = std::chrono::system_clock::now();

            return std::format(
                "{:%Y-%m-%d %H:%M:%S}",
                std::chrono::floor<std::chrono::seconds>(now)
            );
        }

        template<typename... args_t>
        void log(
            log_level level,
            std::format_string<args_t...> format,
            args_t&&... args
        )
        {
            std::lock_guard lock{ m_mutex };

            std::cout
                << '[' << timestamp() << ']'
                << " [" << level_string(level) << "] "
                << std::format(
                    format,
                    std::forward<args_t>(args)...
                )
                << '\n';
        }

    public:
        template<typename... args_t>
        void trace(
            std::format_string<args_t...> format,
            args_t&&... args
        )
        {
            log(
                log_level::trace,
                format,
                std::forward<args_t>(args)...
            );
        }

        template<typename... args_t>
        void debug(
            std::format_string<args_t...> format,
            args_t&&... args
        )
        {
            log(
                log_level::debug,
                format,
                std::forward<args_t>(args)...
            );
        }

        template<typename... args_t>
        void info(
            std::format_string<args_t...> format,
            args_t&&... args
        )
        {
            log(
                log_level::info,
                format,
                std::forward<args_t>(args)...
            );
        }

        template<typename... args_t>
        void warning(
            std::format_string<args_t...> format,
            args_t&&... args
        )
        {
            log(
                log_level::warning,
                format,
                std::forward<args_t>(args)...
            );
        }

        template<typename... args_t>
        void error(
            std::format_string<args_t...> format,
            args_t&&... args
        )
        {
            log(
                log_level::error,
                format,
                std::forward<args_t>(args)...
            );
        }

        template<typename... args_t>
        void fatal(
            std::format_string<args_t...> format,
            args_t&&... args
        )
        {
            log(
                log_level::fatal,
                format,
                std::forward<args_t>(args)...
            );
        }
    };

    inline c_logger g_logger{};
}