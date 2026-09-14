#pragma once

#include <cstdint>
#include <vector>
#include <random>
#include <algorithm>
#include <ranges>
#include <generator>
#include <type_traits>

namespace genedit {
	using Codon = uint8_t;

	struct ORFMarkers {
		Codon start;
		Codon stop;
	};

	struct DNA {
		std::vector<uint8_t> bytes;
	};

	template<typename Self>
	concept Genome = std::is_trivially_constructible_v<Self>;

	namespace detail {
		struct GenomeDummy{ };
	}

	template<typename Self>
	concept GenomeMapper = requires(Self mapper, const DNA& dna, detail::GenomeDummy* const genome, const ORFMarkers markers) {
		{ mapper(dna, genome, markers) } -> std::same_as<bool>;
	};

	template<GenomeMapper GMapper>
	struct GeneticCode {
		GeneticCode(ORFMarkers in_markers) : markers{ in_markers } { };

		template<Genome T>
		bool map_dna_to_genome(const DNA& dna, T* const genome) {
			return GMapper{}(dna, genome, markers);
		}

		ORFMarkers markers;
	};

	static [[nodiscard]] std::vector<uint8_t> random_dna(const size_t size) {
		static std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<uint16_t> dna_dist(0u);
		std::vector<uint8_t> dna(size);
		std::ranges::generate(dna, [&]() { return static_cast<uint8_t>(dna_dist(gen)); });
		return dna;
	}

	template <typename T>
	inline std::generator<std::ranges::subrange<std::ranges::iterator_t<T>>> get_open_reading_frames(T& range, const ORFMarkers markers) {
		auto it = std::ranges::begin(range);
		auto end = std::ranges::end(range);

		while (it != end) {
			it = std::ranges::find(it, end, markers.start);
			if (it == end) break;

			auto it_start = std::next(it);
			auto it_stop = std::ranges::find(it_start, end, markers.stop);
			if (it_stop == end) break;

			co_yield std::ranges::subrange(it_start, it_stop);

			it = std::next(it_stop);
		}
	}

	namespace gm {
		struct Direct {
			template<Genome T>
			inline bool operator()(const DNA& dna, T* const genome, const ORFMarkers markers) const {
				size_t write_offset{ 0 };
				for (auto frame : get_open_reading_frames(dna.bytes, markers)) {
					const size_t delta_offset{ sizeof(T) - write_offset };
					const size_t checked_size{ frame.size() > delta_offset ? delta_offset : frame.size() };
					std::memcpy(genome + write_offset, frame.data(), checked_size * sizeof(uint8_t));
					write_offset += checked_size;
				}

				return write_offset == 0;
			}
		};

		struct DirectUnchecked {
			template<Genome T>
			inline bool operator()(const DNA& dna, T* const genome, const ORFMarkers markers) const {
				size_t write_offset{ 0 };
				for (auto frame : get_open_reading_frames(dna.bytes, markers)) {
					std::memcpy(genome + write_offset, frame.data(), frame.size());
					write_offset += frame.size();
				}

				return write_offset == 0;
			}
		};

		struct DirectManualUnchecked {
			template<Genome T>
			inline bool operator()(const DNA& dna, T* const genome, const ORFMarkers markers) const {
				size_t size{ 0 };
				size_t start_frame{ 0 };
				size_t write_offset{ 0 };
				bool reading{ false };

				for (size_t i{ 0 }; i < dna.bytes.size(); ++i) {
					if (reading) {
						if (dna.bytes[i] == markers.stop) {
							std::memcpy(genome + write_offset, dna.bytes.data() + start_frame + 1, size);
							write_offset += size;
							reading = false;
						}
						else {
							++size;
						}
					}
					else if (dna.bytes[i] == markers.start) {
						reading = true;
						start_frame = i;
					}
				}

				return write_offset == 0;
			}
		};
	}
}