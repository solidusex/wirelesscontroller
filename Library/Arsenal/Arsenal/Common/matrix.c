/*
 * The Arsenal Library
 * Copyright (c) 2009 by Solidus
 * 
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.It is provided "as is" without express 
 * or implied warranty.
 *
 */

#include "common.h"




AR_NAMESPACE_BEGIN


/*****************************************************Debug****************************************************************/

/*
static void __print_matrix(const arMatrix_t *mat, size_t precision)
{
		arString_t *str = AR_CreateString();
		AR_MatrixToString(mat, str, precision, NULL, NULL);
		AR_printf(L"%ls\r\n", AR_GetStringCString(str));
		AR_DestroyString(str);
		str = NULL;
}
*/



/******************************************************Matrix**************************************************************/

struct __arsenal_matrix_tag
{
		size_t			nrows;
		size_t			ncols;
		double			*m;
};

arMatrix_t*		AR_CreateMatrix(size_t rows, size_t cols)
{
		arMatrix_t *mat;
		AR_ASSERT(rows > 0 && cols > 0);
		mat = AR_NEW(arMatrix_t);

		if(mat == NULL)
		{
				return NULL;
		}

		mat->nrows = rows;
		mat->ncols = cols;

		mat->m = AR_NEWARR0(double, rows * cols);

		if(mat->m == NULL)
		{
				AR_DEL(mat);
				return NULL;
		}

		return mat;

}

void			AR_DestroyMatrix(arMatrix_t *mat)
{
		if(mat)
		{
				if(mat->m)
				{
						AR_DEL(mat->m);
						mat->m = NULL;
				}

				AR_DEL(mat);
				mat = NULL;
		}

}


arMatrix_t*		AR_CopyNewMatrix(const arMatrix_t *mat)
{
		arMatrix_t *ret;
		AR_ASSERT(mat != NULL);
		ret = AR_CreateMatrix(mat->nrows, mat->ncols);

		if(ret == NULL)
		{
				return NULL;
		}

		AR_memcpy(ret->m, mat->m, mat->nrows * mat->ncols * sizeof(double));
		return ret;
}

arStatus_t		AR_CopyMatrix(arMatrix_t *dest, const arMatrix_t *src)
{
		arStatus_t status;
		AR_ASSERT(dest != NULL && src != NULL);

		status = AR_S_YES;

		if(dest == src)
		{
				return status;
		}

		if((status = AR_SetMatrixSize(dest, src->nrows, src->ncols)) != AR_S_YES)
		{
				return status;
		}

		AR_memcpy(dest->m, src->m, src->nrows * src->ncols * sizeof(double));
		
		return status;
}


arStatus_t			AR_SetMatrixSize(arMatrix_t *mat, size_t rows, size_t cols)
{
		arStatus_t status;
		AR_ASSERT(mat != NULL);
		AR_ASSERT(rows > 0 && cols > 0);
		
		status = AR_S_YES;

		if(mat->nrows != rows || mat->ncols != cols)
		{
				double *new_tmp;
				size_t	new_size;
				
				new_size = rows * cols;
				new_tmp = AR_NEWARR(double, new_size);

				if(new_tmp == NULL)
				{
						status = AR_E_NOMEM;
						return status;
				}
				
				AR_memcpy(new_tmp, mat->m, AR_MIN(new_size, mat->nrows * mat->ncols));
				AR_DEL(mat->m);
				
				mat->nrows = rows;
				mat->ncols = cols;
				mat->m = new_tmp;
		}

		return status;
}


arStatus_t			AR_SetMatrixData(arMatrix_t *mat, size_t row, size_t col, const double *data)
{
		arStatus_t status;
		AR_ASSERT(mat != NULL);
		AR_ASSERT(data != NULL);
		AR_ASSERT(row > 0 && col > 0);

		if((status = AR_SetMatrixSize(mat, row, col)) != AR_S_YES)
		{
				return status;
		}

		AR_memcpy(mat->m, data, row * col * sizeof(double));

		return status;
}




size_t			AR_GetMatrixNumRows(const arMatrix_t *mat)
{
		AR_ASSERT(mat != NULL);
		return mat->nrows;

}

size_t			AR_GetMatrixNumColumns(const arMatrix_t *mat)
{
		AR_ASSERT(mat != NULL);
		return mat->ncols;
}

int_t			AR_CompareMatrix(const arMatrix_t *l, const arMatrix_t *r, double epsilon)
{
		size_t i;
		AR_ASSERT(l != NULL && r != NULL);
		AR_ASSERT(l->nrows == r->nrows && l->ncols == r->ncols);

		for(i = 0; i < l->nrows * l->ncols; ++i)
		{
				double e = l->m[i] - r->m[i];

				if(AR_abs_dbl(e) > epsilon)
				{
						if(e < 0.0)
						{
								return -1;
						}else
						{
								return 1;
						}
				}
		}
		
		return 0;

}



void			AR_SetMatrixValue(arMatrix_t *mat, size_t row, size_t col, double val)
{
		AR_ASSERT(mat != NULL);
		AR_ASSERT(row < mat->nrows);
		AR_ASSERT(col < mat->ncols);

		mat->m[row * mat->ncols + col] = val;
}

double			AR_GetMatrixValue(const arMatrix_t *mat, size_t row, size_t col)
{
		AR_ASSERT(mat != NULL);
		AR_ASSERT(row < mat->nrows);
		AR_ASSERT(col < mat->ncols);
		return mat->m[row * mat->ncols + col];
}


void			AR_SetMatrixRowByRawData(arMatrix_t *mat, size_t row,  const double *data)
{
		size_t c;
		AR_ASSERT(mat != NULL && row < mat->nrows);
		AR_ASSERT(data != NULL);

		for(c = 0; c < mat->ncols; ++c)
		{
				AR_SetMatrixValue(mat, row, c, data[c]);
		}
}


void			AR_SetMatrixColumnByRawData(arMatrix_t *mat, size_t col, const double *data)
{
		size_t r;
		AR_ASSERT(mat != NULL && col < mat->ncols);
		AR_ASSERT(data != NULL);

		for(r = 0; r < mat->nrows; ++r)
		{
				AR_SetMatrixValue(mat, r, col, data[r]);
		}
}


void			AR_SetMatrixRow(arMatrix_t *mat, size_t row,  const arVector_t *vec)
{
		
		AR_ASSERT(mat != NULL && row < mat->nrows);
		AR_ASSERT(vec != NULL && AR_GetVectorSize(vec) >= mat->ncols);
		AR_SetMatrixRowByRawData(mat, row, AR_GetVectorData(vec));
}


void			AR_SetMatrixColumn(arMatrix_t *mat, size_t col,  const arVector_t *vec)
{
		AR_ASSERT(mat != NULL && col < mat->ncols);
		AR_ASSERT(vec != NULL && AR_GetVectorSize(vec) >= mat->nrows);

		AR_SetMatrixColumnByRawData(mat, col, AR_GetVectorData(vec));
}


arStatus_t			AR_GetMatrixRow(const arMatrix_t *mat, size_t row,  arVector_t *out)
{
		size_t i;
		arStatus_t status;
		AR_ASSERT(mat != NULL);
		AR_ASSERT(row < mat->nrows);
		AR_ASSERT(out != NULL);

		status = AR_S_YES;

		if((status = AR_SetVectorSize(out, mat->ncols)) != AR_S_YES)
		{
				return status;
		}

		for(i = 0; i < mat->ncols; ++i)
		{
				double v = mat->m[row * mat->ncols + i];
				AR_SetVectorValue(out, i, v);
		}

		return status;
}

arStatus_t		AR_GetMatrixColumn(const arMatrix_t *mat, size_t col,  arVector_t *out)
{
		size_t i;
		arStatus_t status;
		AR_ASSERT(mat != NULL);
		AR_ASSERT(col < mat->ncols);
		AR_ASSERT(out != NULL);

		if((status = AR_SetVectorSize(out, mat->ncols)) != AR_S_YES)
		{
				return status;
		}

		for(i = 0; i < mat->nrows; ++i)
		{
				double v = mat->m[i * mat->ncols + col];
				AR_SetVectorValue(out, i, v);
		}

		return status;
}

const double*	AR_GetMatrixRawData(const arMatrix_t *mat)
{
		AR_ASSERT(mat != NULL);
		return mat->m;
}



void			AR_ZeroMatrix(arMatrix_t *mat)
{
		AR_ASSERT(mat != NULL);
		AR_memset(mat->m, 0, sizeof(double) * mat->nrows * mat->ncols);
}


void			AR_IdentityMatrix(arMatrix_t *mat)
{
		size_t i;
		AR_ASSERT(mat != NULL);
		AR_ASSERT(mat->nrows == mat->ncols);

		AR_ZeroMatrix(mat);

		for(i = 0; i < mat->nrows; ++i)
		{
				AR_SetMatrixValue(mat, i, i, 1.0);
		}

}


arStatus_t		AR_DiagonalMatrix(arMatrix_t *mat, const arVector_t *vec)
{
		size_t i;
		arStatus_t status;
		AR_ASSERT(mat != NULL);
		AR_ASSERT(vec != NULL);
		AR_ASSERT(AR_GetVectorSize(vec) > 0);

		if((status = AR_SetMatrixSize(mat, AR_GetVectorSize(vec), AR_GetVectorSize(vec))) != AR_S_YES)
		{
				return status;
		}

		for(i = 0; i < AR_GetVectorSize(vec); ++i)
		{
				double v = AR_GetVectorValue(vec, i);
				AR_SetMatrixValue(mat, i,i,v);
		}

		return status;
}


void			AR_RandomMatrix(arMatrix_t *mat)
{
		size_t i;
		AR_ASSERT(mat != NULL);

		for(i = 0; i < mat->nrows * mat->ncols; ++i)
		{
				mat->m[i] = AR_rand_dbl();
		}
}

void			AR_NegateMatrix(arMatrix_t *mat)
{
		size_t i;
		AR_ASSERT(mat != NULL);

		for(i = 0; i < mat->nrows * mat->ncols; ++i)
		{
				mat->m[i] = -mat->m[i];
		}

}

void			AR_ClampMatrix(arMatrix_t *mat, double min_val, double max_val)
{
		size_t i;
		AR_ASSERT(mat != NULL);

		for(i = 0; i < mat->nrows * mat->ncols; ++i)
		{
				if(AR_DBL_LE(mat->m[i], min_val))
				{
						mat->m[i] = min_val;
				}else if(AR_DBL_GE(mat->m[i], max_val))
				{
						mat->m[i] = max_val;
				}
		}

}

