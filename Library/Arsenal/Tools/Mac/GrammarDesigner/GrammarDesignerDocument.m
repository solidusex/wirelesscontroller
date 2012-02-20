/*
 * Copyright (c) 2011 by Solidus
 * This file is part of Arsenal library tools source code.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.It is provided "as is" without express 
 * or implied warranty.
 *
 */


#import "GrammarDesignerDocument.h"


#if defined(__cplusplus)
using namespace ARSpace;
#endif


@implementation 	ParserDelegate

@synthesize output;

-(id)init
{
		self = [super init];
		if(self)
		{
				output = nil;
				parser = NULL;
		}
		return self;
}


-(void)dealloc
{
		[super dealloc];
}

-(void)onBuildParserMsg : (printNodeParserMsg_t)t Msg : (NSString*)msg Line : (int)line
{
		consoleMessageType_t ct;
		if(t == PRINT_NODE_MSG_T)
		{
				ct = CONSOLE_MSG_MESSAGE_T;
				
		}else if(t == PRINT_NODE_WARNING_T)
		{
				ct = CONSOLE_MSG_WARNING_T;
				
		}else //PRINT_NODE_ERROR_T
		{
				ct = CONSOLE_MSG_ERROR_T;
		}
		   
		
		if(output != nil)
		{
				
				[output append : 
				 [ConsoleMessage consoleMessageWithType :  ct
													Msg : msg
												   Line : line
				  ]
				 ];
		}
}

-(void)onParseMsg		: (printNodeParserMsg_t)t Msg : (NSString*)msg Line : (int)line
{

		consoleMessageType_t ct;
		if(t == PRINT_NODE_MSG_T)
		{
				ct = CONSOLE_MSG_INPUT_MESSAGE_T;
				
		}else if(t == PRINT_NODE_WARNING_T)
		{
				ct = CONSOLE_MSG_INPUT_WARNING_T;
				
		}else //PRINT_NODE_ERROR_T
		{
				ct = CONSOLE_MSG_INPUT_WARNING_T;
		}
		
		if(output != nil)
		{
				[output append : 
				 [ConsoleMessage consoleMessageWithType :  ct
													Msg : msg
												   Line : line
				  ]
				 ];
		}
		
}

-(void)	setParser		: (const parser_t*)psr
{
		parser = psr;
}

-(const parser_t*)parser
{
		return parser;
}


@end






@implementation GrammarDesignerDocument




/****************************Internal************************/

-(void)init_outlets
{
		DLog(@"GrammarDesignerDocument::init_outlets");
		[consoleTabView selectTabViewItemAtIndex : 0];
		
		[grammarTextView setString : grammarContent];
		
}



-(void)load_default_config
{
		DLog(@"GrammarDesignerDocument::load_default_config");
		NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];

		
		
		NSInteger interval = (NSInteger)[defaults doubleForKey : PREFERENCE_BUILD_TAGS_INTERVAL];
		[self on_reset_timer : interval];
		
		
		
		NSInteger paser_mode = (NSInteger)[defaults doubleForKey : PREFERENCE_PARSER_MODE];
		parserMode = (psrLRItemType_t)paser_mode;
		
		lexIsSingleLine = [defaults boolForKey : PREFERENCE_LEX_IS_SINGLELINE];
		lexIsIgnoreCase = [defaults boolForKey : PREFERENCE_LEX_IS_IGNORECASE];
		
		
}


-(void)on_reset_timer : (NSInteger)milliseconds
{
		DLog(@"GrammarDesignerDocument::on_reset_timer");

		if(grammarCheckTimer != nil)
		{
				[grammarCheckTimer invalidate];
				//[grammarCheckTimer release];
				grammarCheckTimer = nil;
		}
		
		if(milliseconds > 0)
		{
				
				
				grammarCheckTimer = [NSTimer scheduledTimerWithTimeInterval	 : (double)milliseconds / 1000.0
																	  target : self
																	selector : @selector(onGrammarChecker:)
																	userInfo : nil
																	 repeats : YES
									 ];
				
				//[grammarCheckTimer retain];
				
				
		}
		
}



/****************************Initialize************************/


