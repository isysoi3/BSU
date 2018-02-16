using System;
using System.Collections.Generic;
using System.IO;

namespace acm
{
    class BST
    {
        public class Node
        {
            public Node left, right;
            public int value, depth;
            public bool way;

            public Node(int val, int dep)
            {
                left = right = null;
                value = val;
                depth = dep;
                way = false;
            }
        }

        public Node root;
        public int MinWay;
        public SortedSet<int> AvarageValues;

        public BST()
        {
            root = null;
            MinWay = 100000;
            AvarageValues = new SortedSet<int>();
        }

        public void Insert(int val)
        {
            if (root == null)
                root = new Node(val, 0);
            InsertNode(root, val);
        }

        private void InsertNode(Node node, int val)
        {
            if (val < node.value)
                if (node.left != null)
                    InsertNode(node.left, val);
                else
                    node.left = new Node(val, node.depth + 1);
            else if (val > node.value)
                if (node.right != null)
                    InsertNode(node.right, val);
                else
                    node.right = new Node(val, node.depth + 1);
        }

        public void Delete(int val)
        {
            Delete(ref root, val);
        }

        private void Delete(ref Node node, int val)
        {
            if (node == null)
                return;
            if (val < node.value)
                Delete(ref node.left, val);
            else if (val > node.value)
                Delete(ref node.right, val);
            else if (node.left != null && node.right != null)
            {
                node.value = Max(node.left).value;
                Delete(ref node.left, node.value);
            }
            else if (isList(node))
                node = null;
            else if (node.left != null)
                node = node.left;
            else
                node = node.right;
        }

        private Node Max(Node node)
        {
            return node.right == null ? node : Max(node.right);
        }

        public void PreOrderedTraverse(Node node, StreamWriter s)
        {
            if (node == null)
                return;
            s.WriteLine(node.value);
            PreOrderedTraverse(node.left, s);
            PreOrderedTraverse(node.right, s);
        }

        public void FindMinWay(Node node)
        {
            if (node == null)
                return;
            if (isList(node) && node.depth < MinWay)
                MinWay = node.depth;
            FindMinWay(node.left);
            FindMinWay(node.right);
        }

        private bool isList(Node node)
        {
            return node.left == null && node.right == null;
        }

        public void MarkNodes(Node node)
        {
            if (node == null)
                return;

            MarkNodes(node.left);
            if (node.left != null && node.left.way)
                node.way = true;

            MarkNodes(node.right);
            if (node.right != null && node.right.way)
                node.way = true;

            if (isList(node) && node.depth == MinWay)
                node.way = true;
        }

        public void FindAverageValue()
        {
            FindAverageValue(root, 0, MinWay);
        }

        private void FindAverageValue(Node node, int start, int end)
        {
            if (node == null)
                return;
            if (node.way && ((start == MinWay / 2 && start == end) ||
                             (end == MinWay / 2 && node.left != null && node.left.way) ||
                             (start == MinWay / 2 && node.right != null && node.right.way)))
                AvarageValues.Add(node.value);
            FindAverageValue(node.left, start, end - 1);
            FindAverageValue(node.right, start + 1, end);
        }


        class Program
        {
            static void Main(string[] args)
            {
                BST bst = new BST();
                using (StreamReader s = new StreamReader("tst.in"))
                {
                    while (s.EndOfStream == false)
                        bst.Insert(int.Parse(s.ReadLine()));
                }
                bst.FindMinWay(bst.root);
                Console.WriteLine(bst.MinWay);
                if (((bst.MinWay + 1) & 1) == 1)
                {
                    bst.MarkNodes(bst.root);
                    bst.FindAverageValue();
                    foreach (var x in bst.AvarageValues)
                        bst.Delete(x);
                }
                using (StreamWriter s = new StreamWriter("tst.out"))
                {
                    bst.PreOrderedTraverse(bst.root, s);
                }


            }
        }
    }
}