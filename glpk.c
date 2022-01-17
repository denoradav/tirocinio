
/* sample.c */

#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>

int main(void) {   
    glp_prob *lp;
    int ia[1+1000], ja[1+1000];
    double ar[1+1000], z, x1, x2, x3, x4, x5;
    lp = glp_create_prob();
    glp_set_prob_name(lp, "sample");
    glp_set_obj_dir(lp, GLP_MIN);
    glp_add_rows(lp, 9);
    glp_set_row_name(lp, 1, "p");
    glp_set_row_bnds(lp, 1, GLP_LO, 1.0, 1.0);
    glp_set_row_name(lp, 2, "q");
    glp_set_row_bnds(lp, 2, GLP_LO, 1.0, 1.0);
    glp_set_row_name(lp, 3, "r");
    glp_set_row_bnds(lp, 3, GLP_LO, 1.0, 1.0);
    glp_set_row_name(lp, 4, "s");
    glp_set_row_bnds(lp, 4, GLP_LO, 1.0, 1.0);
    glp_set_row_name(lp, 5, "t");
    glp_set_row_bnds(lp, 5, GLP_LO, 1.0, 1.0);
    glp_set_row_name(lp, 6, "t");
    glp_set_row_bnds(lp, 6, GLP_LO, 1.0, 1.0);
    glp_set_row_name(lp, 7, "u");
    glp_set_row_bnds(lp, 7, GLP_LO, 1.0, 1.0);
    glp_set_row_name(lp, 8, "v");
    glp_set_row_bnds(lp, 8, GLP_LO, 1.0, 1.0);
    glp_set_row_name(lp, 9, "w");
    glp_set_row_bnds(lp, 9, GLP_LO, 1.0, 0.0);
    glp_add_cols(lp, 5);
    glp_set_col_name(lp, 1, "x1");
    glp_set_col_bnds(lp, 1, GLP_DB, 0.0, 1.0);
    glp_set_obj_coef(lp, 1, 1.0);
    glp_set_col_name(lp, 2, "x2");
    glp_set_col_bnds(lp, 2, GLP_DB, 0.0, 1.0);
    glp_set_obj_coef(lp, 2, 1.0);
    glp_set_col_name(lp, 3, "x3");
    glp_set_col_bnds(lp, 3, GLP_DB, 0.0, 1.0);
    glp_set_obj_coef(lp, 3, 1.0);
    glp_set_col_name(lp, 4, "x4");
    glp_set_col_bnds(lp, 4, GLP_DB, 0.0, 1.0);
    glp_set_obj_coef(lp, 4, 1.0);
    glp_set_col_name(lp, 5, "x5");
    glp_set_col_bnds(lp, 5, GLP_DB, 0.0, 1.0);
    glp_set_obj_coef(lp, 5, 1.0);
    //x1>=1
    ia[1] = 1, ja[1] = 1, ar[1] =  1.0; /* a[1,1] =  1 */
    ia[2] = 1, ja[2] = 2, ar[2] =  0.0; /* a[1,2] =  0 */
    ia[3] = 1, ja[3] = 3, ar[3] =  0.0; /* a[1,3] =  0 */
    ia[4] = 1, ja[4] = 4, ar[4] =  0.0; /* a[1,2] =  0 */
    ia[5] = 1, ja[5] = 5, ar[5] =  0.0; /* a[1,5] =  0 */
    //x1+x2>=1
    ia[6] = 2, ja[6] = 1, ar[6] =  1.0; /* a[2,1] =  1 */
    ia[7] = 2, ja[7] = 2, ar[7] =  1.0; /* a[2,2] =  1 */
    ia[8] = 2, ja[8] = 3, ar[8] =  0.0; /* a[2,3] =  0 */
    ia[9] = 2, ja[9] = 4, ar[9] =  0.0; /* a[2,4] =  0 */
    ia[10] = 2, ja[10] = 5, ar[10] =  0.0; /* a[2,5] =  0 */
    //x1+x3>=1
    ia[11] = 3, ja[11] = 1, ar[11] =  1.0; /* a[3,1] =  1 */
    ia[12] = 3, ja[12] = 2, ar[12] =  0.0; /* a[3,2] =  0 */
    ia[13] = 3, ja[13] = 3, ar[13] =  1.0; /* a[3,3] =  1 */
    ia[14] = 3, ja[14] = 4, ar[14] =  0.0; /* a[3,4] =  0 */
    ia[15] = 3, ja[15] = 5, ar[15] =  0.0; /* a[3,5] =  0 */
    //x4>=1
    ia[16] = 4, ja[16] = 1, ar[16] =  0.0; /* a[4,1] =  0 */
    ia[17] = 4, ja[17] = 2, ar[17] =  0.0; /* a[4,2] =  0 */
    ia[18] = 4, ja[18] = 3, ar[18] =  0.0; /* a[4,3] =  0 */
    ia[19] = 4, ja[19] = 4, ar[19] =  1.0; /* a[4,4] =  1 */
    ia[20] = 4, ja[20] = 5, ar[20] =  0.0; /* a[4,5] =  0 */
    //x2+x4>=1
    ia[21] = 5, ja[21] = 1, ar[21] =  0.0; /* a[5,1] =  0 */
    ia[22] = 5, ja[22] = 2, ar[22] =  1.0; /* a[5,2] =  1 */
    ia[23] = 5, ja[23] = 3, ar[23] =  0.0; /* a[5,3] =  0 */
    ia[24] = 5, ja[24] = 4, ar[24] =  1.0; /* a[5,4] =  1 */
    ia[25] = 5, ja[25] = 5, ar[25] =  0.0; /* a[5,5] =  0 */
    //x3+x4>=1
    ia[26] = 6, ja[26] = 1, ar[26] =  0.0; /* a[6,1] =  0 */
    ia[27] = 6, ja[27] = 2, ar[27] =  0.0; /* a[6,2] =  0 */
    ia[28] = 6, ja[28] = 3, ar[28] =  1.0; /* a[6,3] =  1 */
    ia[29] = 6, ja[29] = 4, ar[29] =  1.0; /* a[6,4] =  1 */
    ia[30] = 6, ja[30] = 5, ar[30] =  0.0; /* a[6,5] =  0 */
    //x4+x5>=1
    ia[31] = 7, ja[31] = 1, ar[31] =  0.0; /* a[7,1] =  0 */
    ia[32] = 7, ja[32] = 2, ar[32] =  0.0; /* a[7,2] =  0 */
    ia[33] = 7, ja[33] = 3, ar[33] =  0.0; /* a[7,3] =  0 */
    ia[34] = 7, ja[34] = 4, ar[34] =  1.0; /* a[7,4] =  1 */
    ia[35] = 7, ja[35] = 5, ar[35] =  1.0; /* a[7,5] =  1 */
    //x2+x5>=1
    ia[36] = 8, ja[36] = 1, ar[36] =  0.0; /* a[8,1] =  0 */
    ia[37] = 8, ja[37] = 2, ar[37] =  1.0; /* a[8,2] =  1 */
    ia[38] = 8, ja[38] = 3, ar[38] =  0.0; /* a[8,3] =  0 */
    ia[39] = 8, ja[39] = 4, ar[39] =  0.0; /* a[8,4] =  0 */
    ia[40] = 8, ja[40] = 5, ar[40] =  1.0; /* a[8,5] =  1 */
    //x3+x5>=1
    ia[41] = 9, ja[41] = 1, ar[41] =  0.0; /* a[7,1] =  0 */
    ia[42] = 9, ja[42] = 2, ar[42] =  0.0; /* a[7,2] =  0 */
    ia[43] = 9, ja[43] = 3, ar[43] =  1.0; /* a[7,3] =  1 */
    ia[44] = 9, ja[44] = 4, ar[44] =  0.0; /* a[7,4] =  0 */
    ia[45] = 9, ja[45] = 5, ar[45] =  1.0; /* a[7,5] =  1 */

    glp_load_matrix(lp, 45, ia, ja, ar);
    glp_simplex(lp, NULL);
    z = glp_get_obj_val(lp);
    x1 = glp_get_col_prim(lp, 1);
    x2 = glp_get_col_prim(lp, 2);
    x3 = glp_get_col_prim(lp, 3);
    x4 = glp_get_col_prim(lp, 4);
    x5 = glp_get_col_prim(lp, 5);
    printf("\nz = %g; x1 = %g; x2 = %g; x3 = %g; x4 = %g; x5 = %g\n"
        , z, x1, x2, x3,x4,x5);
    glp_delete_prob(lp);
    return 0;
}

/* eof */