all: utest_reciver utest_sender

utest_reciver: reciver.o test1_reciver.o
	g++ reciver.o test1_reciver.o -o utest_reciver -pthread

test1_reciver.o: test1_reciver.cpp
	g++ -c test1_reciver.cpp -o test1_reciver.o -pthread

reciver.o: reciver.cpp
	g++ -c reciver.cpp -o reciver.o -pthread

sender.o: sender.cpp
	g++ -c sender.cpp -o sender.o -pthread

utest_sender: test1_sender.o sender.o
	g++ sender.o test1_sender.o -o utest_sender -pthread

test1_sender.o: test1_reciver.cpp
	g++ -c test1_sender.cpp -o test1_sender.o -pthread

clean:
	rm -rf *.o utest *.gcno *.gcda *.gcov utest_reciver utest_sender