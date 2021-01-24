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

TEST_CASE( "issue #2 (pass)" ) {
    const uint64_t payment = 17500;
    const uint64_t reserve0 = 70661300;
    const uint64_t reserve1 = 53569900;
    const uint64_t deposit = reserve0 + reserve1;
    const uint64_t supply = 122372900;
    const uint64_t ratio = 1;

    REQUIRE( rex::issue( payment, deposit, supply, ratio ) == 17238 );
};

TEST_CASE( "retire #3 (pass)" ) {
    // Inputs
    const uint64_t payment = 100000000;
    const uint64_t deposit = 1000000;
    const uint64_t supply = 10000000000;

    REQUIRE( rex::retire( payment, deposit, supply ) == 10000 );
}

TEST_CASE( "retire #4 (pass)" ) {
    // Inputs
    const uint64_t payment = 17238;
    const uint64_t reserve0 = 70661300;
    const uint64_t reserve1 = 53569900;
    const uint64_t deposit = reserve0 + reserve1;
    const uint64_t supply = 122372900;

    REQUIRE( rex::retire( payment, deposit, supply ) == 17499 );
}
