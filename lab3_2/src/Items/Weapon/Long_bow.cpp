#include "Long_bow.hpp"

using Game::Long_bow;

Long_bow::Long_bow():
    Weapon(NAME_, DURABILITY_, KILL_CHANCE_, DMG_, DISTANCE_) {};

const std::string Long_bow::NAME_ = "Long bow";

const unsigned Long_bow::DURABILITY_ = 3;
const unsigned Long_bow::KILL_CHANCE_ = 15;
const unsigned Long_bow::DMG_ = 70;
const unsigned Long_bow::DISTANCE_ = 8;