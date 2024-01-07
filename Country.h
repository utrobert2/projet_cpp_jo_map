//
// Created by utrob on 07/01/2024.
//

#ifndef PROJET_MAP_JO_COUNTRY_H
#define PROJET_MAP_JO_COUNTRY_H

#include <string>

class Country {
public:
    Country(const std::string& name);

    const std::string& getName() const;

private:
    std::string name;
    // Ajoutez d'autres données spécifiques au pays ici
};

#endif //PROJET_MAP_JO_COUNTRY_H
