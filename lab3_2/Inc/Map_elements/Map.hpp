#ifndef __MAP__
#define __MAP__

#include "basic_inc.hpp"

namespace Game {
    class Map;
}

#include "Map_cell.hpp"
#include "IMap.hpp"
#include "Player.hpp"

namespace Game {
    class Map : public IMap {
        public:
            Map(unsigned, unsigned);
            ~Map();

            std::shared_ptr<Map_cell> at(unsigned, unsigned);
            std::shared_ptr<Map_cell> at_rand_free();

            std::vector<std::shared_ptr<Player>> get_players(int, int, int);
            unsigned get_height() const;
            unsigned get_width() const;

            void move_walls();

        private:
            std::vector<std::vector<std::shared_ptr<Map_cell>>> cells_;

            unsigned up_border_,
                   down_border_,
                   left_border_,
                  right_border_;
            
            const int height_,
                       width_;
    };
}

#endif
