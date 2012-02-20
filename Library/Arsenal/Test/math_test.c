
#include "test.h"


#include <math.h>
#include <time.h>

#if defined(__LIB)

AR_NAMESPACE_BEGIN




void misc_test()
{
		AR_printf(L"%d\r\n", AR_abs_32(-1));
		AR_printf(L"%d\r\n", AR_abs_32(1));

		AR_printf(L"%qd\r\n", AR_abs_64(-1));
		AR_printf(L"%qd\r\n", AR_abs_64(1));

		AR_printf(L"%f\r\n", AR_abs_dbl(-0.111f));
		AR_printf(L"%f\r\n", AR_abs_dbl(0.111f));
		
}


static void __print_vector(const arVector_t *vec)
{
		arString_t *str = AR_CreateString();
		AR_VectorToString(vec, str, 2, NULL);
		AR_printf(L"%ls\r\n", AR_GetStringCString(str));
		AR_DestroyString(str);
		str = NULL;
}


void vector_test()
{
		//AR_srand(time(NULL));

		arVector_t *vec = AR_CreateVector(2);
		arVector_t *vec2 = AR_CreateVector(3);
#if(0)
		for(size_t i = 0; i < 3; ++i)
		{
				AR_SetVectorValue(vec, i, AR_rand_dbl());
		}
#endif

		AR_SetVectorValue(vec, 0, 3.0);
		AR_SetVectorValue(vec, 1, 4.0);


		{
		arString_t *out;

		out = AR_CreateString();

		AR_VectorToString(vec, out, 30, L",");

		AR_printf(L"%ls\r\n", AR_GetStringCString(out));

		AR_DestroyString(out);
		out = NULL;
		}
		
		double res;
		arStatus_t status;
		AR_CalcVectorInnerProduct(vec, vec, &res);

		AR_printf(L"%f\r\n", res);


		AR_CalcVectorLength(vec, &res);
		

		AR_printf(L"%f\r\n", res);

		AR_CalcVectorLengthSqr(vec, &res);

		AR_printf(L"%f\r\n", res);


		AR_NormalizeVector(vec);



		{
		arString_t *out;

		out = AR_CreateString();

		AR_VectorToString(vec, out, 30, L",");

		AR_printf(L"%ls\r\n", AR_GetStringCString(out));

		AR_DestroyString(out);
		out = NULL;
		}

		AR_SetVectorSize(vec, 3);

		AR_SetVectorValue(vec, 0, 1);
		AR_SetVectorValue(vec, 1, -2);
		AR_SetVectorValue(vec, 2, 3);

		status = AR_CalcVectorNormNumber(vec, AR_VEC_NORM_1, &res);
		AR_ASSERT(status == AR_S_YES);
		AR_printf(L"AR_VEC_NORM_1 == %g\r\n", res);
		
		status = AR_CalcVectorNormNumber(vec, AR_VEC_NORM_2, &res);
		AR_ASSERT(status == AR_S_YES);
		AR_printf(L"AR_VEC_NORM_2 == %g\r\n", res);

		status = AR_CalcVectorNormNumber(vec, AR_VEC_NORM_MAX, &res);
		AR_ASSERT(status == AR_S_YES);
		AR_printf(L"AR_VEC_NORM_MAX == %g\r\n", res);

		status = AR_CalcVectorNormNumber(vec, AR_VEC_NORM_NEGAMAX, &res);
		AR_ASSERT(status == AR_S_YES);
		AR_printf(L"AR_VEC_NORM_NEGAMAX == %g\r\n", res);



		AR_SetVectorSize(vec2, 3);
		AR_SetVectorSize(vec, 3);

		AR_RandomVector(vec);
		__print_vector(vec);

		AR_MulVectorByValSelf(vec,3.0);
		__print_vector(vec);

		AR_RandomVector(vec2);
		__print_vector(vec2);

		AR_AddVectorByVectorSelf(vec,vec2);
		__print_vector(vec);

		AR_DestroyVector(vec);
		AR_DestroyVector(vec2);
}



void __print_matrix(const arMatrix_t *mat, size_t precision = 2)
{
		arString_t *str = AR_CreateString();
		AR_MatrixToString(mat, str, precision, NULL, NULL);
		AR_printf(L"%ls\r\n", AR_GetStringCString(str));
		AR_DestroyString(str);
		str = NULL;
}



