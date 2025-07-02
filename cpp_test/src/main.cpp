#include<iostream>
#include<memory>
#include<vector>
#include<map>
#include<algorithm>
#include<string>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
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
}