#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "common/common.h"
#include "uintr.h"

volatile unsigned long uintr_received;
volatile unsigned int uintr_count = 0;
int descriptor;

struct Benchmarks bench;

uint64_t uintr_handler(struct __uintr_frame *ui_frame, uint64_t irqs) {
	benchmark(&bench);
	uintr_count++;
	uintr_received = 1;
  return 0;
}

void *client_communicate(void *arg) {

	struct Arguments* args = (struct Arguments*)arg;
	int loop;

	int uipi_index = uintr_register_sender(descriptor);
	if (uipi_index < 0)
		throw("Sender register error\n");

	for (loop = args->count; loop > 0; --loop) {

		uintr_received = 0;
		bench.single_start = now();

		// Send User IPI
		uipi_send(uipi_index);

		while (!uintr_received){
			// Keep spinning until this user interrupt is received.
		}
	}

	return NULL;
}

void server_communicate(int descriptor, struct Arguments* args) {

	while (uintr_count < args->count) {
		//Keep spinning until all user interrupts are delivered.
	}

	// The message size is always one (it's just a signal)
	args->size = 1;
	evaluate(&bench, args);
}

void communicate(int descriptor, struct Arguments* args) {

	pthread_t pt;

	setup_benchmarks(&bench);

	// Create another thread
	if (pthread_create(&pt, NULL, &client_communicate, args)) {
		throw("Error creating sender thread");
	}

	server_communicate(descriptor, args);

	close(descriptor);
}

int main(int argc, char* argv[]) {

	struct Arguments args;

	if (__register_receiver(uintr_handler))
		throw("Interrupt handler register error\n");

	// Create a new uintrfd object and get the corresponding
	// file descriptor.
	descriptor = uintr_create_fd(1);
	if (descriptor < 0)
		throw("Interrupt vector allocation error\n");

	parse_arguments(&args, argc, argv);

	communicate(descriptor, &args);

	return EXIT_SUCCESS;
}