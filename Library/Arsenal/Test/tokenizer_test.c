#include "test.h"



#if defined(__LIB)







/*
** {======================================================
** PATTERN MATCHING
** =======================================================
*/

#define LUA_MAXCAPTURES	32
#define LUA_QL(x)	"'" x "'"
#define LUA_QS		LUA_QL("%s")
#define uchar(c)        ((unsigned char)(c))

#define CAP_UNFINISHED	(-1)
#define CAP_POSITION	(-2)

typedef struct MatchState 
{
		const char *src_init;  /* init of source string */
		const char *src_end;  /* end (`\0') of source string */
		int level;  /* total number of captures (finished or unfinished) */

		void			*L;
		
		struct {
				const char *init;
				ptrdiff_t len;
		} capture[LUA_MAXCAPTURES];
}MatchState;


#define L_ESC		'%'
#define SPECIALS	"^$*+?.([%-"


int luaL_error(void *l, const char *msg)
{
		AR_UNUSED(l);
		printf("%s\r\n", msg);
		abort();
		return -1;
}



static int check_capture (MatchState *ms, int l) 
{
		l -= '1';
		if (l < 0 || l >= ms->level || ms->capture[l].len == CAP_UNFINISHED)
				return luaL_error(ms->L, "invalid capture index");
		return l;
}


static int capture_to_close (MatchState *ms) 
{
		int level = ms->level;
		for (level--; level>=0; level--)
				if (ms->capture[level].len == CAP_UNFINISHED) return level;
		return luaL_error(ms->L, "invalid pattern capture");
}


static const char *classend (MatchState *ms, const char *p) 
{
		switch (*p++) 
		{
		case L_ESC: 
		{
				if (*p == '\0')
						luaL_error(ms->L, "malformed pattern (ends with " LUA_QL("%%") ")");
				return p+1;
		}
		case '[': 
		{
				if (*p == '^') p++;
				do {  /* look for a `]' */
						if (*p == '\0')
								luaL_error(ms->L, "malformed pattern (missing " LUA_QL("]") ")");
						
						if (*(p++) == L_ESC && *p != '\0')
								p++;  /* skip escapes (e.g. `%]') */
				} while (*p != ']');
				return p+1;
		}
		default: 
		{
				return p;
		}
		}
}


static int match_class (int c, int cl) 
{
		int res;
		switch (tolower(cl)) 
		{
		case 'a' : res = isalpha(c); break;
		case 'c' : res = iscntrl(c); break;
		case 'd' : res = isdigit(c); break;
		case 'l' : res = islower(c); break;
		case 'p' : res = ispunct(c); break;
		case 's' : res = isspace(c); break;
		case 'u' : res = isupper(c); break;
		case 'w' : res = isalnum(c); break;
		case 'x' : res = isxdigit(c); break;
		case 'z' : res = (c == 0); break;
		default: 
				return (cl == c);
		}
		return (islower(cl) ? res : !res);
}


static int matchbracketclass (int c, const char *p, const char *ec)
{
		int sig = 1;
		
		if(*(p+1) == '^')
		{
				sig = 0;
				p++;  /* skip the `^' */
		}
		
		while (++p < ec) 
		{
				if (*p == L_ESC) 
				{
						p++;
						if (match_class(c, uchar(*p)))
								return sig;
				}else if ((*(p+1) == '-') && (p+2 < ec)) 
				{
						p+=2;
						if (uchar(*(p-2)) <= c && c <= uchar(*p))
								return sig;
				}else if (uchar(*p) == c)
				{
						return sig;
				}
		}
		
		return !sig;
}


static int singlematch (int c, const char *p, const char *ep) 
{
		switch (*p) 
		{
		case '.': 
				return 1;  /* matches any char */
		case L_ESC:
				return match_class(c, uchar(*(p+1)));
		case '[': 
				return matchbracketclass(c, p, ep-1);
		default:  
				return (uchar(*p) == c);
		}
}


static const char *match (MatchState *ms, const char *s, const char *p);


static const char *matchbalance (MatchState *ms, const char *s, const char *p) 
{
		if (*p == 0 || *(p+1) == 0)
				luaL_error(ms->L, "unbalanced pattern");
		if (*s != *p)
		{
				return NULL;
		}
		else 
		{
				int b = *p;
				int e = *(p+1);
				int cont = 1;
				while (++s < ms->src_end) 
				{
						if (*s == e) 
						{
								if (--cont == 0) return s+1;
						}
						else if (*s == b) 
						{
								cont++;
						}
				}
		}
		return NULL;  /* string ends out of balance */
}


