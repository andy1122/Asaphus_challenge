#include <catch2/catch_test_macros.hpp>
#include "Game.cpp"


TEST_CASE("Final scores for first 4 Fibonacci numbers", "[fibonacci4]") {
  std::vector<uint32_t> inputs{1, 1, 2, 3};
  auto result = play(inputs);
  REQUIRE(result.first == 13.0);
  REQUIRE(result.second == 25.0);
}

TEST_CASE("Final scores for first 8 Fibonacci numbers", "[fibonacci8]") {
  std::vector<uint32_t> inputs{1, 1, 2, 3, 5, 8, 13, 21};
  auto result = play(inputs);
  REQUIRE(result.first == 155.0);
  REQUIRE(result.second == 366.25);
}


TEST_CASE("Final scores of reverse of  first  4 Fibonacci numbers", "[Reverse_fibonacci4]") {
  std::vector<uint32_t> inputs{3, 2, 1, 1};
  auto result = play(inputs);
  REQUIRE(result.first == 13.0);
  REQUIRE(result.second == 8.0);
}

TEST_CASE("Final scores with 4 Random numbers", "[Random_4]") {
  std::vector<uint32_t> inputs{1, 4, 3, 5};
  auto result = play(inputs);
  REQUIRE(result.first == 25.0);
  REQUIRE(result.second == 76.0);
}

TEST_CASE("Test absorption of green box", "[green]") {
  // TODO
}

TEST_CASE("Test absorption of bcd .lue box", "[blue]") {
  // TODO
}
