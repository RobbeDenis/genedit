#include "genedit.hpp"
#include "slime.hpp"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <ftxui/ftxui.hpp>

ftxui::Element docu_dna_to_genome();
ftxui::Element docu_slime_genome();

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    auto screen = ftxui::Screen::Create(ftxui::Dimension::Full());
    ftxui::Render(screen, docu_slime_genome());
    screen.Print();

    return 0;
}

[[nodiscard]] ftxui::Element docu_dna_to_genome() {
    using namespace ftxui;
    const SegmentMarker marker{ .start = 1u, .stop = 2u };
    DNA dna{ };
    Genome genome{ };
    size_t counter{ };

    while (genome.bytes.empty()) {
        dna = { .bytes = random_dna(16) };
        genome = interpret_dna_gen(dna, marker);
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

[[nodiscard]] ftxui::Element docu_slime_genome() {
    using namespace ftxui;
    Slime slime{ };
    size_t counter{ };

    do {
        slime.dna = { .bytes = random_dna(Slime::DNA_SIZE) };
        ++counter;
    } while (interpret_dna_checked(slime.dna, &slime.genome, Slime::SM));

    return vbox({
        hbox({
            text("start  " + std::format("0x{0:02X} | {0}", Slime::SM.start)) | border,
            text("stop   " + std::format("0x{0:02X} | {0}", Slime::SM.stop)) | border
        }),
        hbox({ text("DNA   (HEX) " + bytes_to_hex(slime.dna.bytes)) | border }),
        hbox({ text("DNA   (DEC) " + bytes_to_dec(slime.dna.bytes)) | border }),
        hbox({ text("r: " + std::to_string(slime.genome.color.r)) | border | color(Color::Red),
            text("g: " + std::to_string(slime.genome.color.g)) | border | color(Color::Green),
            text("b: " + std::to_string(slime.genome.color.b)) | border | color(Color::Blue),
            gauge(0.1) | color(ftxui::Color{slime.genome.color.r, slime.genome.color.g, slime.genome.color.b })}),
        hbox({ text("size: " + std::to_string(slime.genome.size)) | border | color(Color::White)}),
        text("counter: " + std::to_string(counter))
        });
}