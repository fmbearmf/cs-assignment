#include <iostream>
#include <utility>
#include <vector>

using namespace std;

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
                    vector<pair<int, int>>& path,
                    vector<vector<pair<int, int>>>& all_paths,
                    const vector<pair<int, int>>& offsets)
{
  path.emplace_back(row, col);

  if (moves_left == 0) {
    all_paths.push_back(path);
    path.pop_back();
    return;
  }

  vector<pair<int, int>> valid_next_positions;
  for (const auto& [row_off, col_off] : offsets) {
    int new_row = row + row_off;
    int new_col = col + col_off;

    if ((new_row >= 0) && (new_row < 8) && (new_col >= 0) && (new_col < 8)) {
      valid_next_positions.emplace_back(new_row, new_col);
    }
  }

  for (const auto& [new_row, new_col] : valid_next_positions) {
    find_positions(new_row, new_col, moves_left - 1, path, all_paths, offsets);
  }

  path.pop_back();
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

  vector<pair<int, int>> path;
  vector<vector<pair<int, int>>> all_paths;

  find_positions(row, col, N, path, all_paths, knight_offsets);

  for (auto& path : all_paths) {
    for (size_t i = 0; i < path.size(); i++) {
      if (i > 0) {
        cout << " -> ";
      }

      cout << '(' << path[i].first << ", " << path[i].second << ')';
    }
    cout << '\n';
  }

  return 0;
}
