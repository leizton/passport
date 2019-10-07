#include "basic.h"

/*

# 单链表相加

给出两个非空的链表用来表示两个非负的整数。
位数是按逆序存储

# ex
{2, 4, 3} + {5, 6, 4, 1} = {7, 0, 8, 1}

*/

struct ListNode {
  int val;
  ListNode* next;

  ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
  if (l1 == nullptr) return l2;
  if (l2 == nullptr) return l1;

  ListNode *p1=l1, *p2=l2;
  int addition = 0, tmp;
  while (p1 != nullptr && p2 != nullptr) {
    tmp = p1->val + p2->val + addition;
    if (tmp >= 10) {
      p1->val = tmp - 10;
      addition = 1;
    } else {
      p1->val = tmp;
      addition = 0;
    }
    p1 = p1->next;
    p2 = p2->next;
  }

  ListNode* dst = l1;
  if (p2 != nullptr) {
    dst = l2;
    p1 = l1, p2 = l2;
    while (p1 != nullptr) {
      p2->val = p1->val;
      p1 = p1->next;
      p2 = p2->next;
    }
    p1 = p2;
  }

  if (addition > 0) {
    if (p1 == nullptr) {
      p1 = dst;
      while (p1->next != nullptr) {
        p1 = p1->next;
      }
      p1->next = new ListNode(addition);
    } else {
      while (addition > 0 && p1 != nullptr) {
        tmp = p1->val + addition;
        if (tmp >= 10) {
          p1->val = tmp - 10;
          addition = 1;
        } else {
          p1->val = tmp;
          addition = 0;
          break;
        }
        p2 = p1;
        p1 = p1->next;
      }
      if (addition > 0) {
        p2->next = new ListNode(addition);
      }
    }
  }

  return dst;
}

ListNode* buildList(vector<int>&& src) {
  if (src.empty()) {
    return new ListNode(0);
  }
  ListNode* dst = new ListNode(src[0]);
  ListNode* p = dst;
  for (size_t i = 1; i < src.size(); i++) {
    p->next = new ListNode(src[i]);
    p = p->next;
  }
  return dst;
}

void releaseList(ListNode** src) {
  if (src == nullptr) return;
  ListNode* l = *src;
  while (l != nullptr) {
    ListNode* p = l->next;
    delete l;
    l = p;
  }
  *src = nullptr;
}

void printList(ListNode* l) {
  ostringstream sout;
  for (; l != nullptr; l = l->next) {
    sout << l->val;
  }
  print(sout.str());
}

void test(vector<int>&& x1, vector<int>&& x2) {
  auto* l1 = buildList(std::move(x1));
  auto* l2 = buildList(std::move(x2));
  auto* ret = addTwoNumbers(l1, l2);
  printList(ret);
  releaseList(&l1);
  releaseList(&l2);
}

void test() {
  test({2, 4, 3}, {5, 6, 4, 1});  // 7081
  test({2, 4, 3}, {5, 6, 7});  // 7011
  test({1}, {9, 9, 9});  // 0001
}
