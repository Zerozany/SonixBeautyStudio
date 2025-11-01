#include "SonixLogger.h"

#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/android_sink.h>
#include <vector>
#include <print>

static constexpr std::size_t LOGSIZE{1024 * 1024 * 5};

SonixLogger::SonixLogger()
{
}

SonixLogger::~SonixLogger() noexcept
{
    std::invoke(&SonixLogger::shutdown);
}

auto SonixLogger::init(const std::string& _logPath, std::size_t _logNum) noexcept -> void
{
    try
    {
        spdlog::init_thread_pool(8192, 1);
        // 控制台 sink：输出所有等级（仅打印，不写文件）
        std::vector<spdlog::sink_ptr> sinks{};
#ifdef _WIN32
        // Windows: 控制台 sink
        auto consoleSink{std::make_shared<spdlog::sinks::stdout_color_sink_mt>()};
        consoleSink->set_level(spdlog::level::debug);
        sinks.push_back(consoleSink);
#elif defined(__ANDROID__)
        // Android: logcat sink
        auto androidSink{std::make_shared<spdlog::sinks::android_sink_mt>("SonixBeauty")};
        androidSink->set_level(spdlog::level::debug);
        sinks.push_back(androidSink);
#endif
        // 文件 sink：只写 warn 以上等级日志（自动轮转）
        auto fileSink{std::make_shared<spdlog::sinks::rotating_file_sink_mt>(_logPath, LOGSIZE, _logNum)};
        fileSink.get()->set_level(spdlog::level::warn);
        sinks.push_back(fileSink);

        m_LoggerInstance = std::make_shared<spdlog::async_logger>("SonixLogger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        spdlog::register_logger(m_LoggerInstance);
        spdlog::set_default_logger(m_LoggerInstance);
        spdlog::set_pattern("[%Y年%m月%d日 %H:%M:%S]-%^ [%l] %n::%v%$");
        m_LoggerInstance.get()->set_level(spdlog::level::trace);
    }
    catch (const std::exception& _e)
    {
        std::println("Failed to enable the logging function:{}", _e.what());
    }
}

auto SonixLogger::shutdown() noexcept -> void
{
    spdlog::drop_all();
    m_LoggerInstance.reset();
}

auto SonixLogger::setLevel(const spdlog::level::level_enum& _level) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->set_level(_level);
    }
}