- (id)init
{
		DLog(@"GrammarDesignerDocument::init");
		self = [super init];
		if (self) {
				
				

				
				NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
				[nc addObserver : self
					   selector : @selector(handleParserChanged:)
						   name : NOTIFICATION_PREFERENCE_PARSER_CHANGED
						 object : nil
				 ];
				
				
				[nc addObserver : self
					   selector : @selector(handleFontChanged:)
						   name : NOTIFICATION_PREFERENCE_FONT_CHANGED
						 object : nil
				 ];
				
				
				[nc addObserver : self
					   selector : @selector(handleLexerChanged:)
						   name : NOTIFICATION_PREFERENCE_LEXER_CHANGED
						 object : nil
				 ];
				
				[nc addObserver : self
					   selector : @selector(handleApplicationChanged:)
						   name : NOTIFICATION_PREFERENCE_APPLICATION_CHANGED
						 object : nil
				 ];
				
				
								
				grammarCheckerTaskDelegate = [[GrammarCheckTask alloc] initWithDocument : self];
				grammarCheckerTask = [[ARDuplexTask alloc] init];
				[grammarCheckerTask setDelegate : grammarCheckerTaskDelegate];
				[grammarCheckerTask start];
				
				
				[self load_default_config];
				
				parserDelegate = nil;
				parser = [[PrintNodeParser alloc] init];

				parser.parserMode = parserMode;
				parser.lexIsSingleLine = lexIsSingleLine;
				parser.lexIsIgnoreCase = lexIsIgnoreCase;

				
				grammarContent = [[NSString alloc] init];
				
				
				
				
		}
		return self;
}


-(void)dealloc
{
		DLog(@"GrammarDesignerDocument::dealloc");

		
		
		
		
				
		[super dealloc];
}


-(void)close
{
		
		[self on_reset_timer : 0];
		
		[grammarCheckerTask		stop];
		[grammarCheckerTask		release];
		grammarCheckerTask	= nil;
		[grammarCheckerTaskDelegate release];
		grammarCheckerTaskDelegate = nil;
		
		[inputChecker close];
		
		NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
		[nc removeObserver : self];
		
		[inputChecker release];
		inputChecker = nil;
		
		[grammarContent release];
		grammarContent = nil;
		
		
		[parser release];
		parser = nil;
		
		[parserDelegate release];
		parserDelegate = nil;
		
		
		[super close];
}


- (NSString *)windowNibName
{
		return @"GrammarDesignerDocument";
}





- (void)windowControllerDidLoadNib:(NSWindowController *) aController
{
		DLog(@"GrammarDesignerDocument::windowControllerDidLoadNib");

		[super windowControllerDidLoadNib:aController];
		

		[self init_outlets];
		
		
		parserDelegate = [[ParserDelegate alloc] init];

		parserDelegate.output = outputView;
		
		[parser setDelegate : parserDelegate];
		
		NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];

		
		[nc addObserver : self
			   selector : @selector(handleMainWindowWillMiniaturize:)
				   name : NSWindowWillMiniaturizeNotification
				 object : mainWindow
		 ];

		[nc addObserver : self
			   selector : @selector(handleMainWindowBecomeMain:)
				   name : NSWindowDidBecomeMainNotification
				 object : mainWindow
		 ];

		
		
		[nc addObserver : self
			   selector : @selector(handleBuildParser:)
				   name : NOTIFICATION_GRAMMARVIEW_INVOKE_BUILD_PARSER
				 object : grammarTextView
		 ];
		
		[nc addObserver : self
			   selector : @selector(handleFindAllReferences:)
				   name : NOTIFICATION_GRAMMARVIEW_INVOKE_FIND_ALL_REFERENCES
				 object : grammarTextView
		 ];
		
		[nc addObserver : self
			   selector : @selector(handleGotoDeclaration:)
				   name : NOTIFICATION_GRAMMARVIEW_INVOKE_GOTO_DECLARATION
				 object : grammarTextView
		 ];
		
		
		
		[nc addObserver : self
			   selector : @selector(handleShowActionTable:)
				   name : NOTIFICATION_GRAMMARVIEW_INVOKE_SHOW_ACTION_TABLE
				 object : grammarTextView
		 ];
		
		[nc addObserver : self
			   selector : @selector(handleShowConflicts:)
				   name : NOTIFICATION_GRAMMARVIEW_INVOKE_SHOW_CONFLICTS
				 object : grammarTextView
		 ];
		
		
		
		[nc addObserver : self
			   selector : @selector(handleShowFirstFollowSet:)
				   name : NOTIFICATION_GRAMMARVIEW_INVOKE_SHOW_FIRSTFOLLOW_SET
				 object : grammarTextView
		 ];
		
		[nc addObserver : self
			   selector : @selector(handleShowLeftRecursive:)
				   name : NOTIFICATION_GRAMMARVIEW_INVOKE_SHOW_LEFT_RECURSIVE
				 object : grammarTextView
		 ];
		
		[nc addObserver : self
			   selector : @selector(handleShowLeftFactor:)
				   name : NOTIFICATION_GRAMMARVIEW_INVOKE_SHOW_LEFT_FACTOR
				 object : grammarTextView
		 ];
		
		
		[nc addObserver : self
			   selector : @selector(handleShowInputChecker:)
				   name : NOTIFICATION_GRAMMARVIEW_INVOKE_SHOW_INPUT_CHECKER
				 object : grammarTextView
		 ];
		
		[nc addObserver : self
			   selector : @selector(handleOutputRelocateText:)
				   name : NOTIFICATION_OUTPUT_INVOKE_RELOCATE_TEXT
				 object : outputView
		 ];
		
		[nc addObserver : self
			   selector : @selector(handleFindResultsRelocateText:)
				   name : NOTIFICATION_FINDRESULTS_INVOKE_RELOCATE_TEXT
				 object : findResultsView
		 ];

		[nc addObserver : self
			   selector : @selector(handleTagsViewRelocateText:)
				   name : NOTIFICATION_TAGSVIEW_INVOKE_RELOCATE_TEXT
				 object : tagsView
		 ];
		

		
		GrammarCheckTaskMessage *msg = [[GrammarCheckTaskMessage alloc] initWithSources : grammarContent];
		[grammarCheckerTask PostMsgToWorker : msg];
}