arStatus_t	AR_SwapMatrixRows(arMatrix_t *mat, size_t l, size_t r)
{
		double *tmp, *lptr, *rptr;
		
		AR_ASSERT(mat != NULL);
		AR_ASSERT(l < mat->nrows);
		AR_ASSERT(r < mat->nrows);

		
		tmp = NULL; lptr = NULL; rptr = NULL;

		if(l == r)
		{
				return AR_S_YES;
		}
		
		tmp = AR_NEWARR(double, mat->ncols);

		if(tmp == NULL)
		{
				return AR_E_NOMEM;
		}

		lptr = &mat->m[l * mat->ncols];
		rptr = &mat->m[r * mat->ncols];

		
		AR_memcpy(tmp, lptr, sizeof(double) * mat->ncols);
		AR_memcpy(lptr, rptr, sizeof(double) * mat->ncols);
		AR_memcpy(rptr, tmp, sizeof(double) * mat->ncols);

		AR_DEL(tmp);
		tmp = NULL;

		return AR_S_YES;
}


arStatus_t		AR_SwapMatrixColumns(arMatrix_t *mat, size_t l, size_t r)
{
		
		size_t i;
		AR_ASSERT(mat != NULL);
		AR_ASSERT(l < mat->ncols);
		AR_ASSERT(r < mat->ncols);

		for(i = 0; i < mat->nrows; ++i)
		{
				double lv,rv;

				lv = AR_GetMatrixValue(mat, i, l);
				rv = AR_GetMatrixValue(mat, i, r);
				AR_SetMatrixValue(mat, i, l, rv);
				AR_SetMatrixValue(mat, i, r, lv);
		}

		return AR_S_YES;
}


void			AR_RemoveMatrixRow(arMatrix_t *mat, size_t r)
{
		size_t i;
		AR_ASSERT(mat != NULL);
		AR_ASSERT(mat->nrows > 1);
		AR_ASSERT(r < mat->nrows);

		mat->nrows -= 1;

		for(i = r; i < mat->nrows; ++i)
		{
				double *np = &mat->m[i * mat->ncols];
				double  *op = &mat->m[(i + 1) * mat->ncols];
				AR_memcpy(np, op, sizeof(double) * mat->ncols);
		}


}


void			AR_RemoveMatrixColumn(arMatrix_t *mat, size_t c)
{
		size_t i;
		AR_ASSERT(mat != NULL);
		AR_ASSERT(c < mat->ncols);
		AR_ASSERT(mat->ncols > 1);

		mat->ncols--;

		for(i = 0; i < mat->nrows-1; ++i)
		{
				double *p1 = &mat->m[i * mat->ncols + c];
				double *p2 = &mat->m[i * (mat->ncols + 1) + c + 1];
				AR_memmove(p1, p2, sizeof(double) * mat->ncols);
		}

		if(mat->ncols - c > 0)
		{
				AR_memmove(&mat->m[i * mat->ncols + c], &mat->m[i * (mat->ncols + 1) + c + 1], sizeof(double) * (mat->ncols - c));
		}
}


void			AR_ClearMatrixUpperTriangle(arMatrix_t *mat)
{
		size_t i,j;
		AR_ASSERT(mat != NULL);
		AR_ASSERT(mat->nrows == mat->ncols);
		for(i = 0; i < mat->nrows - 1; ++i)
		{
				for(j = i + 1; j < mat->ncols; ++j)
				{
						AR_SetMatrixValue(mat, i,j, 0.0);
				}
		}
}

void			AR_ClearMatrixLowerTriangle(arMatrix_t *mat)
{
		size_t i,j;
		AR_ASSERT(mat != NULL);
		AR_ASSERT(mat->nrows == mat->ncols);

		for(i = 1; i < mat->nrows; ++i)
		{
				for(j = 0; j < i; ++j)
				{
						AR_SetMatrixValue(mat, i,j, 0.0);
				}
		}
}



arStatus_t			AR_IsSquareMatrix(const arMatrix_t *mat)
{
		AR_ASSERT(mat != NULL);
		return mat->nrows == mat->ncols ? AR_S_YES : AR_S_NO;
}


arStatus_t			AR_IsZeroMatrix(const arMatrix_t *mat, double epsilon)
{
		size_t i;
		AR_ASSERT(mat != NULL);
		for(i = 0; i < mat->ncols * mat->nrows; ++i)
		{
				if(AR_abs_dbl(mat->m[i]) > epsilon)
				{
						return AR_S_NO;
				}
		}

		return AR_S_YES;
}


arStatus_t			AR_IsIdentityMatrix(const arMatrix_t *mat, double epsilon)
{
		size_t i,j;
		arStatus_t status;
		AR_ASSERT(mat != NULL);

		status = AR_IsSquareMatrix(mat);
		if(status != AR_S_YES)
		{
				return status;
		}

		for(i = 0; i < mat->nrows; ++i)
		{
				for(j = 0; j < mat->ncols; ++j)
				{
						const double v = i == j ? 1.0 : 0.0;

						if(AR_abs_dbl(mat->m[i * mat->ncols + j] - v) > epsilon)
						{
								return AR_S_NO;
						}
				}

		}
		return AR_S_YES;
}

arStatus_t			AR_IsDiagonalMatrix(const arMatrix_t *mat, double epsilon)
{
		size_t i,j;
		arStatus_t status;
		AR_ASSERT(mat != NULL);

		status = AR_IsSquareMatrix(mat);
		if(status != AR_S_YES)
		{
				return status;
		}

		for(i = 0; i < mat->nrows; ++i)
		{
				for(j = 0; j < mat->ncols; ++j)
				{
						if(i != j && AR_abs_dbl(mat->m[i * mat->ncols + j]) > epsilon)
						{
								return AR_S_NO;
						}
				}
		}
		return AR_S_YES;
}


arStatus_t			AR_IsTriDiagonalMatrix(const arMatrix_t *mat, double epsilon)
{
		size_t i,j;
		double v;
		arStatus_t status;
		AR_ASSERT(mat != NULL);

		status = AR_IsSquareMatrix(mat);
		if(status != AR_S_YES)
		{
				return status;
		}

		for(i = 0; i < mat->nrows - 2; ++i)
		{
				for(j = i + 2; j < mat->ncols; ++j)
				{
						v = AR_GetMatrixValue(mat, i,j);

						if(AR_abs_dbl(v) > epsilon)
						{
								return AR_S_NO;
						}

						v = AR_GetMatrixValue(mat, j,i);
						
						if(AR_abs_dbl(v) > epsilon)
						{
								return AR_S_NO;
						}

				}
		}
		return AR_S_YES;
}


arStatus_t			AR_IsSymmetricMatrix(const arMatrix_t *mat, double epsilon)
{
		size_t i,j;
		double l,r;
		arStatus_t status;
		AR_ASSERT(mat != NULL);

		status = AR_IsSquareMatrix(mat);
		if(status != AR_S_YES)
		{
				return status;
		}

		for(i = 0; i < mat->nrows; ++i)
		{
				for(j = i + 1; j < mat->ncols; ++j)
				{
						l = AR_GetMatrixValue(mat, i,j);
						r = AR_GetMatrixValue(mat, j,i);

						if(AR_abs_dbl(l - r) > epsilon)
						{
								return AR_S_NO;
						}
				}
		}
		return AR_S_YES;
}


arStatus_t			AR_IsOrthogonalMatrix(const arMatrix_t *mat, double epsilon)
{
		size_t i,j,k;
		
		double s;
		AR_ASSERT(mat != NULL);


		for(i = 0; i < mat->ncols; ++i)
		{
				for(j = i + 1; j < mat->ncols; ++j)
				{
						
						s = 0.0;

						for(k = 0; k < mat->nrows; ++k)
						{
								double l,r;
								l = AR_GetMatrixValue(mat,k,i);
								r = AR_GetMatrixValue(mat,k,j);
								s += (l * r);
						}

						if(AR_abs_dbl(s) > epsilon)
						{
								return AR_S_NO;
						}
				}
		}
		return AR_S_YES;
}




arStatus_t			AR_IsOrthonormalMatrix(const arMatrix_t *mat, double epsilon)
{
		size_t i,j,k;
		
		double s;
		AR_ASSERT(mat != NULL);


		for(i = 0; i < mat->ncols; ++i)
		{
				for(j = i; j < mat->ncols; ++j)
				{
						s = i == j ? -1.0 : 0.0;
						
						for(k = 0; k < mat->nrows; ++k)
						{
								double l,r;
								l = AR_GetMatrixValue(mat,k,i);
								r = AR_GetMatrixValue(mat,k,j);
								s += (l * r);
						}

						if(AR_abs_dbl(s) > epsilon)
						{
								return AR_S_NO;
						}
				}
		}

		return AR_S_YES;
}




/*
如果A为正定矩阵， 则二次型 x' * A * x > 0; 则

A =		[	a00,	a01;
			a10,	a11
		]
		;

		x = [x0, x1]';

		x' * A * x = a00 * x0 ^ 2 + a11 * x1 ^ 2 + (a01 + a10) * x0 * x1;

		如果此不等式a00 * x0 ^ 2 + a11 * x1 ^ 2 + (a01 + a10) * x0 * x1 > 0 成立

		设x = [1,0]' 则： a00 > 0
		设x = [0,1]' 则： a11 > 0
		设x = [1,1]' 则 : a00 + a11 + (a01 + a10) > 0
		设x = [1,-1]' 则 : a00 + a11 - (a01 + a10) > 0

		由后两个方程推知，|a01| <= (a00 + a11) / 2;
		则A的最大元素在对角线上且为正

		主元为正
		行列式为正

*/



arStatus_t		AR_IsPositiveDefiniteMatrix(const arMatrix_t *mat, double epsilon)
{
		arStatus_t status;
		size_t i, j, k;
		double d, s,t;
		arMatrix_t *tmp;
		
		AR_ASSERT(mat != NULL);

		status = AR_S_YES;
		
		tmp = NULL;

		status = AR_IsSquareMatrix(mat);
		if(status != AR_S_YES)
		{
				goto END_POINT;
		}

		tmp = AR_CopyNewMatrix(mat);

		if(tmp == NULL)
		{

				status = AR_E_NOMEM;
				goto END_POINT;
		}


		for ( i = 0; i < mat->nrows; i++ ) 
		{
				for ( j = 0; j < mat->ncols; j++ ) 
				{
						t = AR_GetMatrixValue(tmp, i,j);
						s = AR_GetMatrixValue(mat, j,i);
						AR_SetMatrixValue(tmp, i,j,s + t);
				}
		}

		

		for(i = 0; i < tmp->nrows; i++)
		{

				for(j = i; j < tmp->ncols; j++) /*检查从第i行开始的对角线元素是否小于等于0*/
				{
						t = AR_GetMatrixValue(tmp, j,j);
						if(AR_DBL_LEEQ(t, epsilon))
						{
								status = AR_S_NO;
								goto END_POINT;
						}
				}

				d = 1.0 / AR_GetMatrixValue(tmp,i,i); /*消元， 求U*/

				for ( j = i + 1; j < tmp->nrows; j++ ) 
				{
						s = d * AR_GetMatrixValue(tmp, j,i);
						AR_SetMatrixValue(tmp, j,i, 0.0);
						
						for(k = i + 1; k < tmp->ncols; k++ ) 
						{
								t = AR_GetMatrixValue(tmp,j,k);
								t -= AR_GetMatrixValue(tmp, i,k) * s;
								AR_SetMatrixValue(tmp,j,k, t);
						}
				}
		}



END_POINT:
		if(tmp)
		{
				AR_DestroyMatrix(tmp);
				tmp = NULL;
		}

		
		return status;
}


