#include <algorithm>

#include "iostream"
#include <vector>
#include <iomanip>

template<typename T>
void PrintVector(std::vector<T> const& vec) {
    for (auto const& x : vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

auto compareFunction (std::string a, std::string b) {return a<b;}

int main() {
    // gebruik functies uit <algorithm> en <functional> om de volgende opdrachten uit te voeren:

    // splits de vector in 2 nieuwe vectoren: 1 met alles wat alfabetisch voor 'purple' komt, 1 met alles er na
    {
        std::vector<std::string> colours{"red", "green", "white", "blue", "orange", "green", "orange", "black", "purple"};
        std::sort(colours.begin(), colours.end(), compareFunction);
        auto split = std::find(colours.begin(), colours.end(), "purple");
        int splitIndex;
        if (split != colours.end()) {
            splitIndex = std::distance(colours.begin(), split);
        }
        std::vector<std::string> colours1{colours.begin(), colours.begin() + splitIndex};
        std::vector<std::string> colours2{colours.begin() + splitIndex, colours.end()};
        //PrintVector(colours1);
        //PrintVector(colours2);
    }

    // maak alle elementen UPPERCASE
    {
        std::vector<std::string> colours{"red", "green", "white", "blue", "orange", "green", "orange", "black", "purple"};
        for (auto& colour : colours) {
            std::transform(colour.begin(), colour.end(), colour.begin(),
                           [](unsigned char c){ return std::toupper(c); });
        }
        PrintVector(colours);
    }

    // verwijder alle dubbele elementen
    {
        std::vector<std::string> colours{"red", "green", "white", "blue", "orange", "green", "orange", "black", "purple"};
    }

    // verwijder alle negatieve elementen
    {
        std::vector<double> numbers{10, 324422, 6, -23, 234.5, 654.1, 3.1242, -9.23, 635};
    }

    // bepaal voor alle elementen of ze even of oneven zijn
    {
        std::vector numbers{10, 324422, 6, -23, 234, 654, 3, -9, 635};
    }

    // bepaal de som, het gemiddelde, en het product van alle getallen te berekenen
    {
        std::vector<double> numbers{10, 324422.1, 6, -23, 234.5, 654.1, 3.1242, -9.23, 635};
    }

    return 0;
}