- (NSData *)dataOfType:(NSString *)typeName error:(NSError **)outError
{
		DLog(@"GrammarDesignerDocument::dataOfType");
		
		[grammarContent release];
		grammarContent = [NSString stringWithString : [grammarTextView string]];
		[grammarContent retain];
		
		NSMutableData *retData = [NSMutableData dataWithCapacity : 4096];
		
		const byte_t header[3] = {0xEF, 0xBB, 0xBF};
		[retData appendBytes : (const void*)header
					  length : sizeof(header)
		 ];
		
		[retData appendData : [grammarContent dataUsingEncoding : NSUTF8StringEncoding]	 ];
		
		return retData;
}


- (BOOL)readFromData:(NSData *)data ofType:(NSString *)typeName error:(NSError **)outError
{
		BOOL ret = YES;
		
		DLog(@"GrammarDesignerDocument::readFromData length == %d", [data length]);
		
		if([data length] >= 1024 * 1024 * 10)
		{
				if(outError != NULL ) 
				{
						*outError = [NSError errorWithDomain:NSOSStatusErrorDomain code:unimpErr userInfo:NULL];
				}
				
				
				return NO;
				
		}
		
		size_t len = [data length];
		
		
		
		arBuffer_t *buf = AR_CreateBuffer(len);
		arString_t *str = AR_CreateString();
		AR_InsertBuffer(buf, (const byte_t*)[data bytes], len);
		
		if(AR_LoadBomTextFromBinary(buf, NULL, str) == AR_S_YES)
		{
				
				
				
				NSString *tempStr = [ARUtility convertUTF32ToNSString : AR_GetStringCString(str)];
				tempStr = [tempStr stringByReplacingOccurrencesOfString : @"\t" 
															 withString : @"    "
						   ];
				
				
				
				[grammarContent release];
				grammarContent = [NSString stringWithString : tempStr];
				[grammarContent retain];
				
				if(grammarTextView != nil)
				{
						[grammarTextView setString : grammarContent];
				}
				
				ret = YES;
		}else
		{
				ret = NO;
				if(outError != NULL ) 
				{
						*outError = [NSError errorWithDomain:NSOSStatusErrorDomain code:unimpErr userInfo:NULL];
				}
		}
		
		AR_DestroyBuffer(buf);
		AR_DestroyString(str);
		buf = NULL;
		str = NULL;
		
		return ret;
}








/****************************Timer Callback************************/

