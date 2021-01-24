import { issue, retire } from "./rex";

test("issue #1 (pass)", () => {
    const payment = 10000n;
    const deposit = 1000000n;
    const supply = 10000000000n;
    const ratio = 10000n;

    expect( issue( payment, deposit, supply, ratio ) ).toBe( 100000000n );
});

test("issue #2 (pass)", () => {
    const payment = 17500n;
    const reserve0 = 70661300n;
    const reserve1 = 53569900n;
    const deposit = reserve0 + reserve1;
    const supply = 122372900n;
    const ratio = 1n;

    expect( issue( payment, deposit, supply, ratio ) ).toBe( 17238n );
});

test("retire #3 (pass)", () => {
    const payment = 100000000n;
    const deposit = 1000000n;
    const supply = 10000000000n;

    expect( retire( payment, deposit, supply ) ).toBe( 10000n );
});

test("retire #4 (pass)", () => {
    const payment = 17238n;
    const reserve0 = 70661300n;
    const reserve1 = 53569900n;
    const deposit = reserve0 + reserve1;
    const supply = 122372900n;

    expect( retire( payment, deposit, supply ) ).toBe( 17499n );
});
