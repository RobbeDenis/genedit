#include "genedit.hpp"

#include <ftxui/ftxui.hpp>

ftxui::Element docu_dna_to_genome();

int main()
{
    auto screen = ftxui::Screen::Create(ftxui::Dimension::Full());
    ftxui::Render(screen, docu_dna_to_genome());
    screen.Print();

    return 0;
}

[[nodiscard]] ftxui::Element docu_dna_to_genome() {
    using namespace ftxui;
    const SegmentMarker marker{ .start = 1u, .stop = 2u };
    DNA dna{ };
    Genome genome{ };
    size_t counter{ };

    while (!genome.debug) {
        dna = { .bytes = random_dna(16) };
        genome = interpret_dna(dna, marker);
        ++counter;
    }

    return vbox({
        hbox({
            text("start  " + std::format("{:02X} ", marker.start)) | border,
            text("stop   " + std::format("{:02X} ", marker.stop)) | border
        }),
        hbox({ text("DNA    " + bytes_to_hex(dna.bytes)) | border, text(bytes_to_hex(genome.bytes)) | border | color(Color::Green)}),
        text("counter: " + std::to_string(counter))
    });
}