- (void)onGrammarChecker:(NSTimer*)theTimer
{
		DLog(@"GrammarDesignerDocument::onGrammarChecker for timer %@", theTimer);
		
		NSString *newContent = [grammarTextView string];
		
		if([grammarContent isEqualToString : newContent])
		{
				return;
		}
		[grammarContent release];
		grammarContent = [NSString stringWithString : newContent];
		[grammarContent retain];

		if([grammarContent length] > 0)
		{
				GrammarCheckTaskMessage *msg = [[GrammarCheckTaskMessage alloc] initWithSources : grammarContent];
				[grammarCheckerTask PostMsgToWorker : msg];
		}
		
}

-(void) onGrammarCheckerCompleted : (const cfgConfig_t*)parseResult
{
		DLog(@"GrammarDesignerDocument::onGrammarCheckerCompleted");
		[tagsView update : parseResult];
}

/********************************************Notification*********************/


-(void)handleFontChanged : (NSNotification*)note
{
		DLog(@"GrammarDesignerDocument::handleFontChanged for notification %@", note);
		
		
}


-(void)handleLexerChanged : (NSNotification*)note
{
		DLog(@"GrammarDesignerDocument::handleLexerChanged for notification %@", note);
		
		
}


-(void)handleParserChanged : (NSNotification*)note
{
		DLog(@"GrammarDesignerDocument::handleParserChanged for notification %@", note);
		
		NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
		NSInteger interval = (NSInteger)[defaults doubleForKey : PREFERENCE_BUILD_TAGS_INTERVAL];
		[self on_reset_timer : interval];
		
}


-(void)handleApplicationChanged : (NSNotification*)note
{
		DLog(@"GrammarDesignerDocument::handleApplicationChanged for notification %@", note);
		
}




-(void)handleMainWindowWillMiniaturize : (NSNotification*)note
{
		DLog(@"GrammarDesignerDocument::handleMainWindowMiniaturize for notification %@", note);

}

-(void)handleMainWindowBecomeMain : (NSNotification*)note
{
		DLog(@"GrammarDesignerDocument::handleMainWindowBecomeMain for notification %@", note);

}


-(void)handleShowInputChecker : (NSNotification*)note
{
		DLog(@"GrammarDesignerDocument::handleShowInputChecker for notification %@", note);
		[self showInputChecker : self];
}



-(void)handleBuildParser : (NSNotification*)note
{
		DLog(@"GrammarDesignerDocument::handleBuildParser for notification %@", note);
		[self buildDocumentParser : self];
}

-(void)handleFindAllReferences : (NSNotification*)note
{
		[findResultsView clear];
		DLog(@"GrammarDesignerDocument::handleFindAllReferences for notification %@", note);
	
		NSString *key = [[note userInfo] objectForKey:@"UserInfo"];
		
		if(key == nil || [key length] == 0)
		{
				return;
		}
		
		WideCharWrapper *wcs_key = [ARUtility convertNSStringToUTF32 : key];

		
		int find_cnt = 0;
		NSString *src = [grammarTextView string];
		if(src == nil || [src length] == 0)
		{
				return;
		}
		
		WideCharWrapper *wcs_src = [ARUtility convertNSStringToUTF32 : src];

		
		
		const cfgLexicalSet_t *lx_set = CFG_CollectLexicalSet([wcs_src string]);
		
		
		if(lx_set != NULL)
		{
				
				for(size_t i = 0; i < lx_set->cnt; ++i)
				{
						const lexToken_t *tok = &lx_set->token_set[i];
						
						if(tok->count == 0 || tok->count != wcslen([wcs_key string]))
						{
								continue;
						}
						assert(tok->str != NULL);
						
						if(wcsncmp(tok->str, [wcs_key string], tok->count) == 0)
						{
								NSString *msg = [NSString stringWithFormat : @"(Line : %u, Col : %u) : %@",
												 (unsigned int)tok->line, 
												 (unsigned int)tok->col, 
												 [grammarTextView getLine : tok->line]
												 
												 ];
								

								[findResultsView append :[ConsoleMessage consoleMessageWithType : CONSOLE_MSG_MESSAGE_T
																							Msg : msg
																						   Line : tok->line
														  ]
								 
								 ];
								
								find_cnt += 1;
								
						}
				}
				
				CFG_DestroyLexicalSet(lx_set);
				lx_set = NULL;
		}
		
		if(find_cnt <= 1)/*如果只找到一个词法值,则此词法值为当前词法值，启动全局搜索*/
		{
				[findResultsView clear];
				NSArray *lines = nil;

				lines = [grammarTextView getLines];
				
				for(size_t i = 0; i < [lines count]; ++i)
				{
						NSString *line = [lines objectAtIndex : i];
						
						NSRange range = [line rangeOfString : key];
						
						if(range.location != NSNotFound && range.length > 0)
						{
								NSString *msg = [NSString stringWithFormat : @"(Line : %u) : %@",
												 i,
												 line
												 ];
								
								
								[findResultsView append :[ConsoleMessage consoleMessageWithType : CONSOLE_MSG_MESSAGE_T
																							Msg : msg
																						   Line : i
														  ]
								 
								 ];
								
								find_cnt += 1;
						}
				}
				
		}

		if(find_cnt == 0)
		{
				[findResultsView append :[ConsoleMessage consoleMessageWithType : CONSOLE_MSG_MESSAGE_T
																			Msg : @"Not found!"
																		   Line : -1
										  ]
				 
				 ];
		}
		
		[consoleTabView selectTabViewItemAtIndex : 1];
}