void matrix_test()
{
		arStatus_t status = AR_S_YES;
		arMatrix_t *mat = NULL, *mat2 = NULL;
		arString_t *str = NULL;

		str = AR_CreateString();


		mat = AR_CreateMatrix(2,2);
		mat2 = AR_CreateMatrix(2,2);
		
		status = AR_SetMatrixSize(mat, 9,5);
		AR_ASSERT(status == AR_S_YES);

		AR_ZeroMatrix(mat);

		AR_RandomMatrix(mat);
		__print_matrix(mat);

		AR_NegateMatrix(mat);
		__print_matrix(mat);
		
		AR_CopyMatrix(mat2, mat);
		__print_matrix(mat);

		int_t ret = AR_CompareMatrix(mat, mat2, DBL_EPSILON);
		AR_printf(L"cmp == %d\r\n", ret);

		AR_NegateMatrix(mat2);

		ret = AR_CompareMatrix(mat, mat2, DBL_EPSILON);
		AR_printf(L"cmp == %d\r\n", ret);

		ret = AR_CompareMatrix(mat2, mat, DBL_EPSILON);
		AR_printf(L"cmp == %d\r\n", ret);


		{
				arMatrix_t *nm = AR_CopyNewMatrix(mat);

				ret = AR_CompareMatrix(mat, nm, DBL_EPSILON);
				AR_printf(L"nm cmp == %d\r\n", ret);
				AR_DestroyMatrix(nm);
				nm = NULL;
		}

		{
				arMatrix_t *nm = AR_CopyNewMatrix(mat);

				AR_NegateMatrix(nm);
				AR_ClampMatrix(nm, 0.1, 0.2);
				__print_matrix(nm);
				
				AR_DestroyMatrix(nm);
				nm = NULL;
		}


		{
				arMatrix_t *nm = AR_CopyNewMatrix(mat);

				AR_SetMatrixSize(nm, 3,3);
				AR_IdentityMatrix(nm);

				__print_matrix(nm);

				
				arVector_t *vtmp = AR_CreateVector(3);
				AR_RandomVector(vtmp);
				__print_vector(vtmp);
				AR_printf(L"----\r\n");
				AR_DiagonalMatrix(nm, vtmp);
				__print_matrix(nm);
				
				AR_DestroyMatrix(nm);
				nm = NULL;

				if(vtmp)
				{
						AR_DestroyVector(vtmp);
						vtmp = NULL;
				}

		}


		{
				AR_SetMatrixSize(mat, 4,5);
				AR_RandomMatrix(mat);
				__print_matrix(mat);

				getchar();
				AR_printf(L"change 0-3\r\n");
				AR_SwapMatrixRows(mat, 0,3);
				__print_matrix(mat);

				AR_printf(L"change 1-2\r\n");
				AR_SwapMatrixRows(mat, 1,2);
				__print_matrix(mat);
				getchar();

				AR_printf(L"change 2-2\r\n");
				AR_SwapMatrixRows(mat, 2,2);
				__print_matrix(mat);
				getchar();


				AR_printf(L"change 0-4\r\n");
				AR_SwapMatrixColumns(mat, 0,4);
				__print_matrix(mat);

				AR_printf(L"change 1-3\r\n");
				AR_SwapMatrixColumns(mat, 1,3);
				__print_matrix(mat);
				getchar();

				AR_printf(L"change 2-2\r\n");
				AR_SwapMatrixColumns(mat, 2,2);
				__print_matrix(mat);
				getchar();


				AR_printf(L"remove 2\r\n");
				AR_RemoveMatrixRow(mat, 2);
				__print_matrix(mat);
				getchar();

				AR_printf(L"remove 0\r\n");
				AR_RemoveMatrixRow(mat, 0);
				__print_matrix(mat);
				getchar();

				AR_printf(L"remove 1\r\n");
				AR_RemoveMatrixRow(mat, 1);
				__print_matrix(mat);
				getchar();
				
				AR_SetMatrixSize(mat, 4,5);
				AR_RandomMatrix(mat);
				__print_matrix(mat);

				while(AR_GetMatrixNumColumns(mat) > 1)
				{
						uint_32_t n = AR_rand32() % AR_GetMatrixNumColumns(mat);
						AR_printf(L"remove %d\r\n", n);
						AR_RemoveMatrixColumn(mat, n);
						__print_matrix(mat);
						getchar();

				}
				
				AR_SetMatrixSize(mat, 5,5);
				AR_RandomMatrix(mat);
				__print_matrix(mat);

				AR_ClearMatrixUpperTriangle(mat);
				__print_matrix(mat);

				getchar();

				AR_SetMatrixSize(mat, 5,5);
				AR_RandomMatrix(mat);
				__print_matrix(mat);

				AR_ClearMatrixLowerTriangle(mat);
				__print_matrix(mat);

				getchar();
		}

		{
				AR_SetMatrixSize(mat, 5,5);
				AR_ZeroMatrix(mat);
				__print_matrix(mat);

				for(size_t i = 0; i < 5; ++i)
				{
						for(size_t j = 0; j < 5; ++j)
						{
								AR_SetMatrixValue(mat, i,j, j);
						}
				}

				__print_matrix(mat);

				/*
				void			(arMatrix_t *mat, size_t row, size_t col, double val);
				double			AR_GetMatrixValue(const arMatrix_t *mat, size_t row, size_t col);
				*/
		}


		{
				arMatrix_t *nm = AR_CopyNewMatrix(mat);

				AR_SetMatrixSize(nm, 4,4);
				AR_IdentityMatrix(nm);
				__print_matrix(nm);

				arVector_t *vtmp = AR_CreateVector(5);

				for(size_t i = 0; i < 4; ++i)
				{
						AR_GetMatrixColumn(nm, i,vtmp);
						__print_vector(vtmp);
						AR_printf(L"----\r\n");
				}

				
				

				
				

				AR_DestroyMatrix(nm);
				nm = NULL;

				if(vtmp)
				{
						AR_DestroyVector(vtmp);
						vtmp = NULL;
				}

				
		}
		

		


		if(mat)
		{
				AR_DestroyMatrix(mat);
				mat = NULL;
		}

		if(mat2)
		{
				AR_DestroyMatrix(mat2);
				mat2 = NULL;
		}

		if(str)
		{
				AR_DestroyString(str);
				str = NULL;
		}

}





