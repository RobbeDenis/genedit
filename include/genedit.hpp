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
	std::vector<uint64_t> data;
};

[[nodiscard]] DNA random_dna() {
	static std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<uint64_t> dna_dist(0ull);
	return DNA{ dna_dist(gen) };
}

[[nodiscard]] Genome interpret_dna(DNA dna, SegmentMarker marker) {
	Genome result{ };
	auto bytes = std::bit_cast<std::array<uint8_t, sizeof(DNA)>>(dna);
	uint64_t segment{ 0 };
	int shift{ 0 };
	bool reading{ false };

	for (size_t i{ 0 }; i < sizeof(dna); ++i) {
		if (reading) {
			if (bytes[i] == marker.stop) {
				reading = false;
				result.data.push_back(segment);
				segment = 0;
				shift = 0;
			}
			else {
				segment += static_cast<uint64_t>(bytes[i]) << shift * 8;
				++shift;
			}
		}
		else if (bytes[i] == marker.start) {
			reading = true;
		}
	}

	return result;
}

[[nodiscard]] std::string dna_to_hex(DNA dna) {
	auto bytes = std::bit_cast<std::array<uint8_t, sizeof(DNA)>>(dna);
	std::string result{ "" };

	for (size_t i{ 0 }; i < sizeof(dna); ++i) {

		result += std::format("{:02X} ", bytes[i]);
	}

	return result;
}