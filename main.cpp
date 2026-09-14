#include "genedit.hpp"
#include "slime.hpp"
#include "utils.hpp"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <ftxui/ftxui.hpp>


ftxui::Element docu_slime_gen_code();

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    auto screen = ftxui::Screen::Create(ftxui::Dimension::Full());
    ftxui::Render(screen, docu_slime_gen_code());
    screen.Print();

    return 0;
}

[[nodiscard]] ftxui::Element docu_slime_gen_code() {
    using namespace ftxui;
    using DSlime = Slime<genedit::gm::Direct>;
    DSlime slime{ };
    size_t counter{ };

    do {
        slime.dna = { .bytes = genedit::random_dna(DSlime::DNA_SIZE) };
        ++counter;
    } while (slime.map_genome());

    return vbox({
        hbox({
            text("start  " + std::format("0x{0:02X} | {0}", DSlime::ORF_MARKERS.start)) | border,
            text("stop   " + std::format("0x{0:02X} | {0}", DSlime::ORF_MARKERS.stop)) | border
        }),
        hbox({ text("DNA   (HEX) " + bytes_to_hex(slime.dna.bytes)) | border }),
        hbox({ text("DNA   (DEC) " + bytes_to_dec(slime.dna.bytes)) | border }),
        hbox({ text("r: " + std::to_string(slime.genome.color.r)) | border | color(Color::Red),
            text("g: " + std::to_string(slime.genome.color.g)) | border | color(Color::Green),
            text("b: " + std::to_string(slime.genome.color.b)) | border | color(Color::Blue),
            gauge(0.1f) | color(ftxui::Color{slime.genome.color.r, slime.genome.color.g, slime.genome.color.b })}),
        hbox({ text("size: " + std::to_string(slime.genome.size)) | border | color(Color::White)}),
        text("counter: " + std::to_string(counter))
    });
}