all:
	cc -g -lpthread -lX11 -L/usr/local/lib -I/usr/local/include *.c -o main
