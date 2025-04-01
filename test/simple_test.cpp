#include <catch2/catch_test_macros.hpp>
#include "Fibered.hpp"

void KickJob(void* fibered)
{
    uint32_t processor_count = std::thread::hardware_concurrency();
    REQUIRE(reinterpret_cast<Fibered*>(fibered)->GetThreadCount() == processor_count);
}

TEST_CASE("Initialization test", "[Init]") {
    Fibered fibered;
}