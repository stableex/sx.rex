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
 * - `{int64_t} [ratio=10000]` - default ratio used to initialize supply
 *
 * ### example
 *
 * ```c++
 * // Inputs
 * const payment = 10000n;
 * const deposit = 1000000n;
 * const supply = 10000000000n;
 * const ratio = 10000n;
 *
 * // Calculation
 * const amount = issue( payment, deposit, supply, ratio );
 * // => 100000000n
 * ```
 */
export function issue( payment: bigint, deposit: bigint, supply: bigint, ratio = 10000n )
{
    if (!(payment > 0)) throw new Error("SX.REX: INSUFFICIENT_PAYMENT_AMOUNT");

    // initialize if no supply
    if ( supply == 0n ) return payment * ratio;

    // issue & redeem supply calculation
    // calculations based on add to REX pool
    // https://github.com/EOSIO/eosio.contracts/blob/f6578c45c83ec60826e6a1eeb9ee71de85abe976/contracts/eosio.system/src/rex.cpp#L1048-L1052
    const S0 = deposit; // deposit
    const S1 = S0 + payment; // payment
    const R0 = supply; // supply
    const R1 = (S1 * R0) / S0;

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
 * - `{bigint} payment` - payment asset
 * - `{bigint} deposit` - deposit assets
 * - `{bigint} supply` - liquidity supply
 * - `{bigint} [ratio=10000]` - default ratio used to initialize supply
 *
 * ### example
 *
 * ```c++
 * // Inputs
 * const payment = 100000000n;
 * const deposit = 1000000n;
 * const supply = 10000000000n;
 *
 * // Calculation
 * const amount = retire( payment, deposit, supply );
 * // => 10000n
 * ```
 */
export function retire( payment: bigint, deposit: bigint, supply: bigint )
{
    if (!(payment > 0n )) throw new Error("SX.REX: INSUFFICIENT_PAYMENT_AMOUNT");
    if (!(deposit > 0n )) throw new Error("SX.REX: INSUFFICIENT_DEPOSIT_AMOUNT");
    if (!(supply > 0n )) throw new Error("SX.REX: INSUFFICIENT_SUPPLY_AMOUNT");

    // issue & redeem supply calculation
    // calculations based on fill REX order
    // https://github.com/EOSIO/eosio.contracts/blob/f6578c45c83ec60826e6a1eeb9ee71de85abe976/contracts/eosio.system/src/rex.cpp#L775-L779
    const S0 = deposit;
    const R0 = supply;
    const p  = (payment * S0) / R0;

    return p;
}