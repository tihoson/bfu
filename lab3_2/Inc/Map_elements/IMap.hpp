#ifndef __IMAP__
#define __IMAP__

#include "basic_inc.hpp"

namespace Game {
    class IMap;
}

#include "Player.hpp"
#include "Map_cell.hpp"

namespace Game {
    class IMap {
        public:
            virtual std::shared_ptr<Map_cell> at(unsigned, unsigned) = 0;
            virtual std::shared_ptr<Map_cell> at_rand_free() = 0;
            virtual std::vector<std::shared_ptr<Player>> get_players(int, int, int) = 0;
    };
}

#endif