static const char *max_expand (MatchState *ms, const char *s,const char *p, const char *ep) 
{
		ptrdiff_t i = 0;  /* counts maximum expand for item */
		while ((s+i)<ms->src_end && singlematch(uchar(*(s+i)), p, ep))
				i++;
		/* keeps trying to match with the maximum repetitions */
		while (i>=0) 
		{
				const char *res = match(ms, (s+i), ep+1);
				if (res) return res;
				i--;  /* else didn't match; reduce 1 repetition to try again */
		}
		return NULL;
}


static const char *min_expand (MatchState *ms, const char *s, const char *p, const char *ep) 
{
		for (;;) 
		{
				const char *res = match(ms, s, ep+1); /*先匹配此模式串后面的模式，如果成功了就返回(匹配0次)*/
				if (res != NULL)
						return res;
				else if (s < ms->src_end && singlematch(uchar(*s), p, ep)) /*否则匹配1-N次*/
						s++;  /* try with one more repetition */
				else 
						return NULL;
		}
}



static const char *start_capture (MatchState *ms, const char *s, const char *p, int what) 
{
		const char *res;
		int level = ms->level;
		if (level >= LUA_MAXCAPTURES) luaL_error(ms->L, "too many captures");
		ms->capture[level].init = s;
		ms->capture[level].len = what;
		ms->level = level+1;
		if ((res=match(ms, s, p)) == NULL)  /* match failed? */
				ms->level--;  /* undo capture */
		return res;
}


static const char *end_capture (MatchState *ms, const char *s, const char *p) 
{
		int l = capture_to_close(ms);
		const char *res;
		ms->capture[l].len = s - ms->capture[l].init;  /* close capture */
		
		if ((res = match(ms, s, p)) == NULL)  /* match failed? */
				ms->capture[l].len = CAP_UNFINISHED;  /* undo capture */
		return res;
}


static const char *match_capture (MatchState *ms, const char *s, int l) 
{
		size_t len;
		l = check_capture(ms, l);
		len = ms->capture[l].len;
		if ((size_t)(ms->src_end-s) >= len && memcmp(ms->capture[l].init, s, len) == 0)
				return s+len;
		else return NULL;
}


static const char *match (MatchState *ms, const char *s, const char *p) 
{

init: /* using goto's to optimize tail recursion */
		switch (*p)
		{
		case '(': 
		{		/* start capture */
				if (*(p+1) == ')')  /* position capture? */
						return start_capture(ms, s, p+2, CAP_POSITION);
				else
						return start_capture(ms, s, p+1, CAP_UNFINISHED);
		}
		case ')': 
		{  /* end capture */
				return end_capture(ms, s, p+1);
		}
		case L_ESC: 
		{
				switch (*(p+1)) 
				{
				case 'b': 
				{  /* balanced string? */
						s = matchbalance(ms, s, p+2);
						if (s == NULL) return NULL;
						p+=4; 
						goto init;  /* else return match(ms, s, p+4); */
				}
				case 'f': 
				{
						/* frontier? */
						const char *ep; char previous;
						p += 2;
						if (*p != '[')
								luaL_error(ms->L, "missing " LUA_QL("[") " after " LUA_QL("%%f") " in pattern");
						
						ep = classend(ms, p);  /* points to what is next */
						previous = (s == ms->src_init) ? '\0' : *(s-1);
						
						if (matchbracketclass(uchar(previous), p, ep-1) || !matchbracketclass(uchar(*s), p, ep-1)) 
								return NULL;

						p=ep;
						goto init;  /* else return match(ms, s, ep); */
				}
				default: 
				{
						if (isdigit(uchar(*(p+1)))) 
						{  /* capture results (%0-%9)? */
								s = match_capture(ms, s, uchar(*(p+1)));
								
								if(s == NULL)
										return NULL;
								p+=2; 
								goto init;  /* else return match(ms, s, p+2) */
						}
						goto dflt;  /* case default */
				}
				}
		}
		case '\0': 
		{  /* end of pattern */
				return s;  /* match succeeded */
		}
		case '$': 
		{
				if (*(p+1) == '\0')  /* is the `$' the last char in pattern? */
						return (s == ms->src_end) ? s : NULL;  /* check end of string */
				else 
						goto dflt;
		}
		default: 
dflt:
		{  /* it is a pattern item */
				const char *ep = classend(ms, p);  /* points to what is next */
				int m = s < ms->src_end && singlematch(uchar(*s), p, ep);
				
				switch (*ep) 
				{
				case '?': 
				{  /* optional */
						const char *res;
						if (m && ((res=match(ms, s+1, ep+1)) != NULL))
								return res;
						p=ep+1; 
						goto init;  /* else return match(ms, s, ep+1); */
				}
				case '*': 
				{  /* 0 or more repetitions */
						return max_expand(ms, s, p, ep);
				}
				case '+': 
				{  /* 1 or more repetitions */
						return (m ? max_expand(ms, s+1, p, ep) : NULL);
				}
				case '-': 
				{		/* 0 or more repetitions (minimum) */
						return min_expand(ms, s, p, ep);
				}
				default: 
				{
						if (!m) return NULL;
						s++; 
						p=ep; 
						goto init;  /* else return match(ms, s+1, ep); */
				}
				}
		}
		}
}