void matrix_test2()
{
		arStatus_t status;
		bool_t ret;
		arMatrix_t *mat = NULL, *mat2 = NULL;
		arString_t *str = NULL;
		arVector_t *vtmp = AR_CreateVector(5);

		str = AR_CreateString();


		mat = AR_CreateMatrix(2,2);
		mat2 = AR_CreateMatrix(2,2);
		


		status = AR_S_YES;
		ret = NULL;
		AR_SetMatrixSize(mat, 5,5);
		AR_RandomMatrix(mat);


		AR_ASSERT(AR_IsSquareMatrix(mat) == AR_S_YES);

		AR_IdentityMatrix(mat);
		status = AR_IsIdentityMatrix(mat, DBL_EPSILON);
		AR_ASSERT(status == AR_S_YES);

		AR_ZeroMatrix(mat);
		status = AR_IsZeroMatrix(mat, DBL_EPSILON);
		AR_ASSERT(status == AR_S_YES);

		status = AR_SetVectorSize(vtmp, AR_GetMatrixNumRows(mat));
		AR_ASSERT(status == AR_S_YES);
		AR_RandomVector(vtmp);

		AR_DiagonalMatrix(mat, vtmp);
		status = AR_IsDiagonalMatrix(mat, DBL_EPSILON);
		AR_ASSERT(status == AR_S_YES);

		status = AR_SetMatrixSize(mat, 4,4);
		AR_ASSERT(status == AR_S_YES);

		AR_ZeroMatrix(mat);
		AR_IdentityMatrix(mat);
		
		for(size_t i = 0; i < AR_GetMatrixNumRows(mat) - 1; ++i)
		{
				AR_SetMatrixValue(mat, i, i + 1, 2);
				AR_SetMatrixValue(mat, i + 1, i, 2);
		}


		__print_matrix(mat);
		status = AR_IsTriDiagonalMatrix(mat, DBL_EPSILON);
		AR_ASSERT(status == AR_S_YES);


		AR_ZeroMatrix(mat);
		AR_IdentityMatrix(mat);
		status = AR_IsSymmetricMatrix(mat, DBL_EPSILON);
		AR_ASSERT(status == AR_S_YES);

		AR_SetMatrixValue(mat, 0,3, 10);
		AR_SetMatrixValue(mat, 3,0, 10);
		__print_matrix(mat);
		status = AR_IsSymmetricMatrix(mat, DBL_EPSILON);
		AR_ASSERT(status == AR_S_YES);


		AR_ZeroMatrix(mat);
		AR_IdentityMatrix(mat);
		AR_SetMatrixValue(mat, 0,0, 10);
		status = AR_IsOrthogonalMatrix(mat, DBL_EPSILON);
		AR_ASSERT(status == AR_S_YES);


		AR_SetMatrixSize(mat, 3,3);


		AR_SetMatrixValue(mat, 0,0,3.0);
		AR_SetMatrixValue(mat, 1,0,1.0);
		AR_SetMatrixValue(mat, 2,0,1.0);

		AR_SetMatrixValue(mat, 0,1,-1);
		AR_SetMatrixValue(mat, 1,1,2);
		AR_SetMatrixValue(mat, 2,1,1);

		AR_SetMatrixValue(mat, 0,2,-1.0/2.0);
		AR_SetMatrixValue(mat, 1,2,-2.0);
		AR_SetMatrixValue(mat, 2,2,7.0/2.0);

		__print_matrix(mat);
		status = AR_IsOrthogonalMatrix(mat, DBL_EPSILON);
		AR_ASSERT(status == AR_S_YES);

		status = AR_IsOrthonormalMatrix(mat, DBL_EPSILON);
		if(status == AR_S_YES)
		{
				AR_ASSERT(false);
		}

		for(size_t i = 0; i < AR_GetMatrixNumColumns(mat); ++i)
		{
				AR_GetMatrixColumn(mat, i, vtmp);
				AR_NormalizeVector(vtmp);
				for(size_t k = 0; k < AR_GetVectorSize(vtmp); ++k)
				{
						AR_SetMatrixValue(mat, k,i,AR_GetVectorValue(vtmp,k));
				}
		}
		__print_matrix(mat);

		status = AR_IsOrthonormalMatrix(mat, FLT_EPSILON);
		AR_ASSERT(status == AR_S_YES);
		

		AR_SetMatrixValue(mat, 2,2,7.0/2.0);

		__print_matrix(mat);

		status = AR_IsOrthonormalMatrix(mat, FLT_EPSILON);
		AR_ASSERT(status != AR_S_YES);
		

/****************************************ÅÐ¶Ï¾ØÕóÀàÐÍ******************************************

bool_t			AR_IsPositiveDefiniteMatrix(const arMatrix_t *mat, double epsilon);
bool_t			AR_IsSymmetricPositiveDefinite(const arMatrix_t *mat, double epsilon);
bool_t			AR_IsPositiveSemiDefinite(const arMatrix_t *mat, double epsilon);
bool_t			AR_IsSymmetricPositiveSemiDefinite(const arMatrix_t *mat, double epsilon);

*/


		if(mat)
		{
				AR_DestroyMatrix(mat);
				mat = NULL;
		}

		if(mat2)
		{
				AR_DestroyMatrix(mat2);
				mat2 = NULL;
		}

		if(vtmp)
		{
				AR_DestroyVector(vtmp);
				vtmp = NULL;
		}

		if(str)
		{
				AR_DestroyString(str);
				str = NULL;
		}
}



