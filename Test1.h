#ifndef TEST1_H
#define TEST1_H
#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<queue>
using namespace std;


struct TreeNode {
  TreeNode* left;
  TreeNode* right;
  int data;
  TreeNode(int data) {
    this->data = data;
    this->left = 0;
    this->right = 0;
  }
};

struct ListNode {
  ListNode* next;
  int data;
  ListNode(int data) {
    this->data = data;
    this->next = 0;
  }
};

class Test1 {
  private:
    static bool isLLPalindrome(ListNode* head);
    static ListNode* ReverseLL(ListNode* head);
    static ListNode* FindMiddleLL(ListNode* head);
    static void FlipBinaryImage(vector<vector<int>>& image);
    static vector<int> MinHeightTree(int vertices, vector<vector<int>>& edges);
    static vector<int> FirstKMissingPositiveNums(int K, vector<int>& nums);
    static vector<vector<int>> KLargestPairs(vector<int>& L1, vector<int>& L2, int K);
    static int RotationCount(vector<int>& nums);
    static ListNode* RotateLL(ListNode* head, int K);
    static vector<TreeNode*> RightView(TreeNode* root);
    static int MaxPathSum(TreeNode* currentNode, int& globalMax);
    static int MaxPathSum(TreeNode* current);
  public:
    static void isLLPalindrome();
    static void FlipBinaryImage();
    static void FreqStack();
    static void MinHeightTree();
    static void FirstKMissingPositiveNums();
    static void KLargestPairs();
    static void RotationCount();
    static void RotateLL();
    static void RightView();
    static void MaxPathSum();
};

#endif