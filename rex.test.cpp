#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <eosio/check.hpp>
#include <uint128_t/uint128_t.cpp>

#include "rex.hpp"

TEST_CASE( "issue #1 (pass)" ) {
    // Inputs
    const uint64_t payment = 10000;
    const uint64_t deposit = 1000000;
    const uint64_t supply = 10000000000;
    const uint16_t ratio = 10000;

    REQUIRE( rex::issue( payment, deposit, supply, ratio ) == 100000000 );
}

TEST_CASE( "retire #2 (pass)" ) {
    // Inputs
    const uint64_t payment = 100000000;
    const uint64_t deposit = 1000000;
    const uint64_t supply = 10000000000;

    REQUIRE( rex::retire( payment, deposit, supply ) == 10000 );
}
