_Pragma("once");
#include "MeasureConfig.hpp"

#if defined(_WIN32) && defined(_MSC_VER)
    #ifdef SonixTools
        #define Sonix_API __declspec(dllexport)
    #else
        #define Sonix_API __declspec(dllimport)
    #endif
#elif defined(__GNUC__) || defined(__clang__)
    #define Sonix_API __attribute__((visibility("default")))
#else
    #define Sonix_API
#endif

class Sonix_API MeasureKits
{
public:
    static auto instance() noexcept -> MeasureKits*;

    ~MeasureKits() noexcept = default;

private:
    explicit(true) MeasureKits();
};