-(void)handleGotoDeclaration : (NSNotification*)note
{
		
		DLog(@"GrammarDesignerDocument::handleGotoDeclaration for notification %@", note);
		
		NSString *key = [[note userInfo] objectForKey:@"UserInfo"];
		
		if(key == nil || [key length] == 0)
		{
				return;
		}
		
		
		TagsItemInfo *info =  [tagsView lookupByName : key];
		
		if(info == nil)
		{
				return;
		}
		
		[grammarTextView selecteLine : info.line];
		
}


-(void)handleShowActionTable : (NSNotification*)note
{
		DLog(@"GrammarDesignerDocument::handleShowActionTable for notification %@", note);

}

-(void)handleShowConflicts : (NSNotification*)note
{
		DLog(@"GrammarDesignerDocument::handleShowConflicts for notification %@", note);
		
		const psrConflictView_t *view = [parser createParserConflictView];
		
		if(view)
		{
				[actionView drawConflictView : view];
				[parser destroyParserConflictView : view];
				[consoleTabView selectTabViewItemAtIndex : 2];
		}
		

}

-(void)handleShowFirstFollowSet : (NSNotification*)note
{
		DLog(@"GrammarDesignerDocument::handleShowFirstFollowSet for notification %@", note);
		
		const psrStatusView_t *view = [parser createParserView];
		if(view)
		{
				[actionView drawFirstFollowView : view];
				[parser destroyParserView : view];
				
				[consoleTabView selectTabViewItemAtIndex : 2];
		}

}

-(void)handleShowLeftRecursive : (NSNotification*)note
{
		DLog(@"GrammarDesignerDocument::handleShowLeftRecursive for notification %@", note);
		
		const psrStatusView_t *view = [parser createParserView];
		if(view)
		{
				[actionView drawLeftRecursionView : view];
				[parser destroyParserView : view];
				
				[consoleTabView selectTabViewItemAtIndex : 2];
		}

		
}

-(void)handleShowLeftFactor : (NSNotification*)note
{
		DLog(@"GrammarDesignerDocument::handleShowLeftFactor for notification %@", note);
		
		const psrStatusView_t *view = [parser createParserView];
		if(view)
		{
				[actionView drawLeftFactorView : view];
				[parser destroyParserView : view];
				
				[consoleTabView selectTabViewItemAtIndex : 2];
		}
		

}

-(void)handleParseInput : (NSNotification*)note
{
		DLog(@"GrammarDesignerDocument::handleParseInput for notification %@", note);

		[outputView clear];
		
		if(![ parser isValidParser])
		{
				[self buildDocumentParser : self];
		}
		
		if(![ parser isValidParser])
		{
				return;
		}
		
		
		
		NSString *s = [[note userInfo] objectForKey:@"UserInfo"];
		
		if(s == nil || [s length] == 0)
		{
				return;
		}
		
		
		PrintNode *node = [parser parse : s];
		
		if(node != nil && inputChecker != nil)
		{
				[inputChecker setSyntaxTree : node];
		}
		
		[node release];
		
}


