/**
 * @file asaphus_coding_challenge.cpp
 * @version 1.1
 * @copyright Copyright (c) 2022 Asaphus Vision GmbH
 *
 * The goal is to implement the mechanics of a simple game and write test cases for them.
 * The rules of the game are:
 * - There are two types of boxes, green and blue. 
 * - Both can absorb tokens of a given weight, which they add to their own total weight. 
 * - Both are initialized with a given initial weight.
 * - After a box absorbs a token weight, it outputs a score. 
 * - Green and blue boxes calculate the score in different ways:
 * - A green box calculates the score as the square of the mean of the 3 weights that it most recently absorbed (square of mean of all absorbed weights if there are fewer than 3).
 * - A blue box calculates the score as Cantor's pairing function of the smallest and largest weight that it has absorbed so far, i.e. pairing(smallest, largest), where pairing(0, 1) = 2
 * - The game is played with two green boxes with initial weights 0.0 and 0.1, and two blue boxes with initial weights 0.2 and 0.3.
 * - There is a list of input token weights. Each gets used in one turn.
 * - There are two players, A and B. Both start with a score of 0.
 * - The players take turns alternatingly. Player A starts.
 * - In each turn, the current player selects one of the boxes with the currently smallest weight, and lets it absorb the next input token weight. Each input weight gets only used once.
 * - The result of the absorption gets added to the current player's score.
 * - When all input token weights have been used up, the game ends, and the player with highest score wins.
 *
 * Task:
 * - Create a git repo for the implementation. Use the git repository to have a commit history.
 * - Implement all missing parts, marked with "TODO", including the test cases.
 * - Split the work in reasonable commits (not just one commit).
 * - Make sure the test cases succeed.
 * - Produce clean, readable code.
 *
 * Notes:
 * - Building and running the executable: g++ --std=c++14 asaphus_coding_challenge.cpp -o challenge && ./challenge
 * - Feel free to add a build system like CMake, meson, etc.
 * - Feel free to add more test cases, if you would like to test more.
 * - This file includes the header-only test framework Catch v2.13.9.
 * - A main function is not required, as it is provided by the test framework.
 */

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <numeric>
#include <vector>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"


class Box {
public:
  explicit Box(double initial_weight) : weight_(initial_weight) {}
  virtual ~Box() = default;  

  virtual void calculateScore(uint32_t input_weight, double score)  { }
  friend class Player;
  bool operator<(const Box& rhs) const { return weight_ < rhs.weight_; }

protected:
  double weight_;
};

enum class BoxType { Green, Blue };


class GreenBox : public Box {
public:
  GreenBox(double initial_weight) : Box(initial_weight) {}

  void calculateScore(uint32_t input_weight, double& score)  override {
    // Update weights based on input and existing values
    int first_empty_slot = -1;
    for (int i = 0; i < num_colors; ++i) {
      if (green_weights_[i] == -1.0) {
        first_empty_slot = i;
        break;
      }
    }

    if (first_empty_slot != -1) {
      green_weights_[first_empty_slot] = input_weight;
    } else { // Shift existing weights if all slots are full
      for (int i = 0; i <num_colors-1; i++) {
        green_weights_[i] = green_weights_[i + 1];
      }
      green_weights_[num_colors-1] = input_weight;
    }

    // Calculate mean of green weights and update score
    double cnt_color = 0, sum_weights = 0;
    for (int i = 0; i<num_colors; i++){
        if (green_weights_[i] != -1) {
            sum_weights+= green_weights_[i];
            cnt_color+= 1;
        }
    }
    double mean = sum_weights/cnt_color;
    score += std::pow(mean, 2);

  }

private:
  static const int num_colors = 3;  // Assuming there are always 3 colors
  double green_weights_[num_colors] = {-1.0, -1.0, -1.0}; 

};

class BlueBox : public Box {
public:
  BlueBox(double initial_weight) : Box(initial_weight) {}

  void calculateScore(uint32_t input_weight, double& score)  override {
    if (blue_max == -1.0 && blue_min == -1.0){
        blue_max = input_weight;
        blue_min = input_weight;
    }
    else if (input_weight > blue_max){ 
        blue_max = input_weight;
    }
    else if (input_weight < blue_min) {
        blue_min = input_weight;
    }
    score+= ((blue_max + blue_min)*(blue_max + blue_min + 1))/2 + blue_max;

  }

private:
    double blue_max{-1.0}, blue_min{-1.0}; 
};

class BoxFactory {
public:
  static std::unique_ptr<Box> createBox(BoxType type, double initial_weight) {
    switch (type) {
      case BoxType::Green:
        return std::make_unique<GreenBox>(initial_weight);
      case BoxType::Blue:
        return std::make_unique<BlueBox>(initial_weight);
      default:
        throw std::invalid_argument("Invalid box type");
    }
  }
};



class Player {
public:
  void takeTurn(uint32_t input_weight,
                const std::vector<std::unique_ptr<Box>>& boxes) {
    int min_index = min_weight_box(boxes);
    boxes[min_index]->calculateScore(input_weight, score_);

    // update the box weight as well
    boxes[min_index]->weight_ += input_weight;
  }

  double getScore() const { return score_; }

  int min_weight_box(const std::vector<std::unique_ptr<Box>>& boxes) {
    int min_index = 0;
    for (int index = 1; index < boxes.size(); index++ ){
        if (boxes[index]->weight_ < boxes[min_index]->weight_){
            min_index = index;
        }
    }
    return min_index;
  }

private:
  double score_{0.0};
};

std::pair<double, double> play(const std::vector<uint32_t>& input_weights) {
  std::vector<std::unique_ptr<Box>> boxes;
  boxes.push_back(BoxFactory::createBox(BoxType::Green, 0.0));
  boxes.push_back(BoxFactory::createBox(BoxType::Green, 0.1));
  boxes.push_back(BoxFactory::createBox(BoxType::Blue, 0.2));
  boxes.push_back(BoxFactory::createBox(BoxType::Blue, 0.3));

  // vector of players
  int num_players = 2;
  std::vector<Player> players(num_players);

  // iterate over the input_weights
  for (int weight_index = 0; weight_index < input_weights.size();) {
    for (int player_index = 0; player_index < players.size(); player_index++) {
      players[player_index].takeTurn(input_weights[weight_index], boxes);
      weight_index++;
    }
  }

  return {players[0].getScore(), players[1].getScore()};
}


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

TEST_CASE("Test absorption of green box", "[green]") {
  // TODO
}

TEST_CASE("Test absorption of blue box", "[blue]") {
  // TODO
}
