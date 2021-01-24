# **`REX`**

[![Build Status](https://travis-ci.org/stableex/sx.rex.svg?branch=master)](https://travis-ci.org/stableex/sx.rex)

> Peripheral EOSIO smart contracts for interacting with REX

## Quickstart

```c++
#include "rex.hpp"

// Inputs
const int64_t payment = 10000;
const int64_t deposit = 1000000;
const int64_t supply = 10000000000;
const uint16_t ratio = 10000;

// Calculation
const int64_t issue_amount = rex::issue( payment, deposit, supply, ratio );
// => 100000000

const int64_t retire_amount = rex::retire( payment, deposit, supply );
// => 10000
```

## Testing

**C++**

```bash
$ ./test.sh
```
**Typescript NodeJS**

```bash
$ npm test
```
