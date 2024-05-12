#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <numeric>
#include <vector>
#include <cmath>

class Box {
public:
  explicit Box(double initial_weight) : weight_(initial_weight) {}
  virtual ~Box() = default;  

  virtual void calculateScore(uint32_t input_weight, double& score)  { }
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

