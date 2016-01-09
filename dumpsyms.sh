#!/bin/bash

if [[ $(uname) == MINGW* ]]; then
    obj=test-bpwrapper.exe
else
    obj=test-bpwrapper
fi

BP_SYMBOLS_FILE=${obj}.sym

dump_syms tests/${obj} > ${BP_SYMBOLS_FILE}

symbol_id=$(head -1 ${BP_SYMBOLS_FILE} | awk '{printf $4}')

mkdir -p ./symbols/${obj}/${symbol_id}/
mv ${BP_SYMBOLS_FILE} ./symbols/${obj}/${symbol_id}/
