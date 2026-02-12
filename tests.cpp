#include "src/bag.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("bag: create & add")
{
  Bag<int> bag;

  REQUIRE(bag.is_empty() == true);
  REQUIRE(bag.to_string() == "{}");
  REQUIRE(bag.number_of(1000) == 0);

  bag.add_item(10);
  bag.add_item(50);

  REQUIRE(bag.is_empty() == false);
  REQUIRE(bag.contains(10) == true);
  REQUIRE(bag.contains(50) == true);
  REQUIRE(bag.contains(18) == false);

  REQUIRE(bag.to_string() == "{10, 50}");
}

TEST_CASE("bag: remove item")
{
  Bag<int> bag;
  bag.add_item(1);
  bag.add_item(2);
  bag.add_item(3);
  bag.add_item(4);
  bag.add_item(5);

  bool removed = bag.remove_item(4);
  REQUIRE(removed == true);
  REQUIRE(bag.contains(4) == false);
  REQUIRE(bag.number_of(4) == 0);
  REQUIRE(bag.to_string() == "{1, 2, 3, 5}");

  removed = bag.remove_item(100);
  REQUIRE(removed == false);
  REQUIRE(bag.to_string() == "{1, 2, 3, 5}");
}

TEST_CASE("bag: number_of with duplicates")
{
  Bag<int> bag;
  bag.add_item(100);
  bag.add_item(200);
  bag.add_item(100);
  bag.add_item(100);
  bag.add_item(500);

  REQUIRE(bag.number_of(100) == 3);
  ;
  REQUIRE(bag.number_of(200) == 1);
  REQUIRE(bag.number_of(500) == 1);
  REQUIRE(bag.number_of(300) == 0);

  bag.remove_item(100);
  REQUIRE(bag.number_of(100) == 2);
}

TEST_CASE("bag: remove_all")
{
  Bag<int> bag;
  bag.add_item(1);
  bag.add_item(2);
  bag.add_item(1);
  bag.add_item(3);
  bag.add_item(1);

  REQUIRE(bag.number_of(1) == 3);

  bag.remove_all_of(1);

  REQUIRE(bag.number_of(1) == 0);
  REQUIRE(bag.contains(2) == true);
  REQUIRE(bag.contains(3) == true);
  REQUIRE(bag.is_empty() == false);
}

TEST_CASE("bag: dump")
{
  Bag<int> bag;
  bag.add_item(1000);
  bag.add_item(2000);

  REQUIRE(bag.is_empty() == false);

  bag.dump();

  REQUIRE(bag.is_empty() == true);
  REQUIRE(bag.number_of(1000) == 0);
  REQUIRE(bag.number_of(2000) == 0);
  REQUIRE(bag.to_string() == "{}");
}

TEST_CASE("bag: random")
{
  Bag<int> bag;
  bag.add_item(123);

  int pick = bag.pick_random();
  REQUIRE(pick == 123);
  REQUIRE(bag.is_empty() == true);

  bag.add_item(1);
  bag.add_item(2);
  bag.add_item(3);

  pick = bag.pick_random();
  bool valid = (pick == 1) || (pick == 2) || (pick == 3);
  REQUIRE(valid == true);
  REQUIRE(bag.contains(pick) == false);
}

TEST_CASE("bag: dump_into")
{
  Bag<int> bag_1;
  Bag<int> bag_2;

  bag_1.add_item(1);
  bag_1.add_item(2);

  bag_2.add_item(3);

  bag_1.dump_into(bag_2);

  REQUIRE(bag_1.is_empty() == true);
  REQUIRE(bag_2.number_of(1) == 1);
  REQUIRE(bag_2.number_of(2) == 1);
  REQUIRE(bag_2.number_of(3) == 1);
}

TEST_CASE("bag: operators & constructors")
{
  Bag<int> bag_1;
  bag_1.add_item(1);
  bag_1.add_item(2);

  Bag<int> bag_2(bag_1);
  REQUIRE(bag_2.number_of(1) == 1);
  REQUIRE(bag_2.number_of(2) == 1);

  bag_1.add_item(3);
  REQUIRE(bag_1.contains(3) == true);
  REQUIRE(bag_2.contains(3) == false);

  Bag<int> bag_3;
  bag_3.add_item(101);
  bag_3 = bag_2;

  REQUIRE(bag_3.number_of(1) == 1);
  REQUIRE(bag_3.number_of(2) == 1);
  REQUIRE(bag_3.number_of(101) == 0);

  bag_2.dump();
  REQUIRE(bag_2.is_empty());
  REQUIRE(!bag_3.is_empty());
}