static void gmatch_aux (const char *sources, const char *pattern)
{
		MatchState ms;
		size_t ls;
		const char *s = sources;
		const char *p = pattern;
		ls = strlen(s);
		
		const char *src;
		ms.L = NULL;
		ms.src_init = s;
		ms.src_end = s+ls;
		src = s;
		while(src < ms.src_end)
		{
				ms.level = 0;
				const char *e;
				
				if ((e = match(&ms, src, p)) != NULL)
				{
						char *tmp = ARSpace::AR_strndup(src, e - src);
						printf("matched str == %s\r\n", tmp);
						//AR_free(tmp);

						size_t	newstart = e-src;
						if (e == src) newstart++;  /* empty match? go at least one position */

						src += newstart;
				}else
				{
						src++;
				}
		}
		
		printf("gmatch_aux finished\r\n");
}





AR_NAMESPACE_BEGIN


/*
		
*/


/********************************************************************************************************************/

/*
typedef struct __arsenal_match_result_tag
{
		bool_t			has_error;
		const wchar_t	*pattern_error_position;
		const wchar_t	*next;

		bool_t			is_matched;
		const wchar_t	*matched_start;
		size_t			matched_len;

}arMatchResult_t;


arMatchResult_t			AR_wcs_match(const wchar_t *s, const wchar_t *pattern);
*/



/********************************************************************************************************************/

typedef enum 
{
		AR_MATCH_SINGLE_LINE	=		0x01,
		AR_MATCH_IGNORE_CASE	=		0x02
}arMatchFlags_t;



#define AR_MATCH_MAX_CAPTURE_COUNT		128

typedef enum
{
		CAPTURE_POSITION_T,
		CAPTURE_UNFINISHED_T,
		CAPTURE_FINISHED_T,
}captureState_t;

typedef struct __match_state_tag
{
		const wchar_t	*start;
		const wchar_t	*end;
		uint_32_t		flags;

		struct {
				const wchar_t	*init;
				size_t			len;
				captureState_t	stat;
		}captures[AR_MATCH_MAX_CAPTURE_COUNT];
		
		size_t	capture_cnt;
}matchState_t;



typedef struct __match_result_tag
{
		bool_t			has_error;
		const wchar_t	*pattern_error_position;
		const wchar_t	*pattern_next;
		bool_t			is_matched;
		const wchar_t	*source_next;
}matchResult_t;


#define _SET_RESULT(_res, _err, _err_pos, _pn, _sn, _matched)	do{\
				(_res)->has_error = (_err);						\
				(_res)->pattern_error_position = (_err_pos);	\
				(_res)->pattern_next = (_err_pos);				\
				(_res)->is_matched  = (_matched);				\
				(_res)->source_next = (_sn);					\
		}while(0)


#define _CLR_RESULT(_res)		do{AR_memset((_res), 0, sizeof(*(_res)));}while(0)





