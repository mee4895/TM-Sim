#include <iostream>

#include "machine.h"
#include "belt.h"

int main() {

	TMachine::action_set_t actions = TMachine::TMachine::generate_empty_action_set();
	actions[0x0][0x0].next_state = 0x1;
	actions[0x0][0x0].action = TMachine::Belt_Action::LEFT;
	actions[0x0][0x1].next_state = 0x0;
	actions[0x0][0x1].action = TMachine::Belt_Action::RIGHT;
	actions[0x0][0x2].next_state = 0x0;
	actions[0x0][0x2].action = TMachine::Belt_Action::RIGHT;
	actions[0x1][0x0].next_state = 0xff;
	actions[0x1][0x0].data_out = 0x2;
	actions[0x1][0x0].action = TMachine::Belt_Action::NONE;
	actions[0x1][0x1].next_state = 0xff;
	actions[0x1][0x1].data_out = 0x2;
	actions[0x1][0x1].action = TMachine::Belt_Action::NONE;
	actions[0x1][0x2].next_state = 0x1;
	actions[0x1][0x2].data_out = 0x1;
	actions[0x1][0x2].action = TMachine::Belt_Action::LEFT;

	const Belt::data_t data[] = {
		0x02, 0x02, 0x02, 0x02,
	};

	ArrayBelt belt(1 << 8);
	TMachine machine(actions, &belt);
	machine.get_belt()->input(data, sizeof(data));

	while (machine.get_state() != 0xff)
	{
		machine.step();
	}

	machine.get_belt()->dump();

	return 0;
}
