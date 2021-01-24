import { issue, retire } from "./rex";

test("issue #1 (pass)", () => {
    const payment = 10000n;
    const deposit = 1000000n;
    const supply = 10000000000n;
    const ratio = 10000n;

    expect( issue( payment, deposit, supply, ratio ) ).toBe( 100000000n );
});

test("retire #2 (pass)", () => {
    const payment = 100000000n;
    const deposit = 1000000n;
    const supply = 10000000000n;

    expect( retire( payment, deposit, supply ) ).toBe( 10000n );
});
