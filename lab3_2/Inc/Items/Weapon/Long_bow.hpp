#ifndef __LONG_BOW__
#define __LONG_BOW__

namespace Game {
    class Long_bow;
}

#include "basic_inc.hpp"
#include "Weapon.hpp"

namespace Game {
    class Long_bow : public Weapon {
        public:
            Long_bow();
        private:
            static const std::string NAME_;
            static const unsigned DURABILITY_;
            static const unsigned KILL_CHANCE_;
            static const unsigned DMG_;
            static const unsigned DISTANCE_;
    };
}

#endif