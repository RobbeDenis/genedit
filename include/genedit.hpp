#pragma once

#include <cstdint>
#include <vector>
#include <random>
#include <array>
#include <bit>
#include <string>
#include <format>

using DNA = uint64_t;

struct SegmentMarker {
	uint8_t start;
	uint8_t stop;
};

struct Genome {
	bool debug;
	std::vector<uint8_t> bytes;
};

[[nodiscard]] DNA random_dna() {
	static std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<uint64_t> dna_dist(0ull);
	return DNA{ dna_dist(gen) };
}

[[nodiscard]] Genome interpret_dna(DNA dna, SegmentMarker marker) {
	Genome genome{  };
	genome.bytes.resize(sizeof(DNA), 0);
	auto bytes = std::bit_cast<std::array<uint8_t, sizeof(DNA)>>(dna);
	size_t size{ 0 };
	size_t start_frame{ 0 };
	size_t dest_offset{ 0 };
	bool reading{ false };

	for (size_t i{ 0 }; i < sizeof(dna); ++i) {
		if (reading) {
			if (bytes[i] == marker.stop) {
				std::memcpy(genome.bytes.data() + dest_offset, bytes.data() + start_frame + 1, size);
				dest_offset += size;
				reading = false;
				genome.debug = true;
			}
			else {
				++size;
			}
		}
		else if (bytes[i] == marker.start) {
			reading = true;
			start_frame = i;
		}
	}

	return genome;
}

[[nodiscard]] std::string dna_to_hex(DNA dna) {
	auto bytes = std::bit_cast<std::array<uint8_t, sizeof(DNA)>>(dna);
	std::string result{ "" };

	for (size_t i{ 0 }; i < sizeof(dna); ++i) {

		result += std::format("{:02X} ", bytes[i]);
	}

	return result;
}

[[nodiscard]] std::string genome_to_hex(Genome genome) {
	std::string result{ "" };

	for (auto byte : genome.bytes) {
		result += std::format("{:02X} ", byte);
	}

	return result;
}