arStatus_t		AR_IsSymmetricPositiveDefinite(const arMatrix_t *mat, double epsilon)
{
		arStatus_t status;
		arMatrix_t *tmp;
		AR_ASSERT(mat != NULL );
		
		status = AR_S_YES;
		
		tmp = NULL;
		if((status = AR_IsSymmetricMatrix(mat, epsilon)) != AR_S_YES)
		{
				goto END_POINT;
		}

		tmp = AR_CopyNewMatrix(mat);

		if(tmp == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}
		
		status = AR_CholeskyFactorMatrixSelf(tmp);

END_POINT:
		if(tmp)
		{
				AR_DestroyMatrix(tmp);
				tmp = NULL;
		}
		
		return status;
}



/*
如果A为半正定矩阵， 则二次型 x' * A * x >= 0; 则
*/

arStatus_t			AR_IsPositiveSemiDefinite(const arMatrix_t *mat, double epsilon)
{
		arStatus_t status;
		size_t i, j, k;
		double d, s,t;
		arMatrix_t *tmp;
		
		AR_ASSERT(mat != NULL );

		status = AR_S_YES;
		
		tmp = NULL;

		if((status = AR_IsSquareMatrix(mat)) != AR_S_YES)
		{
				goto END_POINT;
		}

		tmp = AR_CopyNewMatrix(mat);

		if(tmp == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}

		for ( i = 0; i < mat->nrows; i++ ) 
		{
				for ( j = 0; j < mat->ncols; j++ ) 
				{
						t = AR_GetMatrixValue(tmp, i,j);
						s = AR_GetMatrixValue(mat, j,i);
						AR_SetMatrixValue(tmp, i,j,s + t);
				}
		}


		for(i = 0; i < tmp->nrows; i++)
		{

				for(j = i; j < tmp->nrows; j++)
				{
						t = AR_GetMatrixValue(tmp, j,j);
						if(AR_DBL_LE(t, -epsilon))
						{
								status = AR_S_NO;
								goto END_POINT;
						}

						if(AR_DBL_GE(t, epsilon))
						{
								continue;
						}

						
						for(k = 0; k < tmp->nrows; k++)
						{
								t = AR_GetMatrixValue(tmp,k,j);
								if(AR_DBL_GE(AR_abs_dbl(t), epsilon))
								{
										status = AR_S_NO;
										goto END_POINT;
								}

								t = AR_GetMatrixValue(tmp,j,k);
								if(AR_DBL_GE(AR_abs_dbl(t), epsilon))
								{
										status = AR_S_NO;
										goto END_POINT;
								}
						}
				}


				t = AR_GetMatrixValue(tmp, i,i);
				if(AR_DBL_LEEQ(t, epsilon))
				{
						continue;
				}

				d = 1.0 / t;

				for(j = i + 1; j < tmp->nrows; j++)/*lu分解*/
				{
						s = d * AR_GetMatrixValue(tmp, j,i);
						AR_SetMatrixValue(tmp, j,i, 0.0);
						
						for(k = i + 1; k < tmp->ncols; k++ ) 
						{
								t = AR_GetMatrixValue(tmp,j,k);
								t -= AR_GetMatrixValue(tmp, i,k) * s;
								AR_SetMatrixValue(tmp,j,k, t);
						}
				}
		}

END_POINT:
		if(tmp)
		{
				AR_DestroyMatrix(tmp);
				tmp = NULL;
		}
	
		return status;
}



arStatus_t			AR_IsSymmetricPositiveSemiDefinite(const arMatrix_t *mat, double epsilon)
{
		arStatus_t status;
		AR_ASSERT(mat != NULL);

		status = AR_IsSymmetricMatrix(mat, epsilon);

		if(status != AR_S_YES)
		{
				return status;
		}

		return AR_IsPositiveSemiDefinite(mat, epsilon);

}







/*********************************************************************************/
arStatus_t			AR_MultiplyMatrixByScalar(const arMatrix_t *mat, double value, arMatrix_t *dest)
{
		arStatus_t status;
		size_t i;

		AR_ASSERT(mat != NULL && dest != NULL);

		status = AR_S_YES;

		status = AR_SetMatrixSize(dest, mat->nrows, mat->ncols);
		
		if(status != AR_S_YES)
		{
				return status;
		}

		for(i = 0; i < mat->nrows * mat->ncols; ++i)
		{
				dest->m[i] = mat->m[i] * value;
		}

		return status;
}

arStatus_t		AR_MultiplyMatrixByScalarSelf(arMatrix_t *mat, double value)
{
		size_t i;
		AR_ASSERT(mat != NULL);
		for(i = 0; i < mat->nrows * mat->ncols; ++i)
		{
				mat->m[i] *= value;
		}

		return AR_S_YES;
}

arStatus_t			AR_MultiplyMatrixByVector(const arMatrix_t *mat, const arVector_t *other, arVector_t *dest)
{
		arStatus_t status;
		size_t m,n,i,j;
		double sum;
		AR_ASSERT(mat != NULL);
		AR_ASSERT(other != NULL && dest != NULL);
		m = AR_GetMatrixNumRows(mat);
		n = AR_GetMatrixNumColumns(mat);
		AR_ASSERT(n == AR_GetVectorSize(other));

		status = AR_S_YES;

		if((status = AR_SetVectorSize(dest, m)) != AR_S_YES)
		{
				return status;
		}

		AR_ZeroVector(dest);

		for(i = 0; i < m; ++i)
		{
				sum = 0.0;
				for(j = 0; j < n; ++j)
				{
						sum += AR_GetMatrixValue(mat, i,j) * AR_GetVectorValue(other, j);
				}

				AR_SetVectorValue(dest, i, sum);
		}
		return status;
}


arStatus_t		AR_MultiplyTransposeMatrixByVector(const arMatrix_t *mat, const arVector_t *other, arVector_t *dest)
{
		size_t i,j,m,n;
		double sum;
		arStatus_t status;
		AR_ASSERT(mat != NULL && other != NULL && dest != NULL);

		
		status = AR_S_YES;
		m = AR_GetMatrixNumRows(mat);
		n = AR_GetMatrixNumColumns(mat);

		AR_ASSERT(m == AR_GetVectorSize(other));

		if((status = AR_SetVectorSize(dest, n)) != AR_S_YES)
		{
				return status;
		}

		for(i = 0; i < n; ++i)
		{
				sum = 0.0;
				for(j = 0; j < m; ++j)
				{
						sum += AR_GetMatrixValue(mat, j,i) * AR_GetVectorValue(other,j);
				}
				AR_SetVectorValue(dest, i,sum);
		}

		return status;
}


arStatus_t		AR_MultiplyMatrixByMatrix(const arMatrix_t *mat, const arMatrix_t *other, arMatrix_t *dest)
{
		size_t i,j,k,lm,ln,rm,rn;
		double sum;
		arStatus_t status;
		AR_ASSERT(mat != NULL && other != NULL && dest != NULL);

		status = AR_S_YES;

		lm = AR_GetMatrixNumRows(mat);
		ln = AR_GetMatrixNumColumns(mat);

		rm = AR_GetMatrixNumRows(other);
		rn = AR_GetMatrixNumColumns(other);

		AR_ASSERT(ln == rm);

		if((status = AR_SetMatrixSize(dest, lm, rn)) != AR_S_YES)
		{
				return status;
		}

		AR_ZeroMatrix(dest);

		for(i = 0; i < lm; ++i)
		{
				for(j = 0; j < rn; ++j)
				{
						sum = 0.0;
						for(k = 0; k < rm; ++k)
						{
								sum += AR_GetMatrixValue(mat, i,k) * AR_GetMatrixValue(other, k,j);
						}

						AR_SetMatrixValue(dest, i,j,sum);
				}
		}

		return status;
}


arStatus_t		AR_MultiplyTransposeMatrixByMatrix(const arMatrix_t *mat, const arMatrix_t *other, arMatrix_t *dest)
{
		arStatus_t status;
		size_t i,j,k,lrows,lcols,rrows,rcols;
		double sum;

		AR_ASSERT(mat != NULL && other != NULL && dest != NULL);

		lrows = AR_GetMatrixNumRows(mat);
		lcols = AR_GetMatrixNumColumns(mat);

		rrows = AR_GetMatrixNumRows(other);
		rcols = AR_GetMatrixNumColumns(other);

		AR_ASSERT(lrows == rrows);

		status = AR_S_YES;

		if((status = AR_SetMatrixSize(dest, lcols, rcols)) != AR_S_YES)
		{
				return status;
		}

		AR_ZeroMatrix(dest);

		for(i = 0; i < lcols; ++i)
		{
				for(j = 0; j < rcols; ++j)
				{
						sum = 0.0;
						for(k = 0; k < lrows; ++k)
						{
								sum += AR_GetMatrixValue(mat, k,i) * AR_GetMatrixValue(other, k,j);
						}

						AR_SetMatrixValue(dest, i,j,sum);
				}
		}

		return status;
}


arStatus_t			AR_MultiplyMatrixByMatrixSelf(arMatrix_t *mat, const arMatrix_t *other)
{
		arStatus_t status;
		arMatrix_t *tmp;
		AR_ASSERT(mat != NULL && other != NULL);

		status = AR_S_YES;

		tmp = AR_CreateMatrix(mat->nrows, mat->ncols);

		if(tmp == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}

		
		if((status = AR_MultiplyMatrixByMatrix(mat, other, tmp)) != AR_S_YES)
		{
				goto END_POINT;
		}


		if((status = AR_CopyMatrix(mat, tmp)) != AR_S_YES)
		{
				goto END_POINT;
		}

END_POINT:
		if(tmp)
		{
				AR_DestroyMatrix(tmp);
				tmp = NULL;
		}

		return status;
}