void matrix_test3()
{
		arStatus_t status;
		arMatrix_t *mat = NULL, *mat2 = NULL, *mat3 = NULL;
		arString_t *str = NULL;
		arVector_t *vtmp = NULL, *vtmp1 = NULL;
		bool_t ret = true;

		str = AR_CreateString();
		vtmp = AR_CreateVector(5);
		vtmp1 = AR_CreateVector(5);

		mat = AR_CreateMatrix(2,2);
		mat2 = AR_CreateMatrix(2,2);
		mat3 = AR_CreateMatrix(2,2);

		status = AR_SetMatrixSize(mat,4,4);
		AR_ASSERT(status == AR_S_YES);
		AR_IdentityMatrix(mat);
		__print_matrix(mat);

		status = AR_MultiplyMatrixByScalar(mat, 3.0, mat2);
		AR_ASSERT(status == AR_S_YES);
		__print_matrix(mat2);

		status = AR_MultiplyMatrixByScalarSelf(mat, 2.0);
		AR_ASSERT(status == AR_S_YES);
		__print_matrix(mat);

		status = AR_MultiplyMatrixByMatrix(mat,mat2, mat3);
		AR_ASSERT(status == AR_S_YES);
		__print_matrix(mat3);

		status = AR_IsDiagonalMatrix(mat3, DBL_EPSILON);
		AR_ASSERT(ret);

		status = AR_SetVectorSize(vtmp, 4);
		AR_ASSERT(status == AR_S_YES);

		for(size_t i = 0; i < 4; ++i)
		{
				AR_SetVectorValue(vtmp,i, i + 1);
		}

		status = AR_MultiplyMatrixByVector(mat3, vtmp, vtmp1);
		AR_ASSERT(status == AR_S_YES);
		__print_vector(vtmp1);




		AR_SetMatrixSize(mat, 4,1);
		AR_SetMatrixValue(mat, 0,0, 3.0);
		AR_SetMatrixValue(mat, 1,0, 4.0);
		AR_SetMatrixValue(mat, 2,0, 5.0);
		AR_SetMatrixValue(mat, 3,0, 6.0);
		__print_matrix(mat);
		__print_vector(vtmp);

		status = AR_MultiplyTransposeMatrixByVector(mat, vtmp, vtmp1);
		AR_ASSERT(status == AR_S_YES);
		__print_vector(vtmp1);


		AR_SetMatrixSize(mat, 2,4);
		AR_RandomMatrix(mat);
		__print_matrix(mat);
		status = AR_TransposeMatrixSelf(mat);
		AR_ASSERT(status == AR_S_YES);
		__print_matrix(mat);

		AR_SetMatrixSize(mat2, 2,3);
		AR_RandomMatrix(mat2);
		__print_matrix(mat2);

		status = AR_MultiplyMatrixByMatrix(mat,mat2, mat3);
		AR_ASSERT(status == AR_S_YES);
		__print_matrix(mat3);

		status = AR_TransposeMatrixSelf(mat);
		AR_ASSERT(status == AR_S_YES);
		status = AR_MultiplyTransposeMatrixByMatrix(mat, mat2, mat3);
		AR_ASSERT(status == AR_S_YES);
		__print_matrix(mat3);

END_POINT:
		if(mat)
		{
				AR_DestroyMatrix(mat);
				mat = NULL;
		}

		if(mat2)
		{
				AR_DestroyMatrix(mat2);
				mat2 = NULL;
		}

		if(mat3)
		{
				AR_DestroyMatrix(mat3);
				mat3 = NULL;
		}

		if(vtmp)
		{
				AR_DestroyVector(vtmp);
				vtmp = NULL;
		}

		if(vtmp1)
		{
				AR_DestroyVector(vtmp1);
				vtmp1 = NULL;
		}

		if(str)
		{
				AR_DestroyString(str);
				str = NULL;
		}
}



