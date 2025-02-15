#ifndef LEDSTRUCT_H
#define LEDSTRUCT_H

//======== LED structure =========

struct LEDStruct {
	// LED data array
	struct CRGB led_data[NUM_LEDS];

	// Primary variables
	uint8_t	brightness			= 255;
	uint8_t delay_time			= 15;
	bool	this_dir			= 1;
	ArrayType array_type;					// CURRENT, NEXT, any others, for debug purposes
	bool	use_overlay			= 0;

	// Palette variables
	CRGBPalette16 current_palette;
	CRGBPalette16 target_palette;
	TBlendType current_blending = LINEARBLEND;		// Consider NOBLEND
	uint8_t palette_index;
	bool	use_palette			= 1;		// Determines if palette functions should be used

	// Mode variables
	uint8_t mode_number;					// Used to determine next mode, in change_pattern()
	Mode	mode_name;						// Name of mode, listed in variables.h, used in switch_mode()
	Mode	mode_type;						// Type of mode, for debugging purposes
	bool	mode_initialized	= 0;		// On in regular use, off if new variables need to be set via function_init()

	// Juggle Variables
	uint8_t juggle_index;
	uint8_t juggle_numdots;
	uint8_t juggle_beat;
	uint8_t juggle_fade;
	uint8_t juggle_diff;
	bool	juggle_index_reset;
	bool	juggle_one_dir;
	bool	juggle_phased;
	uint8_t bounce_start;
	uint8_t bounce_start_beat;
	uint8_t bounce_pos;
	uint8_t bounce_length;
	CRGB	bounce[BOUNCE_MAX_LENGTH];
	bool	bounce_rainbow;

	// Rainbow March Variables
	uint8_t rainbow_rot;
	uint8_t rainbow_diff;
	uint8_t rainbow_index;
	bool	rainbow_split;

	// Fire and Torch Variables
	uint8_t fire_sparking;
	uint8_t fire_cooling;
	byte	heat[NUM_LEDS];
	bool	fire_sync;

	// Colorwave and Pride Variables
	uint16_t sPseudotime;
	uint16_t sLastMillis;
	uint16_t sHue16;
	uint8_t  brightdepth, msmultiplier, hue8, sat8, bri8, cwave_index;
	uint16_t brightnessthetainc16, hue16, hueinc16, ms, deltams, brightnesstheta16, h16_128, b16, bri16, pixelnumber;
	uint16_t strip_range;

	// Confetti Variables
	uint8_t confetti_fade;

	// Sin Variables
	uint8_t sin_inc;
	uint8_t sin_speed;
	uint8_t sin_cutoff;
	uint8_t sin_rot;
	uint8_t sin_all_freq;
	uint8_t sin_index;
	uint8_t sin_start;
	uint8_t sin_phase;
	uint8_t sin_hue;
	uint8_t sin_bri;
	uint8_t two_speed;
	uint8_t two_rot;
	uint8_t two_cutoff;
	uint8_t two_phase;
	uint8_t two_hue;
	uint8_t two_bri;

	uint8_t bg_clr;
	uint8_t bg_bri;

	// Fireworks Variables
	uint8_t firework_position;
	uint8_t firework_hue;
	uint8_t firework_bri;
	stage current_stage;
	uint32_t next_explosion_time;
	bool exploded;
	uint8_t number_of_sparks;
	float spark_pos[MAX_NUMBER_OF_SPARKS];
	float spark_vel[MAX_NUMBER_OF_SPARKS];
	bool spark_dir[MAX_NUMBER_OF_SPARKS];
	float spark_fade[MAX_NUMBER_OF_SPARKS];
	float spark_bri[MAX_NUMBER_OF_SPARKS];
	uint8_t brightest_spark;


	// Noise Variables
	uint16_t noise_scale;
	uint16_t noise_yscale;
	uint16_t noise_dist;
	uint8_t noise_index;
	uint8_t noise_fade;

	// Bouncing Balls Variables
	uint8_t bouncing_index;
	uint8_t bouncing_fade;
	uint8_t number_of_balls;
	float   bouncing_heights[MAX_NUMBER_OF_BALLS];
	float   bouncing_vImpact[MAX_NUMBER_OF_BALLS];
	float   bouncing_tCycle[MAX_NUMBER_OF_BALLS];
	int     bouncing_pos[MAX_NUMBER_OF_BALLS];
	long    bouncing_tLast[MAX_NUMBER_OF_BALLS];
	float   bouncing_COR[MAX_NUMBER_OF_BALLS];


