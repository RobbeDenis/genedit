#include "genedit.hpp"

#include <ftxui/ftxui.hpp>

int main()
{
    using namespace ftxui;

    DNA dna_1{ random_dna() };
    DNA dna_2{ random_dna() };
    DNA dna_3{ random_dna() };

    const SegmentMarker marker{ .start = 1ull, .stop = 2ull };

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
    
    auto document =
        vbox({
            text("Random DNA"),
            hbox({ text("DNA    " + dna_to_hex(dna_1)) | border }),
            hbox({ text("DNA    " + dna_to_hex(dna_2)) | border }),
            hbox({ text("DNA    " + dna_to_hex(dna_3)) | border }),
            text("Test DNA"),
            hbox({ text("DNA    " + dna_to_hex(test_dna)) | border, hbox(test_text) })
        });

    auto screen = Screen::Create(Dimension::Full());
    ftxui::Render(screen, document);
    screen.Print();

    return 0;
}