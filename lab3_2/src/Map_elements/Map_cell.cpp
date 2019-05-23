#include "Map_cell.hpp"

using Game::Map_cell;
using Game::Item;
using Game::Player;

/*----------------------------------------------------------------------------------*/

Map_cell::Map_cell(bool wall, unsigned x, unsigned y):
	player_(nullptr), wall_(wall), x_(x), y_(y) {}

Map_cell::~Map_cell() {
	player_ = nullptr;
	for (auto& cur : items_)
		cur = nullptr;
	items_.clear();
}

/*----------------------------------------------------------------------------------*/

void Map_cell::set_player(std::shared_ptr<Player> player) {
	player_ = player;
}

void Map_cell::add_item(std::shared_ptr<Item> item) {
	items_.push_back(item);
}

/*----------------------------------------------------------------------------------*/

void Map_cell::remove_player() {
	player_ = nullptr;
}

void Map_cell::remove_item(std::shared_ptr<Item> item) {
	for (size_t i = 0; i < items_.size(); i++)
		if (items_.at(i) == item)
			items_.erase(items_.begin() + i);
}

/*----------------------------------------------------------------------------------*/

bool Map_cell::is_wall() const {
	return wall_;
}

void Map_cell::set_wall() {
	wall_ = true;
	for (auto& cur : items_)
		cur = nullptr;
	items_.clear();
	if (player_ != nullptr)
		player_->die();
}

unsigned Map_cell::get_x() const {
	return x_;
}

unsigned Map_cell::get_y() const {
	return y_;
}

std::shared_ptr<Player> Map_cell::get_player() {
	return player_;
}
std::vector<std::shared_ptr<Item>>& Map_cell::get_items() {
	return items_;
}

/*----------------------------------------------------------------------------------*/

char Map_cell::cell_char() {
	if (wall_)
		return '#';
	if (player_ != nullptr)
		return 'P';
	if (items_.size() != 0)
		return 'I';
	return '.';
}