	// Twinkle Variables
	uint8_t twinkle_speed;
	uint8_t twinkle_density;
	bool	cool_like_incandescent;
	bool	auto_select_bg_color;

	// Plasma Variables
	int plasma_phase1;
	int plasma_phase2;
	uint8_t plasma_beat1;
	uint8_t plasma_beat2;
	uint8_t plasma_beat3;
	uint8_t plasma_index;
	uint8_t plasma_bright;
	uint8_t plasma_range1;
	uint8_t plasma_range2;

};


// Create LED Structures
LEDStruct curr_leds;
LEDStruct next_leds;
LEDStruct curr_over_leds;
LEDStruct next_over_leds;


void print_palette(uint8_t pn); // Forward declaration


// Debugging function
void LEDDebug(LEDStruct& leds) {
	Serial.println("");
	Serial.println("==================================");

	// Print which Array it is
	if		(leds.array_type == CURRENT) { Serial.println("==============CURRENT============="); }
	else if (leds.array_type == NEXT)	 { Serial.println("~~~~~~~~~~~~~~~NEXT~~~~~~~~~~~~~~~"); }

	// Print Standard Variables
	Serial.print("|| (B) Brightness:\t");
	Serial.print(max_bright);
	Serial.println("\t||");
	Serial.print("|| (D) delay_time:\t");
	Serial.print(leds.delay_time);
	Serial.println("\t||");
	Serial.print("|| (N) this_dir:\t");
	Serial.print(leds.this_dir);
	Serial.println("\t||");
	Serial.print("|| (F) blending:\t");
	if (leds.current_blending == LINEARBLEND) { Serial.print("LINEAR"); }
	else { Serial.print("NOBLEND"); }
	Serial.println("\t||");
	Serial.print("|| (M) mode_number:\t");
	Serial.print(leds.mode_number);
	Serial.println("\t||");
	Serial.print("|| mode_initialized:\t"); // 3 tabs
	Serial.print(leds.mode_initialized);
	Serial.println("\t||");
	Serial.print("|| use_palette:\t\t");
	Serial.print(leds.use_palette);
	Serial.println("\t||");
	if (leds.use_palette) { print_palette(leds.palette_index); }
	Serial.println("=================================="); //4 tabs then ||

	// Print mode-specific variables
	switch (leds.mode_type) {
		case JUGGLE:
			if(leds.mode_name == JUGGLE_HALF)		{ Serial.println("============JUGGLE HALF==========="); }
			else if(leds.mode_name == MULTI_JUGGLE)	{ Serial.println("===========MULTI JUGGLE==========="); }
			else									{ Serial.println("==============JUGGLE=============="); } // 34 characters
			Serial.print("|| (b) one_dir:\t\t");
			Serial.print(leds.juggle_one_dir);
			Serial.println("\t||");
			Serial.print("|| (c) phased:\t\t");
			Serial.print(leds.juggle_phased);
			Serial.println("\t||");
			Serial.print("|| (d) numdots:\t\t");
			Serial.print(leds.juggle_numdots);
			Serial.println("\t||");
			Serial.print("|| (e) beat:\t\t");
			Serial.print(leds.juggle_beat);
			Serial.println("\t||");
			Serial.print("|| (f) fade:\t\t");
			Serial.print(leds.juggle_fade);
			Serial.println("\t||");
			Serial.print("|| (g) diff:\t\t");
			Serial.print(leds.juggle_diff);
			Serial.println("\t||");
			Serial.print("|| (h) index_reset:\t");
			Serial.print(leds.juggle_index_reset);
			Serial.println("\t||");
			break;

		case RAINBOW_MARCH:
			switch (leds.mode_name) {
				case RAINBOW_MARCH:			Serial.println("==========RAINBOW MARCH==========="); break;
				case RAINBOW_MARCH_SPLIT:	Serial.println("=======RAINBOW MARCH SPLIT========"); break;
				case RAINBOW_MARCH_BEAT:	Serial.println("=======RAINBOW MARCH BEAT========="); break;
				default: break;
			}
			Serial.print("|| (b) split:\t\t");
			Serial.print(leds.rainbow_split);
			Serial.println("\t||");
			Serial.print("|| (c) diff:\t\t");
			Serial.print(leds.rainbow_diff);
			Serial.println("\t||");
			Serial.print("|| (d) rot:\t\t");
			Serial.print(leds.rainbow_rot);
			Serial.println("\t||");
			if (leds.mode_name == RAINBOW_MARCH_BEAT) {
				Serial.print("|| (e) juggle_beat:\t");
				Serial.print(leds.juggle_beat);
				Serial.println("\t||");
			}
			break;

		case FIRE:
			switch (leds.mode_name) {
				case FIRE:				Serial.println("==============FIRE================"); break;
				case FIRE_MIRROR:		Serial.println("===========FIRE MIRROR============"); break;
				default: break;
			}
			Serial.print("|| (a) sparking:\t");
			Serial.print(leds.fire_sparking);
			Serial.println("\t||");
			Serial.print("|| (b) cooling:\t\t");
			Serial.print(leds.fire_cooling);
			Serial.println("\t||");
			break;
		
		case COLORWAVE:
			Serial.println("============COLORWAVE=============");
			break;

		case PRIDE:
			Serial.println("==============PRIDE===============");
			break;

		case PACIFICA:
			Serial.println("=============PACIFCIA=============");
			break;

		case CONFETTI:
			Serial.println("=============CONFETTI=============");
			Serial.print("|| (b) confetti_fade:\t");
			Serial.print(leds.confetti_fade);
			Serial.println("\t||");
			break;

		case FIREWORKS:
			Serial.println("============FIREWORKS=============");
			Serial.print("|| Current Stage:\t");
			switch (leds.current_stage) {
				case WAITING:	Serial.print("WAITING"); Serial.println("\t||"); break;
				case FADEUP:	Serial.print("FADEUP");  Serial.println("\t||"); break;
				case EXPLOSION: Serial.println("EXPLOSION|"); break;
			}
			Serial.print("|| firework_position:\t");
			Serial.print(leds.firework_position);
			Serial.println("\t||");
			Serial.print("|| Number of sparks:\t");
			Serial.print(leds.number_of_sparks);
			Serial.println("\t||");
			Serial.print("|| Brightest spark:\t");
			Serial.print(leds.brightest_spark);
			Serial.println("\t||");
			Serial.print("|| Next explosion time:\t");
			Serial.print(leds.next_explosion_time);
			Serial.println("\t||");
			Serial.print("|| (a) use_overlay:\t");
			Serial.print(leds.use_overlay);
			Serial.println("\t||");
			break;

		case ONE_SIN:
			Serial.println("=============ONE SIN==============");
			Serial.print("|| (b) sin_inc:\t\t");
			Serial.print(leds.sin_inc);
			Serial.println("\t||");
			Serial.print("|| (c) sin_speed:\t");
			Serial.print(leds.sin_speed);
			Serial.println("\t||");
			Serial.print("|| (d) sin_cutoff:\t");
			Serial.print(leds.sin_cutoff);
			Serial.println("\t||");
			Serial.print("|| (e) sin_rot:\t\t");
			Serial.print(leds.sin_rot);
			Serial.println("\t||");
			Serial.print("|| (f) sin_phase:\t");
			Serial.print(leds.sin_phase);
			Serial.println("\t||");
			Serial.print("|| (g) all_freq:\t");
			Serial.print(leds.sin_all_freq);
			Serial.println("\t||");
			Serial.print("|| (h) bg_clr:\t\t");
			Serial.print(leds.bg_clr);
			Serial.println("\t||");
			Serial.print("|| (i) bg_bri:\t\t");
			Serial.print(leds.bg_bri);
			Serial.println("\t||");
			break;

		case TWO_SIN:
			Serial.println("=============TWO SIN==============");
			Serial.print("|| (b) sin_hue:\t\t");
			Serial.print(leds.sin_hue);
			Serial.println("\t||");
			Serial.print("|| (c) two_hue:\t\t");
			Serial.print(leds.two_hue);
			Serial.println("\t||");
			Serial.print("|| (d) sin_speed:\t");
			Serial.print(leds.sin_speed);
			Serial.println("\t||");
			Serial.print("|| (e) two_speed:\t");
			Serial.print(leds.two_speed);
			Serial.println("\t||");
			Serial.print("|| (f) sin_rot:\t\t");
			Serial.print(leds.sin_rot);
			Serial.println("\t||");
			Serial.print("|| (g) two_rot:\t\t");
			Serial.print(leds.two_rot);
			Serial.println("\t||");
			Serial.print("|| (h) sin_cutoff:\t");
			Serial.print(leds.sin_cutoff);
			Serial.println("\t||");
			Serial.print("|| (i) two_cutoff:\t");
			Serial.print(leds.two_cutoff);
			Serial.println("\t||");
			Serial.print("|| (j) sin_phase:\t");
			Serial.print(leds.sin_phase);
			Serial.println("\t||");
			Serial.print("|| (k) two_phase:\t");
			Serial.print(leds.two_phase);
			Serial.println("\t||");
			Serial.print("|| (l) all_freq:\t");
			Serial.print(leds.sin_all_freq);
			Serial.println("\t||");
			break;

		case NOISE:
			Serial.println("===============NOISE==============");
			Serial.print("|| (b) noise_scale:\t");
			Serial.print(leds.noise_scale);
			Serial.println("\t||");
			Serial.print("|| (c) noise_yscale:\t");
			Serial.print(leds.noise_yscale);
			Serial.println("\t||");
			Serial.print("|| (d) noise_dist:\t");
			Serial.print(leds.noise_dist);
			Serial.println("\t||");
			Serial.print("|| (e) noise_fade:\t");
			Serial.print(leds.noise_fade);
			Serial.println("\t||");
			break;

		case BOUNCE:
			Serial.println("==============BOUNCE==============");
			Serial.print("|| (a) juggle_fade:\t");
			Serial.print(leds.juggle_fade);
			Serial.println("\t||");
			Serial.print("|| (b) bounce_length:\t");
			Serial.print(leds.bounce_length);
			Serial.println("\t||");
			Serial.print("|| (c) juggle_beat:\t");
			Serial.print(leds.juggle_beat);
			Serial.println("\t||");
			Serial.print("|| (d) rainbow_diff:\t");
			Serial.print(leds.rainbow_diff);
			Serial.println("\t||");
			Serial.print("|| (e) start_beat:\t");
			Serial.print(leds.bounce_start_beat);
			Serial.println("\t||");
			Serial.print("|| (f) bounce_rainbow:\t");
			Serial.print(leds.bounce_rainbow);
			Serial.println("\t||");
			break;

		case BOUNCING_BALLS:
			Serial.println("==========BOUNCING BALLS==========");
			Serial.print("|| (a) fade:\t\t");
			Serial.print(leds.bouncing_fade);
			Serial.println("\t||");
			Serial.print("|| (b) number of balls:\t");
			Serial.print(leds.number_of_balls);
			Serial.println("\t||");
			Serial.print("|| (c) use_palette:\t");
			Serial.print(leds.use_palette);
			Serial.println("\t||");
			break;

		case TWINKLE:
			Serial.println("=============TWINKLE==============");
			Serial.print("|| (b) twinkle_speed:\t");
			Serial.print(leds.twinkle_speed);
			Serial.println("\t||");
			Serial.print("|| (c) twinkle_density:\t");
			Serial.print(leds.twinkle_density);
			Serial.println("\t||");
			Serial.print("|| (d) cool_like_incan:\t");
			Serial.print(leds.cool_like_incandescent);
			Serial.println("\t||");
			Serial.print("|| (e) auto_select_bg:\t");
			Serial.print(leds.auto_select_bg_color);
			Serial.println("\t||");
			break;

		case PLASMA:
			Serial.println("=============PLASMA===============");
			Serial.print("|| (b) plasma_beat1:\t");
			Serial.print(leds.plasma_beat1);
			Serial.println("\t||");
			Serial.print("|| (c) plasma_beat2:\t");
			Serial.print(leds.plasma_beat2);
			Serial.println("\t||");
			Serial.print("|| (d) plasma_beat3:\t");
			Serial.print(leds.plasma_beat3);
			Serial.println("\t||");
			Serial.print("|| (e) plasma_range1:\t");
			Serial.print(leds.plasma_range1);
			Serial.println("\t||");
			Serial.print("|| (f) plasma_range2:\t");
			Serial.print(leds.plasma_range2);
			Serial.println("\t||");
			break;


		default:
			Serial.println("");
			Serial.println("==========MODE TYPE ERROR=========");
			Serial.println("");
			break;
	}
	Serial.println("==================================\n");
}


#endif