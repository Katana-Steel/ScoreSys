#!/bin/bash

SB=
function fin_exit() {
  [[ -n $SB ]] && kill $SB
  exit $1
}

function test_running() {
  ps ax | awk '{print $1}' | grep $SB > /dev/null 2>&1
}

function cli_test () {
  local cmd=$1
  local port=$2
  echo -e "$cmd" | $NCCLI 127.0.0.1 $port || fin_exit 2
  test_running || fin_exit 1
}

function set_trad_nc() {
  NCSERV="nc -dlui 3 -p 9500"
  NCCLI="nc -uq 1"
}

function set_bsd_nc() {
  NCSERV="nc -4 -d -l -u -i 3 0.0.0.0 9500"
  NCCLI="nc -u -q 1"
}

grep = Makefile | head -9 | tee tests/Makefile
cat tests/makefile.build >> tests/Makefile
cd tests
make || fin_exit 1
cd -

tests/sboard_test || fin_exit $?

nc -h 2>&1 | grep -i bsd &> /dev/null
if [ $? -eq 0 ]; then
  set_bsd_nc
else
  set_trad_nc
fi

echo "fake server:      $NCSERV"
echo "fake server cli:  $NCCLI"

$NCSERV &> master.log &

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
cli_test "SetUi 'Killer Floor' karate" $P
echo " Passed!"

echo -n "Player update test 2 (post ui)"
cli_test "player r 'Claude Moné' pt:3 cat1:0 cat2:1" "$P"
echo " Passed!"

echo -n "Player update test 3 (post ui)"
cli_test "player l 'Picasso' pt:6 cat1:2 cat2:0" "$P"
echo " Passed!"

echo -n "Player update test 4 (post ui)"
cli_test "player l 'Picasso' pt:6 cat1:2 cat2:1\nplayer r 'Claude Moné' pt:5 cat1:2 cat2:1" "$P"
echo " Passed!"

echo -n "Player update test 5 (post ui - incomplete option list)"
cli_test "player l 'Picasso' pt:6 cat1:3" "$P"
echo " Passed!"

echo -n "Full players setup test 1 (incl. ui)"
cli_test "SetUi 'Cleb D-Match' karate\nplayer l 'Chuck Norris' pt:0 cat1:0 cat2:0\nplayer r 'Jet Lee' pt:0 cat1:0 cat2:0\ntimer x 6:0:0" "$P"
echo " Passed!"

echo -n "Full players setup test 2 (incl. ui)"
cli_test "SetUi 'AMC Cup finals 1st quarter' football\nplayer r 'Oklahoma state' pt:0 timeouts:3\nplayer l 'South Dakota state' pt:0 timeouts:3\ntimer x 45:0:0" "$P"
echo " Passed!"

echo -n "Full players setup test 3 (incl. ui)"
cli_test "SetUi 'week 3 3rd quarter' nfl\nplayer r 'oak' pt:14 timeouts:3\nplayer l 'tb' pt:10 timeouts:3\ntimer x 45:0:0" "$P"
echo " Passed!"

echo -n "Full players setup test 4 (incl. ui)"
cli_test "SetUi 'troll toss finals' simple\nplayer r 'home' pt:0\nplayer l 'away' pt:0\ntimer x 45:0:0" "$P"
echo " Passed!"

[ "x$1" != "x" ] && sleep 6
echo "All Passed!"
fin_exit $?
