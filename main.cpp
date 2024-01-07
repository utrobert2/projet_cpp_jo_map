#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "Country.h"

class CountryList {
public:
    CountryList(sf::RenderWindow &window) : window(window) {
        countries = {{"Allemagne"},
                     {"Armenie"},
                     {"Autriche"},
                     {"Azerbaijan"},
                     {"Belgique"},
                     {"Bosnie-Herzégovine"},
                     {"Bulgarie"},
                     {"Croatie"},
                     {"Danemark"},
                     {"Espagne"},
                     {"Estonie"},
                     {"Finlande"},
                     {"France"},
                     {"Géorgie"},
                     {"Grande-Bretagne"},
                     {"Grèce"},
                     {"Hongrie"},
                     {"Irlande"},
                     {"Italie"},
                     {"Lituanie"},
                     {"Moldavie"},
                     {"Norvège"},
                     {"Pays-Bas"},
                     {"Pologne"},
                     {"Portugal"},
                     {"Roumanie"},
                     {"Serbie"},
                     {"Slovaquie"},
                     {"Slovénie"},
                     {"Suède"},
                     {"Suisse"},
                     {"Tchéquie"},
                     {"Turquie"},
                     {"Ukraine"}};
        font.loadFromFile("fonts/leaguespartan-bold.ttf"); // Assurez-vous de charger une police de caractères valide
    }

    void setListPosition(const sf::Vector2f &position) {
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
                text.setString(countries[i].getName());
                text.setPosition(listPosition.x, listPosition.y + static_cast<float>(i) * 30.0f);

                // Afficher le pays de manière interactive
                if (isMouseOverCountry(text)) {
                    text.setFillColor(sf::Color::Blue); // Changez la couleur pour indiquer l'interaction
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        // Vous pouvez ajouter ici le code pour afficher des informations sur le pays
                        std::cout << "Informations sur le pays : " << countries[i].getName() << std::endl;
                    }
                }

                window.draw(text);
            }
        }
    }

private:
    sf::RenderWindow &window;
    std::vector<Country> countries;
    sf::Font font;
    sf::Vector2f listPosition;
    bool showList = false;

    bool isMouseOverCountry(const sf::Text &text) {
        sf::FloatRect bounds = text.getGlobalBounds();
        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
        return bounds.contains(mousePosition);
    }
};

class InteractiveMap {
public:
    InteractiveMap() : window(sf::VideoMode(2560, 1109), "Carte Interactive SFML"), countryList(window) {
        if (!mapTexture.loadFromFile("textures/map.png")) {
            std::cerr << "Erreur de chargement de l'image de la carte." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        if (!logoTexture.loadFromFile("textures/logoBleu.png")) {
            std::cerr << "Erreur de chargement de l'image du logo des JO." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        mapSprite.setTexture(mapTexture);
        logoSprite.setTexture(logoTexture);
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

private:
    sf::RenderWindow window;
    sf::Texture mapTexture;
    sf::Texture logoTexture;
    sf::Sprite mapSprite;
    sf::Sprite logoSprite;
    float mapScale = 1.0f;
    sf::FloatRect rectangleBounds{1028, 174, 1446 - 1028, 377 - 174};
    CountryList countryList;

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    if (rectangleBounds.contains(mousePosition)) {
                        // Afficher la liste des pays
                        countryList.setListPosition(mousePosition);
                    } else {
                        // Cacher la liste si le clic est en dehors de la zone du rectangle
                        countryList.hideList();
                    }
                }
            }
        }
    }

    void update() {
        // Mise à jour des éléments si nécessaire
    }

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

        // Affichage de la liste des pays
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
