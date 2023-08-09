#include "Aircraft.hpp"

void Aircraft::_bind_methods()
{

}

void Aircraft::_ready()
{

}

double Aircraft::GetLift()
{
    return (1.0 / 2.0) * this->airPressure * (this->velocity * this->velocity).length() * this->liftCoefficient * this->area;
}

double Aircraft::GetDrag()
{
    return (1.0 / 2.0) * this->airPressure * (this->velocity * this->velocity).length() * this->dragCoefficient * this->area;
}
