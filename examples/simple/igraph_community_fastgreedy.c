/* -*- mode: C -*-  */
/* 
   IGraph library.
   Copyright (C) 2006  Gabor Csardi <csardi@rmki.kfki.hu>
   MTA RMKI, Konkoly-Thege Miklos st. 29-33, Budapest 1121, Hungary
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc.,  51 Franklin Street, Fifth Floor, Boston, MA 
   02110-1301 USA

*/

#include <igraph.h>

void show_results(igraph_t *g, igraph_vector_t *mod, igraph_matrix_t *merges, FILE* f) {
  long int i;
  igraph_vector_t membership;

  igraph_vector_init(&membership, 0);

  i=igraph_vector_which_max(mod);
  fprintf(f, "Modularity:  %f\n", VECTOR(*mod)[i]);
  igraph_community_to_membership(g, merges, i, &membership, 0);
  printf("Membership: ");
  for (i=0; i<igraph_vector_size(&membership); i++) {
    printf("%li ", (long int)VECTOR(membership)[i]);
  }
  printf("\n");

  igraph_vector_destroy(&membership);
}

int main() {
  igraph_t g;
  igraph_vector_t modularity;
  igraph_matrix_t merges;
  FILE *f;

  igraph_vector_init(&modularity,0);
  igraph_matrix_init(&merges,0,0);
  igraph_small(&g, 5, IGRAPH_UNDIRECTED, 
	       0,1,0,2,0,3,0,4, 1,2,1,3,1,4, 2,3,2,4, 3,4,
	       5,6,5,7,5,8,5,9, 6,7,6,8,6,9, 7,8,7,9, 8,9,
         0,5, -1);
  igraph_community_fastgreedy(&g, &merges, &modularity);
  show_results(&g, &modularity, &merges, stdout); 
  igraph_destroy(&g);

  /* Zachary Karate club */

  igraph_small(&g, 0, IGRAPH_UNDIRECTED, 
	       0,  1,  0,  2,  0,  3,  0,  4,  0,  5,
	       0,  6,  0,  7,  0,  8,  0, 10,  0, 11,
	       0, 12,  0, 13,  0, 17,  0, 19,  0, 21,
	       0, 31,  1,  2,  1,  3,  1,  7,  1, 13,
	       1, 17,  1, 19,  1, 21,  1, 30,  2,  3,
	       2,  7,  2,  8,  2,  9,  2, 13,  2, 27,
	       2, 28,  2, 32,  3,  7,  3, 12,  3, 13,
	       4,  6,  4, 10,  5,  6,  5, 10,  5, 16,
	       6, 16,  8, 30,  8, 32,  8, 33,  9, 33,
	       13, 33, 14, 32, 14, 33, 15, 32, 15, 33,
	       18, 32, 18, 33, 19, 33, 20, 32, 20, 33,
	       22, 32, 22, 33, 23, 25, 23, 27, 23, 29,
	       23, 32, 23, 33, 24, 25, 24, 27, 24, 31,
	       25, 31, 26, 29, 26, 33, 27, 33, 28, 31,
	       28, 33, 29, 32, 29, 33, 30, 32, 30, 33,
	       31, 32, 31, 33, 32, 33,
	       -1);
  igraph_community_fastgreedy(&g, &merges, &modularity);
  show_results(&g, &modularity, &merges, stdout); 
  igraph_destroy(&g);
   
  /* Simple disconnected graph with isolates */
  igraph_small(&g, 9, IGRAPH_UNDIRECTED,
	       0,  1,  0,  2,  0,  3,  1,  2,  1,  3,  2,  3,
	       4,  5,  4,  6,  4,  7,  5,  6,  5,  7,  6,  7,
	       -1);
  igraph_community_fastgreedy(&g, &merges, &modularity);
  show_results(&g, &modularity, &merges, stdout); 
  igraph_destroy(&g);

  igraph_vector_destroy(&modularity);
  igraph_matrix_destroy(&merges);
  
  return 0;
}
