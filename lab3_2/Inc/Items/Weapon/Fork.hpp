#ifndef __FORK__
#define __FORK__

namespace Game {
    class Fork;
}

#include "basic_inc.hpp"
#include "Weapon.hpp"

namespace Game {
    class Fork : public Weapon {
        public:
            Fork();
        private:
            static const std::string NAME_;
            static const unsigned DURABILITY_;
            static const unsigned KILL_CHANCE_;
            static const unsigned DMG_;
            static const unsigned DISTANCE_;
    };
}

#endif