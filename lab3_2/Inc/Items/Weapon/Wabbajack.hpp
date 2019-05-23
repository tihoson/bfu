#ifndef __WABBAJACK__
#define __WABBAJACK__

#include "basic_inc.hpp"

namespace Game {
    class Wabbajack;
}

#include "Weapon.hpp"
#include "Player.hpp"

namespace Game {
    class Wabbajack : public Weapon {
        public:
            enum Effects {
                ENEMY_DMG,
                SELF_DMG,
                INST_KILL,
                VAMPIRIC,
                SELF_HILL,
                ENEMY_HILL
            };
            Wabbajack();
        private:
            void attack(Player&, Player&);
            void message(std::string);
            static const std::string NAME_;
            static const unsigned DURABILITY_;
            static const unsigned KILL_CHANCE_;
            static const unsigned DMG_;
            static const unsigned DISTANCE_;
    };
}

#endif