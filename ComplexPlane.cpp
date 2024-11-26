#include "ComplexPlane.h"

ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size.x = pixelWidth;
	m_pixel_size.y = pixelHeight;
	m_aspectRatio = (float)pixelHeight / (float)pixelWidth;
	m_plane_center{ 0,0 };
	m_plane_size{ BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_State = State::CALCULATING;
	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(pixelWidth * pixelHeight);
}
void draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}
void zoomIn()
{
	m_zoomCount++;
	float x = BASE_WIDTH * (pow(BASE_ZOOM, m_ZoomCount);
	float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_ZoomCount);
	m_plane_size{ x,y };
	m_State State::CALCULATING;
}
void zoomOut()
{
	m_zoomCount--;
	float x = BASE_WIDTH * (pow(BASE_ZOOM, m_ZoomCount);
	float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_ZoomCount);
	m_plane_size{ x,y };
	m_State State::CALCULATING;
}
void setCenter(Vector2i mousePixel)
{

}
void setMouseLocation(Vector2i mousePixel)
{

}
void loadText(Text& text)
{

}
void updateRender()
{
	if (m_State == CALCULATING)
	{
		for(int i = 0; i < )
	}
}
