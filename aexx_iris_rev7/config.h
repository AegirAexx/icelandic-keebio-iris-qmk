#pragma once

/* The time (ms) to hold a key before the modifier activates */
#define TAPPING_TERM 250

/* Makes the modifier trigger if you press another key, even if
   the Tapping Term hasn't expired yet. Great for Enter/Alt. */
#define PERMISSIVE_HOLD

/* Prevents the modifier from triggering if you tap the key
   twice quickly (useful for double-tapping Enter for new lines). */
#define QUICK_TAP_TERM 120