#!/bin/bash

for i in test/*.in; do
	f="${i%.*}"
	./main <$f.in >wyj.out 2>wyj.err
	if diff wyj.out $f.out >& /dev/null && diff wyj.err $f.err >& /dev/null; then
		echo -e $i ": OK"
	else
		echo -e $i ": dupa";
		break;
	fi
	# read -p "Press any key to continue... " -n1 -s
done;

rm wyj.out
rm wyj.err
