#!/bin/bash

if [[ ! -d "/dev/serial/by-id" ]]; then
    echo "There is no serial ports I can identify"
    exit 0
fi

PATTERN=$1

// TODO:
//  - list serial ports
//  - filter if $PATTERN is given
//  - resolve links (readlink -f <link>)
