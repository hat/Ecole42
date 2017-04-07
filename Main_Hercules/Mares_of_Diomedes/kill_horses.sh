#!/bin/bash

./manger &

killall -s SIGKILL yes lampon ruins xanthos
kill -9 $(pgrep manger)
kill -9 $(pgrep crap)
kill -9 $(pgrep lampon)
kill -9 $(pgrep ruins)
kill -9 $(pgrep xanthos)

rm -f *.poo

kill -9 $(pgrep yes)

# kill -9 $(ps | grep 'yes' | awk '{print $1}')

# killall -s SIGKILL lampon xanthos ruins yes
# pkill -f .poo
# rm -f ~/Downloads/*.poo

# kill -9 'pgrep -f crap*'

# kill -9 $(ps | grep 'tty' | awk '{print $1}')

# kill `ps -o 'pid= -N T'`
