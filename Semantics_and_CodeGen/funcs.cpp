#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

  // all of your legacy C code here

  int foo(int a, int b)
  {
    printf("a + b is : %d\n", a + b);
    return a + b;
  }

  void main_bfs(int *matrix, int size, int root, int *bfs_final)
  {
    int visited_bfs[1000];
    int pos_bfs = 0;
    int qu[1000];
    int front = 0;
    int back = 0;

    bfs_final[pos_bfs] = root;
    pos_bfs++;
    visited_bfs[root] = 1;
    qu[back] = root;
    back++;
    while (front != back)
    {
      int t = qu[front];
      front++;
      for (int i = 0; i < size; i++)
      {
        if (*((matrix + t * size) + i) == 1 && visited_bfs[i] == 0)
        {
          bfs_final[pos_bfs] = i;
          pos_bfs++;
          visited_bfs[i] = 1;
          qu[back] = i;
          back++;
        }
      }
    }
    auto ret = bfs_final;
    while (size--)
    {
      printf("%d ", *ret);
      ret++;
    }
    printf("\n");
  }

  // int visited_dfs[1000];
  // int dfs_final[1000];
  // int pos_dfs = 0;

  // void sub_DFS(int *matrix, int size, int root)
  // {
  //   dfs_final[pos_dfs] = root;
  //   pos_dfs++;
  //   visited_dfs[root] = 1;
  //   for (int j = 0; j < size; j++)
  //   {
  //     if (*((matrix + root * size) + j) == 1 && !visited_dfs[j])
  //     {
  //       sub_DFS(matrix, size, j);
  //     }
  //   }
  // }

  int *main_dfs(int *matrix, int size, int root)
  {
    // sub_DFS(matrix, size, root);
    printf("DFS func in funcs.cpp\n");
    return nullptr;
  }

#ifdef __cplusplus
}
#endif