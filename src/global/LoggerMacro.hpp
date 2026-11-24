_Pragma("once");

#if __has_include("LogManager.h")
    #include "LogManager.h"
    #define LOG_TRACE(...) LogManager::instance()->trace(__VA_ARGS__)
    #define LOG_DEBUG(...) LogManager::instance()->debug(__VA_ARGS__)
    #define LOG_INFO(...) LogManager::instance()->info(__VA_ARGS__)
    #define LOG_WARN(...) LogManager::instance()->warn(__VA_ARGS__)
    #define LOG_ERROR(...) LogManager::instance()->error(__VA_ARGS__)
    #define LOG_CRITICAL(...) LogManager::instance()->critical(__VA_ARGS__)
#endif
