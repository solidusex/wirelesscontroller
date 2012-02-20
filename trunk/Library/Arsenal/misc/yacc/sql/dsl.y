/*
Distributed Database Facilitator Parcer
Version 1.0
By Leroy G. Cain
1985 Columbia Union College
*/
%union
{
        int     stype;
        char    *nsbuf;
}
%token ADD
%token ALL
%token ALLOWED
%token AFTER
%token ALTER
%token AND
%token ANY
%token AS
%token ASC
%token AT
%token AUDIT
%token BEFORE
%token BBEGIN
%token BETWEEN
%token BY
%token CHECK
%token CLOSE
%token COMMENT
%token COMMIT
%token COMPOSITE
%token CONSTRAINT
%token CREATE
%token DATABASE
%token DEFAULT
%token DELETE
%token DESC
%token DISTINCT
%token DIVIDEBY
%token DOMAIN
%token DROP
%token DUMP
%token END
%token ELSE
%token EXISTS
%token FOR
%token FOREIGN
%token FRAGMENT
%token FROM
%token GRANT
%token GROUP
%token HAVING
%token IDENTIFIES
%token IF
%token IN
%token INDEX
%token INFO
%token INSERT
%token INTO
%token INTERSECT
%token IS
%token LIKE
%token LOCK
%token MINUS
%token MODE
%token MODIFY
%token NOT
%token NULLN
%token NULLS
%token OF
%token ON
%token OPEN 
%token OPTION 
%token OR
%token ORDER 
%token OUTER 
%token PRIMARY 
%token PROGRAM 
%token RANGE
%token REPAIR
%token RESTORE
%token REVOKE 
%token ROLLBACK 
%token ROLLFORWARD 
%token SELECT
%token SET
%token SHOW
%token SNAPSHOT
%token START
%token STORE
%token SYNC
%token SYNONYM
%token TABLE
%token THEN
%token TO
%token TYPE
%token VALUES
%token VIEW
%token UNION
%token UNIQUE
%token UPDATE
%token WHERE
%token WORK
%token WITH
/*
*/
%token ALLFIELDS
%token <nsbuf> IDENTIFIER
%token INTEGER
%token ILLEGAL
%token REAL 
%token STRING
%token PARM 
%left ';'
%left WHERE
%left OR
%left AND
%left ','
%right ASSIGN
%right TCOL
%left '?'
%left E_OR
%left E_AND
%left '|'
%left '^'
%left '&'
%left NLT NGT LT GT EQ GE LE NE
%left RIGHTSHIFT LEFTSHIFT
%left '+' '-'
%left '*' '/' '%' PWR
%right UMINUS  '~' PNOT
%left PORDER
%left '`'
%left '.'


%{
static long     flag;
static short    sqy_flag;

static char     path_name[1024];
static char     scratch[1024];

#include "gtok.h"
#define BEXPR { sqy_flag = 0; }
%}
%%
dsl:
          statement ';' 
          {puttok(T_ROOT);puttok(0);puttok(0);puttok(T_ENDCOMMAND);}
        | STORE PROGRAM prog_name '(' parm_list ')'stats ';' END STORE ';'
        ;

stats:
        statement
        | stats ';' statement
        ;

        /*
trigger_list:
        trigger
        | trigger_list ',' trigger
        |error
        | trigger_list error trigger
        | trigger_list ',' error 
        ;
        */
statement:
          { puttok(0300);} alter        
        | { puttok(0301);} audit
        | { puttok(0302);} begin
        | { puttok(0303);} check
        | { puttok(0304);} close
        | { puttok(0305);} comment
        | { puttok(0306);} commit
        | { puttok(0307);} create
        | { puttok(0310);} delete
        | { puttok(0311);} drop
        | { puttok(0312);} dump
        | { puttok(0313);} grant
        | { puttok(0314);} info
        | { puttok(0315);} insert
        | { puttok(0316);} lock
        | { puttok(0317);} open
        | { puttok(0320);} rollback
        | { puttok(0321);} rollforward
        | { puttok(0322);} repair
        | { puttok(0323);} restore
        | { puttok(0324);} revoke
        | { puttok(0325);} select
        | { puttok(0326);} set
        | { puttok(0327);} start
        | { puttok(0330);} sync
        | { puttok(0331);} update
        ;