static const wchar_t*	__transform_char(const wchar_t *input, wchar_t *c)
{
		const wchar_t	*p; 
		AR_ASSERT(input != NULL && c != NULL);
		
		p = input;
		switch(*p)
		{
		case L'\0':
				return NULL;
		case L'[':
		case L']':
		case L'(':
		case L')':
		case L'\\':
		case L'?':
		case L'+':
		case L'-':
		case L'*':
		case L'|':
		case L'^':
		case L'$':
		case L'"':
		case L'.':
				*c = *p;
				return ++p;
		case L'a': 
				*c = L'\a';
				return ++p;
		case L'b':
				*c = L'\b';
				return ++p;
		case L'f': 
				*c = L'\f';
				return ++p;
		case L'n': 
				*c = L'\n';
				return ++p;
		case L'r': 
				*c = L'\r';
				return ++p;
		case L't': 
				*c = L'\t';
				return ++p;
		case L'v': 
				*c = L'\v';
				return ++p;
		case L'u':
		{
				const wchar_t *ret; uint_32_t val;
				p += 1;

				if(*p != L'{')
				{
						ret = AR_wtou32_s(p,p+4, &val, 10);
						
						if(ret == NULL)
						{
								return NULL;
						}else
						{
								*c = (wchar_t)val;
								p = ret;
						}
				}else
				{
						const wchar_t *end;
						p+=1;
						end = p;
						
						while(*end != L'\0' && *end != L'}')end++;
						
						ret = AR_wtou32_s(p, end, &val, 10);

						if(ret)
						{
								ret = AR_wcstrim_space(ret);
								
								if(*ret != L'}')
								{
										ret = NULL;
								}
						}

						if(ret == NULL)
						{
								return NULL;
						}else
						{
								*c = (wchar_t)val;
								p = ret;
						}

						AR_ASSERT(*p == L'}');
						p++;		
				}

				return p;
		}
				break;
		case L'x':
		{
				const wchar_t *ret;  uint_32_t val;

				p += 1;
				
				if(*p != L'{')
				{
						ret = AR_wtou32_s(p, p + 2, &val, 16);
						if(ret == NULL)
						{
								return NULL;
						}else
						{
								*c = (wchar_t)val;
								p = ret;
						}
				}else
				{
						const wchar_t *end;
						p+=1;
						end = p;
						
						while(*end != L'\0' && *end != L'}')end++;
						
						ret = AR_wtou32_s(p, end, &val, 16);

						if(ret)
						{
								ret = AR_wcstrim_space(ret);
								if(*ret != L'}')ret = NULL;
						}

						if(ret == NULL)
						{
								return NULL;
						}else
						{
								*c = (wchar_t)val;
								p = ret;
						}

						AR_ASSERT(*p == L'}');
						p++;
				}
				return p;
		}
				break;
		default:
				return NULL;
		}
}







static matchResult_t	__match_expr(matchState_t *ms, const wchar_t *src, const wchar_t *pattern, wchar_t end_char);



static matchResult_t	__match_quote(matchState_t *ms, const wchar_t *src, const wchar_t *pattern)
{
		matchResult_t		g_res;
		
		const wchar_t *s, *p;

		AR_ASSERT(src != NULL && pattern != NULL);
		
		_CLR_RESULT(&g_res);
		s = src;
		p = pattern;

		AR_ASSERT(false);
		return g_res;
}





#define IS_NEW_LINE(_c)	((_c) == L'\n' || (_c) == L'\r')
#define IS_LINE_BEGIN(_sp, _input)		((_sp) == (_input) || (IS_NEW_LINE((_sp)[-1])))
#define IS_LINE_END(_sp)				(*(_sp) == L'\0' || (IS_NEW_LINE(*(_sp))))



static const wchar_t* __get_charset(const wchar_t *input, wchar_t *c)
{
		AR_ASSERT(input != NULL && c != NULL);

		switch(*input)
		{
		case L'\0':
		case L'\a': 
		case L'\f': 
		case L'\n': 
		case L'\r': 
		case L'\t': 
		case L'\v': 
		case L'\b':
		case L'[':
		case L']':
		case L'(':
		case L')':
		case L'?':
		case L'+':
		case L'-':
		case L'*':
		case L'"':
		case L'^':
		case L'$':
		case L'.':
				return NULL;
		case L'\\':
				return __transform_char(input + 1, c);
		default:
				*c = *input;
				return ++input;
		}
}



