#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include "main.h"

#define RED 0xff00000
#define GREEN 0x00ff00
#define BLUE 0x0000ff

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 300

Display *display;
int screen;
Window window;
GC gc;

struct Rectangle *start = NULL;

struct Rectangle {
	int x;
	int y;
	unsigned int width, height;
	struct Rectangle *next;
	struct Rectangle *prev;
};

void Render() {
	XClearWindow(display, window);
	printf("Rendered\n");	

	struct Rectangle *index = start;
	while(index != NULL) {
		XFillRectangle(display, window, gc, index->x, index->y, index->width, index->height);
		index = index->next;
	}
}

struct Rectangle* CreateRectangle(int x, int y, unsigned int width, unsigned height){
	struct Rectangle *const rectangle = malloc(sizeof(struct Rectangle));
	rectangle->x = x;
	rectangle->y = y;
	rectangle->width = width;
	rectangle->height = height;
	rectangle->next = NULL;
	
	if(NULL == start) {
		rectangle->prev = NULL;
		start = rectangle;
	} else {		
		struct Rectangle *index = start;
		while(index->next != NULL)
			index = index->next;

		rectangle->prev = index;
		index->next = rectangle;
	}

	return rectangle;	
}

void loop(void callback(), unsigned seconds) {
	while(true) {
		sleep(seconds);
		callback();
	} 
	exit(0);
}

void *start_routine() {
	loop(Render, 1);
	void *status; 
	return status;
}

int main() {
	if(init(&display, &screen, &window, WINDOW_WIDTH, WINDOW_HEIGHT, &gc)) {
		printf("Failed to init\n");
		return 1;
	}
	
	XSetForeground(display, gc, BLUE);
	struct Rectangle *rect = CreateRectangle(50, 50, 100, 100);
	
	pthread_t tid;
	//If you call Render() here it works
	if(pthread_create(&tid, NULL, start_routine, NULL) != 0) {
		printf("Failed to create new thread\n");
		return 1;
	}

	term(display, window, gc);	
	return 0;
}

