all: build run clean

ex-eng-freq: build
			 ./.compiled -f dictionaries/english-freq.txt
			 rm .compiled

ex-eng: build
		./.compiled -f dictionaries/english.txt
		rm .compiled

ex-pt-lg: build
		  ./.compiled -f dictionaries/portuguese-large.txt
		  rm .compiled

ex-pt: build
	   ./.compiled -f dictionaries/portuguese.txt
	   rm .compiled

build: 
	gcc -Wextra -Wall -o .compiled main.c

run: 
	./.compiled -f ${file}

clean: 
	rm .compiled