/*

bool_t			AR_InverseMatrixSelf(arMatrix_t *mat);

bool_t			AR_InverseLowerTriangularMatrixSelf(arMatrix_t *mat);
bool_t			AR_InverseUpperTriangularMatrixSelf(arMatrix_t *mat);

bool_t			AR_InverseMatrixByGaussJordanSelf(arMatrix_t *mat);
void			AR_InverseSolveMatrix(const arMatrix_t *mat, arVector_t *x, const arVector_t *b);

*/
void matrix_test4()
{
		arStatus_t status;
		arMatrix_t *mat = NULL, *mat2 = NULL, *mat3 = NULL;
		arString_t *str = NULL;
		arVector_t *vtmp = NULL, *vtmp1 = NULL;


		str = AR_CreateString();
		vtmp = AR_CreateVector(5);
		vtmp1 = AR_CreateVector(5);

		mat = AR_CreateMatrix(2,2);
		mat2 = AR_CreateMatrix(2,2);
		mat3 = AR_CreateMatrix(2,2);


		AR_RandomMatrix(mat);
		__print_matrix(mat);

		AR_SetMatrixValue(mat, 0,0,1);
		AR_SetMatrixValue(mat, 0,1,2);
		AR_SetMatrixValue(mat, 1,0,3);
		AR_SetMatrixValue(mat, 1,1,4);

		__print_matrix(mat);


		status = AR_InverseMatrixSelf(mat);
		AR_ASSERT(status == AR_S_YES);
	

		__print_matrix(mat);


		double tmp[] = 
		{
						0.9649,    0.9572,    0.1419,
						0.1576,    0.4854,    0.4218,
						0.9706,    0.8003,    0.9157,
		};

		status = AR_SetMatrixData(mat, 3,3, tmp);
		AR_ASSERT(status == AR_S_YES);

		__print_matrix(mat);
		
		status = AR_InverseMatrixSelf(mat);
		AR_ASSERT(status == AR_S_YES);
		
		__print_matrix(mat, 4);


		status = AR_SetMatrixData(mat, 3,3, tmp);
		AR_ASSERT(status == AR_S_YES);
		AR_ClearMatrixUpperTriangle(mat);
		__print_matrix(mat, 4);

		status = AR_InverseLowerTriangularMatrixSelf(mat);
		AR_ASSERT(status == AR_S_YES);
		__print_matrix(mat, 4);


		status = AR_SetMatrixData(mat, 3,3, tmp);
		AR_ASSERT(status == AR_S_YES);
		AR_ClearMatrixUpperTriangle(mat);
		__print_matrix(mat, 4);

		status = AR_InverseMatrixSelf(mat);
		AR_ASSERT(status == AR_S_YES);
		
		__print_matrix(mat, 4);



		status = AR_SetMatrixData(mat, 3,3, tmp);
		AR_ASSERT(status == AR_S_YES);
		AR_ClearMatrixLowerTriangle(mat);
		__print_matrix(mat, 4);

		status = AR_InverseUpperTriangularMatrixSelf(mat);
		AR_ASSERT(status == AR_S_YES);
		
		__print_matrix(mat, 4);


		status = AR_SetMatrixData(mat, 3,3, tmp);
		AR_ClearMatrixLowerTriangle(mat);
		__print_matrix(mat, 4);

		status = AR_InverseMatrixSelf(mat);
		AR_ASSERT(status == AR_S_YES);
	
		__print_matrix(mat, 4);


		double a_tmp1[] = 
		{
				1,2,
				3,4
		};
		
		status = AR_SetMatrixData(mat, 2,2,a_tmp1);
		AR_ASSERT(status == AR_S_YES);
		__print_matrix(mat);

		/*
		AR_InverseMatrixSelf(mat);
		__print_matrix(mat);
		*/

		status = AR_InverseMatrixByGaussJordanSelf(mat);
		AR_ASSERT(status == AR_S_YES);
		
		__print_matrix(mat);




		double a_tmp[] = 
		{
				1,2,
				5,12
		};

		AR_SetMatrixData(mat, 2,2,a_tmp);
		__print_matrix(mat);

		status = AR_InverseMatrixByGaussJordanSelf(mat);
		AR_ASSERT(status == AR_S_YES);
	
		__print_matrix(mat);

		double b[] = 
		{
				-1,
				3
		};

		arVector_t *vx = vtmp, *vb = vtmp1;

		status = AR_SetVectorData(vb, 2, b);
		AR_ASSERT(status == AR_S_YES);
		__print_vector(vb);

		status = AR_InverseSolveMatrix(mat, vx, vb);
		AR_ASSERT(status == AR_S_YES);
		__print_vector(vx);
		
#if(0)
		
		double b_tmp[] = 
		{
				-1,
				3,
		};

		AR_SetVectorData(vtmp, 2, b_tmp);

		__print_vector(vtmp);

		

		AR_InverseSolveMatrix(mat, vtmp1, vtmp);

		__print_vector(vtmp1);
#endif


END_POINT:
		if(mat)
		{
				AR_DestroyMatrix(mat);
				mat = NULL;
		}

		if(mat2)
		{
				AR_DestroyMatrix(mat2);
				mat2 = NULL;
		}

		if(mat3)
		{
				AR_DestroyMatrix(mat3);
				mat3 = NULL;
		}

		if(vtmp)
		{
				AR_DestroyVector(vtmp);
				vtmp = NULL;
		}

		if(vtmp1)
		{
				AR_DestroyVector(vtmp1);
				vtmp1 = NULL;
		}

		if(str)
		{
				AR_DestroyString(str);
				str = NULL;
		}
}



