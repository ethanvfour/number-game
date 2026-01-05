#include "Tile.h"

Tile::Tile() : num{}
{}

int Tile::getNum() const
{
    return num;
}

void Tile::setNum(int newNum)
{
    num = newNum;
}