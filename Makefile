all: build run clean

ex-eng-freq: build
			 ./.compiled dictionaries/english-freq_lower.txt
			 rm .compiled

ex-eng: build
		./.compiled dictionaries/english_lower.txt
		rm .compiled

ex-pt-lg: build
		  ./.compiled dictionaries/portuguese-large_lower.txt
		  rm .compiled

ex-pt: build
	   ./.compiled dictionaries/portuguese_lower.txt
	   rm .compiled

ex-custom: build
	  	   ./.compiled dictionaries/custom.txt
	   	   rm .compiled

build: 
	gcc -lm -Wextra -Wall -o .compiled main.c

run: 
	./.compiled ${file}

clean: 
	rm .compiled