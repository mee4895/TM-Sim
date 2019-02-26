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

ArrayBelt& ArrayBelt::operator =(const ArrayBelt& cpy)
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

ArrayBelt& ArrayBelt::operator =(ArrayBelt&& cpym)
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

LinkedBelt::Node::Node(Belt::data_t value) : previous(nullptr), next(nullptr), value(value) { }

LinkedBelt::LinkedBelt()
{
	root_element = new Node(0x00);
}

LinkedBelt::~LinkedBelt()
{
	while (root_element->previous != nullptr)
	{
		root_element = root_element->previous;
	}

	while (root_element->next != nullptr)
	{
		root_element = root_element->next;
		delete root_element->previous;
	}

	delete root_element;
}

Belt::data_t LinkedBelt::get()
{
	return root_element->value;
}

void LinkedBelt::set(const Belt::data_t data)
{
	root_element->value = data;
}

void LinkedBelt::m_left()
{
	if (root_element->previous == nullptr)
	{
		root_element->previous = new LinkedBelt::Node(0x00);
		root_element->previous->next = root_element;
	}
	root_element = root_element->previous;
}

void LinkedBelt::m_right()
{
	if (root_element->next == nullptr)
	{
		root_element->next = new Node(0x00);
		root_element->next->previous = root_element;
	}
	root_element = root_element->next;
}

void LinkedBelt::input(const Belt::data_t* data, const std::size_t size)
{
	Node* pointer = root_element;

	if (root_element->previous == nullptr && root_element->next == nullptr)
	{
		root_element->value = data[0];
	}
	else
	{
		while (pointer->next != nullptr)
		{
			pointer = pointer->next;
		}

		pointer->next = new Node(data[0]);
		pointer->next->previous = pointer;
		pointer = pointer->next;
	}

	for (std::size_t index = 1; index < size; index++)
	{
		pointer->next = new Node(data[index]);
		pointer->next->previous = pointer;
		pointer = pointer->next;
	}
}

void LinkedBelt::dump()
{
	Node* pointer = root_element;
	while (pointer->previous != nullptr)
	{
		pointer = pointer->previous;
	}

	for (short i = 0; pointer != nullptr; pointer = pointer->next)
	{
		if (i == 0)
		{
			std::cout << "0x" << std::setw(8) << std::setfill('0') << std::hex
					<< 0x00 << "     ";
		}

		std::cout << std::setw(2) << std::setfill('0') << std::hex
				<< (int) root_element->value << ' ';

		if (i == 7)
		{
			std::cout << " ";
		}
		if (i == 15)
		{
			std::cout << std::endl;
		}

		i++;
		i %= 16;
	}
}
