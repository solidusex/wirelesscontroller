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


/******************************************************Vector**************************************************************/

struct __arsenal_vector_tag
{
		double			*v;
		size_t			count;
};


arVector_t*		AR_CreateVector(size_t size)
{
		arVector_t *vec;
		AR_ASSERT(size > 0);
		vec = AR_NEW(arVector_t);
		
		if(vec == NULL)
		{
				return NULL;
		}

		vec->count = size;
		vec->v = AR_NEWARR0(double, size);

		if(vec->v == NULL)
		{
				AR_DEL(vec);
				vec = NULL;
		}
		return vec;
}

void			AR_DestroyVector(arVector_t *vec)
{
		AR_ASSERT(vec != NULL);

		if(vec->v)
		{
				AR_DEL(vec->v);
		};

		AR_DEL(vec);
		vec = NULL;
}

arVector_t*		AR_CopyNewVector(const arVector_t *vec)
{
		arVector_t *new_v;
		AR_ASSERT(vec != NULL);

		new_v = AR_CreateVector(vec->count);

		if(new_v == NULL)
		{
				return NULL;
		}
		
		if(AR_CopyVector(new_v, vec) != AR_S_YES)
		{
				AR_DestroyVector(new_v);
				new_v = NULL;
		}

		return new_v;
}

arStatus_t		AR_CopyVector(arVector_t *dest, const arVector_t *src)
{
		AR_ASSERT(dest != NULL && src != NULL);

		if(dest == src)
		{
				return AR_S_YES;
		}


		if(dest->count != src->count)
		{
				arStatus_t ret = AR_SetVectorSize(dest, src->count);
				if(ret != AR_S_YES)
				{
						return ret;
				}
		}

		AR_memcpy(dest->v, src->v, sizeof(double) * src->count);

		return AR_S_YES;
}


arStatus_t		AR_SetVectorSize(arVector_t *vec, size_t size)
{
		AR_ASSERT(vec != NULL);
		AR_ASSERT(size > 0);

		if(vec->count == size)
		{
				return AR_S_YES;
		}else if(vec->count > size)
		{
				vec->count = size;
				return AR_S_YES;
		}else
		{
				double *p = AR_NEWARR(double, size);

				if(p == NULL)
				{
						return AR_E_NOMEM;
				}

				if(vec->v)
				{
						AR_DEL(vec->v);
						vec->v = NULL;
				}

				vec->count = size;
				vec->v = p;

				return AR_S_YES;
		}

		
}


arStatus_t	AR_SetVectorData(arVector_t *vec, size_t size, const double *data)
{
		arStatus_t ret;
		AR_ASSERT(vec != NULL && data != NULL);
		AR_ASSERT(size > 0);

		ret = AR_SetVectorSize(vec, size);
		if(ret != AR_S_YES)
		{
				return ret;
		}

		AR_memcpy(vec->v, data, vec->count * sizeof(double));

		return AR_S_YES;
}


size_t			AR_GetVectorSize(const arVector_t *vec)
{
		AR_ASSERT(vec != NULL);
		return vec->count;
}


void			AR_ZeroVector(arVector_t *vec)
{
		AR_ASSERT(vec != NULL && vec->count > 0);
		AR_memset(vec->v, 0, sizeof(double) * vec->count);
}

void			AR_NegateVector(arVector_t *vec)
{
		size_t i;
		AR_ASSERT(vec != NULL);

		for(i = 0; i < vec->count; ++i)
		{
				vec->v[i] = -vec->v[i];
		}

}

void			AR_ClampVector(arVector_t *vec, double minval, double maxval)
{
		size_t i;
		AR_ASSERT(vec != NULL);

		for(i = 0; i < vec->count; ++i)
		{
				if(AR_DBL_LE(vec->v[i], minval))
				{
						vec->v[i] = minval;
				
				}else if(AR_DBL_GE(vec->v[i], maxval))
				{
						vec->v[i] = maxval;
				}

		}
}

void			AR_RandomVector(arVector_t *vec)
{
		size_t i;
		AR_ASSERT(vec != NULL);

		for(i = 0; i < vec->count; ++i)
		{
				vec->v[i] = AR_rand_dbl();

		}

}


void		AR_CalcVectorLength(const arVector_t *vec, double *ret)
{
		AR_ASSERT(vec != NULL && ret != NULL);
		
		*ret = 0.0;

		AR_CalcVectorLengthSqr(vec, ret);
		
		*ret = AR_sqrt_dbl(*ret);
}

