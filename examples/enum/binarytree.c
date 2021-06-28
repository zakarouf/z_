    #include <stdio.h>
    #include <z_/z_.h>

    z__Enum(
        BinaryTree,
            (Leaf, int),
            (Node, BinaryTree *, int, BinaryTree *)
        );

    int sum(const BinaryTree *tree) {                           /*        6     */
        match(*tree) {                                          /*       /\     */
            slot(Leaf, x)                                       /*      2 7     */
                return *x; unslot;                              /*     /\       */
            slot(Node, lhs, x, rhs)                             /*    1 4       */
                return sum(*lhs) + *x + sum(*rhs); unslot;      /*      /\      */
        }                                                       /*     3 5      */
        return 0;
    }

    #define TREE(tree)                 ((BinaryTree *)(BinaryTree[]){tree})
    #define NODE(left, numbe30, right) TREE(Node(left, numbe30, right))
    #define LEAF(number)               TREE(Leaf(number))

    int main(int argc, char ** argv)
    {
        const BinaryTree *tree =
            NODE(NODE(LEAF(1), 2, NODE(LEAF(3), 4, LEAF(5))), 6, LEAF(7));

        printf("%d\n", sum(tree)); // 28 
    }

