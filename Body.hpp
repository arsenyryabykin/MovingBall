#include "Resources.hpp"


class Body : public sf::Drawable
{
public:

	bool isMove;
	double velocity;
	sf::Vector2f v0;
	sf::Vector2f v;
	sf::Vector2f acl;	// Ускорение

private:
	sf::CircleShape shape;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(shape);
	}

public:
	Body(float vx, float vy) : shape(SIZE), v0(vx, vy), acl(0, 9.81)
	{
		std::cout << "Creation" << std::endl;
		shape.setOrigin(SIZE, SIZE);
		shape.setFillColor(sf::Color(230, 255, 0));
		shape.setPosition(SCREEN_W/2, SCREEN_H/2);
		isMove = false;
		velocity = 0;
		v.x = v0.x;
		v.y = v0.y;
		
	}

	void setFillColor(sf::Color color)
	{
		shape.setFillColor(color);
	}

	void move(float offsetX, float offsetY)
	{
		shape.move(offsetX, offsetY);
	}

	sf::FloatRect getGlobalBounds()
	{
		return shape.getGlobalBounds();
	}

	sf::FloatRect getLocalBounds()
	{
		return shape.getLocalBounds();
	}

	sf::Vector2f getPosition()
	{
		return shape.getPosition();
	}
};