arStatus_t		AR_MultiplyTransposeMatrixByMatrixSelf(arMatrix_t *mat, const arMatrix_t *other)
{
		arStatus_t status;
		arMatrix_t *tmp;
		AR_ASSERT(mat != NULL && other != NULL);

		status = AR_S_YES;

		tmp = AR_CreateMatrix(mat->nrows, mat->ncols);

		if(tmp == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}
		
		
		if((status = AR_MultiplyTransposeMatrixByMatrix(mat, other, tmp)) != AR_S_YES)
		{
				goto END_POINT;
		}


		if((status = AR_CopyMatrix(mat, tmp)) != AR_S_YES)
		{
				goto END_POINT;
		}

END_POINT:
		if(tmp)
		{
				AR_DestroyMatrix(tmp);
				tmp = NULL;
		}
		return status;
}


arStatus_t		AR_AddMatrixByMatrix(const arMatrix_t *mat, const arMatrix_t *other, arMatrix_t *dest)
{
		arStatus_t status;
		size_t i;
		AR_ASSERT(mat != NULL && other != NULL);
		AR_ASSERT(mat->nrows == other->nrows && mat->ncols == other->ncols);

		if((status = AR_SetMatrixSize(dest, mat->nrows, mat->ncols)) != AR_S_YES)
		{
				return status;
		}

		

		for(i = 0; i < mat->nrows * mat->ncols; ++i)
		{
				dest->m[i] = mat->m[i] + other->m[i];
		}

		return status;
}

arStatus_t			AR_SubMatrixByMatrix(const arMatrix_t *mat, const arMatrix_t *other, arMatrix_t *dest)
{
		arStatus_t status;
		size_t i;
		AR_ASSERT(mat != NULL && other != NULL);
		AR_ASSERT(mat->nrows == other->nrows && mat->ncols == other->ncols);

		if((status = AR_SetMatrixSize(dest, mat->nrows, mat->ncols)) != AR_S_YES)
		{
				return status;
		}

		for(i = 0; i < mat->nrows * mat->ncols; ++i)
		{
				dest->m[i] = mat->m[i] - other->m[i];
		}

		return status;
}


arStatus_t			AR_AddMatrixByMatrixSelf(arMatrix_t *mat, const arMatrix_t *other)
{
		size_t i;
		AR_ASSERT(mat != NULL && other != NULL);
		AR_ASSERT(mat->nrows == other->nrows && mat->ncols == other->ncols);

		for(i = 0; i < mat->nrows * mat->ncols; ++i)
		{
				mat->m[i] += other->m[i];
		}

		return AR_S_YES;
}


arStatus_t		AR_SubMatrixByMatrixSelf(arMatrix_t *mat, const arMatrix_t *other)
{
		size_t i;
		AR_ASSERT(mat != NULL && other != NULL);
		AR_ASSERT(mat->nrows == other->nrows && mat->ncols == other->ncols);

		for(i = 0; i < mat->nrows * mat->ncols; ++i)
		{
				mat->m[i] -= other->m[i];
		}

		return AR_S_YES;
}






arStatus_t			AR_CalcMatrixTrace(const arMatrix_t *mat, double *ret)
{
		double val;
		size_t i;
		AR_ASSERT(mat != NULL && ret != NULL);
		AR_ASSERT(mat->nrows == mat->ncols);

		val = 0.0;
		for(i = 0; i < mat->nrows; ++i)
		{
				val += AR_GetMatrixValue(mat, i,i);
		}

		*ret = val;
		return AR_S_YES;
}


arStatus_t			AR_CalcMatrixDeterminant(const arMatrix_t *mat, double *ret)
{
		arStatus_t status;
		arMatrix_t *tmp;
		size_t *index;
		double det;
		
		AR_ASSERT(mat != NULL);

		status = AR_S_YES;
		det = 0.0;
		index = NULL;
		tmp = NULL;
		

		tmp = AR_CopyNewMatrix(mat);

		if(tmp == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}

		index = AR_NEWARR0(size_t, tmp->nrows);

		if(index == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}

		
		
		status = AR_LUFactorMatrixSelf(tmp, index, &det);
		if(status != AR_S_YES)
		{
				det = 0.0;
		}

END_POINT:
		if(tmp)
		{
				AR_DestroyMatrix(tmp);
				tmp = NULL;
		}

		if(index)
		{
				AR_DEL(index);
				index = NULL;
		}
		*ret = det;
		return status;
}



arStatus_t			AR_TransposeMatrix(const arMatrix_t *mat, arMatrix_t *dest)
{
		arStatus_t status;
		size_t i,j;
		AR_ASSERT(mat != NULL && dest != NULL);

		if((status = AR_SetMatrixSize(dest, mat->ncols, mat->nrows)) != AR_S_YES)
		{
				return status;
		}
		
		for(i = 0; i < mat->nrows; ++i)
		{
				for(j = 0; j < mat->ncols; ++j)
				{
						double v = AR_GetMatrixValue(mat, i,j);
						AR_SetMatrixValue(dest, j,i,v);
				}
		}

		return status;
}


arStatus_t			AR_TransposeMatrixSelf(arMatrix_t *mat)
{
		arStatus_t status;
		arMatrix_t *tmp;
		AR_ASSERT(mat != NULL);
		
		status = AR_S_YES;

		tmp = AR_CreateMatrix(mat->ncols, mat->nrows);

		if(tmp == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}
		

		if((status = AR_TransposeMatrix(mat, tmp)) != AR_S_YES)
		{
				goto END_POINT;
		}

		if((status = AR_CopyMatrix(mat, tmp)) != AR_S_YES)
		{
				goto END_POINT;
		}

END_POINT:
		if(tmp)
		{
				AR_DestroyMatrix(tmp);
				tmp = NULL;
		}
		return status;
}






/*

A = [

     0     0     0     0     2     8     4
     0     0     0     1     3    11     9
     0     3   -12    -3    -9   -24   -33
     0    -2     8     1     6    17    21
];


简化后:

A = [
     0     1    -4     0     0     3     0
     0     0     0     1     0    -1     0
     0     0     0     0     1     4     0
     0     0     0     0     0     0     1
];

*/

arStatus_t			AR_CalcMatrixRank(const arMatrix_t *mat, size_t *ret)
{
		size_t r,c;
		arMatrix_t *tmp;
		double t;
		size_t rank ;
		arStatus_t status;
		AR_ASSERT(mat != NULL && ret != NULL);

		status = AR_S_YES;
		rank = 0;
		
		tmp = AR_CopyNewMatrix(mat);

		if(tmp == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}
		
		AR_ReduceMatrixToEchelonFormSelf(tmp, NULL);

		for(r = 0; r < tmp->nrows; ++r)
		{
				for(c = 0; c < tmp->ncols; ++c)
				{
						t = AR_GetMatrixValue(tmp,r,c);

						if(AR_DBL_GE(t, 0.0))
						{
								rank++;
								break;
						}
				}
		}

END_POINT:
		if(tmp)
		{
				AR_DestroyMatrix(tmp);
				tmp = NULL;
		}
		*ret = rank;
		return status;

}


/*************************************将矩阵化简为简化阶梯型矩阵************************************************/



void			AR_ReduceMatrixToEchelonFormSelf(arMatrix_t *mat, size_t *index)
{


		size_t i,j,k,r,c;
		int_t reduced_r;
		double d,max_val,t;

		AR_ASSERT(mat != NULL);

		if(index)
		{
				for(i = 0; i < mat->nrows; ++i)
				{
						index[i] = i;
				}
		}

		reduced_r = -1;

		for(j = 0; j < mat->ncols; ++j)
		{
				max_val = 0.0;
				r = 0;c = 0;
				
				for(i = (size_t)(reduced_r + 1); i < mat->nrows; ++i)
				{
						t = AR_abs_dbl(AR_GetMatrixValue(mat,i,j));
						
						if(AR_DBL_GE(t,max_val))
						{
								max_val = t;
								r = i;
								c = j;
						}
				}

				if(AR_DBL_EQ(max_val,0.0))/*此列全为0，则精简下一列*/
				{
						continue;
				}

				if(r != (size_t)(reduced_r + 1))
				{
						if(index)
						{
								size_t rt = index[r];
								index[r] = index[(size_t)(reduced_r + 1)];
								index[(size_t)(reduced_r + 1)] = rt;
						}

						AR_SwapMatrixRows(mat, r, (size_t)(reduced_r + 1));
						
						r = (size_t)(reduced_r + 1);
				}

				reduced_r += 1;

				d = 1 / AR_GetMatrixValue(mat, r,c);
				AR_SetMatrixValue(mat, r,c, 1.0);

				for(k = c + 1; k < mat->ncols; ++k)
				{
						t = AR_GetMatrixValue(mat, r,k);
						AR_SetMatrixValue(mat, r,k, t * d);
				}


				for(k = 0; k < mat->nrows; ++k)
				{
						if(k == r)
						{
								continue;
						}

						d = AR_GetMatrixValue(mat, k,c);
						AR_SetMatrixValue(mat, k,c, 0.0);

						if(AR_DBL_EQ(d,0.0))
						{
								continue;
						}

						for(i = c + 1; i < mat->ncols; ++i)
						{
								t = AR_GetMatrixValue(mat, k,i);
								t -= AR_GetMatrixValue(mat, r,i) * d;

								if(AR_DBL_EQ(t,0.0)) /*有些误差会显示为-0.00000000x*/
								{
										t = 0.0;
								}

								AR_SetMatrixValue(mat, k,i,t);
						}
				}
		}
}


arStatus_t			AR_ReduceMatrixToEchelonForm(const arMatrix_t *mat, size_t *index, arMatrix_t *rm)
{
		arStatus_t status;
		AR_ASSERT(mat != NULL && rm != NULL);

		if((status = AR_CopyMatrix(rm, mat)) != AR_S_YES)
		{
				return status;
		}
		
		AR_ReduceMatrixToEchelonFormSelf(rm, index);

		return status;
}


/**************************通过LU取逆*************************************************

A = [ 0, 1, 2;   
      3, 4, 5;
      6, 7, 8
    ]
	;


inv(A) = [ x0, x1, x2;
           x3, x4, x5;
		   x6, x7, x8
		 ]
		 ;

A * inv(A) = I;

类似于

A * col0(inv(A) = [ 1;
					0;
					0
					];

A * col1(inv(A) = [ 0;
					1;
					0
					];


A * col2(inv(A) = [ 0;
					0;
					2
					];


***************************************************************************/

