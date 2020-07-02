#include "kula.hpp"

using namespace sf;

float Block::dlx = 140;
float Block::dly = 40;

template <class T1, class T2> bool ifCollision (T1& a, T2& b)
{
    return a.right() >= b.left() && a.left() <= b.right() && a.bottom() >= b.up() && a.up() <= b.bottom();
}

void spring (Paddle& pal, Ball& kol);
void spring (Block& blo, Ball& kol);
void hesoyam (float* dly2);


int main ()
{
    float dlx = 1600, dly = 900, dly2 = 900;
    RenderWindow window (VideoMode (dlx, dly), "Wreszcie");
    window.setFramerateLimit(60);
    std::vector <Block> blocks;
    Event event;

    Texture texture;
    Sprite sprite;

    Texture paddletex;
    if (!paddletex.loadFromFile("textures/paddle.png"))
    {
        blocks.clear();
        return -1;
    }

    Texture balltex;
    if (!balltex.loadFromFile("textures/ball.png"))
    {
        blocks.clear();
        return -1;
    }

    bool f = 1;

    while (true)
    {
        if (!texture.loadFromFile("textures/menu.png"))
        {
            blocks.clear();
            return -1;
        }
        sprite.setTexture(texture);

        window.draw(sprite);
        window.display();

        do /// MENU
        {
            f = 1;
            Button goodness (704, 868, 296, 361);
            Button evil (704, 868, 380, 445);
            Button exit (1357, 1556, 721, 786);

            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed) window.close ();
                if (goodness.ifClicked(window))
                {
                    if (!texture.loadFromFile("textures/pudzian.png")) return -1;
                    sprite.setTexture(texture);
                    f = 0;
                    break;
                }
                    else if (evil.ifClicked(window))
                    {
                        if (!texture.loadFromFile("textures/putin.png")) return -1;
                        sprite.setTexture(texture);
                        f = 0;
                        break;
                    }
                        else if (exit.ifClicked(window))
                        {
                            return 0;
                        }
            }
        } while (f);

        Ball ball(800, 350, &balltex);
        Paddle paddle(800, 800, &paddletex);

        unsigned short blocksx = 10, blocksy = 4;

        for (unsigned short i = 0; i < blocksy; ++i)
        {
            for (unsigned short j = 0; j < blocksx; ++j)
            {
                blocks.emplace_back((j+1)*(Block::dlx+10), (i+2)*(Block::dly+5));
            }
        }

        while (window.isOpen() && Ball.bottom() < dly2 && blocks.size() > 0) /// GRA
        {
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed) window.close ();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H))
                hesoyam(&dly2);

            window.clear();

            ball.movement(dlx, dly);
            paddle.movement(dlx);
            spring(paddle, Ball);
            for (auto& Block : blocks) spring(block, ball);

            window.draw(sprite);
            window.draw(ball);
            window.draw(paddle);

            int blocksCoun = 0;
            for (auto& Block : blocks)
            {
                if (!Block.ifDestroyed())
                {
                    window.draw(Block);
                    ++blocksCoun;
                }
            }
            if (blocksCoun == 0) break;

            window.display();
        }
    }

    blocks.clear();

    return 0;
}

void hesoyam(float* dly2) /// Switch on/off immortality :D
{
    if (*dly2 == 900) *dly2 = 1000;
        else *dly2 = 900;
}

void spring (Paddle& pal, Ball& kol)
{
    if (!ifCollision(pal, kol)) return;


    kol.moveBevel(kol.position().x - pal.position().x, pal);
    kol.moveUp();

  /*  if (kol.position().x > pal.position().x) kol.moveRight();
    else if (kol.position().x < pal.position().x) kol.moveLeft();*/
}

void spring (Block& blo, Ball& kol)
{
    if (!ifCollision(blo, kol) || blo.ifDestroyed()) return;

    if (kol.position().y > blo.position().y) kol.moveDown();
    else if (kol.position().y < blo.position().y) kol.moveUp();

    if (kol.way()) kol.moveRight();
    else kol.moveLeft();

    blo.destroy();
}
