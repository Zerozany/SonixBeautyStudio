#include "MeasureKits.h"

auto MeasureKits::instance() noexcept -> MeasureKits*
{
    static MeasureKits* measureKits{new MeasureKits};
    return measureKits;
}

MeasureKits::MeasureKits()
{
}
