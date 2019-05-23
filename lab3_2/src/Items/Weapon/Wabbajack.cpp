#include "Wabbajack.hpp"

using Game::Wabbajack;

Wabbajack::Wabbajack():
    Weapon(NAME_, DURABILITY_, KILL_CHANCE_, DMG_, DISTANCE_) {};

void Wabbajack::message(std::string mes) {
    system("cls");
    std::cout << mes << std::endl;
    system("pause");
}

void Wabbajack::attack(Player& user, Player& target) {
    int n = std::rand() % 6;
    switch (n) {
        case Effects::ENEMY_DMG:
            message("MUHAHAHAHA, " + target.get_name() + " GET " + std::to_string(2 * DMG_) + " DAMAGE!");
            target.change_stat(Stat_type::HP, -2 * DMG_);
            break;
        case Effects::ENEMY_HILL:
            target.change_stat(Stat_type::HP, DMG_);
            message("Oups... You heal " + target.get_name() + " up to " + std::to_string(target.get_stat().hp_));
            break;
        case Effects::INST_KILL:
            message("KILL! DESTROY!");
            target.die();
            user.get_point(1);
            message(user.get_name() + " kill " + target.get_name());
            break;
        case Effects::SELF_DMG:
            message("Why you are so stupid?");
            user.change_stat(Stat_type::HP, -DMG_);
            break;
        case Effects::SELF_HILL:
            message("Little chicken");
            user.change_stat(Stat_type::HP, DMG_);
            break;
        case Effects::VAMPIRIC:
            message("Bloodsucker...");
            target.change_stat(Stat_type::HP, -DMG_);
            user.change_stat(Stat_type::HP, DMG_);
            break;
    }
}

const std::string Wabbajack::NAME_ = "Wabbajack";

const unsigned Wabbajack::DURABILITY_ = 6;
const unsigned Wabbajack::KILL_CHANCE_ = 0;
const unsigned Wabbajack::DMG_ = 35;
const unsigned Wabbajack::DISTANCE_ = 5;