#include "belt.h"

Belt::~Belt() { }

ArrayBelt::ArrayBelt(const std::size_t size) : raw_data(new unsigned char[size]), data_size(size)
{
	position = raw_data;
}

ArrayBelt::ArrayBelt(ArrayBelt& cpy) : raw_data(new unsigned char[cpy.data_size]), data_size(cpy.data_size)
{
	position = raw_data + (cpy.position - cpy.raw_data);

	for (std::size_t index = 0; index < data_size; index++)
	{
		raw_data[index] = cpy.raw_data[index];
	}
}

ArrayBelt::ArrayBelt(ArrayBelt&& cpym) : position(cpym.position), raw_data(cpym.raw_data),
		data_size(cpym.data_size)
{
	cpym.position = nullptr;
	cpym.raw_data = nullptr;
	cpym.data_size = 0;

}

ArrayBelt::~ArrayBelt()
{
	delete [] raw_data;
}

ArrayBelt& ArrayBelt::operator=(const ArrayBelt& cpy)
{
	data_size = cpy.data_size;
	raw_data = new unsigned char[cpy.data_size];
	position = raw_data + (cpy.position - cpy.raw_data);

	for (std::size_t index = 0; index < data_size; index++)
	{
		raw_data[index] = cpy.raw_data[index];
	}

	return *this;
}

ArrayBelt& ArrayBelt::operator=(ArrayBelt&& cpym)
{
	position = cpym.position;
	cpym.position = nullptr;

	delete [] raw_data;
	raw_data = cpym.raw_data;
	cpym.raw_data = nullptr;

	data_size = cpym.data_size;
	cpym.data_size = 0;

	return *this;
}

ArrayBelt::data_t ArrayBelt::get()
{
	return *position;
}

void ArrayBelt::set(const data_t data)
{
	*position = data;
}

void ArrayBelt::m_left()
{
	if (position == raw_data)
	{
		position += data_size;
	}

	position -= 1;
}

void ArrayBelt::m_right()
{
	if (position == raw_data + (data_size - 1))
	{
		position -= data_size;
	}

	position += 1;
}

void ArrayBelt::input(const data_t* data, std::size_t size)
{
	if (size > data_size)
	{
		throw std::range_error("Input data too large");
	}

	for (std::size_t index = 0; index < size; index++)
	{
		raw_data[index] = data[index];
	}
}

void ArrayBelt::dump()
{
	std::cout << "Size: 0x" << std::hex << data_size << std::endl;
	std::cout << "Position: 0x" << std::hex << position - raw_data << std::endl;

	for (std::size_t index = 0; index < data_size; index++)
	{
		short i = index % 16;

		if (i == 0)
		{
			std::cout << "0x" << std::setw(8) << std::setfill('0') << std::hex
					<< index << "     ";
		}

		std::cout << std::setw(2) << std::setfill('0') << std::hex
				<< (int) raw_data[index] << ' ';

		if (i == 7)
		{
			std::cout << " ";
		}
		if (i == 15)
		{
			std::cout << std::endl;
		}
	}

	if ((data_size - 1) % 16 != 15)
	{
		std::cout << std::endl;
	}
}
