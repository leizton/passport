#include "basic.h"


/*

最小路径和

给定矩阵grid，如
{
  1,3,1
  1,5,1
  4,2,1
}
计算从 grid(1,1) 到 grid(m,n) 的最短路径

最优子结构
cost(x,y) = grid(x,y) + min{ cost(x-1,y), cost(x,y-1) }

*/


int minPathSum(vector<vector<int>>& grid) {
  if (grid.empty()) return 0;
  const int m = (int)grid.size(), n = (int)grid[0].size();

  vector<int>& row = grid[0];
  for (int i = 1; i < n; i++) {
    row[i] += row[i-1];
  }
  for (int i = 1; i < m; i++) {
    grid[i][0] += grid[i-1][0];
  }
  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
      grid[i][j] += std::min(grid[i-1][j], grid[i][j-1]);
    }
  }
  return grid[m-1][n-1];
}


void test() {
  vector<vector<int>> grid;
  grid.push_back({1,3,1});
  grid.push_back({1,5,1});
  grid.push_back({4,2,1});
  assert_eq(7, minPathSum(grid));
}