/*
static int matchbracketclass (int c, const char *p, const char *ec)
{
		int sig = 1;
		
		if(*(p+1) == '^')
		{
				sig = 0;
				p++;  
		}
		
		while (++p < ec) 
		{
				if (*p == L_ESC) 
				{
						p++;
						if (match_class(c, uchar(*p)))
								return sig;
				}else if ((*(p+1) == '-') && (p+2 < ec)) 
				{
						p+=2;
						if (uchar(*(p-2)) <= c && c <= uchar(*p))
								return sig;
				}else if (uchar(*p) == c)
				{
						return sig;
				}
		}
		
		return !sig;
}
*/



static matchResult_t	__match_cset_range(matchState_t *ms, const wchar_t *src, const wchar_t *pattern)
{
		matchResult_t		g_res;
		const wchar_t *s, *p;
		bool_t	sig = true;
		AR_ASSERT(src != NULL && pattern != NULL);
		
		_CLR_RESULT(&g_res);
		s = src;
		p = pattern;
		
		if(*p == L'^')
		{
				sig = false;
				++p;
		}

		while(*p != L'\0' && *p != L']')
		{
				wchar_t b,e;
				const wchar_t *pn;
				bool_t is_ok;
				pn = __get_charset(p, &b);

				if(pn == NULL)
				{
						_SET_RESULT(&g_res, true, p, NULL, NULL, false); /*未匹配*/
						goto END_POINT;
				}else
				{
						p = pn;
				}

				if(*p == L'-')
				{
						++p;
						pn = __get_charset(p, &e);
						
						if(pn == NULL)
						{
								_SET_RESULT(&g_res, true, p, NULL, NULL, false); 
								goto END_POINT;
						}else
						{
								p = pn;
						}
				}else
				{
						e = b;
				}


				if(*s >= b && *s <= e)
				{
						is_ok = sig ? true : false;
				}else
				{
						is_ok = sig ? false : true;
				}


				if(is_ok)
				{
						while(*p != L'\0' && *p != L']')++p;

						if(*p == L']')
						{
								_SET_RESULT(&g_res, false, NULL, p+1, s + 1, true);
						}else
						{
								_SET_RESULT(&g_res, true, pattern, NULL, NULL, false);
						}
						
						goto END_POINT;
				}
		}

		if(*p == L'\0')
		{
				_SET_RESULT(&g_res, true, pattern, NULL, NULL, false);
		}

		if(*p == L']')
		{
				_SET_RESULT(&g_res, false, NULL, pattern, s, false);
		}

END_POINT:
		return g_res;
}





static matchResult_t	__match_charset(matchState_t *ms, const wchar_t *src, const wchar_t *pattern)
{
		matchResult_t		g_res;
		
		const wchar_t *s, *p;
		wchar_t c;
		AR_ASSERT(src != NULL && pattern != NULL);
		
		_CLR_RESULT(&g_res);
		s = src;
		p = pattern;


		if(*p == L'[')
		{
				return __match_cset_range(ms, s, p + 1);

		}else if(*p == L'.')
		{
				bool_t is_ok;
				if(ms->flags & AR_MATCH_SINGLE_LINE)/*single line 可以匹配包含\r\n在内的所有字符*/
				{
						is_ok = true;
				}else
				{
						if(IS_NEW_LINE(*s))
						{
								is_ok = true;
								_SET_RESULT(&g_res, false, NULL, p, s, false); /*未匹配*/
						}else
						{
								is_ok = false;
						}

				}

				if(is_ok)
				{
						_SET_RESULT(&g_res, false, NULL, p + 1, s + 1, true);
				}else
				{
						_SET_RESULT(&g_res, false, NULL, p, s, false);
				}

				return g_res;
		
		}else if(*p == L'\\')
		{
				if(*(p + 1) == L'B' || *(p + 1) == L'E')
				{
						++p;
						bool_t is_ok = false;
						if(*p == L'B')
						{
								
								if(IS_LINE_BEGIN(s, ms->start))
								{
										is_ok = true;
								}
						}else
						{
								if(IS_LINE_END(s))
								{
										is_ok = true;
								}
						}
						
						if(is_ok)
						{
								_SET_RESULT(&g_res, false, NULL, p + 1, s, true);
						}else
						{
								_SET_RESULT(&g_res, false, NULL, p, s, false);
						}
						return g_res;
				}
		}
		
		p = __get_charset(p, &c);
		
		if(p == NULL)
		{
				_SET_RESULT(&g_res, true, pattern, NULL, NULL, false);
				return g_res;
		}else
		{
				bool_t is_ok = false;

				if(ms->flags & AR_MATCH_IGNORE_CASE)
				{
						is_ok = AR_towlower(c) == AR_towlower(*s) ? true : false;
				}else
				{
						is_ok = c == *s ? true : false;
				}

				if(is_ok)
				{
						_SET_RESULT(&g_res, false, NULL, p, s + 1, true);
				}else
				{
						_SET_RESULT(&g_res, false, NULL, p, s, false);
				}
				return g_res;
		}
}



