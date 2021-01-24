#!/bin/bash

# compile
g++ -std=c++11 -o rex.t.out rex.test.cpp -I __tests__ -I ../

# test
./rex.t.out --success
