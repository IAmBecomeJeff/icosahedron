#ifndef JUGGLE_H
#define JUGGLE_H

/* This is adapted from a routine created by Mark Kriegsman */

/*  Usage - juggle_pal();
 *  
 *  this_hue
 *  this_fade
 *  numdots
 *  this_beat
 *  this_bright
 *  this_diff
 */
// use beatsin16_halfup and beatsin16_halfdown to make it go one way

bool reset_juggle_index = 0;

void juggle_pal() {
	if (mode_change) {
		mode_change = 0;
		numdots = random8(2, 6);
		use_palette = 1;
		reset_juggle_index = random8(1);
		this_fade = random8(16, 64);
		this_beat = random8(4, 20);
		this_diff = random8(1, 255/numdots);
    this_delay = 10;
	}
	if (reset_juggle_index) {
		this_index = 0;
	}
	fadeToBlackBy(leds, NUM_LEDS, this_fade);
	for (int i = 0; i < numdots; i++) {
		leds[beatsin16(this_beat + i + numdots, 0, NUM_LEDS)] += ColorFromPalette(current_palette, this_index, 255, current_blending);    // Munge the values and pick a colour from the palette
		this_index += this_diff;
	}
} // juggle_pal()



void juggle_pal_onedir() {
	if (mode_change) {
		mode_change = 0;
		numdots = random8(2, 6);
		use_palette = 1;
		reset_juggle_index = random8(1);
		this_fade = random8(16, 64);
		this_beat = random8(4, 20);
		this_diff = random8(1, 255 / numdots);
		this_dir = random8(1);
    this_delay =10; 
	}
	if (reset_juggle_index) {
		this_index = 0;
	}
	fadeToBlackBy(leds, NUM_LEDS, this_fade);
	for (int i = 0; i < numdots; i++) {
		if (!this_dir) {
			leds[beatsin16_halfdown(this_beat + 2 * i + numdots, 0, NUM_LEDS - 1)] += ColorFromPalette(current_palette, this_index, this_bright, current_blending);
		}
		else {
			leds[beatsin16_halfup(this_beat + 2 * i + numdots, 0, NUM_LEDS - 1)] += ColorFromPalette(current_palette, this_index, this_bright, current_blending);
		}
		this_index += this_diff;
	}
} // 


#endif
