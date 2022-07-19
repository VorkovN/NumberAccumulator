#!/bin/bash

cd ../../bin/apps/

./Server -i 127.0.0.1 -p 1024 -I 127.0.0.1 -P 1025 &
sleep 1 # чтобы сервер успел подняться
./Client -i 127.0.0.1 -p 1024 -t tcp
killall Server