arStatus_t			AR_InverseMatrixSelf(arMatrix_t *mat)
{
		
		size_t i,j;
		size_t *index;
		arStatus_t status;
		arMatrix_t *m_tmp;
		arVector_t *b_v_tmp, *x_v_tmp;

		AR_ASSERT(mat != NULL);
		AR_ASSERT(mat->nrows == mat->ncols);
		
		status = AR_S_YES;
		
		m_tmp = NULL;
		b_v_tmp = x_v_tmp = NULL;

		index = AR_NEWARR0(size_t, mat->nrows);

		if(index == NULL)
		{
				
				status = AR_E_NOMEM;
				goto END_POINT;
		}

		m_tmp = AR_CopyNewMatrix(mat);

		if(m_tmp == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}

		b_v_tmp = AR_CreateVector(mat->nrows);
		x_v_tmp = AR_CreateVector(mat->nrows);

		if(b_v_tmp == NULL || x_v_tmp == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}

		status = AR_LUFactorMatrixSelf(m_tmp, index, NULL);

		if(status != AR_S_YES)
		{
				goto END_POINT;
		}


		AR_ZeroVector(b_v_tmp);
		AR_ZeroVector(x_v_tmp);

		for(i = 0; i < mat->nrows; ++i)
		{
				AR_SetVectorValue(b_v_tmp, i, 1.0);

				if((status = AR_LUSolveMatrix(m_tmp, index, x_v_tmp, b_v_tmp)) != AR_S_YES)
				{
						status = AR_S_NO;
						goto END_POINT;
				}

				for(j = 0; j < mat->nrows; ++j)
				{
						AR_SetMatrixValue(mat, j,i, AR_GetVectorValue(x_v_tmp, j));
				}

				AR_SetVectorValue(b_v_tmp, i, 0.0);
		}

END_POINT:
		if(b_v_tmp)
		{
				AR_DestroyVector(b_v_tmp);
				b_v_tmp = NULL;
		}

		if(x_v_tmp)
		{
				AR_DestroyVector(x_v_tmp);
				x_v_tmp = NULL;
		}

		if(m_tmp)
		{
				AR_DestroyMatrix(m_tmp);
				m_tmp = NULL;
		}

		if(index)
		{
				AR_DEL(index);
				index = NULL;
		}
		return status;
}



arStatus_t			AR_InverseLowerTriangularMatrixSelf(arMatrix_t *mat)
{
		size_t i,j,k;
		double d,sum,l,r;
		AR_ASSERT(mat != NULL);
		AR_ASSERT(mat->nrows == mat->ncols);

		for(i = 0; i < mat->nrows; ++i)
		{
				d = AR_GetMatrixValue(mat, i,i);

				if(AR_DBL_EQ(d,0.0))
				{
						return AR_S_NO;
				}

				d = 1.0 / d;
				AR_SetMatrixValue(mat, i,i, d);

				for(j = 0; j < i; ++j)
				{
						sum = 0.0;
						for(k = j; k < i; ++k)
						{
								l = AR_GetMatrixValue(mat, i,k);
								r = AR_GetMatrixValue(mat, k,j);
								sum -= l * r;
						}

						AR_SetMatrixValue(mat, i,j,sum * d);
				}

		}
		
		return AR_S_YES;
}



arStatus_t			AR_InverseUpperTriangularMatrixSelf(arMatrix_t *mat)
{
		int_t i,j,k;
		double d,sum,l,r;
		AR_ASSERT(mat != NULL);
		AR_ASSERT(mat->nrows == mat->ncols);

		for(i = (int_t)(mat->nrows - 1); i >= 0; --i)
		{
				d = AR_GetMatrixValue(mat, (size_t)i, (size_t)i);

				if(AR_DBL_EQ(d,0.0))
				{
						return AR_S_NO;
				}

				d = 1.0 / d;
				AR_SetMatrixValue(mat, i,i, d);

				for(j = (int_t)(mat->nrows - 1); j > i; --j)
				{
						sum = 0.0;
						for(k = j; k > i; --k)
						{
								l = AR_GetMatrixValue(mat, i,k);
								r = AR_GetMatrixValue(mat, k,j);
								sum -= l * r;
						}

						AR_SetMatrixValue(mat, i,j,sum * d);
				}

		}
		return AR_S_YES;
}


/*

此算法取自《C++数值算法》第二章

此算法逻辑类似于从

A = [	1,		2;
		3,		4
	];

则 
A =  [	1,		2,		1,		0;
		3,		4,		0,		1
     ];

->	[	1,		2,		1,		0;
		3/4,	1,		0,		1/4
     ];
->因为这里选择的主元是A(1,1) 则，消去A(0,1)这列，则将第二行乘以A(0,1)，则

	[	1,		2,		1,		0;
		3/2,	2,		0,		1/2
     ];

->相减
	[	-1/2,	0,		1,		-1/2;
		3/2,	2,		0,		1/2
     ];

->继续选择主元A(0,0)，则将A(0,0)变为1，需要乘以-2则

	[	1,		0,		-2,		1;
		3/4,	1,		0,		1/4
     ];
->这里需要消去A(1,0),则将第一行乘以3/4，则

	[	3/4,	0,		-3/2,	3/4;
		3/4,	1,		0,		1/4
     ];
->
	[	3/4,	0,		-3/2,	3/4;
		0,		1,		3/2,	-1/2
     ];

->除以3/4
	[	1,		0,		-2,		1;
		0,		1,		3/2,	-1/2
     ];

注意，算法中为了节约空间，去掉了1,0所占用的信息
例如：

A =  [	1,		2；	
		3,		4；	
     ];

->	[	1,		2;					
		3/4,	1/4
	];

-> d = 2;则此处2被消去，变换为0 - 1/4 * 2; 1 - 3/4*2为
	
	[	-1/2,	-1/2;
		3/4,	1/4
	];

之后主元为-1/2 乘以-2得到1，对应 (-1/2,	0,		1,		-1/2; )-> (1,0,-2,1)
-> 1,0被丢弃，保留-2,1										对应于：[	1,		0,		-2,		1;
																		3/4,	1,		0,		1/4
																	];
		[		-2,		1;		
				3/4,	1/4
		]
->																对应于：[	3/4,	0,		-3/2,	3/4;
																			3/4,	1,		0,		1/4
																		];
		d = 3/4; 
		[		-2,		1;		
				0,		1/4
		]

		所以 A(1,0) = 0 - -2 * d = 3/2 ; A(1,1) = 1/4 - 1 * d = -1/2;
->		[		-2,		1;		
				3/2,	-1/2
		]
		

*/

arStatus_t			AR_InverseMatrixByGaussJordanSelf(arMatrix_t *mat)
{
		arStatus_t status;
		
		size_t i, j, k, r, c;
		double d, max_val, t;
		int_t x;
		size_t *col_index, *row_index;
		bool_t *pivot_mark;

		AR_ASSERT(mat != NULL);
		AR_ASSERT(mat->nrows == mat->ncols);
		
		status = AR_S_YES;
		
		col_index = AR_NEWARR0(size_t, mat->nrows);
		row_index = AR_NEWARR0(size_t, mat->nrows);
		pivot_mark = AR_NEWARR0(bool_t, mat->nrows);
		
		if(col_index == NULL || row_index == NULL || pivot_mark == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}

		for(i = 0; i < mat->nrows; ++i)
		{
				max_val = 0.0;
				r = 0; 
				c = 0;

				for(j = 0; j < mat->nrows; ++j)
				{
						if(pivot_mark[j])
						{
								continue;
						}
						
						for(k = 0; k < mat->ncols; ++k)
						{
								if(pivot_mark[k])
								{
										continue;
								}

								d = AR_abs_dbl(AR_GetMatrixValue(mat,j,k));

								if(AR_DBL_GE(d, max_val))
								{
										max_val = d;
										r = j;
										c = k;
								}
						}
				}

				if(AR_DBL_EQ(max_val,0.0))
				{
						status = AR_S_NO;
						goto END_POINT;
				}

				pivot_mark[c] = true;

				if(r != c)
				{
						
						for(k = 0; k < mat->ncols; ++k)
						{
								t = AR_GetMatrixValue(mat, r,k);
								AR_SetMatrixValue(mat, r,k, AR_GetMatrixValue(mat, c,k));
								AR_SetMatrixValue(mat, c,k, t);
						}
				}

				row_index[i] = r;
				col_index[i] = c;

				d = 1.0 / AR_GetMatrixValue(mat, c,c);
				AR_SetMatrixValue(mat, c,c, 1.0);

				for(k = 0; k < mat->ncols; ++k)
				{
						double t = AR_GetMatrixValue(mat, c,k);
						AR_SetMatrixValue(mat, c,k, t * d);
				}

				for(j = 0; j < mat->nrows; ++j)
				{
						if(j == c)
						{
								continue;
						}

						d = AR_GetMatrixValue(mat, j, c);
						AR_SetMatrixValue(mat, j, c, 0.0);
						for(k = 0; k < mat->ncols; ++k)
						{
								double l,r;
								l = AR_GetMatrixValue(mat, j,k);
								r = AR_GetMatrixValue(mat, c,k);
								AR_SetMatrixValue(mat, j,k, l - r * d);
						}
				}

		}

		
		for(x = (int_t)(mat->nrows - 1); x >= 0; x--)
		{
				if(row_index[x] != col_index[x])
				{
						for(k = 0; k < mat->nrows; ++k)
						{
								double t;
								d = AR_GetMatrixValue(mat, k, row_index[x]);
								t = AR_GetMatrixValue(mat, k, col_index[x]);
								AR_SetMatrixValue(mat, k, row_index[x], t);
								AR_SetMatrixValue(mat, k, col_index[x], d);
						}
				}
		}

END_POINT:
		if(col_index)
		{
				AR_DEL(col_index);
				col_index = NULL;
		}

		if(row_index)
		{
				AR_DEL(row_index);
				row_index = NULL;
		}

		if(pivot_mark)
		{
				AR_DEL(pivot_mark);
				pivot_mark = NULL;
		}
		
		return status;
}


arStatus_t		AR_InverseSolveMatrix(const arMatrix_t *mat, arVector_t *x, const arVector_t *b)
{
		return AR_MultiplyMatrixByVector(mat, b, x);
}




/****************************************************************矩阵分解****************************************/

void			AR_TriDiagonalClearMatrixSelf(arMatrix_t *mat)
{
		size_t i,j;
		AR_ASSERT(mat != NULL);
		AR_ASSERT(AR_IsSquareMatrix(mat) == AR_S_YES);

		if(mat->nrows < 2)
		{
				return;
		}

		for(i = 0; i < mat->nrows - 2;  i++)
		{
				for(j = i+2; j < mat->ncols; j++)
				{
						AR_SetMatrixValue(mat, i,j,0.0);
						AR_SetMatrixValue(mat, j,i,0.0);
				}
		}

}

