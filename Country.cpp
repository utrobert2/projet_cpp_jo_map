//
// Created by utrob on 07/01/2024.
//

#include "Country.h"

Country::Country(const std::string& name) : name(name) {
    // Initialisez d'autres données spécifiques au pays si nécessaire
}

const std::string& Country::getName() const {
    return name;
}