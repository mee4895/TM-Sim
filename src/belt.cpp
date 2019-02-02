#include "belt.h"

Belt::Belt(const std::size_t size) : raw_data(new unsigned char[size]), data_size(size)
{
	position = raw_data;
}

Belt::Belt(Belt& cpy) : raw_data(new unsigned char[cpy.data_size]), data_size(cpy.data_size)
{
	position = raw_data + (cpy.position - cpy.raw_data);

	for (std::size_t index = 0; index < data_size; index++)
	{
		raw_data[index] = cpy.raw_data[index];
	}
}

Belt::Belt(Belt&& cpym) : position(cpym.position), raw_data(cpym.raw_data),
		data_size(cpym.data_size)
{
	cpym.position = nullptr;
	cpym.raw_data = nullptr;
	cpym.data_size = 0;

}

Belt::~Belt()
{
	delete [] raw_data;
}

Belt& Belt::operator=(const Belt& cpy)
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

Belt& Belt::operator=(Belt&& cpym)
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

Belt::data_t Belt::get()
{
	return *position;
}

void Belt::set(const data_t data)
{
	*position = data;
}

void Belt::m_left()
{
	if (position == raw_data)
	{
		position += data_size;
	}

	position -= 1;
}

void Belt::m_right()
{
	if (position == raw_data + (data_size - 1))
	{
		position -= data_size;
	}

	position += 1;
}

void Belt::input(const data_t* data, std::size_t size)
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

void Belt::dump()
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
