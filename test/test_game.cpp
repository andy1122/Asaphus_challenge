#include <catch2/catch_test_macros.hpp>
#include "Game.cpp"


TEST_CASE("Final scores for first 4 Fibonacci numbers", "[fibonacci4]") {
  std::vector<uint32_t> inputs{1, 1, 2, 3};
  std::vector<std::unique_ptr<Box>> boxes;
  auto result = play(inputs, boxes);
  REQUIRE(result.first == 13.0);
  REQUIRE(result.second == 25.0);
}

TEST_CASE("Final scores for first 8 Fibonacci numbers", "[fibonacci8]") {
  std::vector<uint32_t> inputs{1, 1, 2, 3, 5, 8, 13, 21};
  std::vector<std::unique_ptr<Box>> boxes;
  auto result = play(inputs, boxes);
  REQUIRE(result.first == 155.0);
  REQUIRE(result.second == 366.25);
}


TEST_CASE("Final scores of reverse of  first  4 Fibonacci numbers", "[Reverse_fibonacci4]") {
  std::vector<uint32_t> inputs{3, 2, 1, 1};
  std::vector<std::unique_ptr<Box>> boxes;
  auto result = play(inputs, boxes);
  REQUIRE(result.first == 13.0);
  REQUIRE(result.second == 8.0);
}

TEST_CASE("Final scores with 4 Random numbers", "[Random_4]") {
  std::vector<uint32_t> inputs{1, 4, 3, 5};
  std::vector<std::unique_ptr<Box>> boxes;
  auto result = play(inputs, boxes);
  REQUIRE(result.first == 25.0);
  REQUIRE(result.second == 76.0);
}


TEST_CASE("Test absorption of green box", "[green]") {
  // TODO
  std::vector<uint32_t> inputs{1, 4, 3, 5};
  std::vector<std::unique_ptr<Box>> boxes;
  auto result = play(inputs, boxes);
  REQUIRE(boxes[0]->getWeight() == 1.0);
  REQUIRE(boxes[1]->getWeight() == 4.1);

  std::vector<uint32_t> inputs1{3, 2, 1, 1};
  std::vector<std::unique_ptr<Box>> boxes1;
  auto result1 = play(inputs1, boxes1);
  REQUIRE(boxes1[0]->getWeight() == 3.0);
  REQUIRE(boxes1[1]->getWeight() == 2.1);

  std::vector<uint32_t> inputs2{1, 1, 2, 3};
  std::vector<std::unique_ptr<Box>> boxes2;
  auto result2 = play(inputs2, boxes2);
  REQUIRE(boxes2[0]->getWeight() == 1.0);
  REQUIRE(boxes2[1]->getWeight() == 1.1);

  std::vector<uint32_t> inputs3{1, 1, 2, 3, 5, 8, 13, 21};
  std::vector<std::unique_ptr<Box>> boxes3;
  auto result3 = play(inputs3, boxes3);
  REQUIRE(boxes3[0]->getWeight() == 6.0);
  REQUIRE(boxes3[1]->getWeight() == 9.1);
 
}

TEST_CASE("Test absorption of blue box", "[blue]") {
  // TODO
    std::vector<uint32_t> inputs{1, 4, 3, 5};
  std::vector<std::unique_ptr<Box>> boxes;
  auto result = play(inputs, boxes);
  REQUIRE(boxes[2]->getWeight() == 3.2);
  REQUIRE(boxes[3]->getWeight() == 5.3);

  std::vector<uint32_t> inputs1{3, 2, 1, 1};
  std::vector<std::unique_ptr<Box>> boxes1;
  auto result1 = play(inputs1, boxes1);
  REQUIRE(boxes1[2]->getWeight() == 1.2);
  REQUIRE(boxes1[3]->getWeight() == 1.3);

  std::vector<uint32_t> inputs2{1, 1, 2, 3};
  std::vector<std::unique_ptr<Box>> boxes2;
  auto result2 = play(inputs2, boxes2);
  REQUIRE(boxes2[2]->getWeight() == 2.2);
  REQUIRE(boxes2[3]->getWeight() == 3.3);

  std::vector<uint32_t> inputs3{1, 1, 2, 3, 5, 8, 13, 21};
  std::vector<std::unique_ptr<Box>> boxes3;
  auto result3 = play(inputs3, boxes3);
  REQUIRE(boxes3[2]->getWeight() == 15.2);
  REQUIRE(boxes3[3]->getWeight() == 24.3);

}