-(void)handleOutputRelocateText : (NSNotification*)note
{
		DLog(@"GrammarDesignerDocument::handleOutputRelocateText for notification %@", note);
		
		ConsoleMessage *msg = [[note userInfo] objectForKey:@"UserInfo"];
		
		if(msg.type == CONSOLE_MSG_MESSAGE_T || msg.type == CONSOLE_MSG_WARNING_T || msg.type == CONSOLE_MSG_ERROR_T)
		{
				if(msg.line >= 0)
				{
						[grammarTextView selecteLine : msg.line ];
				}
		}else if(msg.type == CONSOLE_MSG_INPUT_MESSAGE_T || msg.type == CONSOLE_MSG_INPUT_WARNING_T || msg.type == CONSOLE_MSG_INPUT_ERROR_T)
		{
				if(msg.line >= 0 && inputChecker != nil)
				{
						[inputChecker	selectInputLine : msg.line];
				}
		}
		
}


-(void)handleFindResultsRelocateText : (NSNotification*)note
{
		DLog(@"GrammarDesignerDocument::handleOutputRelocateText for notification %@", note);
		
		ConsoleMessage *msg = [[note userInfo] objectForKey:@"UserInfo"];
		
		if(msg.type == CONSOLE_MSG_MESSAGE_T || msg.type == CONSOLE_MSG_WARNING_T || msg.type == CONSOLE_MSG_ERROR_T)
		{
				if(msg.line >= 0)
				{
						[grammarTextView selecteLine : msg.line ];
				}
		}
		
}


-(void)handleTagsViewRelocateText : (NSNotification*)note
{
		NSNumber *num = [[note userInfo] objectForKey:@"UserInfo"];
		if(num != nil && [num intValue] >= 0)
		{
				[grammarTextView selecteLine : [num intValue]];
		}
}

-(void)handleSyntaxTreeViewRelocateText : (NSNotification*)note
{
		
		PrintNode *node = [[note userInfo] objectForKey:@"UserInfo"];
		DLog(@"%@", node.name);
		
		if(node.isTerm)
		{
				if(inputChecker == nil)
				{
						return;
				}
				
				[inputChecker selectInputLocation : node.index
										   Length : node.length
				 ];
		}else
		{
				TagsItemInfo *info =  [tagsView lookupByName : node.name];
				
				if(info == nil)
				{
						return;
				}
				
				[grammarTextView selecteLine : info.line];
		}
		
}
/***************************************************Action********************************/



-(IBAction)setDocumentLexerSingleLine : (id)sender
{
		DLog(@"On GrammarDesignerDocument::setDocumentLexerSingleLine");
		lexIsSingleLine = !lexIsSingleLine;
		parser.lexIsSingleLine = lexIsSingleLine;
}

-(IBAction)setDocumentLexerIgnoreCase : (id)sender
{
		DLog(@"On GrammarDesignerDocument::setDocumentLexerIgnoreCase");
		lexIsIgnoreCase = !lexIsIgnoreCase;
		
		parser.lexIsIgnoreCase = lexIsIgnoreCase;
}

-(IBAction)setDocumentParserModeSLR : (id)sender
{
		DLog(@"On GrammarDesignerDocument::setDocumentParserModeSLR");
		parserMode = PARSER_SLR;
		parser.parserMode = parserMode;
}

-(IBAction)setDocumentParserModeLALR : (id)sender
{
		DLog(@"On GrammarDesignerDocument::setDocumentParserModeLALR");
		parserMode = PARSER_LALR;
		parser.parserMode = parserMode;
}



-(IBAction)buildDocumentParser	:	(id)sender
{
		DLog(@"On GrammarDesignerDocument::buildDocumentParser");
		[outputView clear];
		[consoleTabView selectTabViewItemAtIndex : 0];
		
		NSString *s = [grammarTextView  string];
		
		if([parser generateFromGrammar : s])
		{
				
		}else
		{
				
				
		}
		
		[grammarTextView setParserIsBuild : [parser isValidParser]];
		
		if(inputChecker != nil)
		{
				[inputChecker setHasValidParser : [parser isValidParser]];
		}
		
		
}


-(IBAction)rebuildDocumentTags	:	(id)sender
{
		DLog(@"On GrammarDesignerDocument::rebuildDocumentTags");
		GrammarCheckTaskMessage *msg = [[GrammarCheckTaskMessage alloc] initWithSources : [grammarTextView string]];
		[grammarCheckerTask PostMsgToWorker : msg];

}

