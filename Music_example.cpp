//this is my testing file many headers my be a part of old test
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h> 
//
//http://www.sfml-dev.org/
//http://www.sfml-dev.org/download/sfml/2.3.2/
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
int main()
{
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("image.jpg"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("toby_fox_-_UNDERTALE_Soundtrack_-_87_Hopes_and_Dre.wav"))
        return EXIT_FAILURE;
    // Play the music
    music.play();
    music.setLoop(true);
    //music.setPitch(0.8);
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(sprite);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
    
}
