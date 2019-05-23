#include "Game_controller.hpp"

using Game::Game_controller;
using Game::Item;
using Game::Weapon;

Game_controller::Game_controller(unsigned players, unsigned h, unsigned w):
    map_(h, w), turns_(1), players_done_(0), continued_(true), DANGER_(5), PLAYERS_(players)  {
    for (int i = 0; i < 80; i++)
        map_.at_rand_free()->set_wall();
    for (size_t i = 0; i < players; i++) {
        std::srand(std::time(nullptr));
        players_queue_.push_back(std::make_shared<Player>("Player" + std::to_string(i + 1), map_.at_rand_free()));
        players_queue_.back()->get_pos()->set_player(players_queue_.at(i));
        players_queue_.back()->get_item(std::make_shared<Long_bow>());
    }
    for (int i = 0; i < 20; i++) { 
        map_.at_rand_free()->add_item(std::make_shared<Fork>());
        map_.at_rand_free()->add_item(std::make_shared<Long_bow>());
    }
    for (int i = 0; i < 15; i++)
        map_.at_rand_free()->add_item(std::make_shared<Wabbajack>());
    
}

void Game_controller::draw() {
    Player current = *players_queue_.front(); 
    unsigned h = current.get_pos()->get_x(),
             w = current.get_pos()->get_y();
    for (size_t i = 0; i < map_.get_height(); i++) {
        for (size_t j = 0; j < map_.get_width(); j++) {
            if (i == h && j == w)
                std::cout << "Y";
            else 
                std::cout << map_.at(i, j)->cell_char();
        }
        std::cout << '\n';
    }
}

void Game_controller::draw_info() {
    Player current = *players_queue_.front();
    std::cout << std::setw(10) << std::left
              << current.get_name() << ' '
              << "HP: " << current.get_stat().hp_ << "/" << current.get_max_stat().hp_ << "  "
              << "AP: " << current.get_stat().ap_ << "/" << current.get_max_stat().ap_ << '\n'; 
    std::cout << "Backpack(" << current.get_stat().sz_ << '/' << current.get_max_stat().sz_ << "):\n";
    std::vector<std::shared_ptr<Item>> items = current.get_items();
    for (size_t i = 0; i < items.size(); i++)
        std::cout << i + 1 << ") " << items.at(i)->get_name() 
                  << '(' << items.at(i)->durability() << ')'
                  << std::endl; 
}

void Game_controller::start() {
    while (continued_) {
        action();
        turn();
    }
    win();
}

void Game_controller::action() {
    std::string command;
    while (1) {
        if (players_queue_.front()->is_dead() || players_queue_.size() < 2)
            return;
        system("cls");
        draw();
        draw_info();
        std::cin >> command;
        if (command == "move") 
            move();
        else if (command == "drop")
            drop();
        else if (command == "use") 
            use();
        else if (command == "look")
            look();
        else if (command == "upgrade")
            upgrade();
        else if (command == "take")
            take();
        else if (command == "turn")
            return;
        else if (command == "suicide") {
            players_queue_.front()->die();
            return;
        } else {
            error("This command doesn't exist!");
        }
    }
}

void Game_controller::error(std::string error_type) {
    system("cls");
    std::cout << error_type << std::endl;
    system("pause");
}

void Game_controller::move() {
    Player current = *players_queue_.front();
    if (!current.is_active()) {
        error("You haven't enough AP.");
        return;
    }
    std::string dir;
    std::cin >> dir;
    int dh, dw;
    if (dir == "up")
        dh = -1, dw = 0;
    else if (dir == "down")
        dh = 1, dw = 0;
    else if (dir == "right")
        dh = 0, dw = 1;
    else if (dir == "left")
        dh = 0, dw = -1;
    else {
        error("This direction doesn't exist.");
        return;
    }
    unsigned h = current.get_pos()->get_x(),
             w = current.get_pos()->get_y();
    if (map_.at(h, w)->is_wall() == false && map_.at(h, w)->get_player() == nullptr) {
        error("You can't go here.");
        return;
    }
    map_.at(h + dh, w + dw)->set_player(players_queue_.front());
    players_queue_.front()->change_stat(Stat_type::AP, -1);
    players_queue_.front()->set_position(map_.at(h + dh, w + dw));
    map_.at(h, w)->remove_player();
}

void Game_controller::use() {
    if (!players_queue_.front()->is_active()) {
        error("You haven't enough AP.");
        return;
    } 
    size_t n;
    std::cin >> n;
    auto item = players_queue_.front()->get_item(n);
    if (item != nullptr) {
        item->use(*(players_queue_.front()), map_);
    }
}

void Game_controller::look() {
    Player current = *players_queue_.front();
    unsigned h = current.get_pos()->get_x(),
             w = current.get_pos()->get_y();
    auto items = map_.at(h, w)->get_items();
    system("cls");
    for (size_t i = 0; i < items.size(); i++)
        std::cout << i + 1 << ") " << items.at(i)->get_name()
                  << "(" << items.at(i)->durability() << ")\n";
    system("pause");
}

void Game_controller::upgrade() {
    if (players_queue_.front()->get_up_points() == 0) {
        error("You haven't enough upgrade points.");
    } else {
        system("cls");
        std::cout << "Choose:\n1) HP\n2) AP\n3) SZ\n";
        int n;
        std::cin >> n;
        players_queue_.front()->lvl_up(static_cast<Stat_type>(n));
    }
}

void Game_controller::take() {
    if (!players_queue_.front()->is_active()) {
        error("You haven't enough AP.");
        return;
    } 
    size_t n;
    std::cin >> n;
    if ((players_queue_.front()->get_pos()->get_items()).size() < n) {
        error("Invalid input.");
    } else {
        if (players_queue_.front()->get_item((players_queue_.front()->get_pos()->get_items()).at(n - 1))) {
            players_queue_.front()->get_pos()->remove_item((players_queue_.front()->get_pos()->get_items()).at(n - 1));
            players_queue_.front()->change_stat(Stat_type::AP, -1);
        }
    }
}

void Game_controller::drop() {
    size_t n;
    std::cin >> n;
    players_queue_.front()->drop_item(n);
}

void Game_controller::turn() {
    bool next = false;
    while (!players_queue_.empty() && players_queue_.front()->is_dead()) {
        players_queue_.pop_front();
        next = true;
    }
    if (!next && !players_queue_.empty() && players_queue_.front()->is_dead() == false) {
        players_queue_.front()->turn();
        players_queue_.push_back(players_queue_.front());
        players_queue_.pop_front();
    }

    if (players_queue_.size() < 2) {
        continued_ = false;
        return;
    }
    players_done_++;
    if (players_done_ == PLAYERS_) {
        players_done_ = 0;
        turns_++;
    }
    if (turns_ % DANGER_ == 0) {
        map_.move_walls();
        turns_ = 1;
    }
}

void Game_controller::win() {
    system("cls");
    if (players_queue_.empty()) {
        std::cout << "Draw\n";
    } else {
        std::cout << players_queue_.front()->get_name() + " won!\n";
    }
    system("pause");
}