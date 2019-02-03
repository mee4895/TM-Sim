#include "machine.h"

TMachine::TMachine(const TMachine::action_set_t actions, Belt* belt) :
		state(0), belt(belt), actions(actions) { }

Belt* TMachine::get_belt()
{
	return belt;
}

TMachine::state_t TMachine::get_state()
{
	return state;
}

void TMachine::step()
{
	const Belt::data_t data = belt->get();
	const Machine_Action current = actions[state][data];

	state = current.next_state;

	if (current.data_out != data)
	{
		belt->set(current.data_out);
	}

	switch (current.action)
	{
		case Belt_Action::LEFT:
			belt->m_left();
			break;

		case Belt_Action::RIGHT:
			belt->m_right();
			break;

		default:
			break;
	}
}

TMachine::action_set_t TMachine::generate_empty_action_set()
{
	TMachine::action_set_t action_set = new TMachine::Machine_Action*[0x100];
	for (std::size_t state = 0; state < 0x100; state++)
	{
		action_set[state] = new TMachine::Machine_Action[0x100];
		for (std::size_t data = 0; data < 0x100; data++)
		{
			action_set[state][data].next_state = 0xff;
			action_set[state][data].data_out = data;
			action_set[state][data].action = TMachine::Belt_Action::NONE;
		}
	}

	return action_set;
}
