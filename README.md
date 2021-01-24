# **`REX`**

> Peripheral EOSIO smart contracts for interacting with REX

## Quickstart

```c++
#include "rex.hpp"

// Inputs
const uint64_t amount_in = 100000;
const uint64_t reserve_in = 45851931234;
const uint64_t reserve_out = 125682033533;
const uint64_t amplifier = 450;
const uint64_t fee = 4;

// Calculation
const uint64_t out = rex::get_amount_out( amount_in, reserve_in, reserve_out, amplifier, fee );
// => 100110
```
