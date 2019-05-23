#include "Item.hpp"

using Game::Item;

Item::Item(std::string name, unsigned durability):
    name_(name), durability_(durability) {}

Item::~Item() {}

void Item::set_durability(unsigned new_dur) {
    durability_ = new_dur;
}

unsigned Item::durability() const {
    return durability_;
}

const std::string& Item::get_name() const {
    return name_;
}
