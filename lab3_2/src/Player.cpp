#include "Player.hpp"

using Game::Stat_type;
using Game::Stats;
using Game::Player;
using Game::Item;
using Game::IMap_cell;

Stats::Stats(int hp, int ap, int sz):
    hp_(hp), ap_(ap), sz_(sz) {}

/*----------------------------------------------------------------------------------*/

Player::Player(std::string name, std::shared_ptr<IMap_cell> position):
    name_(name), position_(position),
    stat_(BASE_HP, BASE_AP, 0),
    max_stat_(BASE_HP, BASE_AP, BASE_SZ),
    up_points_(1) {}

Player::~Player() {
    position_ = nullptr;
    for (auto& cur : items_)
        cur = nullptr;
    items_.clear();
}

/*----------------------------------------------------------------------------------*/

bool Player::get_item(std::shared_ptr<Item> item) {
	if (stat_.sz_ == max_stat_.sz_) {
		system("cls");
		std::cout << "You can't get item!\n";
		system("pause");
		return false;
	}
	items_.push_back(item);
	stat_.sz_++;
	return true;
}

void Player::drop_item(size_t n) {
	if (n > items_.size() || n < 1) {
		system("cls");
		std::cout << "Incorrect input.\n";
		system("pause");
		return;
	} else {
		position_->add_item(items_.at(n - 1));
		items_.erase(items_.begin() + n - 1);
	}
	stat_.sz_--;
}

void Player::turn() {
	stat_.ap_ = max_stat_.ap_;
}

void Player::die() {
	system("cls");
	std::cout << name_ + " died.\n";
	system("pause");
	for (auto& cur : items_)
		position_->add_item(cur);
	stat_.hp_ = 0;
	position_->remove_player();
}

void Player::lvl_up(Stat_type type) {
	switch (type) {
		case Stat_type::AP:
			max_stat_.ap_++;
			stat_.ap_++;
			break;
		case Stat_type::HP:
			max_stat_.hp_ += 10;
			stat_.hp_ += 10;
			break;
		case Stat_type::SZ:
			max_stat_.sz_++;
			break;
		default:
			system("cls");
			std::cout << "Incorrect input!\n";
			system("pause");
			return;
	}	

	up_points_--;
}

/*----------------------------------------------------------------------------------*/

void Player::set_position(std::shared_ptr<IMap_cell> cell) {
	position_ = cell;
}

/*----------------------------------------------------------------------------------*/

const std::string& Player::get_name() const {
	return name_;
}

const Stats& Player::get_stat() const {
	return stat_;
}

const Stats& Player::get_max_stat() const {
	return max_stat_;
}

int Player::get_up_points() const {
	return up_points_;
}

std::shared_ptr<IMap_cell> Player::get_pos() {
	return position_;
}

std::shared_ptr<Item> Player::get_item(size_t n) {
	if (n > items_.size() || n < 1) {
		system("cls");
		std::cout << "Incorrect input.\n";
		system("pause");
		return nullptr;
	}
	return items_.at(n - 1);
}

std::vector<std::shared_ptr<Item>> Player::get_items() const {
	return items_;
}

/*----------------------------------------------------------------------------------*/

void Player::change_stat(Stat_type type, int change) {
	switch (type) {
		case Stat_type::AP:
			stat_.ap_ = std::min(max_stat_.ap_, std::max(0, stat_.ap_ + change));
			break;
		case Stat_type::HP:
			stat_.hp_ = std::min(max_stat_.hp_, std::max(0, stat_.hp_ + change));
			break;
	}
	if (stat_.hp_ == 0)
		die();
}

void Player::get_point(unsigned points) {
	up_points_ += points;
}

/*----------------------------------------------------------------------------------*/

bool Player::is_dead() const {
	return stat_.hp_ == 0;
}

bool Player::is_active() const {
	return stat_.ap_ > 0;
}

/*----------------------------------------------------------------------------------*/

const int Player::BASE_HP = 100,
          Player::BASE_AP = 5,
          Player::BASE_SZ = 3;