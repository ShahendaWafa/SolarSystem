#include <SFML/Graphics.hpp>
#include <vector>

float const G = 6.68;
float const sun_mass = 1.989 * 10e30;

void render(sf::RenderWindow* window, sf::CircleShape* planet) {
    window->draw(*planet);
}

class Planet {
public:
    float dist;
    float mass;
    float diameter;
    float div;
    sf::Vector2f velocity;
    sf::Color col;
    sf::Vector2f position;


    float distance(sf::Vector2f p1, sf::Vector2f p2) {
        float x = p2.x - p1.x;
        float y = p2.y - p1.y;
        return sqrt(x * x + y * y);
    }
    void accelerate(Planet* sun, float dt) {
        float acceleration = (G * sun_mass) / (dist * dist);
        acceleration /= div;
        sf::Vector2f os((*sun).position - position);
        float d = distance((*sun).position, position);
        os = (os / d) * acceleration;
        velocity += (os * dt);
        position += (velocity * dt);
    }
    void draw(sf::RenderWindow* window) {
        sf::CircleShape planet(diameter);
        planet.setFillColor(col);
        planet.setPosition(position);
        planet.setOrigin(diameter, diameter);
        render(window, &planet);
    }
};

void makePlanets(std::vector<Planet>* planets) {
    Planet mercury{ 57.91 * 10e6, 1.0f, 4, 10e11, sf::Vector2f(190, 190), sf::Color::Yellow };
    Planet venus{ 108.2 * 10e6, 1.0f, 7, 10e10, sf::Vector2f(190, 190), sf::Color::Magenta };
    Planet earth{ 147.63 * 10e6, 1.0f, 10, 10e10, sf::Vector2f(200, 200), sf::Color::Blue };
    Planet mars{ 227.9 * 10e6, 1.0f, 13, 10e10, sf::Vector2f(210, 210), sf::Color::Red };
    Planet jupiter{ 778.5 * 10e6, 1.0f, 15, 10e9, sf::Vector2f(220, 220), sf::Color::Cyan };
    Planet saturn{ 1443 * 10e6, 1.0f, 17, 10e8, sf::Vector2f(180, 180), sf::Color::Green };
    Planet uranus{ 2871 * 10e6, 1.0f, 19, 10e8, sf::Vector2f(190, 190), sf::Color::Blue };
    Planet neptune{ 4495 * 10e6, 1.0f, 20, 10e7, sf::Vector2f(200, 200), sf::Color::Red };

    (*planets).push_back(mercury);
    (*planets).push_back(venus);
    (*planets).push_back(earth);
    (*planets).push_back(mars);
    (*planets).push_back(jupiter);
    (*planets).push_back(saturn);
    (*planets).push_back(uranus);
    (*planets).push_back(neptune);
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!");

    Planet sun{ 0, 0, 50, 0, sf::Vector2f(0, 0), sf::Color::Yellow, sf::Vector2f(500, 400) };

    sf::Vector2f mousePos;
    sf::Clock clock;

    std::vector<Planet> planets;
    std::vector<Planet> planetsSoFar;
    makePlanets(&planets);

    float time = 0, dt = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
                int rand = clock.getElapsedTime().asMilliseconds() % planets.size();
                planets[rand].position = mousePos;
                planetsSoFar.push_back(planets[rand]);
            }
        }

        dt = clock.getElapsedTime().asSeconds() - time;
        time += dt;

        sun.draw(&window);
        for (int i = 0; i < planetsSoFar.size(); i++) {
            planetsSoFar[i].accelerate(&sun, dt);
            planetsSoFar[i].draw(&window);
        }
        window.display();
        window.clear();
    }

    return 0;
}