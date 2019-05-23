#ifndef __IMAP_CELL__
#define __IMAP_CELL__

#include "basic_inc.hpp"

namespace Game {
    class IMap_cell;
}

#include "Player.hpp"
#include "Item.hpp"

namespace Game {
    class IMap_cell {
        public:
            virtual void set_player(std::shared_ptr<Player>) = 0;
            virtual std::shared_ptr<Player> get_player() = 0;
            virtual void remove_player() = 0;

            virtual void add_item(std::shared_ptr<Item>) = 0;
            virtual std::vector<std::shared_ptr<Item>>& get_items() = 0;
            virtual void remove_item(std::shared_ptr<Item>) = 0;
            
            virtual unsigned get_x() const = 0;
            virtual unsigned get_y() const = 0;
    };
}

#endif