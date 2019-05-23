#ifndef __ITEM__
#define __ITEM__

#include "basic_inc.hpp"

namespace Game {
    class Item;
}

#include "Player.hpp"
#include "IMap.hpp"

namespace Game {
    class Item {
        public:
            Item(std::string, unsigned);
            virtual ~Item();

            virtual void use(Player&, IMap&) = 0;

            void set_durability(unsigned);

            unsigned durability() const;
            const std::string& get_name() const;
        private:
            std::string name_;
            unsigned durability_;
    };
}

#endif