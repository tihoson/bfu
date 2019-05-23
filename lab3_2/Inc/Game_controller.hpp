#ifndef __GAME_CONTROLLER__
#define __GAME_CONTROLLER__

#include "basic_inc.hpp"

namespace Game {
    class Game_controller;
}

#include "Map_cell.hpp"
#include "Item.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Weapon.hpp"
#include "Items_inc.hpp"
#include "IMap.hpp"
#include "IMap_cell.hpp"

namespace Game {
    class Game_controller {
        public:
            Game_controller(unsigned, unsigned, unsigned);
            void start();
            void win();
            void action();
            void draw();
            void draw_info();
            void turn();
            void player_turn();
            void move();
            void drop();
            void use();
            void look();
            void upgrade();
            void take();
        private:
            void error(std::string);

            Map map_;
            std::deque<std::shared_ptr<Player>> players_queue_;
            unsigned turns_;
            unsigned players_done_;
            bool continued_;

            const unsigned DANGER_;
            const unsigned PLAYERS_;
    };
}

#endif