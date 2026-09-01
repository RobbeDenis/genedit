#pragma once

#include <cstdint>
#include <vector>
#include <random>
#include <array>
#include <bit>
#include <string>
#include <format>

using DNA = uint64_t;

struct Interpreter {
	std::vector<char> start_markers;
	std::vector<char> stop_markers;
};

struct Genome {
	uint32_t data;
};

[[nodiscard]] DNA random_dna() {
	static std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<uint64_t> dna_dist(0ull);
	return DNA{ dna_dist(gen) };
}

[[nodiscard]] std::string dna_to_hex(DNA dna) {
	auto bytes = std::bit_cast<std::array<uint8_t, sizeof(DNA)>>(dna);
	std::string result{ "" };

	for (size_t i{ 0 }; i < sizeof(dna); ++i) {

		result += std::format("{:02X} ", bytes[i]);
	}

	return result;
}