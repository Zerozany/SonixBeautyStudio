_Pragma("once");
#include <memory>
#include <spdlog/spdlog.h>

class SonixLogger
{
public:
    explicit(true) SonixLogger();
    ~SonixLogger() noexcept;

public:
    static auto init(const std::string& _logPath, std::size_t _logNum = 3) noexcept -> void;

    static auto setLevel(const spdlog::level::level_enum& _level) noexcept -> void;

    template <typename... Args>
    static auto trace(const char* _fmt, const Args&... _args) noexcept -> void;

    template <typename... Args>
    static auto debug(const char* _fmt, const Args&... _args) noexcept -> void;

    template <typename... Args>
    static auto info(const char* _fmt, const Args&... _args) noexcept -> void;

    template <typename... Args>
    static auto warn(const char* _fmt, const Args&... _args) noexcept -> void;

    template <typename... Args>
    static auto error(const char* _fmt, const Args&... _args) noexcept -> void;

    template <typename... Args>
    static auto critical(const char* _fmt, const Args&... _args) noexcept -> void;

private:
    static auto shutdown() noexcept -> void;

private:
    inline static std::shared_ptr<spdlog::logger> m_LoggerInstance{nullptr};
};

template <typename... Args>
inline auto SonixLogger::trace(const char* _fmt, const Args&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->trace(_fmt, _args...);
    }
}

template <typename... Args>
inline auto SonixLogger::debug(const char* _fmt, const Args&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->debug(_fmt, _args...);
    }
}

template <typename... Args>
inline auto SonixLogger::info(const char* _fmt, const Args&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->info(_fmt, _args...);
    }
}

template <typename... Args>
inline auto SonixLogger::warn(const char* _fmt, const Args&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->warn(_fmt, _args...);
    }
}

template <typename... Args>
inline auto SonixLogger::error(const char* _fmt, const Args&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->error(_fmt, _args...);
    }
}

template <typename... Args>
inline auto SonixLogger::critical(const char* _fmt, const Args&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->critical(_fmt, _args...);
    }
}
