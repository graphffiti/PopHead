#include "rect.hpp"

template<typename T>
ph::Rect<T>::Rect(const sf::Rect<T>& rect)
	: sf::Rect<T>(rect)
{
}

template<typename T>
ph::Rect<T>& ph::Rect<T>::operator=(const sf::Rect<T>& rect)
{
	sf::Rect<T>::operator=(rect);
	return *this;
}

template<typename T>
T ph::Rect<T>::right() const
{
	return left + width;
}

template<typename T>
inline T ph::Rect<T>::bottom() const
{
	return top + height;
}

template<typename T>
inline sf::Vector2<T> ph::Rect<T>::getCenter() const
{
	return { left + width / 2, top + height / 2};
}

template<typename T>
inline sf::Vector2<T> ph::Rect<T>::getTopLeft() const
{
	return { left, top };
}

template<typename T>
inline sf::Vector2<T> ph::Rect<T>::getTopRight() const
{
	return { right(), top };
}

template<typename T>
inline sf::Vector2<T> ph::Rect<T>::getBottomLeft() const
{
	return { left, bottom() };
}

template<typename T>
inline sf::Vector2<T> ph::Rect<T>::getBottomRight() const
{
	return { right(), bottom() };
}

template<typename T>
inline bool ph::Rect<T>::containsIncludingBounds(const sf::Vector2<T>& point) const
{
	auto r = right();
	auto b = bottom();

	T minX = std::min(left, r);
	T maxX = std::max(left, r);
	T minY = std::min(top, b);
	T maxY = std::max(top, b);

	return (point.x >= minX) && (point.x <= maxX) && (point.y >= minY) && (point.y <= maxY);
}

template<typename T>
bool ph::Rect<T>::doPositiveRectsIntersect(const sf::Rect<T>& rect) const
{
	// this function only works properly for rects with positive width and height
	return left < rect.left + rect.width
		&& right() > rect.left
		&& top < rect.top + rect.height
		&& bottom() > rect.top;
}

template<typename T>
bool ph::Rect<T>::doPositiveRectsIntersect(const sf::Rect<T>& a, const sf::Rect<T>& b)
{
	// this function only works properly for rects with positive width and height
	return a.left < b.left + b.width
		&& a.left + a.width > b.left
		&& a.top < b.top + b.height
		&& a.top + a.height > b.top;
}