-(IBAction)generateDocumentGrammarTemplateCode : (id)sender
{
		DLog(@"On GrammarDesignerDocument::generateDocumentGrammarTemplateCode");
		
		NSString *code = [parser generateCodeTemplate : [grammarTextView string]];
		
		if(code == nil)
		{
				return;
		}
		
		NSSavePanel *panel = [NSSavePanel savePanel];
		[panel setDirectory:NSHomeDirectory()]; 
		if ([panel runModal] == NSOKButton) 
		{
				NSString *path = [[panel URL] path];
				DLog(@"%@", path);
				const wchar_t *wcs_path = [[ARUtility convertNSStringToUTF32 : path] string];
				const wchar_t *wcs_code = [[ARUtility convertNSStringToUTF32 : code] string];
				
				if(AR_SaveBomTextFile(wcs_path, AR_TXT_BOM_UTF_8, wcs_code) != AR_S_YES)
				{
						NSRunAlertPanel(@"Warning", @"Save to \"%@\" failed!", @"OK", nil,nil, path);
				}
		}
}

-(IBAction)showInputChecker : (id)sender
{
		DLog(@"On GrammarDesignerDocument::showInputChecker");
		BOOL need_register_notification = NO;
		if(inputChecker == nil)
		{
				inputChecker = [[InputChecker alloc] init];
				need_register_notification = YES;
				
				[inputChecker show : self];
				
				NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
				
				[nc addObserver : self
					   selector : @selector(handleParseInput:)
						   name : NOTIFICATION_INPUTVIEW_INVOKE_PARSEINPUT
						 object : inputChecker.textView
				 ];
				
				[nc addObserver : self
					   selector : @selector(handleSyntaxTreeViewRelocateText:)
						   name : NOTIFICATION_SYNTAXTREEVIEW_INVOKE_RELOCATE
						 object : inputChecker.syntaxView
				 ];
				
				[inputChecker setHasValidParser : [parser isValidParser]];
				
		}else
		{
		
				if([inputChecker isShow])
				{
						[inputChecker hide : self];

				}else
				{		
						[inputChecker show : self];
				}
				[inputChecker setHasValidParser : [parser isValidParser]];
		}

		
		
}





/***********************************UpdateUI***********************/
/*
 
 -(IBAction)setDocumentLexerSingleLine : (id)sender;
 -(IBAction)setDocumentLexerIgnoreCase : (id)sender;
 -(IBAction)setDocumentParserModeSLR : (id)sender;
 -(IBAction)setDocumentParserModeLALR : (id)sender;
 -(IBAction)buildDocumentParser	:	(id)sender;
 -(IBAction)parseDocumentInput	:	(id)sender;
 -(IBAction)rebuildDocumentTags	:	(id)sender;
 -(IBAction)generateDocumentGrammarTemplateCode : (id)sender;
 
 */

-(BOOL)validateUserInterfaceItem:(id < NSValidatedUserInterfaceItem >)item
{

		BOOL ret = YES;
		assert(item != nil);
		
		NSMenuItem *menuItem = (NSMenuItem*)item;
		
		if([menuItem action] == @selector(setDocumentLexerSingleLine:)) 
		{
				if(lexIsSingleLine)
				{
						[menuItem setState : NSOnState];
				}else
				{
						[menuItem setState : NSOffState];
				}
				
		}else if([menuItem action] == @selector(setDocumentLexerIgnoreCase:))
		{
				if(lexIsIgnoreCase)
				{
						[menuItem setState : NSOnState];
				}else
				{
						[menuItem setState : NSOffState];
				}
				
		}else if([menuItem action] == @selector(setDocumentParserModeSLR:))
		{
				if(parserMode == PARSER_SLR)
				{
						[menuItem setState : NSOnState];
				}else
				{
						[menuItem setState : NSOffState];
				}
				
		}else if([menuItem action] == @selector(setDocumentParserModeLALR:))
		{
				if(parserMode == PARSER_LALR)
				{
						[menuItem setState : NSOnState];
				}else
				{
						[menuItem setState : NSOffState];
				}
				
		}else if([menuItem action] == @selector(buildDocumentParser:))
		{
				
				
		}else if([menuItem action] == @selector(rebuildDocumentTags:))
		{
				
		}else if([menuItem action] == @selector(generateDocumentGrammarTemplateCode:))
		{
				
		}
	

		return ret;
}





/***********************************Used for other class***********************/
-(BOOL)hasParser
{
		return NO;
}


@end




