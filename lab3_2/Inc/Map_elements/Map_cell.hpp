#ifndef __MAP_CELL__
#define __MAP_CELL__

#include "basic_inc.hpp"

namespace Game {
	class Map_cell;
}

#include "Player.hpp"
#include "Item.hpp"
#include "IMap_cell.hpp"

namespace Game {
	class Map_cell : public IMap_cell {
		public:
			Map_cell(bool, unsigned, unsigned);
			~Map_cell();
			
			void set_player(std::shared_ptr<Player>);
			void add_item(std::shared_ptr<Item>);
			
			void remove_player();
			void remove_item(std::shared_ptr<Item>);
			
			bool is_wall() const;
			void set_wall();
			unsigned get_x() const;
			unsigned get_y() const;
			std::shared_ptr<Player> get_player();
			std::vector<std::shared_ptr<Item>>& get_items();
			
			char cell_char();
			std::string info();

		private:
			std::shared_ptr<Player> player_;
			std::vector<std::shared_ptr<Item>> items_;
			bool wall_;
			unsigned x_, 
					 y_;
	};
}

#endif