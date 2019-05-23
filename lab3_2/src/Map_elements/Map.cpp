#include "Map.hpp"

using Game::Map_cell;
using Game::Map;
using Game::Player;

Map::Map(unsigned h, unsigned w):
    height_(h), width_(w),
    up_border_(0), down_border_(h - 1),
    left_border_(0), right_border_(w - 1) {

    cells_.resize(height_);

    for (unsigned i = 0; i < height_; i++)
        for (unsigned j = 0; j < width_; j++) 
            if (i == 0 || i == height_ - 1 ||
                j == 0 || j == width_ - 1)
                cells_.at(i).push_back(std::make_shared<Map_cell>(true, i, j));
            else
                cells_.at(i).push_back(std::make_shared<Map_cell>(false, i, j));
}

Map::~Map() {
    for (size_t i = 0; i < height_; i++)
        for (auto& cur : cells_.at(i))
            cur = nullptr;
    cells_.clear();
}

/*----------------------------------------------------------------------------------*/

std::shared_ptr<Map_cell> Map::at(unsigned h, unsigned w) {
    return cells_.at(h).at(w);
}

std::shared_ptr<Map_cell> Map::at_rand_free() {
    unsigned h, w;
    for (;;) {
        h = std::rand() % height_;
        w = std::rand() % width_;
        auto it = at(h, w);
        if (it->is_wall() == false &&
            it->get_player() == nullptr &&
            it->get_items().size() == 0)
            break;
    }
    return at(h, w);
}

/*----------------------------------------------------------------------------------*/

std::vector<std::shared_ptr<Player>> Map::get_players(int h, int w, int r) {
    std::vector<std::shared_ptr<Player>> players;

    for (int i = std::max(h - r, 0); i < std::min(h + r, height_); i++)
        for (int j = std::max(w - r, 0); j < std::min(w + r, width_); j++) 
            if ((i - h) * (i - h) + (j - w) * (j - w) <= r *r) {
                auto it = at(i, j);
                if (it->get_player() != nullptr)
                    players.emplace_back(it->get_player());
            }
    return players;
}

unsigned Map::get_height() const {
    return height_;
}

unsigned Map::get_width() const {
    return width_;
}

/*----------------------------------------------------------------------------------*/

void Map::move_walls() {
    up_border_++;
    down_border_--;
    left_border_++;
    right_border_--;

    for (int i = 0; i < height_; i++)
        for (int j = 0; j < width_; j++)
            if (i <= up_border_ || i >= down_border_ ||
                j <= left_border_ || j >= right_border_)
                at(i, j)->set_wall();

}