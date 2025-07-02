# programming_language
C++/ python
1、时间复杂度参考
参看文档[时间复杂度](./leetcode-master/problems/前序/时间复杂度.md)和[算法的时间与空间复杂度](https://zhuanlan.zhihu.com/p/50479555)
2、列表操作
- 在列表增删改查的第n个节点的时候用虚拟投节点的时候是操作cur->next（因为dummyHead指向的是cur）;
- 在列表插入第n个节点的时候，注意是先操作右边再操作左边（反之 dummyHead->next = newNode ;由于dummyHead->next指向被覆盖，newNde->next无法之前dummyHead->next的指向）
```CPP
class MyLinkedList {
public:
    struct ListNode
    {
        int val;
        ListNode* next;
        //一般写成对构造函数进行重载
		ListNode(int x):val(x),next(NULL){};
    };
    MyLinkedList() {
        //需要一开始的时候就定义虚拟头节点
        dummyHead = new ListNode(0);
        size = 0;
    }
    
    int get(int index) {
        if(index < 0 || index > size)
        {
            return -1;
        }
        //在列表增删改查的第n个节点的时候用虚拟投节点的时候是操作cur->next（因为dummyHead指向的是cur）
        ListNode* cur = dummyHead;
        while(index)
        {
            cur = cur->next;
            index--;
        }
        
        int tempVal = cur->next->val;

        return tempVal;
    }
    
    void addAtHead(int val) {

        //推荐这种写法
        ListNode* newNode = new ListNode(val);
        //在列表插入第n个节点的时候，注意是先操作右边再操作左边
        newNode->next = dummyHead->next;
        dummyHead->next = newNode;

		std::cout<<"dummyHead->next->val:"<<dummyHead->next->val<<std::endl;
		std::cout<<"dummyHead->next->next:"<<dummyHead->next->next<<std::endl;
        size++;
    }
    
    void addAtTail(int val) {

        ListNode* cur = dummyHead;
        while(cur->next != NULL)
        {
            cur = cur->next;
        }

        ListNode* newNode = new ListNode(val);
        //另外一种表达就是cur->next指向newNode
        cur->next = newNode;

        size++;
    }
    
    void addAtIndex(int index, int val) {
        if(index > size)
           return;

        ListNode* cur = dummyHead;
        while(index)
        {
            cur = cur->next;
            index--;
        }

        ListNode* newNode = new ListNode(val);

        newNode->next = cur->next;
        cur->next = newNode;
        
        size++;
    }
    
    void deleteAtIndex(int index) {
        if(index < 0 || index > size)
        {
            return;
        }

        ListNode* cur = dummyHead;
        while(index)
        {
            cur = cur->next;
            index--;
        }
        
        ListNode* tempNode = cur->next;
        cur->next = cur->next->next;
        delete tempNode;

        size--;
    }
	void printList() {
		ListNode* cur = dummyHead;
		while(cur->next != NULL)
		{
			std::cout << cur->next->val << " ";
			cur = cur->next;
		}
		std::cout << std::endl;
	}

	~MyLinkedList() {
		ListNode* cur = dummyHead;
		while(cur != NULL)
		{
			ListNode* temp = cur;
			cur = cur->next;
			delete temp;
		}
	}
private:
    ListNode* dummyHead;
    int size;
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
```   
二叉树的遍历    

![alt text](image.png)
```C++
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// 定义二叉树节点
struct TreeNode {
    string val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(const string& x) : val(x), left(nullptr), right(nullptr) {}
};

// 从输入流中递归构建二叉树（先序）
TreeNode* buildTree(istringstream& iss) {
    string val;
    if (!(iss >> val)) return nullptr;
    if (val == "#") return nullptr;

    TreeNode* node = new TreeNode(val);
    node->left = buildTree(iss);
    node->right = buildTree(iss);
    return node;
}

// 中序遍历
void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }
}

// 释放内存
void freeTree(TreeNode* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}

int main() {
    cout << "请输入二叉树的先序遍历（空节点用 # 表示，空格分隔）：\n";
    string input;
    getline(cin, input);
    istringstream iss(input);

    TreeNode* root = buildTree(iss);
    cout << "构建成功！中序遍历结果为：\n";
    inorder(root);
    cout << endl;

    freeTree(root);  // 防止内存泄漏
    return 0;
}

```
验证二叉搜索树
中序遍历下，输出的二叉搜索树节点的数值是有序序列
```C++
class Solution {
public:
    TreeNode* pre = NULL;
    bool isValidBST(TreeNode* root) {
        if(root == NULL)  return true;
        bool left_valid = isValidBST(root->left);
   
        std::cout<<"root->val: "<<root->val<<std::endl;
        if(pre != NULL && pre->val >= root->val) 
        {
            std::cout<<"pre->val: "<<pre->val<<" root->val："<<root->val<<std::endl;
            return false;
        }
        pre = root;


        bool right_valid = isValidBST(root->right);
        std::cout<<"left_valid: "<<left_valid<<" right_valid: "<<right_valid<<" root->val:"<<root->val<<std::endl;
        return left_valid&right_valid;
    }
};
int main()
{
    Solution s;
    TreeNode* root = new TreeNode(5);   
    root->left = new TreeNode(1);   
    root->right = new TreeNode(7);  
    // root->left->left = new TreeNode(4);
    // root->left->right = new TreeNode(5);    
    root->right->left = new TreeNode(3);            
    root->right->right = new TreeNode(6);   
    bool is_valid = s.isValidBST(root);
    return 0;
}/*  */
```
示意图   
![alt text](image-1.png)
输出left_valid和right_valid的回溯过程
![alt text](image-2.png)
