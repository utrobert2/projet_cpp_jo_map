#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "Country.h"

class Continent {
public:
    Continent(sf::RenderWindow &window) : window(window) {
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

    void setList() {
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
                text.setPosition(40, 40 + i * 30);

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

        if (!logoBleuTexture.loadFromFile("textures/logoBleu.png")) {
            std::cerr << "Erreur de chargement de l'image du logo des JO." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        if (!logoNoirTexture.loadFromFile("textures/logoNoir.png")) {
            std::cerr << "Erreur de chargement de l'image du logo des JO." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        if (!logoRougeTexture.loadFromFile("textures/logoRouge.png")) {
            std::cerr << "Erreur de chargement de l'image du logo des JO." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        if (!logoJauneTexture.loadFromFile("textures/logoJaune.png")) {
            std::cerr << "Erreur de chargement de l'image du logo des JO." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        if (!logoVertTexture.loadFromFile("textures/logoVert.png")) {
            std::cerr << "Erreur de chargement de l'image du logo des JO." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        mapSprite.setTexture(mapTexture);
        logoBleuSprite.setTexture(logoBleuTexture);
        logoNoirSprite.setTexture(logoNoirTexture);
        logoRougeSprite.setTexture(logoRougeTexture);
        logoJauneSprite.setTexture(logoJauneTexture);
        logoVertSprite.setTexture(logoVertTexture);
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
    sf::Texture logoBleuTexture;
    sf::Texture logoNoirTexture;
    sf::Texture logoRougeTexture;
    sf::Texture logoJauneTexture;
    sf::Texture logoVertTexture;


    sf::Sprite mapSprite;
    sf::Sprite logoBleuSprite;
    sf::Sprite logoNoirSprite;
    sf::Sprite logoRougeSprite;
    sf::Sprite logoJauneSprite;
    sf::Sprite logoVertSprite;

    // Définition des rectangles de sélection des continents
    sf::FloatRect rectangleEurope{1028, 174, 1446 - 1028, 377 - 174};
    sf::FloatRect rectangleAfrique{1110, 424, 1538 - 1110, 1538 - 424};
    sf::FloatRect rectangleAmerique{352, 181, 969 - 352, 1052 - 181};
    sf::FloatRect rectangleAsie{1523, 302, 2258 - 1523, 724 - 302};
    sf::FloatRect rectangleOceanie{2021, 728, 2548 - 2021, 1034 - 728};

    sf::Font font;


    Continent countryList;

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Gestion des événements de souris
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Obtention des coordonnées du clic de souris
                    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    // Vous pouvez maintenant utiliser les coordonnées de la souris pour interagir avec la carte
                    // Par exemple, afficher les coordonnées dans la console
                    std::cout << "Clic de souris à la position : " << (int)mousePosition.x << ", " << (int)mousePosition.y << std::endl;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    if (rectangleEurope.contains(mousePosition)) {
                        // Afficher la liste des pays
                        countryList.setList();
                    } else if (rectangleAfrique.contains(mousePosition)) {
                        countryList.setList();
                    }
                    else if (rectangleAmerique.contains(mousePosition)) {
                        countryList.setList();
                    }
                    else if (rectangleAsie.contains(mousePosition)) {
                        countryList.setList();
                    }
                    else if (rectangleOceanie.contains(mousePosition)) {
                        countryList.setList();
                    }
                    else {
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

        if (!font.loadFromFile("fonts/leaguespartan-bold.ttf")) {
            std::cout << "Erreur lors du chargement de la police" << std::endl;
        }


        // Affichage du rectangle opaque avec le logo des JO si le curseur est dans la zone
        if (rectangleEurope.contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            logoBleuSprite.setPosition(rectangleEurope.left, rectangleEurope.top);
            logoBleuSprite.setColor(sf::Color(255, 255, 255, 128)); // Blanc avec une opacité de 128
            window.draw(logoBleuSprite);
            sf::Text textEurope;
            textEurope.setFont(font);
            textEurope.setString("Europe");
            textEurope.setCharacterSize(24);
            textEurope.setFillColor(sf::Color::White);
            textEurope.setPosition(rectangleEurope.left + 10, rectangleEurope.top + 10);
            window.draw(textEurope);
            window.draw(logoVertSprite);
        }
        if (rectangleAfrique.contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            logoNoirSprite.setPosition(rectangleAfrique.left, rectangleAfrique.top);
            logoNoirSprite.setColor(sf::Color(255, 255, 255, 128)); // Blanc avec une opacité de 128
            window.draw(logoNoirSprite);
        }
        if (rectangleAmerique.contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            logoRougeSprite.setPosition(rectangleAmerique.left, rectangleAmerique.top);
            logoRougeSprite.setColor(sf::Color(255, 255, 255, 128)); // Blanc avec une opacité de 128
            window.draw(logoRougeSprite);
        }
        if (rectangleAsie.contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            logoJauneSprite.setPosition(rectangleAsie.left, rectangleAsie.top);
            logoJauneSprite.setColor(sf::Color(255, 255, 255, 128)); // Blanc avec une opacité de 128
            window.draw(logoJauneSprite);
        }
        if (rectangleOceanie.contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            logoVertSprite.setPosition(rectangleOceanie.left, rectangleOceanie.top);
            logoVertSprite.setColor(sf::Color(255, 255, 255, 128)); // Blanc avec une opacité de 128


        }

        // Affichage de la liste des pays
        countryList.drawInteractiveList();

        // Affichage des changements
        window.display();
    }
};

int main() {
    //Continent Europe();
    InteractiveMap interactiveMap;
    interactiveMap.run();

    return 0;
}
