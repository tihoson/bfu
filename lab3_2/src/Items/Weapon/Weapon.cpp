#include "Weapon.hpp"

using Game::Weapon;
using Game::Weapon_stats;
using Game::Player;
using Game::Item;
using Game::Map_cell;
using Game::IMap;

Weapon_stats::Weapon_stats(unsigned kill_chance, unsigned dmg, unsigned distance):
    kill_chance_(kill_chance), dmg_(dmg), distance_(distance) {}

Weapon::Weapon(std::string name, unsigned durability, unsigned kill_chance, unsigned dmg, unsigned distance):
    Item(name, durability), stats_(kill_chance, dmg, distance) {};

Weapon::~Weapon() {}

void Weapon::use(Player& user, IMap& map) {
    if (!user.is_active() || durability() == 0) {
        system("cls");
        std::cout << "You can't do it!\n";
        system("pause");
        return;
    }

    std::vector<std::shared_ptr<Player>> targets = map.get_players(user.get_pos()->get_x(), user.get_pos()->get_y(), stats_.distance_);    

    system("cls");
    std::cout << "Choose target:\n";
    for (size_t i = 0; i < targets.size(); i++)
        std::cout << i + 1 << ") " << targets.at(i)->get_name() 
                  << " (" << (targets.at(i)->get_stat()).hp_ 
                  << '/' << (targets.at(i)->get_max_stat()).hp_ << ')'
                  << std::endl;
    std::cout << "0) Exit\n";

    int n;
    std::cin >> n;

    if (n > targets.size() || n < 0) {
        system("cls");
        std::cout <<  "Invalid choose\n";
        system("pause");
        return;
    }

    if (n == 0)
        return;

    set_durability(durability() - 1);
    user.change_stat(Stat_type::AP, -1);

    if (std::rand() % 100 < stats_.kill_chance_) {
        targets.at(n - 1)->die();
        user.get_point(1);
        system("cls");
        std::cout << user.get_name() + " kill " + targets.at(n - 1)->get_name() << std::endl;
        system("pause");
        return;
    }

    attack(user, *targets.at(n - 1));
}

void Weapon::attack(Player& user, Player& target) {
    target.change_stat(Stat_type::HP, -stats_.dmg_);
    if (target.get_stat().hp_ == 0) {
        system("cls");
        std::cout << user.get_name() + " kill " + target.get_name() << std::endl;
        system("pause");
        return;
    }
    system("cls");
    std::cout << user.get_name() + " deal " + std::to_string(stats_.dmg_) + " to " + target.get_name() + '\n';
    system("pause");
}