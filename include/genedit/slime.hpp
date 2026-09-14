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

struct SlimeGenomePadded {
	RGB color;
	uint8_t size;
	uint8_t _padding[12];
};

template<genedit::GenomeMapper GMapper, genedit::Genome Genome = SlimeGenome>
struct Slime {
	static constexpr genedit::ORFMarkers ORF_MARKERS = { .start = 16, .stop = 64 };
	static constexpr size_t DNA_SIZE = { 16 };

	bool map_genome() {
		return code.map_dna_to_genome(dna, &genome);
	}

	genedit::GeneticCode<GMapper> code{ ORF_MARKERS };
	genedit::DNA dna;
	Genome genome;
};