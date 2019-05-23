#ifndef __PLAYER__
#define __PLAYER__

#include "basic_inc.hpp"

namespace Game {
	enum class Stat_type {
		HP = 1,
		AP,
		SZ
	};

	struct Stats {
		int hp_,
			ap_,
			sz_;
		Stats(int, int, int);
	};

	class Player;
}

#include "Item.hpp"
#include "IMap_cell.hpp"

namespace Game {
	class Player {
		public:
			Player(std::string, std::shared_ptr<IMap_cell>);
			~Player();
			
			bool get_item(std::shared_ptr<Item>);
			void drop_item(size_t);
			void turn();
			void lvl_up(Stat_type);
			void die();
			
			void set_position(std::shared_ptr<IMap_cell>);
			
			const std::string& get_name() const;
			const Stats& get_stat() const;
			const Stats& get_max_stat() const;
			int get_up_points() const;
			std::shared_ptr<IMap_cell> get_pos();
			std::shared_ptr<Item> get_item(size_t);
			std::vector<std::shared_ptr<Item>> get_items() const;
			
			void change_stat(Stat_type, int);
			void get_point(unsigned);

			bool is_dead() const;
			bool is_active() const;
			
		private:
			std::string name_;
			Stats stat_,
				max_stat_;
			int up_points_;
			std::shared_ptr<IMap_cell> position_;
			std::vector<std::shared_ptr<Item>> items_;

			static const int BASE_HP,
						   	 BASE_AP,
							 BASE_SZ;
	};
}

#endif