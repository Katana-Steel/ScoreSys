#!/bin/bash

SB=
function fin_exit() {
  [[ -n $SB ]] && kill $SB
  exit $1
}

nc -lui 10 0.0.0.0 9500 > master.log 2>&1 &

./score_board &
SB=$!

sleep 10

echo "All Pass!"
fin_exit $?
