#include "basic.h"


#if comment(叶值的最小代价生成树)
按中序遍历二叉树的顺序给出叶节点的值数组arr
二叉树满足以下条件
  1. 非叶节点都有2个子节点
  2. 非叶节点的值 = max(左子树的叶节点) × max(右子树的叶节点)
计算所有可能的二叉树中非叶节点和的最小值
#endif

#if comment(任意数量的叶节点至少可以构成一种满足上述条件的二叉树)
设叶节点[l1 l2 l3 ...], 非叶节点[o1 o2 o3 ...]
这种二叉树是
   o1
  ↙  ↘
l1    o2
     ↙  ↘
   l2    o3_l3
        ↙  ↘
      l3    o4_l4
#endif

#if comment(分治递归化)
可以把叶节点 [l1 l2 l3 ... ln] 分成两部分, 一部分在root的左子树上, 一部分在root的右子树上
即: { (L, R); L=l[1,i], R=l[i+1,n], i∈[1,n) }
mct(L,R) = mct(L) + mct(R) + cost(root)
cost(root) = maxCost(L) × maxCost(R)
特别地, 只有2个叶节点的 mct = l1·l2, 只有1个叶节点的 mtc = 0
#endif


int mct(vector<int>& arr, int begin, int last, vector<vector<int>>& mct_memo, vector<vector<int>>& max_memo) {
  int ret = mct_memo[begin][last];
  if (ret >= 0) {
    return ret;
  }
  ret = numeric_limits<int>::max();
  for (int i = begin; i < last; i++) {
    int mct_l = mct(arr, begin, i, mct_memo, max_memo);
    int mct_r = mct(arr, i+1, last, mct_memo, max_memo);
    int max_l = max_memo[begin][i];
    int max_r = max_memo[i+1][last];
    int cur = mct_l + mct_r + max_l * max_r;
    ret = std::min(ret, cur);
  }
  mct_memo[begin][last] = ret;
  return ret;
}

int mctFromLeafValues(vector<int>& arr) {
  const int n = (int)arr.size();
  if (n == 1) {
    return 0;
  }
  if (n == 2) {
    return arr[0] * arr[1];
  }

  vector<vector<int>> max_memo;
  max_memo.resize(n);
  for (int i = 0; i < n; i++) {
    auto& v = max_memo[i];
    v.resize(n, -1);
    v[i] = arr[i];
    for (int j = i+1; j < n; j++) {
      v[j] = std::max(v[j-1], arr[j]);
    }
  }

  vector<vector<int>> mct_memo;
  mct_memo.resize(n);
  for (int i = 0; i < n; i++) {
    auto& v = mct_memo[i];
    v.resize(n, -1);
    v[i] = 0;  // mct(i, i)
    if (i < n-1) {
      v[i+1] = arr[i] * arr[i+1];  // mct(i, i+1)
    }
  }

  // 递归
  // return mct(arr, 0, n-1, mct_memo, max_memo);

  for (int j_st = 2; j_st < n; j_st++) {
    int i = 0;
    for (int j = j_st; j < n; j++, i++) {
      int mct_ij = INT32_MAX;
      for (int k = i; k < j; k++) {
        mct_ij = std::min(mct_ij, mct_memo[i][k] + mct_memo[k+1][j] + max_memo[i][k] * max_memo[k+1][j]);
      }
      mct_memo[i][j] = mct_ij;
    }
  }
  return mct_memo[0][n-1];
}

void test() {
  vector<int> arr{6,2,4};
  assert_eq(32, mctFromLeafValues(arr));

  arr = {15,13,5,3,15};
  assert_eq(500, mctFromLeafValues(arr));
}