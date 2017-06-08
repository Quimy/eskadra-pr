#pragma once

enum TAG { 
			REQUEST_P, ALLOW_P, TAKEN_P,
			REQUEST_S, ALLOW_S, TAKEN_S, RELEASED_S,
			RELEASED_BOTH
	 	};
enum STATE { WANTED_P,WANTED_S, //process wants access
		HELD_P,HELD_S, // process holds resource
		CHOSEN_P,CHOSEN_S, // process awaits for RELEASED message
		NOT_INTERESTED // process not interested in resource
		};