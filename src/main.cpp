#include <array>
#include <format>
#include <iostream>
#include <utility>
#include <vector>

using std::cin, std::cout, std::endl, std::vector, std::pair, std::array,
    std::format;

constexpr auto knight_move_offsets()
{
  vector<pair<int, int>> offsets;

  for (int large_delta : {-2, 2}) {
    for (int small_delta : {-1, 1}) {
      offsets.emplace_back(large_delta, small_delta);
      offsets.emplace_back(small_delta, large_delta);
    }
  }
  return offsets;
}

void find_positions(int row, int col, int moves_left,
                    array<array<int, 8>, 8>& reachable,
                    const vector<pair<int, int>>& offsets)
{
  if (moves_left == 0) {
    reachable[row][col]++;
    return;
  }

  for (const auto& [row_off, col_off] : offsets) {
    int new_row = row + row_off;
    int new_col = col + col_off;

    if ((new_row >= 0) && (new_row < 8) && (new_col >= 0) && (new_col < 8)) {
      find_positions(new_row, new_col, moves_left - 1, reachable, offsets);
    }
  }
}

int main(int argc, char* argv[])
{
  int row, col, N;

  cout << "Enter starting row (0-7): ";
  cin >> row;
  cout << "Enter starting col (0-7): ";
  cin >> col;
  cout << "Enter number of moves: ";
  cin >> N;

  const auto knight_offsets = knight_move_offsets();

  array<array<int, 8>, 8> reachable{};

  find_positions(row, col, N, reachable, knight_offsets);

  cout << "   ";
  for (int display_col = 0; display_col < 8; display_col++) {
    cout << format("{:5}", display_col);
  }
  cout << '\n';

  for (int i = 0; i < 8; i++) {
    cout << format("{}  ", i);

    for (int j = 0; j < 8; j++) {
      cout << format("{:5}", reachable[i][j]);
    }
    cout << '\n';
  }

  return 0;
}
