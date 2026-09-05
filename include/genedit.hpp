#pragma once

#include <cstdint>
#include <vector>
#include <random>
#include <array>
#include <bit>
#include <utility>
#include <string>
#include <format>
#include <algorithm>
#include <ranges>
#include <generator>
#include <span>

struct DNA {
	std::vector<uint8_t> bytes;
};

struct SegmentMarker {
	uint8_t start;
	uint8_t stop;
};

struct Genome {
	std::vector<uint8_t> bytes;
	bool debug;
};

using genome_data_t = std::span<uint8_t>;

[[nodiscard]] std::vector<uint8_t> random_dna(const size_t size) {
	static std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<uint16_t> dna_dist(0u);
	std::vector<uint8_t> dna(size);
	std::ranges::generate(dna, [&]() { return static_cast<uint8_t>(dna_dist(gen)); });
	return dna;
}

template <typename T>
std::generator<std::ranges::subrange<std::ranges::iterator_t<T>>> between_markers(T& range, const SegmentMarker marker) {
	auto it = std::ranges::begin(range);
	auto end = std::ranges::end(range);

	while (it != end) {
		it = std::ranges::find(it, end, marker.start);
		if (it == end) break;

		auto it_start = std::next(it);
		auto it_stop = std::ranges::find(it_start, end, marker.stop);
		if (it_stop == end) break;

		co_yield std::ranges::subrange(it_start, it_stop);

		it = std::next(it_stop);
	}
}

size_t map_dna_to_genome(const DNA& dna, const genome_data_t genome, const SegmentMarker marker) {
	size_t genome_size{ };
	for (auto segment : between_markers(dna.bytes, marker)) {
		std::memcpy(genome.data() + genome_size, segment.data(), segment.size());
		genome_size += segment.size();
	}
	return genome_size;
}

[[nodiscard]] Genome interpret_dna(const DNA& dna, const SegmentMarker marker) {
	Genome genome{ .bytes = std::vector<uint8_t>(dna.bytes.size(), 0u) };
	size_t size{ 0 };
	size_t start_frame{ 0 };
	size_t dest_offset{ 0 };
	bool reading{ false };

	//for (size_t i{ 0 }; i < dna.bytes.size(); ++i) {
	//	if (reading) {
	//		if (dna.bytes[i] == marker.stop) {
	//			std::memcpy(genome.bytes.data() + dest_offset, dna.bytes.data() + start_frame + 1, size);
	//			dest_offset += size;
	//			reading = false;
	//			genome.debug = true;
	//		}
	//		else {
	//			++size;
	//		}
	//	}
	//	else if (dna.bytes[i] == marker.start) {
	//		reading = true;
	//		start_frame = i;
	//	}
	//}

	size = map_dna_to_genome(dna, genome.bytes, marker);

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