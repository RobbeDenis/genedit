#pragma once

#include "genedit.hpp"

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
	static constexpr SegmentMarker SM = { .start = 16, .stop = 64 };
	static constexpr size_t DNA_SIZE = { 16 };

	DNA dna;
	SlimeGenome genome;
};

struct SlimeGenomePadded {
	RGB color;
	uint8_t size;
	uint8_t _padding[12];
};

struct SlimePadded {
	DNA dna;
	SlimeGenomePadded genome;
};