arStatus_t			AR_TriDiagonalSolveMatrix(const arMatrix_t *mat, arVector_t *x, const arVector_t *b)
{
		size_t i;
		int_t k;
		
		double *tmp, d,t;
		arStatus_t status;
		AR_ASSERT(mat != NULL && x != NULL && b != NULL);
		
		AR_ASSERT(AR_IsSquareMatrix(mat) == AR_S_YES);
		AR_ASSERT(AR_GetVectorSize(b) >= mat->nrows);
		
		status = AR_S_YES;
		
		tmp = NULL;
		tmp = AR_NEWARR0(double, mat->nrows);

		if(tmp == NULL)
		{
				status = AR_E_NOMEM;
				
				goto END_POINT;
		}

		if((status = AR_SetVectorSize(x, mat->ncols)) != AR_S_YES)
		{
				
				goto END_POINT;
		}


		d = AR_GetMatrixValue(mat, 0,0);
		if(AR_DBL_EQ(d,0.0))
		{
				status = AR_S_NO;
				goto END_POINT;
		}
		
		d = 1.0 / d;
		AR_SetVectorValue(x, 0, AR_GetVectorValue(b,0) * d);
		
		for(i = 1; i < mat->nrows; ++i)
		{
				tmp[i] = AR_GetMatrixValue(mat, i - 1, i) * d;
				d = AR_GetMatrixValue(mat, i,i) - AR_GetMatrixValue(mat, i, i -1) * tmp[i];
				
				if(AR_DBL_EQ(d,0.0))
				{
						status = AR_S_NO;
						goto END_POINT;
				}

				d = 1.0 / d;

				t = (AR_GetVectorValue(b, i) - AR_GetMatrixValue(mat, i, i - 1) * AR_GetVectorValue(x, i - 1)) * d;
				AR_SetVectorValue(x, i, t);
		}


		
		for(k = (int_t)mat->nrows - 2; k >= 0; k--)
		{
				t = AR_GetVectorValue(x,k);
				t = t - tmp[k + 1] * AR_GetVectorValue(x, k + 1);
				AR_SetVectorValue(x, k, t);
		}
		

END_POINT:
		if(tmp)
		{
				AR_DEL(tmp);
				tmp = NULL;
		}
		
		return status;
}



arStatus_t			AR_TriDiagonalInverseMatrix(const arMatrix_t *mat, arMatrix_t *inv)
{
		size_t i,j;
		arVector_t *x,*b;
		arStatus_t status;
		AR_ASSERT(mat != NULL && inv != NULL);
		AR_ASSERT(AR_IsSquareMatrix(mat) == AR_S_YES);

		status = AR_S_YES;

		x = AR_CreateVector(mat->ncols);
		b = AR_CreateVector(mat->nrows);

		if(x == NULL || b == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}

		AR_ZeroVector(b);
		AR_ZeroVector(x);

		if((status = AR_SetMatrixSize(inv, mat->nrows, mat->ncols)) != AR_S_YES)
		{
				status = AR_S_NO;
				goto END_POINT;
		}


		for(i = 0; i < mat->nrows; ++i)
		{
				AR_SetVectorValue(b, i, 1.0);
				
				status = AR_TriDiagonalSolveMatrix(mat, x, b);
				if(status != AR_S_YES)
				{
						goto END_POINT;
				}

				for(j = 0; j < mat->nrows; ++j)
				{
						AR_SetMatrixValue(inv, j,i, AR_GetVectorValue(x,j));
				}

				AR_SetVectorValue(b, i, 0.0);
		}

END_POINT:
		if(x)
		{
				AR_DestroyVector(x);
				x = NULL;
		}

		if(b)
		{
				AR_DestroyVector(b);
				b = NULL;
		}

		
		return status;
}



/*
LU分解

非方阵

L =  [	1	,	0
		l10	,	1
		l20	,	l21
     ];

U = [ 	u00	,	u01
		0	,	u11
    ];


则L = [	u00		,		u01
		l10 * u00	,		l10 * u01 + u11
		l20 * u00	,		l20 * u01 + l21 * u11
      ];

	  
方阵：
	L= 	[	1,		0,		0
			l10,	1,		0
			l20,	l21,	1
		];
	
	U=	[	u00,	u01,	u02
			0,		u11,	u12
			0,		0,		u22
		];


	A=	[	u00,				u01,					u02
			l10 * u00,			l10 * u01 + u11			l10 * u02 + u12
			l20 * u00,			l20 * u01 + l21 * u11,	l20 * u02 + l21 * u12 + u22
		];


算法：
A初始化为

	A=	[		u00,		u01,					u02
				l10 * u00,	l10 * u01 + u11			l10 * u02 + u12
				l20 * u00,	l20 * u01 + l21 * u11,	l20 * u02 + l21 * u12 + u22
		];


pivot = A(0,...) = [u00, u01, u02];
A10 = A10 / pivot[0] = l10;
A20 = A20 / pivot[0] = l20;

	A=	[	u00,		u01,					u02
			l10,		l10 * u01 + u11			l10 * u02 + u12
			l20,		l20 * u01 + l21 * u11,	l20 * u02 + l21 * u12 + u22
		];


A11 = A11 - l10 * pivot[1] = u11
A12 = A12 - l10 * pivot[2] = u12

A21 = A21 - l20 * pivot[1] = l21 * u11
A22 = A22 - l20 * pivot[2] = l21 * u12 + u22;

变换后A为：

	A=	[	u00,		u01,			u02
			l10,		u11				u12
			l20,		l21 * u11,		l21 * u12 + u22
		];


pivot = A(1,...) = [l10, u11, u12];
A21 = A21 / pivot[1] = l21 * u11 / u11 = l21;

	A=	[	u00,		u01,			u02
			l10,		u11			u12
			l20,		l21,			l21 * u12 + u22
		];


A22 = A22 - l21 * pivot[2] = l21 * u12 + u22 - l21 * u12 = u22;


	A=	[	u00,		u01,			u02
			l10,		u11			u12
			l20,		l21,			u22
		];
	


则LU分解完成
*/

arStatus_t		AR_LUFactorMatrixSelf(arMatrix_t *mat, size_t *index, double *det)
{
		size_t i,j,k,new_i,min_rc;
		double d, w, s,t;
		
		AR_ASSERT(mat != NULL);


		if(index)
		{
				for(i = 0; i < mat->nrows; ++i)
				{
						index[i] = i;
				}
		}

		w = 1.0f;

		min_rc = AR_MIN(mat->nrows, mat->ncols);

		for(i = 0; i < min_rc; ++i)
		{
				new_i = i;
				s = AR_abs_dbl(AR_GetMatrixValue(mat, i,i));

				if(index)
				{
						double t;
						for(j = i + 1; j < mat->nrows; ++j)
						{
								t = AR_abs_dbl(AR_GetMatrixValue(mat, j,i));

								if(AR_DBL_GE(t,s))
								{
										new_i = j;
										s = t;
								}
						}
				}

				if(AR_DBL_EQ(s,0.0))
				{
						return AR_S_NO;
				}

				if(new_i != i )
				{
						w = -w; /*换行后，行列式符号改变*/

						if(index)
						{
								k = index[i];
								index[i] = index[new_i];
								index[new_i] = k;
						}

						for(k = 0; k < mat->ncols; ++k)
						{
								t = AR_GetMatrixValue(mat, new_i,k);
								AR_SetMatrixValue(mat, new_i, k, AR_GetMatrixValue(mat, i,k));
								AR_SetMatrixValue(mat, i, k, t);
						}
				}

				d = 1.0 / AR_GetMatrixValue(mat, i,i);
				for(j = i + 1; j < mat->nrows; ++j)
				{
						t = AR_GetMatrixValue(mat, j, i);
						AR_SetMatrixValue(mat, j, i, t * d);
				}

				if(i < min_rc - 1)
				{
						for(j = i + 1; j < mat->nrows; ++j)
						{
								double l_x = AR_GetMatrixValue(mat, j,i);
								
								for(k = i + 1; k < mat->ncols; ++k)
								{
										t = AR_GetMatrixValue(mat, j,k);
										t -= AR_GetMatrixValue(mat, i,k) * l_x;
										AR_SetMatrixValue(mat, j,k,t);
								}
						}
				}
		}
		
		if(det != NULL)
		{
				for(i = 0; i < min_rc; ++i)
				{
						w *= AR_GetMatrixValue(mat, i,i);
				}

				*det = w;
		}

		return AR_S_YES;
}


arStatus_t			AR_LUSolveMatrix(const arMatrix_t *mat, const size_t *index, arVector_t *x,const arVector_t *b)
{
		int_t i,j;
		double s;
		arStatus_t status;
		AR_ASSERT(mat != NULL && b != NULL && x != NULL);

		AR_ASSERT(AR_GetVectorSize(b) == AR_GetMatrixNumRows(mat));

		status = AR_S_YES;
		status = AR_SetVectorSize(x, AR_GetMatrixNumColumns(mat));

		if(status != AR_S_YES)
		{
				return status;
		}

		for(i = 0; i < (int_t)mat->nrows; ++i)
		{
				if(index)
				{
						s = AR_GetVectorValue(b, index[i]);
				}else
				{
						s = AR_GetVectorValue(b, i);
				}

				for(j = 0; j < i; ++j)
				{
						s -= AR_GetMatrixValue(mat, (size_t)i,(size_t)j) * AR_GetVectorValue(x, (size_t)j);
				}

				AR_SetVectorValue(x, (size_t)i,s);
		}


		for(i = (int_t)AR_GetMatrixNumRows(mat) - 1; i >= 0; --i)
		{
				s = AR_GetVectorValue(x, i);
				for(j = i + 1; j < (int_t)mat->nrows; ++j)
				{
						s -= AR_GetMatrixValue(mat, i,j) * AR_GetVectorValue(x, j);
				}

				AR_SetVectorValue(x, i, s / AR_GetMatrixValue(mat, i,i));
		}

		return status;
}



