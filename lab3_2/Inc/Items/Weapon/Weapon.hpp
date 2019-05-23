#ifndef __WEAPON__
#define __WEAPON__

#include "basic_inc.hpp"

namespace Game {
    struct Weapon_stats {
        unsigned kill_chance_,
                        dmg_,
                    distance_;
        Weapon_stats(unsigned, unsigned, unsigned);   
    };

    class Weapon;
}

#include "Item.hpp"
#include "Player.hpp"
#include "IMap.hpp"

namespace Game {
    class Weapon : public Item {
        public:
            Weapon(std::string, unsigned, unsigned, unsigned, unsigned);
            virtual ~Weapon();

            virtual void use(Player&, IMap&) override;
            virtual void attack(Player&, Player&);
        private:
            Weapon_stats stats_;
    };
}
#endif