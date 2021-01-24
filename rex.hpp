#pragma once

using namespace eosio;

namespace rex {
    /**
     * ## STATIC `issue`
     *
     * Issue supply calculation
     * Calculations based on add to REX pool
     * https://github.com/EOSIO/eosio.contracts/blob/f6578c45c83ec60826e6a1eeb9ee71de85abe976/contracts/eosio.system/src/rex.cpp#L775-L779
     *
     * ### params
     *
     * - `{uint64_t} payment` - payment asset
     * - `{uint64_t} deposit` - deposit assets
     * - `{uint64_t} supply` - liquidity supply
     * - `{uint16_t} [ratio=10000]` - default ratio used to initialize supply
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const uint64_t payment = 10000;
     * const uint64_t deposit = 1000000;
     * const uint64_t supply = 10000000000;
     * const uint16_t ratio = 10000;
     *
     * // Calculation
     * const uint64_t issue_amount = rex::issue( payment, supply, deposit, ratio );
     * // => 100000000
     * ```
     */
    static uint64_t issue( const uint64_t payment, const uint64_t deposit, const uint64_t supply, const uint16_t ratio = 10000 )
    {
        eosio::check(payment > 0, "SX.REX: INSUFFICIENT_PAYMENT_AMOUNT");

        // initialize if no supply
        if ( supply == 0 ) return payment * ratio;

        // issue & redeem supply calculation
        // calculations based on add to REX pool
        // https://github.com/EOSIO/eosio.contracts/blob/f6578c45c83ec60826e6a1eeb9ee71de85abe976/contracts/eosio.system/src/rex.cpp#L1048-L1052
        uint64_t S0 = deposit; // deposit
        uint64_t S1 = S0 + payment; // payment
        uint64_t R0 = supply; // supply
        uint64_t R1 = (uint128_t(S1) * R0) / S0;

        return R1 - R0;
    }

    /**
     * ## STATIC `retire`
     *
     * Retire supply calculation
     * Calculations based on fill REX order
     * https://github.com/EOSIO/eosio.contracts/blob/f6578c45c83ec60826e6a1eeb9ee71de85abe976/contracts/eosio.system/src/rex.cpp#L775-L779
     *
     * ### params
     *
     * - `{uint64_t} payment` - payment asset
     * - `{uint64_t} deposit` - deposit assets
     * - `{uint64_t} supply` - liquidity supply
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const uint64_t payment = 100000000;
     * const uint64_t deposit = 1000000;
     * const uint64_t supply = 10000000000;
     *
     * // Calculation
     * const uint64_t amount_retire = rex::retire( payment, deposit, supply );
     * // => 10000
     * ```
     */
    static uint64_t retire( const uint64_t payment, const uint64_t deposit, const uint64_t supply )
    {
        eosio::check(payment > 0, "SX.REX: INSUFFICIENT_PAYMENT_AMOUNT");
        eosio::check(deposit > 0, "SX.REX: INSUFFICIENT_DEPOSIT_AMOUNT");
        eosio::check(supply > 0, "SX.REX: INSUFFICIENT_SUPPLY_AMOUNT");

        // issue & redeem supply calculation
        // calculations based on fill REX order
        // https://github.com/EOSIO/eosio.contracts/blob/f6578c45c83ec60826e6a1eeb9ee71de85abe976/contracts/eosio.system/src/rex.cpp#L775-L779
        const uint64_t S0 = deposit;
        const uint64_t R0 = supply;
        const uint64_t p  = (uint128_t(payment) * S0) / R0;

        return p;
    }
}