start:
          prog_name '(' expr_list ')'
          /*
        | START INTEGER '(' parm_list ')'
          */
        ;

parm_list:
          parm
        | parm ',' parm_list
        ;

parm:
          parm_name
        | parm_name EQ expr %prec ASSIGN
        ;

/*
Data Manipulation
*/

delete:
          DELETE FROM rec_alias where_clause /* Set where flag */
        ;

insert:
            INSERT INTO rec_alias '(' field_list ')' icond
          | INSERT INTO rec_alias icond
          ;

update:
          UPDATE rec_alias set_show where_clause /* Set where flag */
        ;

rec_alias:
          path
        | path alias
        ;

icond:  
          FROM filename
        | select_statement
        | VALUES '(' const_list ')'
        ;

set_show:
          SHOW setelements
        | SET setelements
        ;

setelements:
          setelement
        | setelements ',' setelement
        ;

setelement: 
          field EQ expr %prec ASSIGN
        | field EQ select_statement %prec ASSIGN
        | '[' field_list ']' EQ '[' expr_list ']' %prec ASSIGN
        | '[' field_list ']' EQ select_statement %prec ASSIGN
        ;

/*
Query Langauge
*/

select:
        select_expr order_clause into_clause
        ;

select_expr:
          select_statement
        | select_expr UNION any select_statement 
        | select_expr MINUS select_statement 
        | select_expr DIVIDEBY select_statement 
        | select_expr INTERSECT select_statement 
        | '(' select_expr ')'
        ;

order_clause:
        | ORDER BY norder_list
        ;

into_clause:
        | INTO filename
        ;

select_statement:
        { puttok(T_TLEND); }
          select_clause
                FROM from_item_list
                select_options
        { puttok(T_QLEND); }
        ;

order_list:
          path orderdir %prec PORDER
        | order_list ',' path orderdir
        ;

norder_list:
/*
          INTEGER orderdir %prec PORDER
*/
          expr orderdir %prec PORDER
/*
        | path orderdir %prec PORDER
*/
        | norder_list ',' norder_list
        ;

select_clause:
          SELECT unique sellist
        | SELECT unique '*'
        ;

from_item_list:
          from_item
        | from_item_list ',' from_item_list
        ;

from_item:
          rec_alias
        | OUTER rec_alias
        | OUTER '(' from_item_list ')'
        ;

select_options:
        | WHERE predicate /* Set where flag */
        | WHERE predicate group_clause
        | group_clause
        ;

group_clause:
          GROUP BY path_list
        | GROUP BY path_list HAVING predicate /* Set having flag */
        ;

unique:
        | ALL
        | DISTINCT
        | UNIQUE
        ;

sellist:
          selelement {puttok(T_RESDOM);}
        | sellist ',' selelement {puttok(T_RESDOM);}
        ;

selelement:
          record ALLFIELDS
        | expr
        | expr STRING
        ;

predicate:
          condition
        | condition AND predicate 
        | condition OR predicate 
        | NOT predicate %prec PNOT
        | '(' predicate ')'
        | IF predicate THEN predicate else_pred
        ;

else_pred:
        |ELSE predicate
        ;

condition:
           expr
        |  expr not IN in_sel_expr /* singler flag */
        | '[' path_list ']'  not IN in_sel_expr
        |  expr IS not NULLN
        |  expr IS not DEFAULT
        |  expr not BETWEEN expr AND expr
        |  expr not LIKE const  /* Like flag */
        | EXISTS '(' select_statement ')'
        ;

not:
        |NOT
        ;

any:
        |ALL
        |ANY
        ;

