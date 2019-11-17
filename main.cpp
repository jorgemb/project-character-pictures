#include <iostream>
#include <picture/picture.hpp>

int main() {
    Picture pic{
            "This is a picture",
            "with multiple lines.",
    };

    Picture pic2{
            "It should work just fine.",
    };

    Picture pic3{
            "This should be expected",
            "on the right of the other image.",
    };

    std::cout << hcat(frame(pic), frame(vcat(pic3, pic2)));

    return 0;
}