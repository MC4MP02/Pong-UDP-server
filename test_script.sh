#!/bin/bash

set -e

function finish {
	echo "##################################################################"
	echo "TESTS RESULT: $RESULT"
	echo "##################################################################"
}

trap finish EXIT

RESULT="FAIL"

echo "##################################################################"
echo "PONG SERVER TEST"
echo "##################################################################"

echo "Starting Server" 

strace -e network ./reference_binary/pong &
PONGPID=$!

echo "Waiting one second for it to start"

sleep 1

echo "Performing a simple test"

cmp -b -l <(echo -en "ping1\n" | netcat -w 1 -q 1 -u 127.0.0.1 8080) <(echo -en "ping1\n") || exit 1

cmp -b -l <(echo -en "ping2\n" | netcat -w 1 -q 1 -u 127.0.0.1 8080) <(echo -en "ping2\n") || exit 1

cmp -b -l <(echo -en "ping3\n" | netcat -w 1 -q 1 -u 127.0.0.1 8080) <(echo -en "ping3\n") || exit 1

kill -9 "$PONGPID" 2> /dev/null && { echo "Server stayed alive when should have died!" ; false ; }

echo "Starting Server" 

./reference_binary/pong &
PONGPID=$!

echo "Waiting one second for it to start"

sleep 1

echo "Performing a more complicated test"

cmp -b -l <(echo -en "ping1\n" | netcat -w 1 -q 1 -u 127.0.0.1 8080) <(echo -en "ping1\n") || exit 1

cmp -b -l <(echo -en "p\0ng" | netcat -w 1 -q 1 -u 127.0.0.1 8080) <(echo -en "p\0ng") || exit 1

LONGSTRING=$(printf '%.0c' {1..1024})

cmp -b -l <(echo -en "$LONGSTRING" | netcat -w 1 -q 1 -u 127.0.0.1 8080) <(echo -en "$LONGSTRING") || exit 1

echo "Checking that server quit properly"

kill -9 "$PONGPID" 2> /dev/null && { echo "Server stayed alive when should have died!" ; false ; }

RESULT="PASS"

