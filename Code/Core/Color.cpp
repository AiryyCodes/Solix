#include "Core/Color.h"

Color Color::Normalize() const
{
    Color newColor;
    // Should not serialize if value is 1 or less
    newColor.r = this->r <= 1 ? this->r : this->r / 255.0f;
    newColor.g = this->g <= 1 ? this->g : this->g / 255.0f;
    newColor.b = this->b <= 1 ? this->b : this->b / 255.0f;
    newColor.a = this->a <= 1 ? this->a : this->a / 255.0f;

    return newColor;
}
