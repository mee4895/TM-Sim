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

		virtual ~Belt() = 0;

		virtual data_t get() = 0;
		virtual void set(const data_t data) = 0;

		virtual void m_left() = 0;
		virtual void m_right() = 0;

		virtual void input(const data_t* data, const std::size_t size) = 0;
		virtual void dump() = 0;

	protected:

	private:
};

class ArrayBelt : public Belt
{
	public:
		ArrayBelt(const std::size_t size);

		ArrayBelt(ArrayBelt& cpy);
		ArrayBelt(ArrayBelt&& cpym);
		~ArrayBelt();

		ArrayBelt& operator =(const ArrayBelt& cpy);
		ArrayBelt& operator =(ArrayBelt&& cpym);

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

class LinkedBelt : public Belt
{
	public:

		struct Node
		{
			Node(data_t value);

			Node* previous;
			Node* next;

			data_t value;
		};

		LinkedBelt();

		LinkedBelt(LinkedBelt& cpy);
		LinkedBelt(LinkedBelt&& cpym);
		~LinkedBelt();

		LinkedBelt& operator =(const LinkedBelt& cpy);
		LinkedBelt& operator =(LinkedBelt&& cpy);

		data_t get();
		void set(const data_t data);

		void m_left();
		void m_right();

		void input(const data_t* data, const std::size_t size);
		void dump();

	protected:

	private:
		Node* root_element;
};

#endif // BELT_H
