#include <gtest/gtest.h>

extern "C" {
#include "func.h"
}


TEST(GraphTest, Init) {
    graph g;
    init_graph(&g, 5);
    EXPECT_EQ(g.cnt_v, 5);
    free_graph(&g);
}


TEST(GraphTest, AddEdge) {
    graph g;
    init_graph(&g, 3);
    add_edge(&g, 0, 1);
    EXPECT_EQ(g.matrix[0][1], 1);
    EXPECT_EQ(g.matrix[1][0], 0);
    free_graph(&g);
}


TEST(TopSort, SimpleDAG) {
    graph g;
    init_graph(&g, 3);
    add_edge(&g, 0, 1);
    add_edge(&g, 1, 2);

    int res[3];
    EXPECT_EQ(topological_sort(&g, res), 1);
    EXPECT_EQ(res[0], 0);
    EXPECT_EQ(res[1], 1);
    EXPECT_EQ(res[2], 2);
    free_graph(&g);
}


TEST(TopSort, Cycle) {
    graph g;
    init_graph(&g, 3);
    add_edge(&g, 0, 1);
    add_edge(&g, 1, 2);
    add_edge(&g, 2, 0);

    int res[3];
    EXPECT_EQ(topological_sort(&g, res), 0);
    free_graph(&g);
}


TEST(TopSort, ComplexDAG) {
    graph g;
    init_graph(&g, 6);
    add_edge(&g, 5, 2);
    add_edge(&g, 5, 0);
    add_edge(&g, 4, 0);
    add_edge(&g, 4, 1);
    add_edge(&g, 2, 3);
    add_edge(&g, 3, 1);

    int res[6];
    EXPECT_EQ(topological_sort(&g, res), 1);


    int pos4 = -1, pos5 = -1, pos1 = -1;
    for (int i = 0; i < 6; i++) {
        if (res[i] == 4) pos4 = i;
        if (res[i] == 5) pos5 = i;
        if (res[i] == 1) pos1 = i;
    }
    EXPECT_LT(pos4, pos1);
    EXPECT_LT(pos5, pos1);
    free_graph(&g);
}
