#include "kula.hpp"

///***************************///
///********* BALL ***********///
///***************************///

using namespace sf;

Ball::Ball (float x, float y, Texture* texture)
{
    shape.setPosition(x, y);
    //shape.setFillColor(sf::Color::White);
    shape.setTexture(texture);
    shape.setRadius(this->radious);
    shape.setOrigin(this->radious, this->radious);
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(this->shape, state);
}
sf::Vector2f Ball::position()
{
    return shape.getPosition();
}
float Ball::left()
{
    return this->shape.getPosition().x - this->radious;
}
float Ball::right()
{
    return this->shape.getPosition().x + this->radious;
}
float Ball::up()
{
    return this->shape.getPosition().y - this->radious;
}
float Ball::bottom()
{
    return this->shape.getPosition().y + this->radious;
}


void Ball::movement(float dx, float dy)
{
    shape.move(this->speedVector);
    if (this->left() < 0) this->moveRight();
    else if (this->right() > dx) this->moveLeft();
    else if (this->up() < 0) this->moveDown();
    else if (this->bottom() > dy) this->moveUp();
}
void Ball::moveLeft()
{
    //this->speedVector.x = -this->speed;
    if (speedVector.x > 0) speedVector.x *= -1;
}
void Ball::moveRight()
{
    //this->speedVector.x = this->speed;
    if (speedVector.x < 0) speedVector.x *= -1;
}
void Ball::moveUp()
{
    //this->speedVector.y = -this->speed;
    if (speedVector.y > 0) speedVector.y *= -1;
}
void Ball::moveDown()
{
    //this->speedVector.y = this->speed;
    if (speedVector.y < 0) speedVector.y *= -1;
}
void Ball::moveBevel(float f, Paddle pal)
{
    //this->speedVector.x = (speed/(pal.width()/2)) * f;

    this->speedVector.x = speed/pal.width() * 2 * f;
    this->speedVector.y = sqrt(fabs((speed*speed)-(this->speedVector.x*this->speedVector.x)));
}
bool Ball::way()
{
    if (this->speedVector.x > 0) return true;
        else return false;
}

///*****************************///
///********* PADDLE ***********///
///*****************************///

Paddle::Paddle (float x, float y, Texture* texture)
{
    shape.setPosition(x, y);
    shape.setSize({this->dlx, this->dly});
    //shape.setFillColor(sf::Color::Blue);
    shape.setTexture(texture);
    shape.setOrigin(this->dlx/2, this->dly/2);
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(this->shape, state);
}

void Paddle::movement(float dx)
{
    shape.move(this->speedVector);

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) && this->left() > 0)
        this->speedVector.x = -this->speed;
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && this->right() < dx)
        this->speedVector.x = this->speed;
    else
        speedVector.x = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        this->speedVector.x *= 3;
}
sf::Vector2f Paddle::position()
{
    return shape.getPosition();
}
float Paddle::left()
{
    return this->shape.getPosition().x - this->dlx/2;
}
float Paddle::right()
{
    return this->shape.getPosition().x + this->dlx/2;
}
float Paddle::up()
{
    return this->shape.getPosition().y - this->dly/2;
}
float Paddle::bottom()
{
    return this->shape.getPosition().y + this->dly/2;
}
float Paddle::width()
{
    return this->dlx;
}

///*****************************///
///*********** BLOCK ************///
///*****************************///

Block::Block (float x, float y)
{
    shape.setPosition(x, y);
    shape.setSize({this->dlx, this->dly});
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(this->dlx/2, this->dly/2);
}
void Block::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(this->shape, state);
}
sf::Vector2f Block::position()
{
    return shape.getPosition();
}
float Block::left()
{
    return this->shape.getPosition().x - this->dlx/2;
}
float Block::right()
{
    return this->shape.getPosition().x + this->dlx/2;
}
float Block::up()
{
    return this->shape.getPosition().y - this->dly/2;
}
float Block::bottom()
{
    return this->shape.getPosition().y + this->dly/2;
}
bool Block::ifDestroyed()
{
    return this->destroyed;
}
void Block::destroy()
{
    this->destroyed = true;
}

///***************************///
///********* BUTTON ********///
///***************************///

Button::Button(int l, int r, int t, int b) : left(l), right(r), up(u), bottom(b){}

bool Button::ifClicked(sf::RenderWindow& window)
{
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) return false;
    sf::Vector2i speedVector = sf::Mouse::getPosition(window);
    if (speedVector.x > this->left && speedVector.x < this->right && speedVector.y > this->up && speedVector.y < this->bottom)
        return true;
            else return false;
}
