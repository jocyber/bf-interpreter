#include "tape.hpp"

Tape::~Tape() {
	Node* current = tapeHead->next;
	
	while (current) {
		Node *temp = current;
		current = current->next;

		delete temp;
	}
	
	current = tapeHead->back;

	while (current) {
		Node *temp = current;
		current = current->back;

		delete temp;
	}

	delete tapeHead;
}

void Tape::setHeadData(const unsigned char input) noexcept {
	tapeHead->data_ = input;
}

void Tape::incrementHead() noexcept { tapeHead->data_++; }
void Tape::decrementHead() noexcept { tapeHead->data_--; }

void Tape::moveLeft() noexcept {
	if (!tapeHead->back) {
		tapeHead->back = new Node(0);

		tapeHead->back->next = tapeHead;
	}
	
	tapeHead = tapeHead->back;
}

void Tape::moveRight() noexcept {
	if (!tapeHead->next) {
		tapeHead->next = new Node(0);

		tapeHead->next->back = tapeHead;
	}
	
	tapeHead = tapeHead->next;
}	
