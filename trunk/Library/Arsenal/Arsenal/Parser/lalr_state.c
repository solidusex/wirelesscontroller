
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


#include "lalr.h"

AR_NAMESPACE_BEGIN


lalrState_t*	Parser_CreateState()
{
		lalrState_t		*state;
		state = AR_NEW0(lalrState_t);

		if(state == NULL)
		{
				return NULL;
		}


		return state;
}

void			Parser_DestroyState(lalrState_t *state)
{
		AR_ASSERT(state != NULL);

		if(state->actions != NULL)
		{
				AR_DEL(state->actions);
				state->actions = NULL;
		}

		if(state->basis != NULL)
		{
				Parser_DestroyConfigList(state->basis, false);
				state->basis = NULL;
		}

		if(state->all_config != NULL)
		{

				Parser_DestroyConfigList(state->all_config, true);
				state->all_config = NULL;
		}

		AR_DEL(state);
}


lalrAction_t*	Parser_InsertAction(lalrState_t *state, lalrState_t *to, const psrSymb_t *symb, const lalrConfig_t *config)
{
		lalrAction_t	*action;
		AR_ASSERT(state != NULL  && symb != NULL && config != NULL);

		if(state->count == state->cap)
		{
				size_t new_cap;
				lalrAction_t *new_acts;


				new_cap =  (state->cap + 4)*2;
				new_acts = AR_NEWARR(lalrAction_t, new_cap);

				if(new_acts == NULL)
				{
						return NULL;
				}

				AR_memcpy(new_acts, state->actions, state->count * sizeof(lalrAction_t));

				if(state->actions)
				{
						AR_DEL(state->actions);
						state->actions = NULL;
				}
				
				state->cap = new_cap;
				state->actions = new_acts;
		}
		
		action = &state->actions[state->count];
		state->count++;
		action->act_type = to == NULL ? LALR_ACT_REDUCE : LALR_ACT_SHIFT;
		action->symb = symb;
		action->to = to;
		action->config = config;
		return action;
}


void			Parser_DestroyState_ALL(lalrState_t *state)
{
		lalrStateSet_t	set;
		size_t i;
		AR_ASSERT(state != NULL);

		Parser_InitStateSet(&set);

		if(Parser_CollectState(&set, state) != AR_S_YES)
		{
				AR_error(AR_ERR_FATAL, L"collect lalrState_t* overflow\r\n");
				return;
		}

		for(i = 0; i < set.count; ++i)
		{
				Parser_DestroyState(set.set[i]);
		}
		
		Parser_UnInitStateSet(&set);
}



void			Parser_InitStateSet(lalrStateSet_t *set)
{
		AR_ASSERT(set != NULL);
		AR_memset(set, 0, sizeof(*set));
}

void			Parser_UnInitStateSet(lalrStateSet_t *set)
{
		AR_ASSERT(set != NULL);

		if(set->set != NULL)
		{
				AR_DEL(set->set);
		}
		AR_memset(set, 0, sizeof(*set));
}


arStatus_t			Parser_InsertToStateSet(lalrStateSet_t *set, lalrState_t *state)
{
		AR_ASSERT(set != NULL && state != NULL);
		
		if(set->count == set->cap)
		{
				size_t new_cap;
				lalrState_t **new_stats;

				new_cap = (set->cap + 4) * 2;
				new_stats = AR_NEWARR(lalrState_t*, new_cap);

				if(new_stats == NULL)
				{
						return AR_E_NOMEM;
				}

				AR_memcpy(new_stats, set->set, set->count * sizeof(lalrState_t*));

				if(set->set)
				{
						AR_DEL(set->set);
						set->set = NULL;
				}

				set->cap = new_cap;
				set->set = new_stats;
		}
		set->set[set->count++] = state;
		return AR_S_YES;
}



int_t			Parser_IndexOfStateSet(const lalrStateSet_t *set, const lalrState_t *state)
{
		int_t i;
		AR_ASSERT(set != NULL && state != NULL);

		for(i = 0; i < (int_t)set->count; ++i)
		{
				if(set->set[i] == state)
				{
						return i;
				}
		}
		return -1;
}


lalrState_t*	Parser_FindStateByBasis(lalrStateSet_t *set, lalrConfigList_t *basis)
{
		size_t i;
		AR_ASSERT(set != NULL && basis != NULL);

		for(i = 0; i < set->count; ++i)
		{
				if(Parser_CompConfigList(set->set[i]->basis, basis) == 0)
				{
						return set->set[i];
				}
		}
		
		return NULL;
}

arStatus_t			Parser_CollectState(lalrStateSet_t *set, lalrState_t *start)
{
		size_t i;
		arStatus_t status;
		AR_ASSERT(set != NULL && start != NULL);

		status = AR_S_YES;

		set->count = 0;

		status = Parser_InsertToStateSet(set, start);

		if(status != AR_S_YES)
		{
				return status;
		}

		for(i = 0; i < set->count; ++i)
		{
				size_t k;
				lalrState_t *state;

				state = set->set[i];
				
				AR_ASSERT(state != NULL);

				for(k = 0; k < state->count; ++k)
				{
						if(state->actions[k].act_type == LALR_ACT_SHIFT)
						{
								AR_ASSERT(state->actions[k].to != NULL);

								if(Parser_IndexOfStateSet(set, state->actions[k].to) == -1)
								{
										status = Parser_InsertToStateSet(set, state->actions[k].to);

										if(status != AR_S_YES)
										{
												return status;
										}
								}
						}
				}
		}

		return status;
}




AR_NAMESPACE_END

