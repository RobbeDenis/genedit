#pragma once

#include <vector>
#include <format>
#include <string>

inline [[nodiscard]] std::string bytes_to_hex(const std::vector<uint8_t>& bytes) {
	std::string result{ "" };

	for (auto byte : bytes) {
		result += std::format("{:02X} ", byte);
	}

	return result;
}

inline [[nodiscard]] std::string bytes_to_dec(const std::vector<uint8_t>& bytes) {
	std::string result{ "" };

	for (auto byte : bytes) {
		result += std::format("{} ", byte);
	}

	return result;
}