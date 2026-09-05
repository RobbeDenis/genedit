#pragma once

#include "genedit.hpp"

static constexpr SegmentMarker SlimeSM = { .start = 16, .stop = 64 };

struct RGB {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct SlimeGenome {
	RGB color;
	uint8_t size;
};

struct Slime {
	DNA dna;
	SlimeGenome genome;
};