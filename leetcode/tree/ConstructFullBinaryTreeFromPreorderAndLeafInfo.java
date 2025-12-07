

/** Construct a full binary tree from the preorder sequence with leaf node information
 * 
 * preorder = [1, 2, 4, 5, 3, 6, 8, 9, 7]
 * isLeaf   = [0, 0, 1, 1, 0, 0, 1, 1, 1]
 *            (0 = internal, 1 = leaf)
 * 
 * Because the tree is full (every internal node has exactly 2 children),
 * and preorder + leaf info is enough to reconstruct uniquely.
 * 
 */

class TreeNode {
     int val;
     TreeNode left;
     TreeNode right;
     TreeNode() {}
     TreeNode(int val) { this.val = val; }
     TreeNode(int val, TreeNode left, TreeNode right) {
         this.val = val;
         this.left = left;
         this.right = right;
     }
}

public class ConstructFullBinaryTreeFromPreorderAndLeafInfo {
    private int idx;

    private TreeNode helper(int[] preorder, boolean[] isLeaf) {
        if (idx >= preorder.length) return null;

        TreeNode root = new TreeNode(preorder[idx]);

        if (isLeaf[idx]) { // a leaf
            idx++;
            return root;
        }

        // internal node
        idx++;
        root.left = helper(preorder, isLeaf);
        root.right = helper(preorder, isLeaf);

        return root;
    }
    public TreeNode construct(int[] preorder, boolean[] isLeaf) {
        idx = 0;
        return helper(preorder, isLeaf);
    }

    private void inorder(TreeNode root) {
        if (root == null) return;

        inorder(root.left);
        System.out.println(root.val + " ");
        inorder(root.right);
    }
    private void test1() {
        int[] preorder = new int[]{1, 2, 4, 5, 3, 6, 8, 9, 7};
        boolean[] isLeaf   = new boolean[]{false, false, true, true, false, false, true, true, true};
        TreeNode res = construct(preorder, isLeaf);

        // inorder check
        inorder(res);
    }

    public static void main(String[] args) {
        Solution_1 s = new Solution_1();
        s.test1();
    }
} 

