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
     * - `{int64_t} payment` - payment asset
     * - `{int64_t} deposit` - deposit assets
     * - `{int64_t} supply` - liquidity supply
     * - `{uint16_t} [ratio=10000]` - default ratio used to initialize supply
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const int64_t payment = 10000;
     * const int64_t deposit = 1000000;
     * const int64_t supply = 10000000000;
     * const uint16_t ratio = 10000;
     *
     * // Calculation
     * const int64_t issue_amount = rex::issue( payment, supply, deposit, ratio );
     * // => 100000000
     * ```
     */
    static int64_t issue( const int64_t payment, const int64_t deposit, const int64_t supply, const uint16_t ratio = 10000 )
    {
        eosio::check(payment > 0, "SX.REX: INSUFFICIENT_PAYMENT_AMOUNT");

        // initialize if no supply
        if ( supply == 0 ) return payment * ratio;

        // issue & redeem supply calculation
        // calculations based on add to REX pool
        // https://github.com/EOSIO/eosio.contracts/blob/f6578c45c83ec60826e6a1eeb9ee71de85abe976/contracts/eosio.system/src/rex.cpp#L1048-L1052
        const int64_t S0 = deposit; // deposit
        const int64_t S1 = S0 + payment; // payment
        const int64_t R0 = supply; // supply
        const int64_t R1 = (uint128_t(S1) * R0) / S0;

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
     * - `{int64_t} payment` - payment asset
     * - `{int64_t} deposit` - deposit assets
     * - `{int64_t} supply` - liquidity supply
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const int64_t payment = 100000000;
     * const int64_t deposit = 1000000;
     * const int64_t supply = 10000000000;
     *
     * // Calculation
     * const int64_t amount_retire = rex::retire( payment, deposit, supply );
     * // => 10000
     * ```
     */
    static int64_t retire( const int64_t payment, const int64_t deposit, const int64_t supply )
    {
        eosio::check(payment > 0, "SX.REX: INSUFFICIENT_PAYMENT_AMOUNT");
        eosio::check(deposit > 0, "SX.REX: INSUFFICIENT_DEPOSIT_AMOUNT");
        eosio::check(supply > 0, "SX.REX: INSUFFICIENT_SUPPLY_AMOUNT");

        // issue & redeem supply calculation
        // calculations based on fill REX order
        // https://github.com/EOSIO/eosio.contracts/blob/f6578c45c83ec60826e6a1eeb9ee71de85abe976/contracts/eosio.system/src/rex.cpp#L775-L779
        const int64_t S0 = deposit;
        const int64_t R0 = supply;
        const int64_t p  = (uint128_t(payment) * S0) / R0;

        return p;
    }
}