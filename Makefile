compile:
	gcc -Wall -g3  -pthread client1.c -o client1
	gcc -Wall -g3  -pthread client2.c -o client2
	gcc -Wall -g3  -pthread semaphore1.c -o semaphore1
	gcc -Wall -g3  -pthread semaphore2.c -o semaphore2
	g++ -Wall -g3  -pthread process1.c -o process1
	g++ -Wall -g3  -pthread process2.c -o process2
clean:
	@echo "Delete file ..."
	rm -rf client1
	rm -rf client2
	rm -rf semaphore1
	rm -rf semaphore2
	rm -rf data.txt
	rm -rf process1
	rm -rf process2