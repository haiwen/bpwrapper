#!/bin/bash

BP_SYMBOLS_FILE=testbp.sym

dump_syms testbp > ${BP_SYMBOLS_FILE}

symbol_id=$(head -1 ${BP_SYMBOLS_FILE} | awk '{printf $4}')

mkdir -p ./symbols/testbp/${symbol_id}/
mv ${BP_SYMBOLS_FILE} ./symbols/testbp/${symbol_id}/