static matchResult_t	__match_postfix(matchState_t *ms, const wchar_t *src, const wchar_t *pattern)
{
		matchResult_t		g_res;
		
		const wchar_t *s, *p;

		AR_ASSERT(ms != NULL && src != NULL && pattern != NULL);
		
		_CLR_RESULT(&g_res);
		
		s = src;
		p = pattern;


		return g_res;
}

static matchResult_t	__match_factor(matchState_t *ms, const wchar_t *src, const wchar_t *pattern)
{
		matchResult_t		g_res;
		
		const wchar_t *s, *p;

		AR_ASSERT(ms != NULL && src != NULL && pattern != NULL);
		
		_CLR_RESULT(&g_res);
		
		s = src;
		p = pattern;


		switch(*p)
		{
		case L'(':
		{
				size_t l = ms->capture_cnt;

				if(l >= AR_MATCH_MAX_CAPTURE_COUNT)
				{
						_SET_RESULT(&g_res, true, p, NULL, NULL, false);
				}else
				{

						ms->captures[l].init = s;
						ms->captures[l].len = 0;
						ms->captures[l].stat = CAPTURE_UNFINISHED_T;
						ms->capture_cnt++;

						if(*(p + 1) == L')')
						{
								ms->captures[l].stat = CAPTURE_POSITION_T;

								_SET_RESULT(&g_res, false, NULL, p + 2, s, true);

						}else
						{
								g_res = __match_expr(ms, s, p + 1, L')');
								
								if(!g_res.has_error && g_res.is_matched)
								{
										ms->captures[l].len = g_res.source_next - ms->captures[l].init;
										ms->captures[l].stat = CAPTURE_FINISHED_T;
								}else
								{
										ms->capture_cnt--;
								}
						}
				}
		}
				break;
		case L'^':
				if(s == ms->start)
				{
						_SET_RESULT(&g_res, false, NULL, p+1, s, true);
				}else
				{
						_SET_RESULT(&g_res, false, NULL, p+1, s, false);
				}
				break;
		case L'$':
				if(s == ms->end)
				{
						_SET_RESULT(&g_res, false, NULL, p+1, s, true);
				}else
				{
						_SET_RESULT(&g_res, false, NULL, p+1, s, false);
				}
				break;
		case L'\"':
				g_res = __match_quote(ms, src, p);
				break;
		default:
				g_res = __match_charset(ms, src, p);
				break;
		}


		if(!g_res.has_error && g_res.is_matched)
		{
				g_res = __match_postfix(ms, g_res.source_next, pattern);
		}
		
		return g_res;
}


static matchResult_t	__match_expr(matchState_t *ms, const wchar_t *src, const wchar_t *pattern, wchar_t end_char)
{
		matchResult_t		g_res;
		
		const wchar_t *s, *p;

		AR_ASSERT(src != NULL && pattern != NULL);
		
		AR_memset(&g_res, 0, sizeof(g_res));
		
		s = src;
		p = pattern;

		while(*p != L'\0' && *p != end_char)
		{
				matchResult_t tmp = __match_factor(ms, s,p);
				
				if(tmp.has_error || !tmp.is_matched)
				{
						g_res = tmp;
						goto END_POINT;
				}else
				{
						p = tmp.pattern_next;
						s = tmp.source_next;
				}
		}
		
		AR_ASSERT(*p == end_char);

		if(*p != end_char)
		{
				_SET_RESULT(&g_res, true, p, NULL, NULL, false);
				goto END_POINT;
		}

		if(*p != L'\0')
		{
				p++;
		}
		
		_SET_RESULT(&g_res, false, NULL, p, s, true);
		
END_POINT:
		return g_res;
}






void tokenizer_test()
{
		gmatch_aux("hello world from Lua", "(%a)+");


}


AR_NAMESPACE_END


#endif