/* * Copyright (c) 2011 by Solidus * This file is part of Arsenal library tools source code. * * Permission to use, copy, modify, distribute and sell this software * and its documentation for any purpose is hereby granted without fee, * provided that the above copyright notice appear in all copies and * that both that copyright notice and this permission notice appear * in supporting documentation.It is provided "as is" without express  * or implied warranty. * */#import "Preferences.h"#import "Common.h"@implementation Preferences+(void)setDefaultPreferences{		NSMutableDictionary *defaultValues = [NSMutableDictionary dictionary];						[defaultValues setObject : [NSNumber numberWithBool : YES] forKey : PREFERENCE_APPLICATION_IS_OPEN_EMPTY_DOCUMENT];				[defaultValues setObject : [NSNumber numberWithInt : PARSER_LALR] forKey : PREFERENCE_PARSER_MODE];		[defaultValues setObject : [NSNumber numberWithInt : 500] forKey : PREFERENCE_BUILD_TAGS_INTERVAL];		[defaultValues setObject : [NSNumber numberWithBool : NO] forKey : PREFERENCE_LEX_IS_SINGLELINE];		[defaultValues setObject : [NSNumber numberWithBool : NO] forKey : PREFERENCE_LEX_IS_IGNORECASE];						[defaultValues setObject : @"Menlo" forKey : PREFERENCE_FONT_GRAMMAR_NAME];		[defaultValues setObject : [NSNumber numberWithInt : 13] forKey : PREFERENCE_FONT_INPUT_SIZE];				[defaultValues setObject : @"Menlo" forKey : PREFERENCE_FONT_INPUT_NAME];		[defaultValues setObject : [NSNumber numberWithInt : 13] forKey : PREFERENCE_FONT_GRAMMAR_SIZE];				[defaultValues setObject : @"Menlo" forKey : PREFERENCE_FONT_TAGS_NAME];		[defaultValues setObject : [NSNumber numberWithInt : 13] forKey : PREFERENCE_FONT_TAGS_SIZE];				[defaultValues setObject : @"Menlo" forKey : PREFERENCE_FONT_TREEVIEW_NAME];		[defaultValues setObject : [NSNumber numberWithInt : 12] forKey : PREFERENCE_FONT_TREEVIEW_SIZE];				[defaultValues setObject : @"Menlo" forKey : PREFERENCE_FONT_CONSOLE_NAME];		[defaultValues setObject : [NSNumber numberWithInt : 12] forKey : PREFERENCE_FONT_CONSOLE_SIZE];				[[NSUserDefaults standardUserDefaults] registerDefaults : defaultValues];				DLog(@"registered defaults : %@", defaultValues);		}-(void)setFontLabel : (NSTextField*)label  			   name : (NSString*)name 			   size : (NSInteger)size{		NSString *v = [NSString stringWithFormat:@"%@ %d", name, size];		DLog(@"%@", v);		[label setStringValue : v];}-(id)init{				DLog(@"On Preferences init");				self = [super initWithWindowNibName : @"Preferences"];				if(self)		{				NSNotificationCenter *dc = [NSNotificationCenter defaultCenter];				id obj = [self window];				[dc addObserver : self 					   selector : @selector(onPanelClose:)						   name : NSWindowWillCloseNotification						 object : obj				 ];								NSString *name;				NSInteger size;				NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];								name = [defaults stringForKey : PREFERENCE_FONT_GRAMMAR_NAME];				size = (NSInteger)[defaults doubleForKey : PREFERENCE_FONT_GRAMMAR_SIZE];				grammarFont = [NSFont fontWithName:name size:size];				[grammarFont retain];															name = [defaults stringForKey : PREFERENCE_FONT_INPUT_NAME];				size = (NSInteger)[defaults doubleForKey : PREFERENCE_FONT_INPUT_SIZE];				inputFont = [NSFont fontWithName:name size:size];				[inputFont retain];												name = [defaults stringForKey : PREFERENCE_FONT_TAGS_NAME];				size = (NSInteger)[defaults doubleForKey : PREFERENCE_FONT_TAGS_SIZE];				tagsFont = [NSFont fontWithName:name size:size];				[tagsFont retain];												name = [defaults stringForKey : PREFERENCE_FONT_TREEVIEW_NAME];				size = (NSInteger)[defaults doubleForKey : PREFERENCE_FONT_TREEVIEW_SIZE];				treeViewFont = [NSFont fontWithName:name size:size];				[treeViewFont retain];											name = [defaults stringForKey : PREFERENCE_FONT_CONSOLE_NAME];				size = (NSInteger)[defaults doubleForKey : PREFERENCE_FONT_CONSOLE_SIZE];				consoleFont = [NSFont fontWithName:name size:size];				[consoleFont retain];		}		return self;}-(void)dealloc{		[grammarFont release];		[inputFont release];		[tagsFont release];		[treeViewFont release];		[consoleFont release];				NSNotificationCenter *dc = [NSNotificationCenter defaultCenter];		[dc removeObserver : self];		[super dealloc];}-(void) setupRebuildTagsInterval : (NSInteger)value{				NSInteger interval  = value;				NSString *s;				if(interval > 0)		{				s = [NSString stringWithFormat : @"%d ms", interval];		}else		{				s = @"Disable";		}						[rebuildTagIntervalField setStringValue : s];				NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];		[defaults setInteger : value					  forKey : PREFERENCE_BUILD_TAGS_INTERVAL		 ];				}-(void)onPanelClose : (NSNotification*)note{		DLog(@"%@", note);}-(void)windowDidLoad{		DLog(@"Nib file is loaded");}-(void)show : (id)sender{				[self showWindow : sender];}-(IBAction)	onSingleLine : (id)sender{		DLog(@"Preferences::onSingleLine : %@", [sender state] == NSOnState ? @"ON" : @"OFF");				NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];		[defaults setBool : [sender state] == NSOnState				   forKey : PREFERENCE_LEX_IS_SINGLELINE		 ];						DLog(@"Sending notification '%@'", NOTIFICATION_PREFERENCE_LEXER_CHANGED);		NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];		[nc postNotificationName: NOTIFICATION_PREFERENCE_LEXER_CHANGED 						 object : self		 ];						}-(IBAction) onIgnoreCase : (id)sender{		DLog(@"Preferences::onIgnoreCase : %@", [sender state] == NSOnState ? @"ON" : @"OFF");		NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];		[defaults setBool : [sender state] == NSOnState				   forKey : PREFERENCE_LEX_IS_IGNORECASE		 ];				DLog(@"Sending notification '%@'", NOTIFICATION_PREFERENCE_LEXER_CHANGED);		NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];		[nc postNotificationName: NOTIFICATION_PREFERENCE_LEXER_CHANGED 						 object : self		 ];								}-(IBAction) onParserModeSLR : (id)sender{		DLog(@"Preferences::onParserModeSLR : %@", [sender selectedCell]);				NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];		[defaults setInteger : PARSER_SLR					  forKey : PREFERENCE_PARSER_MODE		 ];						DLog(@"Sending notification '%@'", NOTIFICATION_PREFERENCE_PARSER_CHANGED);				NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];		[nc postNotificationName: NOTIFICATION_PREFERENCE_PARSER_CHANGED 						 object : self		 ];						}-(IBAction) onParserModeLALR : (id)sender{		DLog(@"Preferences::onParserModeLALR : %@", [sender selectedCell]);		NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];		[defaults setInteger : PARSER_LALR					  forKey : PREFERENCE_PARSER_MODE		 ];				DLog(@"Sending notification '%@'", NOTIFICATION_PREFERENCE_PARSER_CHANGED);				NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];		[nc postNotificationName: NOTIFICATION_PREFERENCE_PARSER_CHANGED 						 object : self		 ];						}-(IBAction) onRebuildTagsIntervalChanged : (id)sender{		NSInteger value = (NSInteger)[sender doubleValue];				value -= value % 10;				DLog(@"Preferences::onRebuildTagsIntervalChanged : %u", value);		[self setupRebuildTagsInterval : value * 50];		DLog(@"Sending notification '%@'", NOTIFICATION_PREFERENCE_PARSER_CHANGED);				NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];		[nc postNotificationName: NOTIFICATION_PREFERENCE_PARSER_CHANGED 						 object : self		 ];								}-(IBAction) onChangeGrammarFont : (id)sender{		changing_font = FONT_CHANGE_GRAMMAR;		[[NSFontManager sharedFontManager] setSelectedFont : grammarFont isMultiple:NO];		[[NSFontManager sharedFontManager] orderFrontFontPanel:self];}-(IBAction) onChangeInputFont : (id)sender{		changing_font = FONT_CHANGE_INPUT;		[[NSFontManager sharedFontManager] setSelectedFont : inputFont isMultiple:NO];		[[NSFontManager sharedFontManager] orderFrontFontPanel:self];}-(IBAction) onChangeTagsFont : (id)sender{		changing_font = FONT_CHANGE_TAGS;		[[NSFontManager sharedFontManager] setSelectedFont : tagsFont isMultiple:NO];		[[NSFontManager sharedFontManager] orderFrontFontPanel:self];}-(IBAction) onChangeTreeViewFont : (id)sender{		changing_font = FONT_CHANGE_TREEVIEW;		[[NSFontManager sharedFontManager] setSelectedFont : treeViewFont isMultiple:NO];		[[NSFontManager sharedFontManager] orderFrontFontPanel:self];}-(IBAction) onChangeConsoleFont : (id)sender{		changing_font = FONT_CHANGE_CONSOLE;		[[NSFontManager sharedFontManager] setSelectedFont : consoleFont isMultiple:NO];		[[NSFontManager sharedFontManager] orderFrontFontPanel:self];}- (void)changeFont:(id)sender{		DLog(@"Preferences::changeFont");				NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];								NSFontManager *fontManager = [NSFontManager sharedFontManager];				switch(changing_font)		{		case FONT_CHANGE_GRAMMAR:		{				grammarFont = [fontManager convertFont:grammarFont];				[grammarFont retain];				NSString *name = [grammarFont displayName];				NSInteger size = [grammarFont pointSize];								[defaults setObject : name							 forKey : PREFERENCE_FONT_GRAMMAR_NAME				 ];								[defaults setInteger : size							  forKey : PREFERENCE_FONT_GRAMMAR_SIZE				 ];								[self setFontLabel : grammarFontLabel							  name : name							  size : size				 ];				DLog(@"Preferences::changeFont grammarFont to %@", grammarFont);				break;		}		case FONT_CHANGE_INPUT:		{				inputFont = [fontManager convertFont:inputFont];				[inputFont retain];				NSString *name = [inputFont displayName];				NSInteger size = [inputFont pointSize];								[defaults setObject : name							 forKey : PREFERENCE_FONT_INPUT_NAME				 ];								[defaults setInteger : size							  forKey : PREFERENCE_FONT_INPUT_SIZE				 ];								[self setFontLabel : inputFontLabel							  name : name							  size : size				 ];				DLog(@"Preferences::changeFont inputFont to %@", inputFont);		}				break;		case FONT_CHANGE_TAGS:		{				tagsFont = [fontManager convertFont:tagsFont];				[tagsFont retain];				NSString *name = [tagsFont displayName];				NSInteger size = [tagsFont pointSize];								[defaults setObject : name							 forKey : PREFERENCE_FONT_TAGS_NAME				 ];								[defaults setInteger : size							  forKey : PREFERENCE_FONT_TAGS_SIZE				 ];								[self setFontLabel : tagsFontLabel							  name : name							  size : size				 ];				DLog(@"Preferences::changeFont tagsFont to %@", tagsFont);		}						break;		case FONT_CHANGE_TREEVIEW:		{				treeViewFont = [fontManager convertFont:treeViewFont];				[treeViewFont retain];				NSString *name = [treeViewFont displayName];				NSInteger size = [treeViewFont pointSize];								[defaults setObject : name							 forKey : PREFERENCE_FONT_TREEVIEW_NAME				 ];								[defaults setInteger : size							  forKey : PREFERENCE_FONT_TREEVIEW_SIZE				 ];								[self setFontLabel : treeViewFontLabel							  name : name							  size : size				 ];										DLog(@"Preferences::changeFont treeViewFont to %@", treeViewFont);		}				break;						case FONT_CHANGE_CONSOLE:		{				consoleFont = [fontManager convertFont:consoleFont];				[consoleFont retain];				NSString *name = [consoleFont displayName];				NSInteger size = [consoleFont pointSize];								[defaults setObject : name							 forKey : PREFERENCE_FONT_CONSOLE_NAME				 ];								[defaults setInteger : size							  forKey : PREFERENCE_FONT_CONSOLE_SIZE				 ];								[self setFontLabel : consoleFontLabel							  name : name							  size : size				 ];						DLog(@"Preferences::changeFont consoleFont to %@", consoleFont);		}				break;		default:				assert(false);		}				DLog(@"Sending notification '%@'", NOTIFICATION_PREFERENCE_FONT_CHANGED);				NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];		[nc postNotificationName: NOTIFICATION_PREFERENCE_FONT_CHANGED 						 object : self		 ];		}-(void)awakeFromNib{				NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];				BOOL isOpenEmptyDocument = [defaults boolForKey : PREFERENCE_APPLICATION_IS_OPEN_EMPTY_DOCUMENT];		[openEmptyDocument setState : isOpenEmptyDocument];								NSInteger paser_mode = (NSInteger)[defaults doubleForKey : PREFERENCE_PARSER_MODE];		[parserModeCtrl selectCellAtRow : 0 								 column : paser_mode == PARSER_SLR  ? 0 : 1		 ];				NSInteger interval = (NSInteger)[defaults doubleForKey : PREFERENCE_BUILD_TAGS_INTERVAL];		[self setupRebuildTagsInterval : interval];		[buildTagsIntervalSlider setDoubleValue : interval / 50];						BOOL isSingleLine = [defaults boolForKey : PREFERENCE_LEX_IS_SINGLELINE];		BOOL isIgnoreCase = [defaults boolForKey : PREFERENCE_LEX_IS_IGNORECASE];		[singlelineButton setState : isSingleLine];		[ignorecaseButton setState : isIgnoreCase];						NSString *name;		NSInteger size;								name = [defaults stringForKey : PREFERENCE_FONT_GRAMMAR_NAME];		size = (NSInteger)[defaults doubleForKey : PREFERENCE_FONT_GRAMMAR_SIZE];		[self setFontLabel : grammarFontLabel 					  name : name					  size : size		 ];						name = [defaults stringForKey : PREFERENCE_FONT_INPUT_NAME];		size = (NSInteger)[defaults doubleForKey : PREFERENCE_FONT_INPUT_SIZE];		[self setFontLabel : inputFontLabel 					  name : name					  size : size		 ];				name = [defaults stringForKey : PREFERENCE_FONT_TAGS_NAME];		size = (NSInteger)[defaults doubleForKey : PREFERENCE_FONT_TAGS_SIZE];		[self setFontLabel : tagsFontLabel 					  name : name					  size : size		 ];				name = [defaults stringForKey : PREFERENCE_FONT_TREEVIEW_NAME];		size = (NSInteger)[defaults doubleForKey : PREFERENCE_FONT_TREEVIEW_SIZE];		[self setFontLabel : treeViewFontLabel 					  name : name					  size : size		 ];				name = [defaults stringForKey : PREFERENCE_FONT_CONSOLE_NAME];		size = (NSInteger)[defaults doubleForKey : PREFERENCE_FONT_CONSOLE_SIZE];		[self setFontLabel : consoleFontLabel 					  name : name					  size : size		 ];				}-(IBAction) onIsOpenEmptyDocument : (id)sender{		DLog(@"Preferences::onIsOpenEmptyDocument : %@", sender);						NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];		[defaults setBool : [sender state] == NSOnState				   forKey : PREFERENCE_APPLICATION_IS_OPEN_EMPTY_DOCUMENT		 ];						DLog(@"Sending notification '%@'", NOTIFICATION_PREFERENCE_APPLICATION_CHANGED);				NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];		[nc postNotificationName: NOTIFICATION_PREFERENCE_APPLICATION_CHANGED 						 object : self		 ];				}@end