#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
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
    for (int i = 0; i < size; i++)
      bfs_final[i]++;
    // auto ret = bfs_final;
    // while (size--)
    // {
    //   printf("%d ", *ret);
    //   ret++;
    // }
    // printf("\n");
  }

  void main_dfs(int *matrix, int size, int root, int *dfs_final)
  {
    int visited_dfs[size];
    for (int i = 0; i < size; i++)
    {
      visited_dfs[i] = 0;
    }
    int pos_dfs = 0;
    int st[1000];
    int top = 0;
    st[top] = root;
    top++;
    while (top)
    {
      int t = st[top - 1];
      top--;
      visited_dfs[t] = 1;
      dfs_final[pos_dfs] = t;
      pos_dfs++;
      for (int i = 0; i < size; i++)
      {
        if (*((matrix + t * size) + i) == 1 && visited_dfs[i] == 0)
        {
          st[top] = i;
          top++;
        }
      }
    }
    for (int i = 0; i < size; i++)
    {
      // printf("%d ",dfs_final[i]);
      dfs_final[i]++;
    }
    printf("\n");
  }

  int has_cycle(int *matrix, int size)
  {
    int bfs_final[1000];
    int parent_arr[size];
    for (int i = 0; i < size; i++)
    {
      parent_arr[i] = -1;
    }
    int visited_bfs[1000];
    int qu[1000];
    int front = 0;
    int back = 0;

    visited_bfs[0] = 1;
    qu[back] = 0;
    back++;
    while (front != back)
    {
      int t = qu[front];
      front++;
      for (int i = 0; i < size; i++)
      {
        if (*((matrix + t * size) + i) == 1)
        {
          if (!visited_bfs[i])
          {
            visited_bfs[i] = 1;
            qu[back] = i;
            parent_arr[i] = t;
          }
          else if (parent_arr[i] != t)
          {
            return 1;
          }
        }
      }
    }
    return 0;
  }

  // int min_key(int key[], bool mst_set[], int size)
  // {
  //   int min = INT_MAX;
  //   int min_index;

  //   for(int v = 0;v<size;v++)
  //   {
  //     if(mst_set[v] == false && key[v] < min)
  //     {
  //       min = key[v];
  //       min_index = v;
  //     }
  //   }
  //   return min_index;
  // }
  // void prims_algo(int * matrix, int size)
  // {
  //   int parent[size];
  //   int key[size];
  //   bool mst_set[size];

  //   for(int i = 0;i<size;i++)
  //   {
  //     key[i] = INT_MAX;
  //     mst_set[i] = false;
  //   }

  //   key[0] = 0;
  //   parent[0] = -1;
  //   for(int count = 0;count < size-1;count++)
  //   {
  //     int u = min_key(key,mst_set);
  //     mst_set[u] = true;
  //     for(int v = 0; v< size;v++)
  //     {
  //       if(*((matrix + u*size)+v) && mst_set[v] == false
  //       && *((matrix + u*size)+v) < key[v] )
  //       {
  //         parent[v] = u;
  //         key[v] = *((matrix + u*size)+v);
  //       }
  //     }
  //   }
  //   return;
  // }

  void print()
  {
    printf("\n");
  }

  void print_i(int a)
  {
    printf("%d ", a);
    return;
  }

  void print_f(double a)
  {
    printf("%lf ", a);
    return;
  }

  void dijkstras(int *matrix, int size, int root, int *dists)
  {
    bool sptSet[size];
    for (int i = 0; i < size; i++)
    {
      dists[i] = INT_MAX, sptSet[i] = false;
    }
    dists[root] = 0;
    for (int count = 0; count < size - 1; count++)
    {
      int min = INT_MAX, min_index;

      for (int v = 0; v < size; v++)
      {
        if (sptSet[v] == false && dists[v] <= min)
        {
          min = dists[v], min_index = v;
        }
      }

      int u = min_index;
      sptSet[u] = true;
      for (int v = 0; v < size; v++)
      {
        if (!sptSet[v] && *((matrix + u * size) + v) && dists[u] != INT_MAX &&
            dists[u] + *((matrix + u * size) + v) < dists[v])
        {
          dists[v] = dists[u] + *((matrix + u * size) + v);
        }
      }
    }
    for (int v = 0; v < size; v++)
    {
      printf("%d ", dists[v]);
    }
    printf("\n");
  }

#ifdef __cplusplus
}
#endif