void			AR_CalcVectorLengthSqr(const arVector_t *vec, double *ret)
{
		size_t i;
		AR_ASSERT(vec != NULL && ret != NULL);

		*ret = 0.0;

		for(i = 0; i < vec->count; ++i)
		{
				*ret += vec->v[i] * vec->v[i];
		}

		
}

void			AR_NormalizeVector(arVector_t *vec)
{
		double len = 0.0;
		AR_ASSERT(vec != NULL);

		AR_CalcVectorLength(vec, &len);

		
		if(!AR_DBL_EQ(len,0.0))
		{
				AR_DivVectorByValSelf(vec, len);
		}
}


arStatus_t			AR_CalcVectorDistanceByVector(const arVector_t *vec, const arVector_t *other, double *ret)
{
		arVector_t *tmp;
		
		AR_ASSERT(vec != NULL && other != NULL);
		AR_ASSERT(vec->count == other->count);
		
		tmp = NULL;
		*ret = 0.0;

		tmp = AR_CopyNewVector(vec);
		
		if(tmp == NULL)
		{
				return AR_E_NOMEM;
		}

		AR_SubVectorByVectorSelf(tmp, other);
		AR_CalcVectorLength(tmp, ret);


		if(tmp)
		{
				AR_DestroyVector(tmp);
				tmp = NULL;
		}

		return AR_S_YES;
}


const double*	AR_GetVectorData(const arVector_t *vec)
{
		AR_ASSERT(vec != NULL);
		return vec->v;
}

void			AR_SwapElements(arVector_t *vec, size_t l, size_t r)
{
		double t;
		AR_ASSERT(vec != NULL);
		AR_ASSERT(l < vec->count && r < vec->count);
		t = vec->v[l];
		vec->v[l] = vec->v[r];
		vec->v[r] = t;
}

/*
int_t			AR_CompareVector(const arVector_t *l, const arVector_t *r)
{
		size_t i;
		AR_ASSERT(l != NULL && r != NULL);
		AR_ASSERT(l->count == r->count);

		for(i = 0; i < l->count; ++i)
		{
				if(!AR_DBL_EQ(l->v[i], r->v[i]))
				{
						return AR_DBL_LE(l->v[i], r->v[i]) ? -1 : 1;
				}
		}

		return 0;
}
*/

