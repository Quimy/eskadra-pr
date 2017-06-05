#pragma once

enum TAG { REQUEST_P,REQUEST_S, //ask for resource
		ALLOW_P,ALLOW_S, // allow to go
		TAKEN_P,TAKEN_S, // send when in critical section, when allow arrives
		RELEASED_P,RELEASED_S // send when one realese critical section
	 	};

enum STATE { WANTED_P,WANTED_S, //process wants access
		HELD_P,HELD_S, // process holds resource
		CHOSEN_P,CHOSEN_S, // process awaits for RELEASED message
		NOT_INTERESTED // process not interested in resource
		};