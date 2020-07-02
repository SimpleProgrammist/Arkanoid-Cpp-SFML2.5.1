#ifndef kula_hpp
#define kula_hpp
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>


///*****************************///
///********* PADDLE ************///
///*****************************///

class Paddle : public sf::Drawable
{
    sf::RectangleShape shape;
    const float dlx = 150;
    const float dly = 30;
    const float speed = 6;
    sf::Vector2f speedVec {speed, 0};
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

public:
    Paddle(float x, float y, sf::Texture* texture);
    void movement (float dx);
    sf::Vector2f position();

    float left();
    float right();
    float top();
    float bottom();
    float width();
};

///***************************///
///********* BALL ************///
///***************************///

class Ball : public sf::Drawable
{
    sf::CircleShape shape;
    const float r = 20;     /// radious
    const float speed = 10;
    sf::Vector2f speedVec {0, speed};
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

public:
    Ball (float x, float y, sf::Texture* texture);

    void movement (float dx, float dy);
    sf::Vector2f position();
    float left();
    float right();
    float top();
    float bottom();

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveBottom();

    void moveBevel(float f, Paddle pal);

    bool way();
};



///*****************************///
///*********** BLOCK ***********///
///*****************************///

class Blok : public sf::Drawable
{
    sf::RectangleShape shape;

    bool destroyed = false;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

public:
    static float dlx;
    static float dly;
    Blok(float x, float y);
    sf::Vector2f position();

    void destroy();
    bool ifDestroyed();

    float left();
    float right();
    float top();
    float bottom();

};

///***************************///
///********* BUTTON** ********///
///***************************///

class Button
{
    int left;
    int right;
    int top;
    int bottom;
public:
    Button (int l, int p, int g, int d);
    bool ifClicked(sf::RenderWindow& window);
};

#endif
