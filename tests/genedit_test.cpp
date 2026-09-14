//#include "genedit.hpp"
//#include "slime.hpp"
//
//#include <gtest/gtest.h>
//
//TEST(InterpretDNATest, BasicAssertions) {
//	Slime slime{ };
//	slime.dna.bytes = std::vector<uint8_t>{ Slime::ORF_MARKERS.start, 0xFF, 0xFF, 0xFF, 0xFF, Slime::ORF_MARKERS.stop };
//	slime.dna.bytes.resize(Slime::DNA_SIZE, 0xFF);
//	EXPECT_FALSE(interpret_dna(slime.dna, &slime.genome, Slime::ORF_MARKERS));
//
//	const RGB color{ 0xFF, 0XFF, 0XFF };
//	EXPECT_EQ(slime.genome.color.r, color.r);
//	EXPECT_EQ(slime.genome.color.g, color.g);
//	EXPECT_EQ(slime.genome.color.b, color.b);
//
//	const uint8_t size{ 0xFF };
//	EXPECT_EQ(slime.genome.size, size);
//}