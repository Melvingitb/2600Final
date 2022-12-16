#!/bin/bash
VALUE=$xprintidle
if [$VALUE -ge 10000]; then
	echo "No input detected, beginning auto mode"
	./auto.out
	break
else
	echo "Input detected, beginning PVP mode"
	./tictac.out
fi


