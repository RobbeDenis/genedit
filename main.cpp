#include "genedit.hpp"

#include <ftxui/ftxui.hpp>

ftxui::Element docu_rnd_dna();
ftxui::Element docu_test_genome();
ftxui::Element docu_valid_genomes();

int main()
{
    auto screen = ftxui::Screen::Create(ftxui::Dimension::Full());
    //ftxui::Render(screen, docu_rnd_dna());
    //ftxui::Render(screen, docu_test_genome());
    ftxui::Render(screen, docu_valid_genomes());
    screen.Print();

    return 0;
}

[[nodiscard]] ftxui::Element docu_rnd_dna() {
    using namespace ftxui;
    DNA dna_1{ random_dna() };
    DNA dna_2{ random_dna() };
    DNA dna_3{ random_dna() };
    return vbox({
            text("Random DNA"),
            hbox({ text("DNA    " + dna_to_hex(dna_1)) | border }),
            hbox({ text("DNA    " + dna_to_hex(dna_2)) | border }),
            hbox({ text("DNA    " + dna_to_hex(dna_3)) | border })
    });
}

[[nodiscard]] ftxui::Element docu_test_genome() {
    using namespace ftxui;
    const SegmentMarker marker{ .start = 1u, .stop = 2u };

    DNA test_dna{ marker.start };
    test_dna += 240ull << 8;
    test_dna += 108ull << 16;
    test_dna += 23ull << 24;
    test_dna += static_cast<uint64_t>(marker.stop) << 32;

    Genome test_genome{ interpret_dna(test_dna, marker) };
    Elements test_text{ };
    for (size_t i = 0; i < test_genome.data.size(); ++i) {
        test_text.push_back(text(dna_to_hex(test_genome.data[i])) | border | color(Color::Green));
    }
    return vbox({
            text("Test DNA"),
            hbox({ text("DNA    " + dna_to_hex(test_dna)) | border, hbox(test_text) })
    });
}

[[nodiscard]] ftxui::Element docu_valid_genomes() {
    using namespace ftxui;
    const SegmentMarker marker{ .start = 1u, .stop = 2u };
    DNA dna{ };
    Genome genome{ };
    size_t counter{ };

    while (genome.data.empty()) {
        dna = random_dna();
        genome = interpret_dna(dna, marker);
        ++counter;
    }

    Elements genome_text{ };
    for (size_t i = 0; i < genome.data.size(); ++i) {
        genome_text.push_back(text(dna_to_hex(genome.data[i])) | border | color(Color::Green));
    }

    return vbox({
            hbox({ 
                text("start  " + std::format("{:02X} ", marker.start)) | border, 
                text("stop   " + std::format("{:02X} ", marker.stop)) | border 
            }),
            hbox({ text("DNA    " + dna_to_hex(dna)) | border, hbox(genome_text) }),
            text("counter: " + std::to_string(counter))
    });
}