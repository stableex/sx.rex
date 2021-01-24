/**
 * ## STATIC `issue`
 *
 * Issue supply calculation
 * Calculations based on add to REX pool
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
    return (((deposit + payment) * supply) / deposit) - supply;
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
    return payment * deposit / supply;
}