int_t			AR_CompareVector(const arVector_t *l, const arVector_t *r, double epsilon)
{
		size_t i;
		AR_ASSERT(l != NULL && r != NULL);
		AR_ASSERT(l->count == r->count);

		for(i = 0; i < l->count; ++i)
		{
				double e = AR_abs_dbl(l->v[i] - r->v[i]);
				if(e > epsilon)
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


double			AR_GetVectorValue(const arVector_t *vec, size_t idx)
{
		AR_ASSERT(vec != NULL);
		AR_ASSERT(idx < vec->count);

		return vec->v[idx];
}

void			AR_SetVectorValue(arVector_t *vec, size_t idx, double val)
{
		AR_ASSERT(vec != NULL);
		AR_ASSERT(idx < vec->count);

		vec->v[idx] = val;
}



void			AR_CalcVectorInnerProduct(const arVector_t *vec, const arVector_t *other, double *ret)
{
		size_t i;
		AR_ASSERT(vec != NULL && other != NULL && ret != NULL);
		AR_ASSERT(vec->count == other->count);

		*ret = 0.0;

		for(i = 0; i < vec->count; ++i)
		{
				*ret += (vec->v[i] * other->v[i]);
		}
}



arStatus_t			AR_CalcVectorNormNumber(const arVector_t *vec, arVectorNormType_t t, double *ret)
{
		size_t i;
		double sum, tmp;
		AR_ASSERT(vec != NULL && ret != NULL);
		*ret = 0.0;
		sum = 0.0;

		switch(t)
		{
		case AR_VEC_NORM_MAX:
		case AR_VEC_NORM_NEGAMAX:
		{
				sum = AR_GetVectorValue(vec, 0);
				
				for(i = 1; i < vec->count; ++i)
				{
						tmp = AR_abs_dbl(AR_GetVectorValue(vec, i));

						if(t == AR_VEC_NORM_NEGAMAX)
						{
								if(AR_DBL_LE(tmp, sum))
								{
										sum = tmp;
								}
						}else
						{
								if(AR_DBL_GE(tmp, sum))
								{
										sum = tmp;
								}
						}
				}
		}
				break;
		case AR_VEC_NORM_1:
				for(i = 0; i < vec->count; ++i)
				{
						sum += AR_abs_dbl(AR_GetVectorValue(vec, i));
				}
				break;
		default: /*AR_VEC_NORM_2:*/
				AR_CalcVectorLength(vec, &sum);
				break;
		}
		*ret = sum;
		return AR_S_YES;

}





void			AR_AddVectorByVectorSelf(arVector_t *vec, const arVector_t *other)
{
		size_t i;
		AR_ASSERT(vec != NULL && other != NULL);
		AR_ASSERT(vec->count == other->count);

		for(i = 0; i < vec->count; ++i)
		{
				vec->v[i] += other->v[i];
		}
}

void			AR_SubVectorByVectorSelf(arVector_t *vec, const arVector_t *other)
{
		size_t i;
		AR_ASSERT(vec != NULL && other != NULL);
		AR_ASSERT(vec->count == other->count);

		for(i = 0; i < vec->count; ++i)
		{
				vec->v[i] -= other->v[i];
		}
}


void			AR_MulVectorByValSelf(arVector_t *vec, double val)
{
		size_t i;
		AR_ASSERT(vec != NULL);
		for(i = 0; i < vec->count; ++i)
		{
				vec->v[i] *= val;
		}
}

void			AR_DivVectorByValSelf(arVector_t *vec, double val)
{
		AR_ASSERT(vec != NULL);
		AR_ASSERT(!AR_DBL_EQ(val,0.0));

		AR_MulVectorByValSelf(vec, 1.0 / val);

}



arStatus_t		AR_AddVectorByVector(const arVector_t *vec, const arVector_t *other, arVector_t *dest)
{
		arStatus_t ret;
		AR_ASSERT(vec != NULL && other != NULL && dest != NULL);
		AR_ASSERT(vec->count == other->count);

		ret = AR_CopyVector(dest, vec);
		if(ret != AR_S_YES)
		{
				return ret;
		}

		AR_AddVectorByVectorSelf(dest, other);

		return AR_S_YES;
}

arStatus_t			AR_SubVectorByVector(const arVector_t *vec, const arVector_t *other, arVector_t *dest)
{
		arStatus_t ret;
		AR_ASSERT(vec != NULL && other != NULL && dest != NULL);
		AR_ASSERT(vec->count == other->count);
		
		ret = AR_CopyVector(dest, vec);
		if(ret != AR_S_YES)
		{
				return ret;
		}

		AR_SubVectorByVectorSelf(dest, other);

		return AR_S_YES;
}

arStatus_t			AR_MulVectorByVal(const arVector_t *vec, double val, arVector_t *dest)
{
		arStatus_t ret;
		AR_ASSERT(vec != NULL && dest != NULL);
		
		ret = AR_CopyVector(dest, vec);
		if(ret != AR_S_YES)
		{
				return ret;
		}

		AR_MulVectorByValSelf(dest, val);

		return AR_S_YES;
}


arStatus_t			AR_DivVectorByVal(const arVector_t *vec, double val, arVector_t *dest)
{
		arStatus_t ret;
		AR_ASSERT(vec != NULL && dest != NULL);
		AR_ASSERT(!AR_DBL_EQ(val,0.0));

		ret = AR_CopyVector(dest, vec);
		if(ret != AR_S_YES)
		{
				return ret;
		}

		AR_DivVectorByValSelf(dest, val);

		return AR_S_YES;
}




/***********************************************************************************************************************/


arStatus_t			AR_VectorToString(const arVector_t *vec, arString_t *str, size_t precision, const wchar_t *sp_str)
{
		arStatus_t ret;
		size_t i;
		
		wchar_t fmt[80];

		AR_ASSERT(vec != NULL && str != NULL);

		if(sp_str == NULL)
		{
				sp_str = L" ";
		}
		
		
		if(AR_swprintf(fmt, 64, L"%%.%Iuf",  precision) < 0)
		{
				return AR_E_INVAL;
		}

		for(i = 0; i < vec->count; ++i)
		{
				ret = AR_AppendFormatString(str, fmt, vec->v[i]);
				if(ret != AR_S_YES)
				{
						return ret;
				}

				if(i < vec->count - 1)
				{
						ret = AR_AppendString(str, sp_str);
						if(ret != AR_S_YES)
						{
								return ret;
						}
				}
		}

		return AR_S_YES;
}




	



AR_NAMESPACE_END
