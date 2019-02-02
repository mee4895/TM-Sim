#ifndef BELT_H
#define BELT_H

#include <cstddef>
#include <iostream>
#include <iomanip>
#include <stdexcept>

class Belt
{
	public:
		typedef unsigned char data_t;

		Belt(const std::size_t size);

		Belt(Belt& cpy);
		Belt(Belt&& cpym);
		~Belt();

		Belt& operator=(const Belt& cpy);
		Belt& operator=(Belt&& cpym);

		data_t get();
		void set(const data_t data);

		void m_left();
		void m_right();

		void input(const data_t* data, const std::size_t size);
		void dump();

	protected:

	private:
		data_t* position;
		data_t* raw_data;
		std::size_t data_size;
};

#endif // BELT_H
