compile:
	gcc -Wall -g3  -pthread client1.c -o client1
	gcc -Wall -g3  -pthread client2.c -o client2
	gcc -Wall -g3  -pthread semaphore1.c -o semaphore1
	gcc -Wall -g3  -pthread semaphore2.c -o semaphore2
clean:
	@echo "Delete file ..."
	rm -rf client1
	rm -rf client2
	rm -rf semaphore1
	rm -rf semaphore2
	rm -rf data.txt