in_sel_expr:
          '(' select_statement ')' 
        | const_recs
        ;

cond_sel_expr:
          expr
        | '(' select_statement ')' 
	  {if (sqy_flag) yyerror ("Illegal subquery"); else sqy_flag = 1;}
        ;

const_recs:
          '(' const_list ')'
        | '[' const_rec_list ']'
        ;

const_rec_list:
          '(' const_list ')'
        | const_rec_list ',' '(' const_list ')'
        ;

path_list:
          path
        | path_list ',' path
        ;

field_list:
          field
        | field_list ',' field
        ;
/*
path is a field or record path.
node.database.record  -- for records
node.database.record.field  -- for fields
*/
path:
        path_e_list {puttok(T_VAR);putvar(path_name);*path_name='\0';}
        | path_e_list '[' element_name ']'
        ;

path_e_list:
        path_element
        | path_element  {strcat(path_name,".");} '.' path_e_list
        ;

element_name:/* element_name flag */
         norder_list
        ;

orderdir: 
        | DESC
        | ASC
        ;

const_list:
          const
        | const_list ',' const
        ;

expr:
          expr '`' s_control    /* Semantic control */
        | '-' expr %prec UMINUS {puttok(T_NEG);}/* negate */
        | expr '+' expr {puttok(T_ADD);}/* add */
        | expr '-' expr {puttok(T_SUB);}/* subtract */
        | expr '*' expr {puttok(T_MUL);}/* multiply */
        | expr '/' expr {puttok(T_DIV);}/* divide */
        | expr '%' expr {puttok(T_MOD);}/* modulus */
        | expr PWR expr {puttok(T_ADD);}/* power */
        | expr '?' else_part
        | '~' expr      /* ones compliment */
        | expr RIGHTSHIFT expr /* bit shift right */
        | expr LEFTSHIFT expr /* bit shift left */
        | expr '^' expr /* exclusive or */
        | expr '|' expr /* or */
        | expr '&' expr /* and */
        | expr E_OR expr        /* or */
        | expr E_AND expr       /* and */
        | expr NLT cond_sel_expr {puttok(T_NLT);}
        | expr NGT cond_sel_expr {puttok(T_NGT);}
        | expr LT any cond_sel_expr {puttok(T_LT);}
        | expr GT any cond_sel_expr {puttok(T_GT);}
        | expr EQ any cond_sel_expr {puttok(T_EQ);}
        | expr GE cond_sel_expr {puttok(T_GE);}
        | expr LE cond_sel_expr {puttok(T_LE);}
        | expr NE any cond_sel_expr {puttok(T_NE);}
        | '(' expr ')'  /* parenthesis */
        | const
        | path
        | function
        ;

else_part:
        expr ':' expr %prec TCOL
        ;

const:
          INTEGER {puttok(T_INT4); putint(yytext);}
        | REAL {puttok(T_FLT8); putreal(yytext);}
        | STRING {puttok(T_CHAR); putstr(yytext);}
        | DEFAULT
        | NULLN
        | PARM
        ;

function: 
          fname '(' '*' ')'
        | fname '(' expr_list ')'
        | fname '(' UNIQUE path ')'
        ;

expr_list:
          expr
        | expr_list ',' expr
        ;

/*
Data Definition Language
*/
create:
          CREATE cluster TABLE path tfd_list with_clause
        | CREATE VIEW view_name vfd AS select_statement with_clause
        | CREATE FRAGMENT view_name vfd AS select_statement with_clause
        | CREATE SNAPSHOT view_name vfd AS select_statement with_clause
        | CREATE SYNONYM syn_name FOR path 
        | CREATE unique cluster INDEX index_name
                ON path '(' order_list ')' with_clause
        | CREATE DATABASE dbname TYPE dbtype ON hname with_clause
        | CREATE DOMAIN domain_name_list IS domain_types
                defaults domain_restrict
        | CREATE TYPE type_name IS 
        | CREATE CONSTRAINT constr_name trigger_list CHECK predicate
