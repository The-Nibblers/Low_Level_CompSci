#include <algorithm>
#include <numeric>

#include "iostream"
#include <vector>
#include <iomanip>

template<typename T>
void printVector(std::vector<T> const& vec) {
    for (auto const& x : vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

int main() {
    // gebruik functies uit <algorithm> en <functional> om de volgende opdrachten uit te voeren:

    // splits de vector in 2 nieuwe vectoren: 1 met alles wat alfabetisch voor 'purple' komt, 1 met alles er na
    {
        std::vector<std::string> colours{"red", "green", "white", "blue", "orange", "green", "orange", "black", "purple"};
        std::sort(colours.begin(), colours.end());
        auto split = std::find(colours.begin(), colours.end(), "purple");
        int splitIndex;
        if (split != colours.end()) {
            splitIndex = std::distance(colours.begin(), split);
        }
        std::vector<std::string> colours1{colours.begin(), colours.begin() + splitIndex};
        std::vector<std::string> colours2{colours.begin() + splitIndex, colours.end()};
        //printVector(colours1);
        //printVector(colours2);
    }

    // maak alle elementen UPPERCASE
    {
        std::vector<std::string> colours{"red", "green", "white", "blue", "orange", "green", "orange", "black", "purple"};
        for (auto& colour : colours) {
            std::transform(colour.begin(), colour.end(), colour.begin(),
                           [](unsigned char c){ return std::toupper(c); });
        }
        //printVector(colours);
    }

    // verwijder alle dubbele elementen
    {
        std::vector<std::string> colours{"red", "green", "white", "blue", "orange", "green", "orange", "black", "purple"};
        std::sort(colours.begin(), colours.end());
        auto uniques = std::unique(colours.begin(), colours.end());
        colours.erase(uniques, colours.end());
        //printVector(colours);
    }

    // verwijder alle negatieve elementen
    {
        std::vector<double> numbers{10, 324422, 6, -23, 234.5, 654.1, 3.1242, -9.23, 635};

        numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
                             [](double number) { return number < 0; }),
              numbers.end());

        //printVector(numbers);
    }

    // bepaal voor alle elementen of ze even of oneven zijn
    {
        std::vector numbers{10, 324422, 6, -23, 234, 654, 3, -9, 635};
        std::vector<std::string> evenOdds;
        std::transform(numbers.begin(), numbers.end(),std::back_inserter(evenOdds), [](int number) {if (number % 2) return "odd"; else return "even"; });

        //printVector(numbers);
        //printVector(evenOdds);
    }

    // bepaal de som, het gemiddelde, en het product van alle getallen te berekenen
    {
        std::vector<double> numbers{10, 324422.1, 6, -23, 234.5, 654.1, 3.1242, -9.23, 635};
        double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0, std::plus());
        double avarage = sum / numbers.size();
        double product = std::accumulate(numbers.begin(), numbers.end(), 1.0, std::multiplies<>());
        std::cout << "Sum = " << sum << std::endl;
        std::cout << "Avarage = " << avarage << std::endl;
        std::cout << "Product = " << product << std::endl;
    }

    return 0;
}