#include "genedit.hpp"

#include <ftxui/ftxui.hpp>

int main()
{
    DNA dna_1{ random_dna() };
    DNA dna_2{ random_dna() };
    DNA dna_3{ random_dna() };
    
    using namespace ftxui;
    auto document =
        vbox({
            hbox({ text("DNA    " + dna_to_hex(dna_1)) | border }),
            hbox({ text("DNA    " + dna_to_hex(dna_2)) | border }),
            hbox({ text("DNA    " + dna_to_hex(dna_3)) | border })
        });

    auto screen = Screen::Create(Dimension::Full());
    Render(screen, document);
    screen.Print();

    return 0;
}