/*
 * To change this license header, choose License Headers in Project Properties.
 * To chang/*
 e this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package src;

import java.util.ArrayList;
import sun.security.util.BitArray;

/**
 *
 * @author Espinas
 */
public class BST {

    /**
     * The tree root.
     */
    protected BinaryNode root;
    ArrayList<BinaryNode> nodes;
    ArrayList<Byte> values;
    ArrayList<Integer> freqs;

    /**
     * Construct the tree.
     */
    public BST(ArrayList<Byte> values, ArrayList<Integer> freqs) {
        this.nodes = new ArrayList<>();
        this.freqs = freqs;
        this.values = values;
        this.buildTree();
    }

    private int maxDepth(BinaryNode node) {
        if (node == null) {
            return (0);
        } else {
            // compute the depth of each subtree
            int lDepth = maxDepth(node.left);
            int rDepth = maxDepth(node.right);
            // use the larger one
            if (lDepth > rDepth) {
                return (lDepth + 1);
            } else {
                return (rDepth + 1);
            }
        }
    }

    public ArrayList<Boolean> generateCode(byte character) {
        return this.root.traverseTree(character, new ArrayList<Boolean>());
    }

    private ArrayList<BinaryNode> insertionSort(ArrayList<BinaryNode> nodeList) {
        ArrayList<BinaryNode> listToReturn = new ArrayList<>();
        for (int i = 0; i < nodeList.size(); i++) {
            listToReturn.add(nodeList.get(i));
        }
        int f = listToReturn.size();
        for (int i = 0; i < f; i++) {
            for (int j = i + 1; j < f; j++) {
                if (listToReturn.get(i).freq > (listToReturn.get(j).freq)) {
                    BinaryNode temp = listToReturn.get(i);
                    listToReturn.set(i, listToReturn.get(j));
                    listToReturn.set(j, temp);

                }
            }
        }
        return listToReturn;
    }

    private void buildTree() {
        for (int i = 0; i < freqs.size(); i++) {
            nodes.add(new BinaryNode(freqs.get(i), values.get(i)));
        }
        while (nodes.size() > 1) {
            ArrayList<BinaryNode> ordered = insertionSort(nodes);
            if (ordered.size() >= 2) {
                ArrayList<BinaryNode> taken = new ArrayList<>();
                taken.add(ordered.get(0));
                taken.add(ordered.get(1));

                BinaryNode parent = new BinaryNode(taken.get(0).freq + taken.get(1).freq, (byte) '*');
                parent.left = taken.get(0);
                parent.right = taken.get(1);
                nodes.remove(taken.get(0));
                nodes.remove(taken.get(1));
                nodes.add(parent);
            }
            this.root = nodes.get(0);
        }
    }
}

// Basic node stored in unbalanced binary search trees
class BinaryNode {

    BinaryNode left;         // Left child
    BinaryNode right;        // Right child
    byte character;        // Character of the node
    int freq;
    ArrayList<Boolean> reachCode = new ArrayList<>();

    BinaryNode(Integer freq, byte character) {
        this.freq = freq;
        this.character = character;
        left = right = null;
    }

    public ArrayList<Boolean> getReachCode() {
        return reachCode;
    }

    public void setChar(byte c) {
        character = c;
    }

    public ArrayList<Boolean> traverseTree(Byte p, ArrayList<Boolean> a) {
        if (this.isLast()) {
            if (this.character == p) {
                return a;
            } else {
                return null;
            }
        } else {
            ArrayList<Boolean> leftList = null;
            ArrayList<Boolean> rightList = null;
            if (this.left != null) {
                ArrayList<Boolean> _leftList = new ArrayList<>();
                _leftList.addAll(a);
                _leftList.add(false);
                leftList = left.traverseTree(p, _leftList);
            }
            if (this.right != null) {
                ArrayList<Boolean> _rightList = new ArrayList<>();
                _rightList.addAll(a);
                _rightList.add(true);
                rightList = right.traverseTree(p, _rightList);
            }
            if (leftList != null) {
                return leftList;
            } else {
                return rightList;
            }
        }
    }

    public boolean isLast() {
        if (this.left != null && this.right != null) {
            return false;
        }
        return true;
    }

}
