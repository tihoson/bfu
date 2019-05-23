#include "Fork.hpp"

using Game::Fork;

Fork::Fork():
    Weapon(NAME_, DURABILITY_, KILL_CHANCE_, DMG_, DISTANCE_) {};

const std::string Fork::NAME_ = "Fork of Horripilation";

const unsigned Fork::DURABILITY_ = 220;
const unsigned Fork::KILL_CHANCE_ = 146;
const unsigned Fork::DMG_ = 2;
const unsigned Fork::DISTANCE_ = 2;