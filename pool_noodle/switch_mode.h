#ifndef SWITCH_MODE_H
#define SWITCH_MODE_H

// Modes determine init inputs
//		Vary them via change_pattern function

void switch_mode(LEDStruct& leds) {
	switch (leds.mode_name) {

		// Juggle Functions -----------------------------------------------------------------------
		case JUGGLE:
			if (!leds.mode_initialized) { juggle_init(leds, 0, 0); }	// one_dir off | phased off
			juggle(leds);
			break;

		case JUGGLE_ONE_DIR:
			if (!leds.mode_initialized) { juggle_init(leds, 1, 0); }	// one_dir on  | phased off
			juggle(leds);
			break;

		case JUGGLE_PHASED:
			if (!leds.mode_initialized) { juggle_init(leds, 0, 1); }	// one_dir off | phased on
			juggle(leds);
			break;

		case JUGGLE_PHASED_ONE_DIR:
			if (!leds.mode_initialized) { juggle_init(leds, 1, 1); }	// one_dir on  | phased on
			juggle(leds);
			break;

		case JUGGLE_HALF:
			if (!leds.mode_initialized) { juggle_init(leds); }
			juggle_half(leds);
			break;

		case JUGGLE_RANDOM:
			juggle(leds);
			break;


		// Rainbow March Functions -----------------------------------------------------------------------
		case RAINBOW_MARCH:
			if (!leds.mode_initialized) { rainbow_init(leds, 0); }		// split off
			rainbow_march(leds);
			break;

		case RAINBOW_MARCH_SPLIT:
			if (!leds.mode_initialized) { rainbow_init(leds, 1); }		// split on
			rainbow_march(leds);
			break;

		case RAINBOW_MARCH_RANDOM:
			rainbow_march(leds);
			break;

		case RAINBOW_1:		// custom 1, rainbows slowly emanating from center
			if (!leds.mode_initialized) { leds.this_dir = 0; rainbow_init(leds, 1, 4, 2, 0); }
			rainbow_march(leds);

		
		// Fire Functions -----------------------------------------------------------------------
		case FIRE:
			if (!leds.mode_initialized) { fire_init(leds, 0, 0); }		// sync off | mirror off
			fire(leds);
			break;

		case FIRE_SYNC:
			if (!leds.mode_initialized) { fire_init(leds, 1, 0); }		// sync on  | mirror off
			fire(leds);
			break;

		case FIRE_MIRROR:
			if (!leds.mode_initialized) { fire_init(leds, 0, 1); }		// sync off | mirror on
			fire(leds);
			break;

		case FIRE_MIRROR_SYNC:
			if (!leds.mode_initialized) { fire_init(leds, 1, 1); }		// sync on  | mirror on
			fire(leds);
			break;

		case FIRE_RANDOM:
			fire(leds);
			break;

		case TORCH:
			if (!leds.mode_initialized) { fire_init(leds, 0, 0, 20, 70, 90); }		// sync off | mirror must be off
			torch(leds);
			break;

		case TORCH_SYNC:
			if (!leds.mode_initialized) { fire_init(leds, 1, 0, 20, 100, 90); }		// sync on  | mirror must be off
			torch(leds);
			break;


		// Colorwave, Pride, Pacifica Functions -----------------------------------------------------------------------
		case COLORWAVE:
			colorwave(leds);
			break;

		case PRIDE:
			pride(leds);
			break;

		case PACIFICA:
			pacifica(leds);
			break;


		// Confetti Functions -----------------------------------------------------------------------
		case CONFETTI:
			confetti(leds);
			break;


		// Sin Functions -----------------------------------------------------------------------
		case ONE_SIN:
			one_sin(leds);
			break;

		case TWO_SIN:
			two_sin(leds);
			break;


		// Fireworks Functions -----------------------------------------------------------------------
		case FIREWORKS:
			fireworks(leds);
			break;


		// Shooting Pole -----------------------------------------------------------------------
		case SHOOTING_POLE:
			shooting_pole(leds);
			break;


		// Noise Functions -----------------------------------------------------------------------
		case NOISE:
			noise(leds);
			break;

		case NOISE_MOVER:
			noise_mover(leds);
			break;


		// Bouncing Functions -----------------------------------------------------------------------
		case BOUNCING_BALLS:
			bouncing_balls(leds);
			break;

		case BOUNCE:
			bounce(leds);
			break;

		// Lightsaber Functions ---------------------------------------------------------------------
		case LIGHTSABER:
			lightsaber(leds);
			break;
	}
}


#endif
