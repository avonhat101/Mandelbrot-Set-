#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size.x = pixelWidth;
	m_pixel_size.y = pixelHeight;
	m_aspectRatio = (float)pixelHeight / (float)pixelWidth;
	m_plane_center{ 0,0 };
	m_plane_size{ BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::CALCULATING;
	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(pixelWidth * pixelHeight);
}
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}
void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size{ x,y };
	m_state = State::CALCULATING;
}
void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size{ x,y };
	m_state = State::CALCULATING;
}
void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_mouseLocation = ComplexPlane::mapPixelToCoords(mousePixel);
}
void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_plane_center = ComplexPlane::mapPixelToCoords(mousePixel);
	m_state = State::CALCULATING;
}
void ComplexPlane::loadText(Text& text)
{
	stringstream ss;
	ss << "Mandelbrot Set" << endl;
	ss << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")" << endl;
	ss << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")" << endl;
	ss << "Left-click to Zoom in" << endl << "Right-click to Zoom out"
	text.setString(ss.str());

}
void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING)
	{
		for (int i = 0; i < m_pixel_size.y; i++)
		{
			for (int j = 0; j < m_pixel_size.x; j++)
			{
				m_vArray[j + i * pixelWidth].position = { (float)j,(float)i };
				Vector2i location = { j,i };
				Vector2f Coord1 = ComplexPlane::mapPixelToCoords(location);
				int inter = ComplexPlane::countIterations(Coord1);
				Uint8 r;
				Uint8 g;
				Uint8 b;
				ComplexPlane::iterationsToRGB(iter, r, g, b);
				vArray[j + i * pixelWidth].color = { r,g,b };
			}
		}
		m_state = State::DISPLAYING;
	}
}
int ComplexPlane::countIterations(Vector2f coord)
{
	complex<double> z = coord;
	int i = 0;
	while (abs(z) < 2.0 && i < 64)
	{
		z = z * z + coord;
		//cout << "z_" << i << "= " << z << endl;
		//cout << "|z| = " << abs(c) << endl;
		i++;
	}
	return i;
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count == MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else if (count > 50)
	{
		r = 0;
		g = 0;
		b = 255;
	}
	else if (count > 35)
	{
		r = 0;
		g = 255;
		b = 0;
	}
	else if (count > 20)
	{
		r = 255;
		g = 0;
		b = 0;
	}
	else if (count >= 0)
	{
		r = 255;
		g = 255;
		b = 255;
	}
}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	Vector2f result;
	result.x = ((((float)mousePixel.x) / (m_pixel_size.x)) * m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0));
	result.x = ((((float)mousePixel.y) / (m_pixel_size.y)) * m_plane_size.y + (m_plane_center.y - m_plane_size.y / 2.0));
	return result;
}
