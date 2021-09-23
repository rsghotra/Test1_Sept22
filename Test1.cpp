#include "Test1.h"

/*
Q1: IsLLPalindrome
*/
ListNode* Test1::FindMiddleLL(ListNode* head) {
  ListNode* slow = head;
  ListNode* fast = head;
  while(fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}

ListNode* Test1::ReverseLL(ListNode* head) {
  ListNode* current = head;
  ListNode* previous = 0;
  ListNode* next = 0;
  while(current != 0) {
    next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }
  return previous;
}

bool Test1::isLLPalindrome(ListNode* head) {
  if(head == 0 || head->next == 0) return true;
  ListNode* middle = FindMiddleLL(head);
  ListNode* reversedHead = ReverseLL(middle);
  ListNode* copyReversedHead = reversedHead;
  while(head != 0 && reversedHead != 0) {
    if(head->data != reversedHead->data) {
      break;
    }
    head = head->next;
    reversedHead = reversedHead->next;
  }
  //1->2->2->1
  ReverseLL(copyReversedHead);
  //normal guy condition will fail for this 1->2->2->1 case;
  // if(head == 0 && reversedHead == 0) {
  //   return true;
  // }
  if(head == 0 || reversedHead == 0) {
    return true;
  }
  return false;
}

void Test1::isLLPalindrome() {
  ListNode* head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(2);
  head->next->next->next = new ListNode(1);
  //head->next->next->next->next = new ListNode(2);
  if(isLLPalindrome(head)) cout << "List is Palindrome" << endl;
  else cout << "List is not a palindrome" << endl;
}

/*
Flip Binary Image
T(N): O(N^2)
S(N): O(1)
*/

void Test1::FlipBinaryImage(vector<vector<int>>& image) {
  for(int row = 0; row < image.size(); row++) {
    for(int col = 0; col < (image[0].size()+1)/2; col++) {
      int temp = image[row][col] ^ 1;
      image[row][col] = image[row][image[0].size() - col - 1] ^ 1;
      image[row][image[0].size() - col - 1] = temp;
    }
  }
}

void Test1::FlipBinaryImage() {
  vector<vector<int>> image{{1,1,0,0}, {1,0,0,1}, {0,1,1,1}, {1,0,1,0}};

  cout << "Printing Image before flipping & inverting: " << endl;
  for(auto entry: image) {
    for(auto val: entry) {
      cout << val << " ";
    }
    cout << endl;
  }
  FlipBinaryImage(image);
  cout << "Printing Image AFTER flipping & inverting: " << endl;
  for(auto entry: image) {
    for(auto val: entry) {
      cout << val << " ";
    }
    cout << endl;
  }
}

/*
Frequency Stack:

Element should be popped which is most frequenct at the moment;
if same frequency return with high sequence number

push(int num)
pop()

Element : val, sequence, frequency

*/
class Element{
  public:
    int data = 0;
    int sequenceNumber = 0;
    int frequency = 0;
    Element(int data, int sequenceNumber, int frequency) {
      this->data = data;
      this->sequenceNumber = sequenceNumber;
      this->frequency = frequency;
    }
};

class FrequencyStack {
  struct FrequencyCompare {
    bool operator()(const Element& e1, const Element& e2) {
      if(e1.frequency == e2.frequency) {
        return e1.sequenceNumber < e2.sequenceNumber;
      }
      return e1.frequency < e2.frequency;
    }
  };
private:
  int sequenceNumber = 0;
  unordered_map<int, int> frequencies;
  priority_queue<Element, vector<Element>, FrequencyCompare> maxHeap;
public:
  virtual void push(int num) {
    frequencies[num]++;
    maxHeap.push({num,this->sequenceNumber++, frequencies[num]});
  }

  virtual int pop() {
    int num = maxHeap.top().data;
    maxHeap.pop();
    if(frequencies[num] > 1) {
      frequencies[num]--;
    }else {
      frequencies.erase(num);
    }
    return num;
  }
};

void Test1::FreqStack() {
  FrequencyStack frequencyStack;
  frequencyStack.push(1);
  frequencyStack.push(2);
  frequencyStack.push(3);
  frequencyStack.push(2);
  frequencyStack.push(1);
  frequencyStack.push(2);
  frequencyStack.push(5);
  cout << frequencyStack.pop() << endl;
  cout << frequencyStack.pop() << endl;
  cout << frequencyStack.pop() << endl;
}

/*
Minimum Height Tree

T(N): O(V+E); since each vertex is processed atmost only once.
S(N): O(V+E); since we are storing all vertices and edges in an adjacency list;
*/

vector<int> Test1::MinHeightTree(int vertices, vector<vector<int>>& edges) {
  //initializegraph
  unordered_map<int, vector<int>> graph;
  unordered_map<int, int> inDegree;
  vector<int> minHeightTreeNodes;
  for(int i = 0; i < vertices; i++) {
    graph[i] = vector<int>();
    inDegree[i] = 0;
  }

  //buildgraph
  for(int i = 0; i < edges.size(); i++) {
    int parent = edges[i][0];
    int child = edges[i][1];

    graph[parent].push_back(child);
    graph[child].push_back(parent);

    inDegree[parent]++;
    inDegree[child]++;
  }

  //find sources with inDegree=1; because leaves will never give us MinHeightTree;
  //leaves will have InDegree = 1; root's InDegree = 0 while any middle's inDegree will be greater than 1
  //this is happening due to directed graph
  queue<int> leaves;
  for(auto entry: inDegree) {
    if(entry.second == 1) {
      leaves.push(entry.first);
    }
  }

  int currentNodes = vertices;
  while(currentNodes > 2) {
    int leavesSize = leaves.size();
    currentNodes -= leavesSize;
    for(int i = 0; i < leavesSize; i++) {
      int node = leaves.front();
      leaves.pop();
      vector<int> children = graph[node];
      for(auto child: children) {
        inDegree[child]--;
        if(inDegree[child] == 1) {
          //it is now leaves
          leaves.push(child);
        }
      }
    }
  }
  while(leaves.empty() == false) {
    minHeightTreeNodes.push_back(leaves.front());
    leaves.pop();
  }
  return minHeightTreeNodes;
}

void Test1::MinHeightTree() {
  vector<vector<int>> vec = {{0, 1}, {1, 2}, {1, 3}, {2, 4}};
  vector<int> result = MinHeightTree(5, vec);
  cout << "Roots of MHTs: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;

  vec = {{0, 1}, {0, 2}, {2, 3}};
  result = MinHeightTree(4, vec);
  cout << "Roots of MHTs: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;

  vec = {{0, 1}, {1, 2}, {1, 3}};
  result = MinHeightTree(4, vec);
  cout << "Roots of MHTs: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;
}

/*
First K Missing Positive Numbers;
*/

void Swap(vector<int>& nums, int i, int j) {
  int temp = nums[i];
  nums[i] = nums[j];
  nums[j] = temp;
}

vector<int> Test1::FirstKMissingPositiveNums(int k, vector<int>& nums){
  vector<int> missingNums;
  //perform cyclic sort on the numsl
  //nums[i] = i+1
  int i = 0;
  while(i < nums.size()) {
    if(nums[i] - 1 < nums.size() && nums[i] > 0 && nums[i] != i+1 && nums[i] != nums[nums[i] - 1]) {
      Swap(nums, i, nums[i]-1);
    } else {
      i++;
    }
  }
  for(int num: nums) {
    cout << num << " ";
  }
  cout << endl;
  unordered_set<int> seenNums;
  for(int j = 0; j < nums.size() && k > 0; j++) {
    if(nums[j] != j+1) {
      missingNums.push_back(j+1);
      k--;
      seenNums.insert(nums[j]);
    }
  }

  int seed = 1;
  while(k > 0) {
    int candidate = seed + nums.size();
    if(seenNums.find(candidate) == seenNums.end()) {
      k--;
      missingNums.push_back(candidate);
    }
    seed++;
  }
  return missingNums;
}

void Test1::FirstKMissingPositiveNums() {
  vector<int> nums{2,3,4};
  vector<int> result = FirstKMissingPositiveNums(3, nums);
  for(int num: result) {
    cout << num << " ";
  }
  cout << endl;
}

/*
K Largest Pairs
*/

struct MaxSumCompare {
  bool operator()(const vector<int>& x, const vector<int>& y) {
    return x[0] + x[1] > y[0] + y[1];
  }
};

vector<vector<int>> Test1::KLargestPairs(vector<int>& L1, vector<int>& L2, int K) {
  vector<vector<int>> result;
  //as arrays are sorted in descending order; it means the largest pairs could be found
  //only until index K of both the arrays at most;
  priority_queue<vector<int>, vector<vector<int>>, MaxSumCompare> minHeap;
  for(int i = 0; i < L1.size() && i < K; i++) {
    for(int j = 0; j < L2.size() && j < K; j++) {
      int pairSum = L1[i] + L2[j];
      if(minHeap.size() < K) {
        minHeap.push({L1[i], L2[j]});
      } else if(minHeap.top()[0] + minHeap.top()[1] < pairSum) {
        minHeap.pop();
        minHeap.push({L1[i], L2[j]});
      } else if(minHeap.top()[0] + minHeap.top()[1] > pairSum) {
        break;
      }
    }
  }
  while(minHeap.empty() == false) {
    result.push_back(minHeap.top());
    minHeap.pop();
  }
  return result;
}

void Test1::KLargestPairs() {
  vector<int> L1{9,8,2};
  vector<int> L2{6,3,1};
  vector<vector<int>> result = KLargestPairs(L1, L2, 3);
  for(auto vect: result) {
    cout << " [";
    for(int num: vect) {
      cout << num << " ";
    }
    cout << "] ";
  }
  cout << endl;
}

/*
Find Rotation Count of Array
*/
int Test1::RotationCount(vector<int>& nums) {
  int start = 0;
  int end = nums.size() - 1;
  while(start <= end) {
    int mid = start + (end - start)/2;
    if(mid < end && nums[mid] > nums[mid+1]) {
      return mid+1;
    }
    if(mid > start && nums[mid-1] > nums[mid]) {
      return mid;
    }

    if(nums[mid] < nums[end]) {
      //right side is sorted;
      end = mid-1;
    } else {
      start = mid+1;
    }
  }
  return 0;
}

void Test1::RotationCount() {
  vector<int> nums{4,5,7,9,10,-1,2};
  cout << "Array has been rotated: " << RotationCount(nums) << endl;
}

/*
Rotate Linked List By K
*/

ListNode* Test1::RotateLL(ListNode* head, int K) {
  if(head == 0) return head;
  int len = 0;
  ListNode* ptr = head;
  ListNode* prev = 0;
  while(ptr != 0) {
    len++;
    prev = ptr;
    ptr = ptr->next;
  }
  prev->next = head;
  ptr = head;
  prev = 0;
  K = K%len;
  int skipLength = len - K;
  while(skipLength > 0) {
    prev = ptr;
    ptr = ptr->next;
    skipLength--;
  }
  prev->next = 0;
  head = ptr;
  return head;
}

void Test1::RotateLL() {
  ListNode *head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);
  head->next->next->next->next = new ListNode(5);
  head->next->next->next->next->next = new ListNode(6);

  ListNode *result = RotateLL(head, 3);
  cout << "\nNodes of the rotated LinkedList are: ";
  while (result != nullptr) {
    cout << result->data << " ";
    result = result->next;
  }
  cout << endl;
}

