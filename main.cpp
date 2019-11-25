#include <iostream>
#include <picture/Picture.hpp>

int main() {
    Picture pic1{
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

    std::cout << frame(hcat(frame(pic1), vcat(frame(pic3), pic2)));

    return 0;
}