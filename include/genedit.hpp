#pragma once

#include <cstdint>
#include <vector>
#include <random>
#include <array>
#include <bit>
#include <string>
#include <format>
#include <algorithm>

struct DNA {
	std::vector<uint8_t> bytes;
};

struct SegmentMarker {
	uint8_t start;
	uint8_t stop;
};

struct Genome {
	bool debug;
	std::vector<uint8_t> bytes;
};

[[nodiscard]] std::vector<uint8_t> random_dna(const size_t size) {
	static std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<uint16_t> dna_dist(0ull);
	std::vector<uint8_t> dna(size);
	std::ranges::generate(dna, [&]() { return static_cast<uint8_t>(dna_dist(gen)); });
	return dna;
}

[[nodiscard]] Genome interpret_dna(const DNA& dna, const SegmentMarker marker) {
	Genome genome{ .bytes = std::vector<uint8_t>(dna.bytes.size(), 0) };
	size_t size{ 0 };
	size_t start_frame{ 0 };
	size_t dest_offset{ 0 };
	bool reading{ false };

	for (size_t i{ 0 }; i < dna.bytes.size(); ++i) {
		if (reading) {
			if (dna.bytes[i] == marker.stop) {
				std::memcpy(genome.bytes.data() + dest_offset, dna.bytes.data() + start_frame + 1, size);
				dest_offset += size;
				reading = false;
				genome.debug = true;
			}
			else {
				++size;
			}
		}
		else if (dna.bytes[i] == marker.start) {
			reading = true;
			start_frame = i;
		}
	}

	genome.bytes.resize(size);
	return genome;
}

[[nodiscard]] std::string bytes_to_hex(const std::vector<uint8_t>& bytes) {
	std::string result{ "" };

	for (auto byte : bytes) {
		result += std::format("{:02X} ", byte);
	}

	return result;
}