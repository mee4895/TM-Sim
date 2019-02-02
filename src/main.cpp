#include <iostream>
#include "belt.h"

int main() {
	const Belt::data_t data[] = {
		0xde, 0xad, 0xbe, 0xef
	};

	Belt b(1 << 8);
	b.input(data, sizeof(data));
	b.m_left();
	b.set(0x12);
	b.m_left();
	b.set(0x34);
	b.dump();
	b.m_right();
	std::cout << (int) b.get() << std::endl;
	return 0;
}