else_clause
        ;

alter:
          ALTER TABLE path alter_list with_clause
        | ALTER TABLE path path with_clause
        ;

drop:
          DROP INDEX index_name
        | DROP object_type path
        ;

comment:
          COMMENT ON path
        | COMMENT ON path IS comment_str
        ;

info:
          INFO
        ;

comment_str:
          STRING
        | STRING ',' STRING
        ;

trigger_list:
        trigger
        | trigger_list ',' trigger
        ;

trigger:
          AT event
        | AFTER event OF path FROM path
        | BEFORE event OF path FROM path
        ;

event:
          COMMIT
        | DELETE
        | INSERT
        | UPDATE
        ;

else_clause:
        | ELSE statement
        ;

index_name:     path;

cluster:
        | IDENTIFIER
        /*
        |CLUSTERED |NONCLUSTERED
        */
        ;

view_name:
          record
        | user '.' record
        ;

with_clause:
        |WITH option_list
        ;

option_list:
          option
        | option ',' option_list
        ;

option:
        IDENTIFIER
        | IDENTIFIER IDENTIFIER
        | IDENTIFIER EQ const
/*
reconfigure| check option |logfile = "file_name"
*/
        ;

tfd_list:
          primary_key
          foreign_keys
          field_dis
        ;

field_dis:
          '(' tfd_fields ')'
        ;

primary_key:
        | PRIMARY '(' primary_keys ')'
        ;

primary_keys:
          field
        | primary_keys ',' field
        ;

foreign_keys:
        | foreign_keys foreign_key
        ;

foreign_key:
          FOREIGN '(' f_key IDENTIFIES path
                  nulls
                  DELETE OF path effect
                  UPDATE OF path effect')'
        ;

/*
f_keys:
          f_key
        | f_keys ',' f_key
        ;
*/

nulls:
          NULLS ALLOWED
        | NULLS NOT ALLOWED
        ;

tfd_fields:
          tfd
        | tfd_fields ',' tfd
        ;

tfd:
          field o_domain_name
        | field '(' field_list ')' o_domain_name
        ;

o_domain_name:
        |domain_name
        ;

type_name:
        IDENTIFIER
        /*
Base types:
        boolean(bit)|
        char|short_integer|long_integer|
        byte|short_word|long_word|
        float|double|extended|bcd|bcdflt
predefine extentions:
        char|byte[1-2,000,000,000]
        [short|long]_[integer|word][1-2,000,000,000]
        float|double|extended[1-2,000,000,000]
        bcd|bcdflt[1-2,000,000,000]
        date_[]
        money
        time_[m,ap,sm,sap,micro]
        */
        ;

domain_name_list:
        domain_name
        | domain_name_list ',' domain_name
        ;

domain_types:
        domain_type
        | '(' domain_type_list ')'
        ;

defaults:
        | DEFAULT 
        ;

domain_restrict:
          where_clause
        | select_statement
        ;

domain_type_list:
        | domain_type_list ',' domain_type
        ;

domain_type:
          type_name
        | type_name '(' i_list ')'
        ;

i_list:
        INTEGER
        | i_list ',' INTEGER
        ;

vfd:
        | '(' vfd_list ')' 
        ;

vfd_list:
          field
        | vfd_list ',' field
        ;

alter_list:
        alteration
        | alter_list ',' alteration
        ;

alteration:
          ADD '(' a_tfd_fields ')'
        | DROP vfd
        | MODIFY '(' m_tfd_fields ')'
        ;

a_tfd_fields:
          tfd before
        | a_tfd_fields ',' tfd before
        ;

m_tfd_fields:
          field tfd
        | m_tfd_fields ',' field tfd
        ;

before:
        | BEFORE field
        ;

effect:
        IDENTIFIER
/*
        CASCADES | RESTRICTED | NULLIFIES
*/
        ;
