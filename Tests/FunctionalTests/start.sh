cd ../../bin/apps/

./Server -i 127.0.0.1 -p 1024 -I 127.0.0.1 -P 1025
./Client -i 127.0.0.1 -p 1024 -t tcp
