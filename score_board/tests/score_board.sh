#!/bin/bash

SB=
function fin_exit() {
  [[ -n $SB ]] && kill $SB
  exit $1
}

function test_running() {
  ps ax | grep $SB > /dev/null 2>&1
}

grep = Makefile | head -9 > tests/Makefile
cat tests/makefile.build >> tests/Makefile
cd tests
make
cd -

nc -lui 3 -p 9500 > master.log 2>&1 &

./score_board &
SB=$!

sleep 5
P=$(cat master.log|awk '{print $2}')
[[ -z $P ]] && echo "Failed to send needUi Request" && fin_exit 1
echo "Got Port ${P}"

echo -n "Timer test 1 fake input x<space>"
echo "timer x " | nc -uq 1 127.0.0.1 $P
test_running || fin_exit 1
echo " Passed!"

echo -n "Timer test 2 fake input non-integers and wrong format"
echo "timer x y z" | nc -uq 1 127.0.0.1 $P
test_running || fin_exit 1
echo " Passed!"

echo -n "Timer test 3 fake input non-integers"
echo "timer x MM:SS:%%" | nc -uq 1 127.0.0.1 $P
test_running || fin_exit 1
echo " Passed!"

echo -n "Timer test 4 start 6:0:0"
echo "timer start 6:0:0" | nc -uq 1 127.0.0.1 $P
test_running || fin_exit 1
echo " Passed!"

echo -n "Timer test 5 stop"
echo "timer stop" | nc -uq 1 127.0.0.1 $P
test_running || fin_exit 1
echo " Passed!"

echo -n "Pre Ui player update 1"
echo "player r 'Claude Moné' pt:4 cat1:0 cat2:1" | nc -uq 1 127.0.0.1 $P
test_running || fin_exit 1
echo " Passed!"

echo -n "Set Ui test 1"
echo "setUi 'Killer Floor' karate" | nc -uq 1 127.0.0.1 $P
test_running || fin_exit 1
echo " Passed!"

echo -n "Player update test 2 (post ui)"
echo "player r 'Claude Moné' pt:3 cat1:0 cat2:1" | nc -uq 1 127.0.0.1 $P
test_running || fin_exit 1
echo " Passed!"

tests/sboard_test || fin_exit $?

echo "All Passed!"
fin_exit $?
