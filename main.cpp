#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

struct Country {
    std::string name;
    // Ajoutez ici d'autres informations spécifiques au pays
};

class CountryList {
public:
    CountryList(sf::RenderWindow& window) : window(window) {
        // Remplissez ici la liste des pays (ce peut être une liste préétablie ou dynamique)
        countries = {{"Allemagne"}, {"Armenie"}, {"Autriche"}, {"Azerbaijan"}, {"Belgique"}, {"Bosnie-Herzégovine"}, {"Bulgarie"}, {"Croatie"}, {"Danemark"}, {"Espagne"}, {"Estonie"}, {"Finlande"}, {"France"}, {"Géorgie"}, {"Grande-Bretagne"}, {"Grèce"}, {"Hongrie"}, {"Irlande"}, {"Italie"}, {"Lituanie"}, {"Moldavie"}, {"Norvège"}, {"Pays-Bas"}, {"Pologne"}, {"Portugal"}, {"Roumanie"}, {"Serbie"}, {"Slovaquie"}, {"Slovénie"}, {"Suède"}, {"Suisse"}, {"Tchéquie"}, {"Turquie"}, {"Ukraine"}};
        font.loadFromFile("fonts/leaguespartan-bold.ttf"); // Assurez-vous de charger une police de caractères valide
    }

    void setListPosition(const sf::Vector2f& position) {
        listPosition = position;
        showList = true;
    }

    void hideList() {
        showList = false;
    }

    void drawInteractiveList() {
        if (showList) {
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::Black);
            for (size_t i = 0; i < countries.size(); ++i) {
                text.setString(countries[i].name);
                text.setPosition(listPosition.x, listPosition.y + static_cast<float>(i) * 30.0f);

                // Afficher le pays de manière interactive
                if (isMouseOverCountry(text)) {
                    text.setFillColor(sf::Color::Blue); // Changez la couleur pour indiquer l'interaction
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        // Vous pouvez ajouter ici le code pour afficher des informations sur le pays
                        std::cout << "Informations sur le pays : " << countries[i].name << std::endl;
                    }
                }

                window.draw(text);
            }
        }
    }

private:
    sf::RenderWindow& window;
    std::vector<Country> countries;
    sf::Font font;
    sf::Vector2f listPosition;
    bool showList = false;

    bool isMouseOverCountry(const sf::Text& text) {
        sf::FloatRect bounds = text.getGlobalBounds();
        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
        return bounds.contains(mousePosition);
    }
};

class InteractiveMap {
public:
    // ... (le reste de votre code reste inchangé)

private:
    // ... (le reste de votre code reste inchangé)

    void render() {
        // Effacement de la fenêtre
        window.clear();

        // Affichage de la carte
        window.draw(mapSprite);

        // Affichage du rectangle opaque avec le logo des JO si le curseur est dans la zone
        if (rectangleBounds.contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            logoSprite.setPosition(rectangleBounds.left, rectangleBounds.top);
            logoSprite.setColor(sf::Color(255, 255, 255, 128)); // Blanc avec une opacité de 128
            window.draw(logoSprite);
        }

        // Affichage de la liste des pays de manière interactive
        countryList.drawInteractiveList();

        // Affichage des changements
        window.display();
    }
};

int main() {
    InteractiveMap interactiveMap;
    interactiveMap.run();

    return 0;
}
