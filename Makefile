all: build run clean

ex-eng-freq: build
			 ./.compiled dictionaries/english-freq.txt
			 rm .compiled

ex-eng: build
		./.compiled dictionaries/english.txt
		rm .compiled

ex-pt-lg: build
		  ./.compiled dictionaries/portuguese-large.txt
		  rm .compiled

ex-pt: build
	   ./.compiled dictionaries/portuguese.txt
	   rm .compiled

build: 
	gcc -Wextra -Wall -o .compiled main.c

run: 
	./.compiled ${file}

clean: 
	rm .compiled