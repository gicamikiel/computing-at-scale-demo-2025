#include <vector>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("check vector") {
    std::vector<double> v(10);
    REQUIRE(v.size() == 10);
}