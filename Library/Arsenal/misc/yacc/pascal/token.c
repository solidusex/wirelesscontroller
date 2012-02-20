char *token_name(i)
int i;
{
    static char buf[10];
    switch(i)
    {
	default  : if(i<256)
		   {
		       if(i<32 || i>126)
			   sprintf(buf, "0%o", i);
		       else
		           sprintf(buf, "%c", i);
		       return buf;
		   }
		   else
		       return("<Unknown token>");
	case   0 : return("<End of input>");
	case 257 : return("UNSIGNED_INT");
	case 258 : return("UNSIGNED_REAL");
	case 259 : return("STRING");
	case 260 : return("IDENTIFIER");
	case 261 : return("NE");
	case 262 : return("LE");
	case 263 : return("GE");
	case 264 : return("BECOMES");
	case 265 : return("DIV");
	case 266 : return("MOD");
	case 267 : return("NIL");
	case 268 : return("IN");
	case 269 : return("OR");
	case 270 : return("AND");
	case 271 : return("NOT");
	case 272 : return("DOTDOT");
	case 273 : return("IF");
	case 274 : return("THEN");
	case 275 : return("ELSE");
	case 276 : return("CASE");
	case 277 : return("OF");
	case 278 : return("REPEAT");
	case 279 : return("UNTIL");
	case 280 : return("WHILE");
	case 281 : return("DO");
	case 282 : return("FOR");
	case 283 : return("TO");
	case 284 : return("DOWNTO");
	case 285 : return("SBEGIN");
	case 286 : return("END");
	case 287 : return("WITH");
	case 288 : return("GOTO");
	case 289 : return("CONST");
	case 290 : return("VAR");
	case 291 : return("TYPE");
	case 292 : return("ARRAY");
	case 293 : return("RECORD");
	case 294 : return("SET");
	case 295 : return("SFILE");
	case 296 : return("FUNCTION");
	case 297 : return("PROCEDURE");
	case 298 : return("LABEL");
	case 299 : return("PACKED");
	case 300 : return("PROGRAM");
    }
}
