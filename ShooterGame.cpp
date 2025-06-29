#include <iostream>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <cstdlib>
#include <string>
#include <sstream>
#include <memory> // Include the <memory> header for smart pointers
#include<vector>

using namespace std;
using namespace sf;

int main() {
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(640, 400), "BALL SHOOTING", sf::Style::Default);
    window.setFramerateLimit(60); // Set framerate limit to 60 FPS

    sf::Font font;
    if (!font.loadFromFile("E:/Project RPG/Project XIA/arial_narrow_7.ttf")) {
        return -1; // Error handling
    }

    // Load the sound file
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("E:/Project RPG/Project XIA/shoot.wav"))
    {
        // Error handling if sound file fails to load
        return EXIT_FAILURE;
    }

    sf::SoundBuffer buffer2;
    if (!buffer2.loadFromFile("E:/Project RPG/Project XIA/table-smash-47690.wav"))
    {
        // Error handling if sound file fails to load
        return EXIT_FAILURE;
    }

    sf::SoundBuffer buffer3;
    if (!buffer3.loadFromFile("E:/Project RPG/Project XIA/8-bit-video-game-points-version-1-145826.wav"))
    {
        // Error handling if sound file fails to load
        return EXIT_FAILURE;
    }


    sf::SoundBuffer buffer4;
    if (!buffer4.loadFromFile("E:/Project RPG/Project XIA/game-start-6104.wav"))
    {
        // Error handling if sound file fails to load
        return EXIT_FAILURE;
    }


    sf::SoundBuffer buffer5;
    if (!buffer5.loadFromFile("E:/Project RPG/Project XIA/pixel-song-20-60935.wav"))
    {
        // Error handling if sound file fails to load
        return EXIT_FAILURE;
    }

   

    // Create the sound object and set its buffer
    sf::Sound sound;
    sound.setBuffer(buffer);

    sf::Sound elim;
    elim.setBuffer(buffer2);

    sf::Sound hit;
    hit.setBuffer(buffer3);

    sf::Sound gameStart;
    gameStart.setBuffer(buffer4);

    sf::Sound song;
    song.setBuffer(buffer5);
    song.setVolume(50);



    // Create a text object
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(0, 0);
    int number = 0;

    sf::Text text2;
    text2.setFont(font);
    text2.setString("DAMN!, Rectangle Invading!!!");
    text2.setCharacterSize(20); // in pixels, not points!
    text2.setFillColor(sf::Color::Yellow);
    text2.setPosition(230.f, 150.f);

    sf::Text text3;
    text3.setFont(font);
    text3.setCharacterSize(20); // in pixels, not points!
    text3.setFillColor(sf::Color::Yellow);
    text3.setPosition(window.getPosition().x - 100, 0.f);
    int health = 5;

    sf::Text text4;
    text4.setFont(font);
    text4.setString("GAME OVER! PRESS A TO RESTART");
    text4.setCharacterSize(20); // in pixels, not points!
    text4.setFillColor(sf::Color::Yellow);
    text4.setPosition(200.f, 150.f);
 

    // Initialize the projectile object with default properties.
    CircleShape projectile;
    projectile.setFillColor(Color::White); // Set the color of the projectile to white.
    projectile.setRadius(10.f); // Set the radius of the projectile to 10 units.
    vector<CircleShape> projectiles; // Create a vector to store all projectiles.
    projectiles.push_back(CircleShape(projectile)); // Add the initialized projectile to the vector.

    // Initialize the enemy object with default properties.
    RectangleShape enemy;
    enemy.setFillColor(Color::Blue); // Set the color of the enemy to blue.
    enemy.setSize(Vector2f(50.f, 50.f)); // Set the size of the enemy to 50x50 units.
    vector<RectangleShape> enemies; // Create a vector to store all enemies.
    enemies.push_back(RectangleShape(enemy)); // Add the initialized enemy to the vector.
    int spaw = 0; // Initialize a spawn counter for enemy generation.

    // Initialize the player object with default properties.
    CircleShape player;
    player.setFillColor(Color::Red); // Set the color of the player to red.
    player.setRadius(20.f); // Set the radius of the player to 20 units.
    // Set the initial position of the player to the middle of the window, near the bottom.
    player.setPosition(window.getSize().x / 2 - player.getRadius(),
        window.getSize().y - player.getRadius() * 2 - 10.f);
    Vector2f playerCenter; // Declare a variable to store the center position of the player.
    int shooting = 30; // Initialize a shooting counter to control projectile firing rate.


    //something else
    bool start = true;
    song.setLoop(true);
    song.play();

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Check for window close event
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Check for Escape key press event
            if (event.KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
        }


        if (start) {
            // Calculate the center position of the player by adding the radius to the x and y coordinates.
            playerCenter = Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());

            // Increment the shooting timer if it's less than 30.
            if (shooting < 30)
            {
                shooting++;
            }

            // Set the player's x position to the current x position of the mouse, keeping the y position unchanged.
            player.setPosition(Mouse::getPosition(window).x, player.getPosition().y);

            // Check if the left mouse button is pressed and the shooting timer has reached 30.
            if (Mouse::isButtonPressed(Mouse::Left) && shooting >= 30)
            {
                // Play the shooting sound effect.
                sound.play();

                // Set the projectile's position to the player's center position.
                projectile.setPosition(playerCenter);

                // Generate a random color for the projectile.
                Color randomColor(
                    std::rand() % 256, // Red component between 0-255
                    std::rand() % 256, // Green component between 0-255
                    std::rand() % 256  // Blue component between 0-255
                );

                // Apply the random color to the projectile's fill color.
                projectile.setFillColor(randomColor);

                // Add the new projectile to the vector of projectiles.
                projectiles.push_back(CircleShape(projectile));

                // Reset the shooting timer to allow for a new shot.
                shooting = 0;
            }

            // Iterate through all projectiles.
            for (size_t i = 0; i < projectiles.size(); i++)
            {
                // Move each projectile upwards by 5 units.
                projectiles[i].move(0.f, -5.f);

                // Check if the projectile has moved off the screen (y position less than or equal to 0).
                if (projectiles[i].getPosition().y <= 0)
                {
                    // If so, remove the projectile from the vector.
                    projectiles.erase(projectiles.begin() + i);
                }
            }


            // Enemy Spawning
            // Increment the spawn timer until it reaches 50.
            if (spaw < 50)
                spaw++;

            // Check if the spawn timer has reached 50 to spawn a new enemy.
            if (spaw >= 50)
            {
                // Set the new enemy's position to a random x coordinate within the window bounds and y to 0.
                enemy.setPosition(rand() % int(window.getSize().x - enemy.getSize().x), 0.f);

                // Generate a random color for the new enemy.
                Color randomColor(
                    std::rand() % 256, // Red component between 0-255
                    std::rand() % 256, // Green component between 0-255
                    std::rand() % 256  // Blue component between 0-255
                );

                // Apply the random color to the enemy's fill color.
                enemy.setFillColor(randomColor);

                // Add the new enemy to the vector of enemies.
                enemies.push_back(RectangleShape(enemy));

                // Reset the spawn timer to 0 after spawning an enemy.
                spaw = 0;
            }

            // Enemy Movement
            // Iterate through all enemies to update their positions.
            for (size_t i = 0; i < enemies.size(); i++)
            {
                // Move each enemy downwards by 2 units.
                enemies[i].move(0.f, 2.f);

                // Check if the enemy has moved off the screen (y position greater than window height).
                if (enemies[i].getPosition().y > window.getSize().y)
                {
                    // If so, decrement the score counter 'number' and remove the enemy from the vector.
                    number--;
                    enemies.erase(enemies.begin() + i);
                }
            }




            // Collision Detection and Handling
            // Check if there are any enemies and projectiles in the game.
            if (!enemies.empty() && !projectiles.empty()) {
                // Iterate through all projectiles.
                for (size_t i = 0; i < projectiles.size(); i++) {
                    // Check each enemy for collision with the current projectile.
                    for (size_t j = 0; j < enemies.size(); j++) {
                        // If the projectile intersects with an enemy's global bounds.
                        if (projectiles[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds())) {
                            // Play the elimination sound effect.
                            elim.play();
                            // Increment the score counter 'number'.
                            number++;
                            // Erase the projectile that hit the enemy from the vector.
                            projectiles.erase(projectiles.begin() + i);
                            // Erase the enemy that was hit by the projectile from the vector.
                            enemies.erase(enemies.begin() + j);
                            // Break out of the loop to avoid checking other enemies with the erased projectile.
                            break;
                        }
                    }
                }
            }

            // Iterate through all enemies to check for collision with the player.
            for (size_t j = 0; j < enemies.size(); ) {
                // If the player intersects with an enemy's global bounds.
                if (player.getGlobalBounds().intersects(enemies[j].getGlobalBounds())) {
                    // Play the hit sound effect.
                    hit.play();
                    // Decrement the score counter 'number'.
                    number--;
                    // Decrement the player's health.
                    health--;
                    // Erase the enemy that collided with the player from the vector.
                    enemies.erase(enemies.begin() + j);
                }
                else {
                    // Only increment the loop counter if no enemy was erased.
                    // This ensures the next enemy is checked after an erasure.
                    ++j;
                }
            }


            // Update the points display after collision checks have been performed.
            stringstream ss;
            ss << number; // Convert the 'number' variable to a string using stringstream.
            text.setString("Points: " + ss.str()); // Set the text object to display the points with a label.

            // Update the health display.
            stringstream ss2;
            ss2 << health; // Convert the 'health' variable to a string using stringstream.
            text3.setString("HEALTH: " + ss2.str()); // Set the text object to display the health with a label.

            // Check if the player's health reaches zero and end the game if it does.
            if (health == 0)
                start = false; // Set the 'start' flag to false, stopping the game loop.

            // Rendering Section
            // Clear the entire window with a black color before drawing the new frame.
            window.clear(sf::Color::Black);

            // Draw the player sprite.
            window.draw(player);

            // Draw all enemy sprites currently in the 'enemies' vector.
            for (size_t i = 0; i < enemies.size(); i++)
            {
                window.draw(enemies[i]);
            }

            // Draw all projectile sprites currently in the 'projectiles' vector.
            for (size_t i = 0; i < projectiles.size(); i++)
            {
                window.draw(projectiles[i]);
            }

            // Draw additional text objects, such as instructions or other UI elements.
            window.draw(text2); // Assuming 'text2' is another text object used in the game.

            // Draw the health text updated earlier.
            window.draw(text3);

            // Draw the points text updated earlier.
            window.draw(text);

            // Display the contents of the window after all drawing commands.
            window.display();

        }
        else
        {
             window.clear(sf::Color::Black);
             window.draw(text4);
             window.display();
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                gameStart.play();
                number = 0;
                health = 5;
                start = true;
                enemies.clear(); // Clear all enemies from the vector
            }
        }
    }
    return 0;
}