#include "ComplexPlane.h"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "MANDELBROT set YAY", Style::Default);
	ComplexPlane Cplane(1920,1080);
	Font font;
	Text text;
	font.loadFromFile("ARIAL.TTF");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(Color::Black);

	while (window.isOpen())
	{
		
		Event event;
		while (window.pollEvent(event))
		{
			
			if (event.type == Event::Closed)
			{
				// Quit the game when the window is closed
				window.close();
			}
			/// set shape
			/// set type of generation only after user has clicked for points vector
			
			
			if (event.type == sf::Event::MouseButtonPressed)
            		{
                		if (event.mouseButton.button == sf::Mouse::Left)
                		{
                   			Cplane.zoomIn();
                    			Cplane.setCenter(Vector2i(event.mouseButton.x, event.mouseButton.y));
                		}
		                if (event.mouseButton.button == sf::Mouse::Right)
		                {
		                	Cplane.zoomOut();
		                	Cplane.setCenter(Vector2i(event.mouseButton.x, event.mouseButton.y));
		                }
		        	}
		        	if (event.type == sf::Event::MouseMoved)
		        	{
		        		Cplane.setMouseLocation(Vector2i(event.mouseMove.x, event.mouseMove.y));
		        	}
				if (Keyboard::isKeyPressed(Keyboard::r))
				{
					Cplane.reset();
				}
			}

		
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/

		Cplane.updateRender();
		Cplane.loadText(text);
		
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		window.draw(Cplane);
		window.draw(text);
		window.display();
	}
}
