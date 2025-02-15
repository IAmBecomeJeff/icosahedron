#ifndef RAINBOW_MARCH_H
#define RAINBOW_MARCH_H

void rainbow_init(LEDStruct& leds, bool rs = random8(2), uint8_t rd = random8(1, 20), uint8_t rr = random8(1, 4), bool ufr = random8(2), uint8_t jb = random8(3,13)) {
    leds.mode_initialized	= 1;
	leds.mode_type			= RAINBOW_MARCH;
    leds.use_palette		= 0;
	leds.delay_time			= 15;

	leds.rainbow_split  = rs;
	if (rd == 1) { rr = 1; }
    leds.rainbow_diff   = rd;
    leds.rainbow_rot    = rr;
	
	leds.juggle_beat	= jb;
    if (DEBUG) { LEDDebug(leds); }
}

void rainbow_update(LEDStruct& leds) {
	keyboard_update = 0;
	switch (update_var) {
		case 1:		leds.rainbow_split	= (bool)update_arg;		break;	//b		
		case 2:		leds.rainbow_diff	= (uint8_t)update_arg;	break;	//c
		case 3:		leds.rainbow_rot	= (uint8_t)update_arg;	break;	//d
		case 4:		leds.juggle_beat	= (uint8_t)update_arg;	break;  //e
		default:	break;
	}
	LEDDebug(leds);
}



void rainbow_march(LEDStruct& leds) {
	if (!leds.mode_initialized) { rainbow_init(leds, RAINBOW_MARCH); }
	if (keyboard_update) { rainbow_update(leds); }

	if (leds.this_dir == 0) leds.rainbow_index += leds.rainbow_rot; else leds.rainbow_index -= leds.rainbow_rot;

	if (!leds.rainbow_split) {
		fill_rainbow(leds.led_data, NUM_LEDS, leds.rainbow_index, leds.rainbow_diff); 
	}
	else {
		fill_rainbow(leds.led_data, NUM_LEDS / 2, leds.rainbow_index, leds.rainbow_diff);
		for (int i = 0; i < NUM_LEDS / 2; i++) { leds.led_data[NUM_LEDS - 1 - i] = leds.led_data[i]; }
	}
}

void rainbow_march_beat(LEDStruct& leds) {
	if (!leds.mode_initialized) { rainbow_init(leds, RAINBOW_MARCH); }
	if (keyboard_update) { rainbow_update(leds); }

	if (leds.this_dir == 0) {
		leds.rainbow_index += leds.rainbow_rot + beatsin8(leds.juggle_beat, 0, 5);
	}
	else {
		leds.rainbow_index -= (leds.rainbow_rot + beatsin8(leds.juggle_beat, 0, 5));
	}

	if (!leds.rainbow_split) {
		fill_rainbow(leds.led_data, NUM_LEDS, leds.rainbow_index, leds.rainbow_diff);
	}
	else {
		fill_rainbow(leds.led_data, NUM_LEDS / 2, leds.rainbow_index, leds.rainbow_diff);
		for (int i = 0; i < NUM_LEDS / 2; i++) { leds.led_data[NUM_LEDS - 1 - i] = leds.led_data[i]; }
	}
}




#endif