void matrix_test_factorization()
{
		arStatus_t status;
		
		arMatrix_t *mat = NULL, *mat2 = NULL, *mat3 = NULL, *L = NULL, *U = NULL;
		arString_t *str = NULL;
		arVector_t *vtmp = NULL, *vtmp1 = NULL;


		str = AR_CreateString();
		vtmp = AR_CreateVector(5);
		vtmp1 = AR_CreateVector(5);

		mat = AR_CreateMatrix(2,2);
		mat2 = AR_CreateMatrix(2,2);
		mat3 = AR_CreateMatrix(2,2);
		L = AR_CreateMatrix(2,2);
		U = AR_CreateMatrix(2,2);

		double data[] = 
		{
				8,		9,		10,
				21,		5,		47,
				3,		7,		11
		};
		size_t index[20];
		double det = 0.0;
		AR_SetMatrixData(mat, 3,3,data);
		__print_matrix(mat);

		status = AR_S_YES;
		

		status = AR_LUFactorMatrixSelf(mat, index, &det);
		AR_ASSERT(status == AR_S_YES);
		

		__print_matrix(mat);

		AR_printf(L"det == %g\r\n", det);


		status = AR_UnpackMatrixLUFactors(mat, L,U);
		AR_ASSERT(status == AR_S_YES);

		__print_matrix(L);
		__print_matrix(U);


		status = AR_MultiplyMatrixLUFactors(mat, NULL, mat2);
		AR_ASSERT(status == AR_S_YES);
		__print_matrix(mat2);

printf("------------------------------------------------\r\n");

		double data_ldlt[] = 
		{
				10,		20,		30,
				20,		45,		80,
				30,		80,		171
		};

		status = AR_SetMatrixData(mat, 3,3,data_ldlt);
		AR_ASSERT(status == AR_S_YES);

		__print_matrix(mat);
		status = AR_LDLTFactorMatrixSelf(mat);
		AR_ASSERT(status == AR_S_YES);
		

		__print_matrix(mat);


		status = AR_UnpackMatrixLDLTFactors(mat, L,U);
		AR_ASSERT(status == AR_S_YES);

		__print_matrix(L);
		__print_matrix(U);

		status = AR_MultiplyMatrixLDLTFactors(mat, mat2);
		AR_ASSERT(status == AR_S_YES);
		__print_matrix(mat2);



		double data_rref[] = 
		{
				0,     0,     0,     0,     2,     8,     4,
				0,     0,     0,     1,     3,    11,     9,
				0,     3,   -12,    -3,    -9,   -24,   -33,
				0,    -2,     8,     1,     6,    17,    21
		};

		AR_SetMatrixData(mat, 4,7,data_rref);
		__print_matrix(mat);


		AR_ReduceMatrixToEchelonFormSelf(mat, index);
		__print_matrix(mat);

		size_t calc = 0;
		status = AR_CalcMatrixRank(mat, &calc);
		AR_ASSERT(status == AR_S_YES);

		printf("rank == %u\r\n", calc);
		printf("------------------------\r\n");


		double data_rref2[] = 
		{
				1,     2,
				3,     4,
				5,     6,
				7,     8,
		};

		AR_SetMatrixData(mat, 4,2,data_rref2);
		__print_matrix(mat);


		AR_ReduceMatrixToEchelonFormSelf(mat, index);
		__print_matrix(mat);
		for(size_t i = 0; i < 4; ++i)
		{
				printf("%d ", index[i]);
		}
		printf("\r\n");
		status = AR_CalcMatrixRank(mat, &calc);
		AR_ASSERT(status == AR_S_YES);
		printf("rank == %u\r\n", calc);
		printf("------------------------\r\n");



		double data_rref3[] = 
		{
				9,     8,		9,10,
				3,     4,		5,6,
				1,     2,		3,4,
				5,     6,		7,8,
				
		};

		AR_SetMatrixData(mat, 4,4,data_rref3);
		__print_matrix(mat);


		AR_ReduceMatrixToEchelonFormSelf(mat, index);
		__print_matrix(mat);
		for(size_t i = 0; i < 4; ++i)
		{
				printf("%d ", index[i]);
		}
		printf("\r\n");
		
		status = AR_CalcMatrixRank(mat, &calc);
		AR_ASSERT(status == AR_S_YES);
		printf("rank == %u\r\n", calc);



		double data_rref4[] = 
		{
				2,0,2,1,
				0,5,2,-2,
				0,0,3,2,
				0,0,0,0
		};
		
		AR_SetMatrixData(mat, 4,4,data_rref4);
		__print_matrix(mat);


		AR_ReduceMatrixToEchelonFormSelf(mat, index);
		__print_matrix(mat);
		for(size_t i = 0; i < 4; ++i)
		{
				printf("%d ", index[i]);
		}
		printf("\r\n");
		
		status = AR_CalcMatrixRank(mat, &calc);
		AR_ASSERT(status == AR_S_YES);
		printf("rank == %u\r\n", calc);



		double data_adj[] = 
		{
				1, 2, 3,
				2, 3, 4,
				3, 4, 5
		};
		
		AR_SetMatrixData(mat, 3,3,data_adj);
		__print_matrix(mat);

		status = AR_CalcMatrixDeterminant(mat, &det);
		AR_ASSERT(status == AR_S_NO);
		printf("det == %g\r\n", det);



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		double data_chol[] = 
		{
				1,     1     ,1     ,1     ,1     ,1,
				1     ,2     ,3     ,4     ,5     ,6,
				1     ,3     ,6    ,10    ,15    ,21,
				1     ,4    ,10    ,20    ,35    ,56,
				1     ,5    ,15    ,35    ,70   ,126,
				1     ,6    ,21    ,56   ,126   ,252
		};


		AR_SetMatrixData(mat, 6,6,data_chol);
		__print_matrix(mat);

		status = AR_IsSymmetricMatrix(mat, DBL_EPSILON);
		AR_ASSERT(status == AR_S_YES);
		

		status = AR_CholeskyFactorMatrixSelf(mat);
		AR_ASSERT(status == AR_S_YES);
		

		AR_ClearMatrixUpperTriangle(mat);
		__print_matrix(mat);

		status = AR_MultiplyMatrixCholeskyFactors(mat, mat2);
		AR_ASSERT(status == AR_S_YES);

		__print_matrix(mat2);

		status = AR_CholeskyInverseMatrix(mat, mat2);
		AR_ASSERT(status == AR_S_YES);
		__print_matrix(mat2);





		double data_ldlt2[] = 
		{
				10,		20,		30,
				20,		45,		80,
				30,		80,		171
		};

		AR_SetMatrixData(mat, 3,3,data_ldlt2);
		__print_matrix(mat);

		AR_CopyMatrix(mat2, mat);
		
		status = AR_LUFactorMatrixSelf(mat2, index, NULL);
		AR_ASSERT(status == AR_S_YES);
		__print_matrix(mat2);
		
		
		
		status = AR_LDLTFactorMatrixSelf(mat);
		AR_ASSERT(status == AR_S_YES);
		
		

		__print_matrix(mat);


		status = AR_UnpackMatrixLDLTFactors(mat, L,U);
		AR_ASSERT(status == AR_S_YES);

		__print_matrix(L);
		__print_matrix(U);

		status = AR_MultiplyMatrixLDLTFactors(mat, mat2);
		AR_ASSERT(status == AR_S_YES);
		__print_matrix(mat2);



		double data_cho2[] = 
		{
				1,     -2,  
				-2,		1
		};


		AR_SetMatrixData(mat, 2,2,data_cho2);
		__print_matrix(mat);

		status = AR_CholeskyFactorMatrixSelf(mat);
		AR_ASSERT(status != AR_S_YES);
		
		
		AR_SetMatrixData(mat, 2,2,data_cho2);
		__print_matrix(mat);

		status = AR_IsPositiveDefiniteMatrix(mat, DBL_EPSILON);
		AR_ASSERT(status != AR_S_YES);
	

		



END_POINT:

		if(L)
		{
				AR_DestroyMatrix(L);
				L = NULL;
		}

		if(U)
		{
				AR_DestroyMatrix(U);
				U = NULL;
		}

		if(mat)
		{
				AR_DestroyMatrix(mat);
				mat = NULL;
		}

		if(mat2)
		{
				AR_DestroyMatrix(mat2);
				mat2 = NULL;
		}

		if(mat3)
		{
				AR_DestroyMatrix(mat3);
				mat3 = NULL;
		}

		if(vtmp)
		{
				AR_DestroyVector(vtmp);
				vtmp = NULL;
		}

		if(vtmp1)
		{
				AR_DestroyVector(vtmp1);
				vtmp1 = NULL;
		}

		if(str)
		{
				AR_DestroyString(str);
				str = NULL;
		}
}

#if(0)
#endif

void math_test()
{

		AR_srand(time(NULL));
		//misc_test();
		//vector_test();

		/*matrix_test();
		matrix_test2();
		matrix_test3();
		matrix_test4();
		*/
		matrix_test_factorization();

}





AR_NAMESPACE_END

#endif