/*
*/
object_type:
        DATABASE| DOMAIN| PROGRAM| SYNONYM| TYPE| TABLE| VIEW
        ;
/*
Security
*/

grant:
          GRANT privileges gr_on TO users at_option between_option
                on_option where_option wgo
        ;

at_option:
        |AT terminal_list
        ;

between_option:
        |BETWEEN time1 AND time2
        ;

on_option:
        |ON day1 AND day2
        ;

where_option:
        |WHERE predicate
        ;

wgo:
        | WITH GRANT OPTION
        ;

terminal_list:
          tty
        | tty ',' terminal_list
        ;

revoke:
        REVOKE privileges gr_on FROM users
        ;

privileges:
        | privileg
        | privileges ',' privileg
        ;

privileg:
          priv_name
        | priv_name '(' field_list ')'
        ;

gr_on:
        | ON object_type objects 
        ;

users:
        user
        | users ',' user
        ;

objects:
          IDENTIFIER
        | objects ',' IDENTIFIER
        ;

/*
Transaction Management
*/

lock:
          LOCK TABLE path IN mode MODE
        ;

begin:
          BBEGIN work
        ;

commit:
          COMMIT work
        ;

rollback:
          ROLLBACK work
        | ROLLBACK SYNC
        ;

rollforward:
          ROLLFORWARD path FROM path roll_op
        ;

roll_op:
        |TO STRING time
        ;

time:
        |STRING 
        ;

sync:
          SYNC
        ;

work:
        |WORK
        ;
/*
Acess management
*/


close:
        CLOSE dbname
        ;

open:
        OPEN dbname password
        ;


password:
        |IDENTIFIER
        ;
/*
DataBase Maintaince and Configuration
*/
audit:
          AUDIT into_clause path_list
                from_clause where_clause /* Set audit flag */
        ;

check:
        CHECK
        ;

dump:
          DUMP DATABASE dbname to_clause
        | DUMP TABLE dbname to_clause
        ;

repair:
        REPAIR
        ;

restore:
          RESTORE DATABASE dbname rfrom_clause
        | RESTORE TABLE dbname rfrom_clause
        ;

to_clause:
        |TO filename
        ;

rfrom_clause:
        |FROM filename
        ;

set:
        SET option_list
        ;

where_clause:
        | WHERE predicate
        ;

from_clause:
        | FROM path_list
        ;
/*
CONSTRAND IDENTIFIERS
*/
mode:
        IDENTIFIER
/* check
        SHARE | EXCLUSIVE | OFF
*/
        ;

priv_name:
          IDENTIFIER
        | ALTER | CREATE | DELETE | DUMP | RESTORE 
        | DROP | INSERT | LOCK | SELECT | UPDATE
/* check
        | CREATE_TABLE | CREATE_DATABASE 
        | CREATE_INDEX | ALL
*/      ;

s_control:
          IDENTIFIER
          ;
/*
IDENTIFIERS
*/
alias:  IDENTIFIER;
constr_name:    IDENTIFIER;/* Constraint Name */
day1: IDENTIFIER;
day2: IDENTIFIER;
dbtype: PARM |  IDENTIFIER;/* Database type */
dbname: PARM |  IDENTIFIER;/* Database name */
domain_name:    IDENTIFIER;
field:  IDENTIFIER;
filename:       PARM |  IDENTIFIER; /* File name */
fname:  IDENTIFIER;     /* FUNCTION NAME */
f_key:  IDENTIFIER;
hname:  IDENTIFIER;
parm_name:      IDENTIFIER;
/* Field or Record path element */
path_element:   IDENTIFIER {strcat(path_name,$1);};
prog_name:      IDENTIFIER;
record: IDENTIFIER;
syn_name:       IDENTIFIER;
tty:    IDENTIFIER;
time1: IDENTIFIER;
time2: IDENTIFIER;
user:   PARM | IDENTIFIER;
/*
range_num: IDENTIFIER | INTEGER;
*/
%%
#include "lex.yy.c"