arStatus_t			AR_LUInverseMatrix(const arMatrix_t *mat, const size_t *index, arMatrix_t *inv)
{
		arStatus_t status;
		size_t i,j;
		arVector_t *x,*b;
		AR_ASSERT(mat != NULL && inv != NULL);

		AR_ASSERT(mat->nrows == mat->ncols);

		status = AR_S_YES;

		x = AR_CreateVector(mat->ncols);
		b = AR_CreateVector(mat->nrows);

		if(x == NULL || b == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}

		AR_ZeroVector(b);
		AR_ZeroVector(x);
		if((status = AR_SetMatrixSize(inv, mat->nrows, mat->ncols)) != AR_S_YES)
		{
				goto END_POINT;
		}

		for(i = 0; i < mat->nrows; ++i)
		{
				AR_SetVectorValue(b, i, 1.0);

				if((status = AR_LUSolveMatrix(mat, index, x, b)) != AR_S_YES)
				{
						goto END_POINT;
				}

				for(j = 0; j < mat->nrows; ++j)
				{
						AR_SetMatrixValue(inv, j,i, AR_GetVectorValue(x,j));
				}

				AR_SetVectorValue(b, i, 0.0);
		}

END_POINT:
		if(x)
		{
				AR_DestroyVector(x);
				x = NULL;
		}

		if(b)
		{
				AR_DestroyVector(b);
				b = NULL;
		}

		return status;
}



arStatus_t			AR_UnpackMatrixLUFactors(const arMatrix_t *mat, arMatrix_t *L, arMatrix_t *U)
{
		size_t i,j;
		size_t lm,ln,um,un;
		arStatus_t status;
		AR_ASSERT(mat != NULL && L != NULL && U != NULL);

		status = AR_S_YES;
		if(mat->nrows == mat->ncols)
		{
				lm = ln = um = un = mat->nrows;
		}else if(mat->nrows > mat->ncols)
		{
				lm = mat->nrows;
				ln = mat->ncols;

				um = un = mat->ncols;
		}else
		{
				lm = ln = mat->nrows;
				um = mat->nrows;
				un = mat->ncols;
		}

		if((status = AR_SetMatrixSize(L, lm,ln)) != AR_S_YES)
		{
				return status;
		}
		AR_ZeroMatrix(L);

		if((status= AR_SetMatrixSize(U, um,un)) != AR_S_YES)
		{
				return status;
		}

		AR_ZeroMatrix(U);

		for ( i = 0; i < mat->nrows; i++ )
		{
				for (j = 0; j < i; j++ ) 
				{
						if(i < lm && j < ln)
						{
								AR_SetMatrixValue(L, i,j, AR_GetMatrixValue(mat, i,j));
						}
				}

				if(i < lm && i < ln)
				{
						AR_SetMatrixValue(L, i,i, 1.0);
				}

				for(j = i; j < mat->ncols; ++j)
				{
						if(i < um && j < un)
						{
								AR_SetMatrixValue(U, i,j, AR_GetMatrixValue(mat, i,j));
						}
				}
		}

		return status;
}



/*
输入：
		A=	[	u00,		u01,			u02
				l10,		u11			u12
				l20,		l21,			u22
			];

输出：
		A=	[		u00,		u01,					u02
					l10 * u00,	l10 * u01 + u11			l10 * u02 + u12
					l20 * u00,	l20 * u01 + l21 * u11,	l20 * u02 + l21 * u12 + u22
		];




*/

arStatus_t			AR_MultiplyMatrixLUFactors(const arMatrix_t *mat, const size_t *index, arMatrix_t *original_mat)
{
		arStatus_t status;
		size_t r, original_r, c, k;
		double sum;

		AR_ASSERT(mat != NULL && original_mat != NULL);
		status = AR_S_YES;

		if((status = AR_SetMatrixSize(original_mat, mat->nrows, mat->ncols)) != AR_S_YES)
		{
				return status;
		}

		AR_ZeroMatrix(original_mat);

		for(r = 0; r < mat->nrows; r++)
		{

				if(index != NULL)
				{
						original_r = index[r];
				}else 
				{
						original_r = r;
				}

				for(c = 0; c < mat->ncols; c++)
				{
						if(c >= r)
						{
								sum = AR_GetMatrixValue(mat, r,c);
						}else
						{
								sum = 0.0f;
						}

						for(k = 0; k <= c && k < r; k++)
						{
								sum += AR_GetMatrixValue(mat, r,k) * AR_GetMatrixValue(mat, k,c);
						}

						AR_SetMatrixValue(original_mat, original_r, c, sum);
				}
		}

		return status;
}



/*

LDL^T分解

  
方阵：
	L= 	[	1,		0,		0
			l10,	1,		0
			l20,	l21,	1
		];
	
	D=	[	d00,	0,		0
			0,		d11,	0
			0,		0,		d22
		];

	L^t = [	1,		l10,	l20
			0,	    1,		l21
			0,	    0,	    1
		];

		
   A = L * D * L^t


	A=	[	d00,				d00 * l10,						d00 * l20
			l10 * d00,			l10 * l10 * d00 + d11,			l10 * l20 * d00 + l21 * d11
			l20 * d00,			l10 * l20 * d00 + l21 * d11,	l20 * l20 * d00 + l21 * l21 * d11 + d22
		];

*/

arStatus_t			AR_LDLTFactorMatrixSelf(arMatrix_t *mat)
{
		arStatus_t status;
		size_t i,j,k;
		double sum, d;
		double *v;
		AR_ASSERT(mat != NULL);
		AR_ASSERT(AR_IsSquareMatrix(mat) == AR_S_YES);

		status = AR_S_YES;
		v = NULL;

		if((status = AR_IsSymmetricMatrix(mat, DBL_EPSILON)) != AR_S_YES)
		{
				goto END_POINT;
		}


		v = AR_NEWARR0(double, mat->nrows);

		if(v == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}

		for(i = 0; i < mat->nrows; ++i)
		{
				sum = AR_GetMatrixValue(mat, i,i);

				for(j = 0; j < i; ++j)
				{
						d = AR_GetMatrixValue(mat, i,j);
						v[j] = AR_GetMatrixValue(mat, j,j) * d;
						sum -= v[j] * d;
				}

				if(AR_DBL_EQ(sum, 0.0))
				{
						status = AR_S_NO;
						goto END_POINT;
				}

				AR_SetMatrixValue(mat, i,i, sum);
				d = 1 / sum;

				for(j = i + 1; j < mat->nrows; ++j)
				{
						sum = AR_GetMatrixValue(mat, j,i);
						
						for ( k = 0; k < i; k++ ) 
						{
								sum -= AR_GetMatrixValue(mat,j,k) * v[k];
						}

						AR_SetMatrixValue(mat, j, i, sum * d);
				}

		}

END_POINT:
		if(v)
		{
				AR_DEL(v);
				v = NULL;
		}
		
		return status;
}



void			AR_LDLTSolveMatrix(const arMatrix_t *mat, arVector_t *x, const arVector_t *b)
{
		int_t i, j;
		double sum;

		AR_ASSERT(mat->nrows == mat->ncols);
		AR_ASSERT(AR_GetVectorSize(x) == mat->nrows);
		AR_ASSERT(AR_GetVectorSize(b) == mat->nrows);
		
		AR_ZeroVector(x);

		
		for (i = 0; i < (int_t)mat->nrows; i++) 
		{
				sum = AR_GetVectorValue(b,(size_t)i);
				
				for(j = 0; j < i; j++)
				{
						sum = sum - AR_GetMatrixValue(mat, (size_t)i,(size_t)j) * AR_GetVectorValue(x, (size_t)j);
				}

				AR_SetVectorValue(x,(size_t)i,sum);
		}

		
		for (i = 0; i < (int_t)mat->nrows; i++)
		{ 
				sum = AR_GetVectorValue(x,(size_t)i);
				AR_SetVectorValue(x,i,sum / AR_GetMatrixValue(mat, (size_t)i,(size_t)i));
		}


		for(i = (int_t)mat->nrows - 1; i >= 0; i--)
		{
				sum = AR_GetVectorValue(x,i);

				for (j = i + 1; j < (int_t)mat->nrows; j++)
				{
						sum = sum - AR_GetMatrixValue(mat, j,i) * AR_GetVectorValue(x, j);
				}

				AR_SetVectorValue(x,i, sum);
		}
}


arStatus_t		AR_LDLTInverseMatrix(const arMatrix_t *mat, arMatrix_t *inv)
{
		arStatus_t status;
		size_t i,j;
		arVector_t *x,*b;
		AR_ASSERT(mat != NULL && inv != NULL);
		AR_ASSERT(mat->nrows == mat->ncols);
		status = AR_S_YES;
		x = NULL;
		b = NULL;

		x = AR_CreateVector(mat->ncols);
		b = AR_CreateVector(mat->nrows);

		if(x == NULL || b == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}

		AR_ZeroVector(b);
		AR_ZeroVector(x);

		if((status = AR_SetMatrixSize(inv, mat->nrows, mat->ncols)) != AR_S_YES)
		{
				goto END_POINT;
		}

		for(i = 0; i < mat->nrows; ++i)
		{
				AR_SetVectorValue(b, i, 1.0);
				AR_LDLTSolveMatrix(mat, x,b);

				for(j = 0; j < mat->nrows; ++j)
				{
						AR_SetMatrixValue(inv, j,i, AR_GetVectorValue(x,j));
				}

				AR_SetVectorValue(b, i, 0.0);
		}

END_POINT:
		if(x)
		{
				AR_DestroyVector(x);
				x = NULL;
		}

		if(b)
		{
				AR_DestroyVector(b);
				b = NULL;
		}

		return status;
}



arStatus_t			AR_UnpackMatrixLDLTFactors(const arMatrix_t *mat, arMatrix_t *L, arMatrix_t *D)
{
		size_t i,j;
		arStatus_t status;

		AR_ASSERT(mat != NULL && L != NULL && D != NULL);

		status = AR_S_YES;

		if((status = AR_SetMatrixSize(L, mat->nrows, mat->ncols)) != AR_S_YES)
		{
				return status;
		}

		if((status = AR_SetMatrixSize(D, mat->nrows, mat->ncols)) != AR_S_YES)
		{
				return status;
		}
		
		AR_ZeroMatrix(L);
		AR_ZeroMatrix(D);

		for (i = 0; i < mat->nrows; i++)
		{
				for(j = 0; j < i; j++) 
				{
						AR_SetMatrixValue(L, i,j, AR_GetMatrixValue(mat, i,j));
				}
				AR_SetMatrixValue(L,i,i,1.0);
				AR_SetMatrixValue(D,i,i, AR_GetMatrixValue(mat,i,i));
		}

		return status;
}