/*
Right View of BT
*/

vector<TreeNode*> Test1::RightView(TreeNode* root) {
  vector<TreeNode*> result;
  queue<TreeNode*> inputs;
  inputs.push(root);

  while(!inputs.empty()) {
    int levelSize = inputs.size();
    for(int i = 0; i < levelSize; i++) {
      TreeNode* node = inputs.front();
      inputs.pop();
      if(i == levelSize - 1) {
        result.push_back(node);
      }
      if(node->left) {
        inputs.push(node->left);
      }
      if(node->right) {
        inputs.push(node->right);
      }
    }
  }
  return result;
}

void Test1::RightView() {
  cout << "\nRight view of BT: " << endl;
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(9);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  root->left->left->left = new TreeNode(3);
  vector<TreeNode *> result = RightView(root);
  for (auto node : result) {
    cout << node->data << " ";
  }
  cout << endl;
}

/*
Max Path Sum
*/

int Test1::MaxPathSum(TreeNode* current) {
  int globalMax = INT32_MIN;
  MaxPathSum(current, globalMax);
  return globalMax;
}

int Test1::MaxPathSum(TreeNode* current, int& globalMax) {
  if(current == 0) {
    return 0;
  }

  int leftTreeMaxSum = MaxPathSum(current->left, globalMax);
  int rightTreeMaxSum = MaxPathSum(current->right, globalMax);

  //ignoring negative paths;
  leftTreeMaxSum = max(leftTreeMaxSum, 0);
  rightTreeMaxSum = max(rightTreeMaxSum, 0);

  //root's max path sum
  int localMax = leftTreeMaxSum + rightTreeMaxSum + current->data;
  globalMax = max(globalMax, localMax);
  //any path going through the root
  return max(leftTreeMaxSum, rightTreeMaxSum) + current->data;
}

void Test1::MaxPathSum() {
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  cout << "Maximum Path Sum: " << MaxPathSum(root) << endl;
  
  root->left->left = new TreeNode(1);
  root->left->right = new TreeNode(3);
  root->right->left = new TreeNode(5);
  root->right->right = new TreeNode(6);
  root->right->left->left = new TreeNode(7);
  root->right->left->right = new TreeNode(8);
  root->right->right->left = new TreeNode(9);
  cout << "Maximum Path Sum: " << MaxPathSum(root) << endl;
  
  root = new TreeNode(-1);
  root->left = new TreeNode(-3);
  cout << "Maximum Path Sum: " << MaxPathSum(root) << endl;
}