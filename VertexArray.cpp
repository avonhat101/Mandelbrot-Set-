// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <iostream>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

class RainbowScreen : public Drawable
{
public:
	RainbowScreen(int pixelWidth, int pixelHeight);
	void draw(RenderTarget& target, RenderStates states) const override;
	void update();
private:
	VertexArray m_va;
	Vector2i m_pixel_size;
};

void RainbowScreen::update()
{
	int pixelHeight = m_pixel_size.y;
	int pixelWidth = m_pixel_size.x;

	for (int i = 0; i < pixelHeight; i++)
	{
		//random color for each row
		Uint8 r, g, b;
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;
		for (int j = 0; j < pixelWidth; j++)
		{
			m_va[i * pixelWidth + j].position = { (float)j, (float)i };
			m_va[i * pixelWidth + j].color = { r,g,b };
		}
	}
}

RainbowScreen::RainbowScreen(int pixelWidth, int pixelHeight)
{
	m_pixel_size = { pixelWidth, pixelHeight };
	m_va.setPrimitiveType(Points);
	m_va.resize(pixelWidth * pixelHeight);
}

void RainbowScreen::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_va);
}

int main()
{
	// Create a video mode object
	int pixelWidth = VideoMode::getDesktopMode().width;
	int pixelHeight = VideoMode::getDesktopMode().height;
	VideoMode vm(pixelWidth, pixelHeight);
	// Create and open a window for the game
	RenderWindow window(vm, "Rainbow Screen", Style::Default);
	
	//resize window for different resolutions
	/*View view;
	view.setSize(pixelWidth, pixelHeight);
	view.setCenter(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 2);
	window.setView(view);*/
	
	RainbowScreen rain(pixelWidth, pixelHeight);

	bool update = true;

	while (window.isOpen())
	{

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					update = true;
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (update)
		{
			rain.update();
			update = false;
		}

		/*
		****************************************
		Draw the scene
		****************************************
		*/

		window.clear();
		window.draw(rain);
		window.display();
	}
}