/*
从
LDT=	[	d00,			l10,			l20
			l10,			d11,			l21
			l20,			l21,			d22
		];

还原到A

	A=	[	d00,				d00 * l10,						d00 * l20
			l10 * d00,			l10 * l10 * d00 + d11,			l10 * l20 * d00 + l21 * d11
			l20 * d00,			l10 * l20 * d00 + l21 * d11,	l20 * l20 * d00 + l21 * l21 * d11 + d22
		];

算法：

O = [
			0,			0,			0,
			0,			0,			0,
			0,			0,			0
	];

	r = 0;

	O = [
			d00,		l10*d00,			l20*d00,
			0,			0,			0,
			0,			0,			0
	];

	r = 1;
	v[0] = A(1,0) * A(0,0) = l10 * d00;

	O = [
			d00,		l10*d00,						l20*d00,
			l00*d00,	l10 * l10 * d00 + d11,			l10 * l20 * d00 + l21 * d11,
			0,			0,								0
	];

	以此类推，得到原来的A

*/
arStatus_t		AR_MultiplyMatrixLDLTFactors(const arMatrix_t *mat, arMatrix_t *original_mat)
{
		size_t i,j,r;
		double *v, sum;
		arStatus_t status;
		AR_ASSERT(mat != NULL && original_mat != NULL);
		status = AR_S_YES;
		v = NULL;

		if((status = AR_SetMatrixSize(original_mat, mat->nrows, mat->ncols)) != AR_S_YES)
		{
				goto END_POINT;
		}

		AR_ZeroMatrix(original_mat);

		v = AR_NEWARR0(double, mat->nrows);

		if(v == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}

		for(r = 0; r < mat->nrows; r++)
		{
				for(i = 0; i < r; i++)
				{
						v[i] = AR_GetMatrixValue(mat, r,i) * AR_GetMatrixValue(mat, i,i);
				}

				for(i = 0; i < mat->ncols; i++) 
				{
						if(i < r)
						{
								sum = AR_GetMatrixValue(mat, i,i) * AR_GetMatrixValue(mat, r,i);
						}else if(i == r)
						{
								sum = AR_GetMatrixValue(mat, i,i);
						}else
						{
								sum = AR_GetMatrixValue(mat, r,r) * AR_GetMatrixValue(mat, i,r);
						}

						for(j = 0; j < i && j < r; j++)
						{
								sum = sum + AR_GetMatrixValue(mat, i,j) * v[j];
						}

						AR_SetMatrixValue(original_mat, r,i, sum);
				}
		}

END_POINT:
		if(v)
		{
				AR_DEL(v);
				v = NULL;
		}

		return status;
}






/**************************************************************************************************************************************/

/*
A = G*G^t;

G =		[		g00,	0,		0;
				g10,	g11,	0;
				g20,	g21,	g22
		];

G^t =	[
				g00,	g10,	g20;
				0,		g11,	g21;
				0,		0,		g22;
		];

A = [	g00 * g00,		g00 * g10,						g00 * g20;
		g10 * g00,		g10 * g10 + g11 * g11,			g10 * g20 + g11 * g21;
		g20 * g00,		g20 * g10 + g21 * g11,			g20 * g20 + g21 * g21 + g22 * g22
	];

*/





arStatus_t			AR_CholeskyFactorMatrixSelf(arMatrix_t *mat)
{
		arStatus_t status;
		size_t i,j,k;
		double *diag, sum;
		
		AR_ASSERT(mat != NULL);
		AR_ASSERT(AR_IsSquareMatrix(mat) == AR_S_YES);

		status = AR_S_YES;
		diag = NULL;

		diag = AR_NEWARR0(double, mat->nrows);

		if(diag == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}

		for(i = 0; i < mat->nrows; ++i)
		{
				for(j = 0; j < i; ++j)
				{
						sum = AR_GetMatrixValue(mat, i,j);

						for(k = 0; k < j; ++k)
						{
								sum -= AR_GetMatrixValue(mat, i,k) * AR_GetMatrixValue(mat, j,k);
						}

						AR_SetMatrixValue(mat, i,j, sum * diag[j]);
				}

				sum = AR_GetMatrixValue(mat, i,i);

				for(k = 0; k < i; ++k)
				{
						sum -= AR_GetMatrixValue(mat, i,k) * AR_GetMatrixValue(mat, i,k);
				}

				/*
				如果是正定矩阵，则sum必定为两个相同实数的平方，因此值必大于0
				*/
				if(AR_DBL_LEEQ(sum,0.0)) 
				{
						status = AR_S_NO;
						goto END_POINT;
				}

				diag[i] = 1 / AR_sqrt_dbl(sum);
				AR_SetMatrixValue(mat, i,i, diag[i] * sum);
		}

END_POINT:
		if(diag)
		{
				AR_DEL(diag);
				diag = NULL;
		}
		
		return status;
}



/*
G =		[		g00,	0,		0;
				g10,	g11,	0;
				g20,	g21,	g22
		];

G' =	[		g00,	g10,	g20;
				0,		g11,	g21;
				0,		0,		g22
		];

A = GG';

GG' * x = b;

Gz = b;



		g00 * x0 = b0;
		g10 * x0 + g11 * x1 = b1;
		g20 * x0 + g21 * x1 + g22 * x2 = b2;

G'x = z;
		g00 * x0 + g10 * x1 + g20 * x2 = z0;
		g11 * x1 + g21 * x2 = z1;
		g22 * x2 = z2;

*/
arStatus_t			AR_CholeskySolveMatrix(const arMatrix_t *mat, arVector_t *x, const arVector_t *b)
{
		arStatus_t status;
		int_t i,j;
		double sum;

		AR_ASSERT(mat->nrows == mat->ncols);
		AR_ASSERT(AR_GetVectorSize(b) >= mat->nrows);

		status = AR_S_YES;

		if((status = AR_SetVectorSize(x, mat->ncols)) != AR_S_YES)
		{
				return status;
		}

		for(i = 0; i < (int_t)mat->nrows; ++i)
		{
				sum = AR_GetVectorValue(b, (size_t)i);

				for(j = 0; j < i; ++j)
				{
						sum -= AR_GetMatrixValue(mat, (size_t)i, (size_t)j) * AR_GetVectorValue(x, (size_t)j);
				}
				
				AR_ASSERT(!AR_DBL_EQ(AR_GetMatrixValue(mat, (size_t)i,(size_t)i), 0.0));

				AR_SetVectorValue(x, (size_t)i, sum / AR_GetMatrixValue(mat, (size_t)i,(size_t)i));
		}

		for(i = (int_t)mat->nrows - 1; i >= 0; --i)
		{
				sum = AR_GetVectorValue(x, (size_t)i);

				for(j = i + 1; j < (int_t)mat->nrows; ++j)
				{
						sum -= AR_GetMatrixValue(mat,(size_t)j,(size_t)i) * AR_GetVectorValue(x, j);
				}

				AR_ASSERT(!AR_DBL_EQ(AR_GetMatrixValue(mat, (size_t)i,(size_t)i), 0.0));
				AR_SetVectorValue(x, (size_t)i, sum / AR_GetMatrixValue(mat, (size_t)i,(size_t)i));
		}

		return status;
}


arStatus_t		AR_CholeskyInverseMatrix(const arMatrix_t *mat, arMatrix_t *inv)
{
		arStatus_t status;
		size_t i,j;
		arVector_t *x,*b;
		AR_ASSERT(mat != NULL && inv != NULL);
		AR_ASSERT(mat->nrows == mat->ncols);

		status = AR_S_YES;
		x = NULL;
		b = NULL;


		x = AR_CreateVector(mat->ncols);
		b = AR_CreateVector(mat->nrows);

		if(x == NULL || b == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}

		AR_ZeroVector(b);
		AR_ZeroVector(x);

		if( (status = AR_SetMatrixSize(inv, mat->nrows, mat->ncols)) != AR_S_YES)
		{
				goto END_POINT;
		}

		for(i = 0; i < mat->nrows; ++i)
		{
				AR_SetVectorValue(b, i, 1.0);
				AR_CholeskySolveMatrix(mat, x,b);

				for(j = 0; j < mat->nrows; ++j)
				{
						AR_SetMatrixValue(inv, j,i, AR_GetVectorValue(x,j));
				}

				AR_SetVectorValue(b, i, 0.0);
		}

END_POINT:
		if(x)
		{
				AR_DestroyVector(x);
				x = NULL;
		}

		if(b)
		{
				AR_DestroyVector(b);
				b = NULL;
		}

		return status;
}



/*
G =		[		g00,	0,		0;
				g10,	g11,	0;
				g20,	g21,	g22
		];

A = G * G';


A = [	g00 * g00,		g00 * g10,						g00 * g20;
		g10 * g00,		g10 * g10 + g11 * g11,			g10 * g20 + g11 * g21;
		g20 * g00,		g20 * g10 + g21 * g11,			g20 * g20 + g21 * g21 + g22 * g22
	];

*/

arStatus_t			AR_MultiplyMatrixCholeskyFactors(const arMatrix_t *mat, arMatrix_t *original_mat)
{
		arStatus_t status;
		size_t i,j,r;
		double sum;

		AR_ASSERT(mat != NULL && original_mat != NULL);

		status = AR_S_YES;
		if((status = AR_SetMatrixSize(original_mat, mat->nrows, mat->ncols)) != AR_S_YES)
		{
				return status;
		}
		
		AR_ZeroMatrix(original_mat);
		

		for(r = 0; r < mat->nrows; r++)
		{
				for(i = 0; i < mat->nrows; i++) 
				{
						sum = 0.0f;
						
						for(j = 0; j <= i && j <= r; j++) 
						{
								sum += AR_GetMatrixValue(mat, r,j) * AR_GetMatrixValue(mat, i,j);
						}
						AR_SetMatrixValue(original_mat, r,i,sum);
				}
		}

		return status;
}









/************************************************************打印矩阵信息**************************************************************************/


arStatus_t			AR_MatrixToString(const arMatrix_t *mat, arString_t *str, size_t precision, const wchar_t *sp_str, const wchar_t *row_sp)
{
		size_t i;
		arVector_t *tmp;
		arStatus_t status;
		AR_ASSERT(mat != NULL && str != NULL);

		if(row_sp == NULL)
		{
				row_sp = AR_LINE_SP;
		}

		status = AR_S_YES;

		tmp = AR_CreateVector(mat->ncols);

		if(tmp == NULL)
		{
				status = AR_E_NOMEM;
				goto END_POINT;
		}


		for(i = 0; i < mat->nrows; ++i)
		{
				AR_GetMatrixRow(mat, i, tmp);
				status = AR_VectorToString(tmp, str, precision, sp_str);
				
				if(status != AR_S_YES)
				{
						goto END_POINT;
				}

				status = AR_AppendString(str, row_sp);

				if(status != AR_S_YES)
				{
						goto END_POINT;
				}
		}

END_POINT:
		if(tmp)
		{
				AR_DestroyVector(tmp);
				tmp = NULL;
		}
		return status;
}




AR_NAMESPACE_END
