#pragma once
enum TAG { REQUEST_P,REQUEST_S, //ask for resource
		ALLOW_P,ALLOW_S, // allow to go
		TAKEN_P,TAKEN_S, // send when in critical section, when allow arrives
		RELEASED_P,RELEASED_S // send when one realese critical section
	 	};

enum STATE { WANTED_P,WANTED_S,
		HELD_P,HELP_S,
		NOT_INTERESTED
		};