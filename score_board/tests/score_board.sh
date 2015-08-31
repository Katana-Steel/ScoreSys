#!/bin/bash

SB=
function fin_exit() {
  [[ -n $SB ]] && kill $SB
  exit $1
}

function test_running() {
  ps ax | grep $SB > /dev/null 2>&1
}

function cli_test () {
  local cmd=$1
  local port=$2
  echo $cmd | $NCCLI 127.0.0.1 $port || fin_exit 2
  test_running || fin_exit 1
}

function set_trad_nc() {
  NCSERV="nc -lui 3 -p 9500"
  NCCLI="nc -uq 1"
}

function set_bsd_nc() {
  NCSERV="nc -l -p 9500 -u -i 3"
  NCCLI="nc -u -q 1"
}

grep = Makefile | head -9 | tee tests/Makefile
cat tests/makefile.build >> tests/Makefile
cd tests
make || fin_exit 1
cd -

tests/sboard_test || fin_exit $?

nc -h 2>&1 | grep -i bsd 
if [ $? -eq 0 ]; then
  set_bsd_nc
else
  set_trad_nc
fi
echo "fake server:      $NCSERV"
echo "fake server cli:  $NCCLI"

$NCSERV > master.log &

./score_board &
SB=$!

sleep 5
P=$(tail -1 master.log|awk '{print $2}')
[[ -z $P ]] && echo "Failed to send needUi Request" && fin_exit 1
echo "Got Port ${P}"

echo -n "Timer test 1 fake input x<space>"
cli_test "timer x " "$P"
echo " Passed!"

echo -n "Timer test 2 fake input non-integers and wrong format"
cli_test "timer x y z" "$P"
echo " Passed!"

echo -n "Timer test 3 fake input non-integers"
cli_test "timer x MM:SS:%%" "$P"
echo " Passed!"

echo -n "Timer test 4 start 6:0:0"
cli_test "timer start 6:0:0" "$P"
echo " Passed!"

echo -n "Timer test 5 stop"
cli_test "timer stop" "$P"
echo " Passed!"

echo -n "Pre Ui player update 1"
cli_test "player r 'Claude Moné' pt:4 cat1:0 cat2:1" "$P"
echo " Passed!"

echo -n "Set Ui test 1"
cli_test "setUi 'Killer Floor' karate" $P
echo " Passed!"

echo -n "Player update test 2 (post ui)"
cli_test "player r 'Claude Moné' pt:3 cat1:0 cat2:1" "$P"
echo " Passed!"

echo "All Passed!"
fin_exit $?
