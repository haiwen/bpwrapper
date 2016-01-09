#!/bin/bash

BP_SYMBOLS_FILE=test-bpwrapper.sym

dump_syms tests/test-bpwrapper* > ${BP_SYMBOLS_FILE}

symbol_id=$(head -1 ${BP_SYMBOLS_FILE} | awk '{printf $4}')

mkdir -p ./symbols/test-bpwrapper/${symbol_id}/
mv ${BP_SYMBOLS_FILE} ./symbols/test-bpwrapper/${symbol_id}/
