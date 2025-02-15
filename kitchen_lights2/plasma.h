#ifndef PLASMA_H
#define PLASMA_H


void plasma_init(LEDStruct& leds, uint8_t b1 = random8(13,41),  uint8_t b2 = random8(13,41), uint8_t b3 = random8(3,31), int r1 = random8(30,101), int r2 = random8(30,101)) {
	leds.mode_initialized	= 1;
	leds.mode_type			= PLASMA;
	leds.use_palette		= 1;
	leds.delay_time			= 15;

	leds.plasma_beat1	= b1;
	leds.plasma_beat2	= b2;
	leds.plasma_beat3	= b3;
	leds.plasma_range1	= r1;
	leds.plasma_range2  = r2;
}


void plasma_update(LEDStruct& leds) {
	keyboard_update = 0;

	switch (update_var) {
		case 1: leds.plasma_beat1 = (uint8_t)update_arg; break; //b
		case 2: leds.plasma_beat2 = (uint8_t)update_arg; break; //c
		case 3: leds.plasma_beat3 = (uint8_t)update_arg; break; //d
		case 4: leds.plasma_range1 = (uint8_t)update_arg; break; //e
		case 5: leds.plasma_range2 = (uint8_t)update_arg; break; //f
		default: break;
	}
	LEDDebug(leds);
}



void plasma(LEDStruct& leds) {
	if (!leds.mode_initialized) { plasma_init(leds); }
	if (keyboard_update) { plasma_update(leds); }

	leds.plasma_phase1 = beatsin8(leds.plasma_beat1, (0 - leds.plasma_range1), leds.plasma_range1);
	leds.plasma_phase2 = beatsin8(leds.plasma_beat2, (0 - leds.plasma_range2), leds.plasma_range2);

	for (uint16_t k = 0; k < NUM_LEDS; k++) {
		leds.plasma_index = cubicwave8((k * 23) + leds.plasma_phase1) / 2 + cos8((k * 15) + leds.plasma_phase2) / 2;
		leds.plasma_bright = qsuba(leds.plasma_index, beatsin8(leds.plasma_beat3, 0, 96));

		leds.led_data[k] = ColorFromPalette(leds.current_palette, leds.plasma_index, leds.plasma_bright, leds.current_blending);
	}
}


#endif