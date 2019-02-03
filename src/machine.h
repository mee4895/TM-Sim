#ifndef MACHINE_H
#define MACHINE_H

#include <cstddef>

#include "belt.h"

class TMachine
{
	public:
		typedef unsigned char state_t;

		enum Belt_Action
		{
			NONE,
			LEFT,
			RIGHT,

			NUM_ACTIONS
		};

		struct Machine_Action
		{
			state_t next_state;
			Belt::data_t data_out;
			Belt_Action action;
		};
		typedef Machine_Action** action_set_t;

		TMachine(const std::size_t belt_size, const action_set_t actions);

		Belt& get_belt();
		state_t get_state();

		void step();

		static action_set_t generate_empty_action_set();

	protected:

	private:
		state_t state;
		Belt belt;
		const action_set_t actions;
};

#endif // MACHINE_H
