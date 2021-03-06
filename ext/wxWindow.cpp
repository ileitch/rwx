/*
 * wxWindow.cpp
 *
 *  Created on: 04.02.2012
 *      Author: hanmac
 */
#include "wxWindow.hpp"
#include "wxEvtHandler.hpp"
#include "wxProgressDialog.hpp"
#include "wxFont.hpp"
#include "wxColor.hpp"
#include "wxSizer.hpp"
#include "wxPoint.hpp"
#include "wxDC.hpp"

#include "wxCursor.hpp"

#include "wxAui.hpp"
#define _self wrap<wxWindow*>(self)

VALUE rb_cWXWindow;

static std::map<ID,wxWindowID> idholder;

VALUE wrapID(wxWindowID val)
{
	if(val == wxID_NONE)
		return Qnil;

	for(std::map<ID,wxWindowID>::const_iterator it = idholder.begin();
			it != idholder.end();
			it++)
	{
		if(it->second == val)
			return ID2SYM(it->first);
	}
#if wxUSE_XRC
	wxString str(wxXmlResource::FindXRCIDById(val));
	if(!str.IsEmpty()) {
		ID id = rb_intern(str.c_str());
		idholder.insert(std::make_pair(id,val));
		return ID2SYM(id);
	}
#endif
	return INT2NUM(val);
}
wxWindowID unwrapID(VALUE val)
{
	if(NIL_P(val))
		return wxID_ANY;
	if(SYMBOL_P(val))
	{
		ID id = SYM2ID(val);
		std::map<ID,wxWindowID>::iterator it = idholder.find(id);
		if(it != idholder.end())
			return it->second;
		else
		{
			wxWindowID newid;
#if wxUSE_XRC
			newid = XRCID(rb_id2name(id));
#else
			newid = wxNewId();
#endif
			idholder.insert(std::make_pair(id,newid));
			return newid;
		}
	}else
		return NUM2INT(val);
}

void registerID(const char *name,wxWindowID id)
{
	idholder.insert(std::make_pair(rb_intern(name),id));
}

#if wxUSE_TOOLTIPS

template <>
VALUE wrap< wxToolTip >(wxToolTip* window)
{
	return wrap(window->GetTip());
}

template <>
wxToolTip* wrap< wxToolTip* >(const VALUE &vwindow)
{
	if(NIL_P(vwindow))
		return NULL;
	return new wxToolTip(wrap<wxString>(vwindow));
}
#endif

namespace RubyWX {
namespace Window {

macro_attr(Label,wxString)
macro_attr(Name,wxString)
//macro_attr(WindowVariant,wxWindowVariant)
//macro_attr(LayoutDirection,wxLayoutDirection)

macro_attr_with_func(Id,wrapID,unwrapID)

macro_attr(Position,wxPoint)

macro_attr(Size,wxSize)
macro_attr(VirtualSize,wxSize)

macro_attr(ClientSize,wxSize)

macro_attr(MinSize,wxSize)
macro_attr(MinClientSize,wxSize)

macro_attr(MaxSize,wxSize)
macro_attr(MaxClientSize,wxSize)

//macro_attr(BackgroundStyle,wxBackgroundStyle)

macro_attr(Font,wxFont)
macro_attr(Cursor,wxCursor)

macro_attr_with_func(WindowStyleFlag,LONG2NUM,NUM2LONG)
macro_attr_with_func(ExtraStyle,LONG2NUM,NUM2LONG)

#if wxUSE_VALIDATORS
//macro_attr(Validator,wxValidator)
#endif // wxUSE_VALIDATORS
#if wxUSE_CARET
//macro_attr(Caret,wxCaret*)
#endif // wxUSE_CARET
#if wxUSE_HELP
macro_attr(HelpText,wxString)
#endif // wxUSE_HELP
#if wxUSE_TOOLTIPS
macro_attr(ToolTip,wxToolTip*)
#endif // wxUSE_TOOLTIPS
#if wxUSE_DRAG_AND_DROP
//macro_attr(DropTarget,wxDropTarget*)
#endif // wxUSE_DRAG_AND_DROP
macro_attr(AutoLayout,bool)
macro_attr(ThemeEnabled,bool)

macro_attr(Sizer,wxSizer*)
macro_attr(ContainingSizer,wxSizer*)

singlefunc(Show)
singlefunc(Hide)

singlefunc(Enable)
singlefunc(Disable)


singlefunc(Raise)
singlefunc(Lower)

singlefunc(Freeze)
singlefunc(Thaw)


singlefunc(CaptureMouse)
singlefunc(ReleaseMouse)

singlefunc(Update)
singlefunc(Refresh)

singlefunc(Fit)
singlereturn(Layout)

singlereturn(GetParent)
singlereturn(GetGrandParent)

singlereturn(GetBackgroundColour)
singlereturn(GetForegroundColour)

singlereturn(LineUp)
singlereturn(LineDown)
singlereturn(PageUp)
singlereturn(PageDown)


VALUE _SetParent(VALUE self,VALUE parent)
{
	_self->Reparent(wrap<wxWindow*>(parent));
	return parent;
}


VALUE _SetBackgroundColour(VALUE self,VALUE val)
{
	_self->SetBackgroundColour(wrap<wxColor>(val));
	return val;
}

VALUE _SetForegroundColour(VALUE self,VALUE val)
{
	_self->SetForegroundColour(wrap<wxColor>(val));
	return val;
}

APP_PROTECT(wxWindow)

VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE parent,hash;
	rb_scan_args(argc, argv, "11",&parent,&hash);

	if(!_created) {
		_self->Create(wrap<wxWindow*>(parent),wxID_ANY);
		_created = true;
	}

	if(rb_obj_is_kind_of(hash,rb_cHash))
	{
		VALUE temp;
		if(!NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("extra_style")))))
			_self->SetExtraStyle(NUM2INT(temp));

		if(!NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("name")))))
			_self->SetName(wrap<wxString>(temp));
		if(!NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("label")))))
			_self->SetLabel(wrap<wxString>(temp));
#if wxUSE_HELP
		if(!NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("help_text")))))
			_self->SetHelpText(wrap<wxString>(temp));
#endif // wxUSE_HELP


		if(!NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("id")))))
			_self->SetId(unwrapID(temp));
		if(!NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("size")))))
			_self->SetSize(wrap<wxSize>(temp));
		if(!NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("position")))))
			_self->SetPosition(wrap<wxPoint>(temp));

		if(RTEST(rb_hash_aref(hash,ID2SYM(rb_intern("disabled")))))
			_self->Disable();

	}

	if(rb_block_given_p() && !(wxUSE_PROGRESSDLG && wxUSE_TIMER && rb_obj_is_kind_of(self,rb_cWXProgressDialog)))
		rb_yield(self);
	return self;
}

VALUE _getchild(VALUE self,VALUE id)
{
	return wrap(_self->FindWindow(unwrapID(id)));
}


VALUE _draw(int argc,VALUE *argv,VALUE self)
{
	VALUE paint;
	rb_scan_args(argc, argv, "01",&paint);
	wxDC *dc;
if(NIL_P(paint) || RTEST(paint))
{
	wxPaintDC *mdc = new wxPaintDC(_self);
	_self->PrepareDC(*mdc);
#if wxUSE_GRAPHICS_CONTEXT
	 dc = new wxGCDC(*mdc);
	_self->PrepareDC(*dc);
#else
	dc = mdc;
#endif
}else
{
	wxClientDC *cdc = new wxClientDC(_self);
	_self->PrepareDC(*cdc);
#if wxUSE_GRAPHICS_CONTEXT
	dc = new wxGCDC(*cdc);
	_self->PrepareDC(*dc);
#else
	dc = cdc;
#endif
}

	dc->Clear();
	rb_yield(wrap(dc));
	return self;
}

VALUE _Close(int argc,VALUE *argv,VALUE self)
{
	VALUE force;
	rb_scan_args(argc, argv, "01",&force);
	return wrap(_self->Close(RTEST(force)));
}


#if wxUSE_MENUS
VALUE _popupmenu(int argc,VALUE *argv,VALUE self)
{
	VALUE menu,pos;
	wxPoint cpoint;
	if(rb_block_given_p())
	{
		rb_scan_args(argc, argv, "01",&pos);
		menu = wrap(new wxMenu);
		rb_yield(menu);
	}else{
		rb_scan_args(argc, argv, "11",&menu,&pos);
	}
	if(NIL_P(pos))
		cpoint = wxDefaultPosition;
	else
		cpoint = wrap<wxPoint>(pos);


	return wrap(_self->PopupMenu(wrap<wxMenu*>(menu),cpoint));
}
#endif

#if wxUSE_AUI
VALUE _aui(VALUE self)
{
	wxWindow *wnd = _self;
	VALUE result = Qnil;
	wxAuiManager *mgr = wxAuiManager::GetManager(wnd);
	if(!mgr && rb_block_given_p())
	{
		result = wrap(new wxAuiManager(wnd));
	}
	if(rb_block_given_p())
		rb_yield(result);
	return result;
}
#endif

VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wxWindowList list = _self->GetChildren();
	for(wxWindowList::iterator it = list.begin();it != list.end();++it)
	{
		rb_yield(wrap(*it));
	}
	return self;
}

VALUE _GetMousePosition(VALUE self)
{
	return wrap(wxGetMousePosition());
}


VALUE _ClientToScreen(VALUE self,VALUE point)
{
	return wrap(_self->ClientToScreen(wrap<wxPoint>(point)));
}

VALUE _ScreenToClient(VALUE self,VALUE point)
{
	return wrap(_self->ScreenToClient(wrap<wxPoint>(point)));
}

}
}

void Init_WXWindow(VALUE rb_mWX)
{
	using namespace RubyWX::Window;
#if 0
	rb_define_attr(rb_cWXWindow, "label",1,1);
	rb_define_attr(rb_cWXWindow, "name",1,1);
	rb_define_attr(rb_cWXWindow, "parent",1,1);

	rb_define_attr(rb_cWXWindow, "id",1,1);

	rb_define_attr(rb_cWXWindow, "size",1,1);
	rb_define_attr(rb_cWXWindow, "min_size",1,1);
	rb_define_attr(rb_cWXWindow, "max_size",1,1);

	rb_define_attr(rb_cWXWindow, "sizer",1,1);
	rb_define_attr(rb_cWXWindow, "containing_sizer",1,1);

	rb_define_attr(rb_cWXWindow, "backgroundColor",1,1);
	rb_define_attr(rb_cWXWindow, "foregroundColor",1,1);

	rb_define_attr(rb_cWXWindow, "font",1,1);
	rb_define_attr(rb_cWXWindow, "help_text",1,1);

#endif

	rb_cWXWindow = rb_define_class_under(rb_mWX,"Window",rb_cObject);
	rb_define_alloc_func(rb_cWXWindow,_alloc);

	rb_define_method(rb_cWXWindow,"initialize",RUBY_METHOD_FUNC(_initialize),-1);

	rb_include_module(rb_cWXWindow,rb_mWXEvtHandler);

	rb_define_attr_method(rb_cWXWindow, "label",_getLabel,_setLabel);
	rb_define_attr_method(rb_cWXWindow, "name",_getName,_setName);
	rb_define_attr_method(rb_cWXWindow, "parent",_GetParent,_SetParent);

	rb_define_attr_method(rb_cWXWindow, "id",_getId,_setId);

	rb_define_attr_method(rb_cWXWindow, "size",_getSize,_setSize);
	rb_define_attr_method(rb_cWXWindow, "min_size",_getMinSize,_setMinSize);
	rb_define_attr_method(rb_cWXWindow, "max_size",_getMaxSize,_setMaxSize);

	rb_define_attr_method(rb_cWXWindow, "sizer",_getSizer,_setSizer);
	rb_define_attr_method(rb_cWXWindow, "containing_sizer",_getContainingSizer,_setContainingSizer);

	rb_define_attr_method(rb_cWXWindow, "backgroundColor",_GetBackgroundColour,_SetBackgroundColour);
	rb_define_attr_method(rb_cWXWindow, "foregroundColor",_GetForegroundColour,_SetForegroundColour);

	rb_define_attr_method(rb_cWXWindow, "font",_getFont,_setFont);
#if wxUSE_HELP
	rb_define_attr_method(rb_cWXWindow, "help_text",_getHelpText,_setHelpText);
#endif // wxUSE_HELP

	rb_define_method(rb_cWXWindow,"show",RUBY_METHOD_FUNC(_Show),0);
	rb_define_method(rb_cWXWindow,"hide",RUBY_METHOD_FUNC(_Hide),0);

	rb_define_method(rb_cWXWindow,"[]",RUBY_METHOD_FUNC(_getchild),1);

	rb_define_method(rb_cWXWindow,"each_child",RUBY_METHOD_FUNC(_each),0);

	rb_define_method(rb_cWXWindow,"fit",RUBY_METHOD_FUNC(_Fit),0);
	rb_define_method(rb_cWXWindow,"layout",RUBY_METHOD_FUNC(_Layout),0);

	rb_define_method(rb_cWXWindow,"update",RUBY_METHOD_FUNC(_Update),0);
	rb_define_method(rb_cWXWindow,"refresh",RUBY_METHOD_FUNC(_Refresh),0);

	rb_define_method(rb_cWXWindow,"draw",RUBY_METHOD_FUNC(_draw),-1);
	rb_define_method(rb_cWXWindow,"close",RUBY_METHOD_FUNC(_Close),-1);

#if wxUSE_MENUS
	rb_define_method(rb_cWXWindow,"popupmenu",RUBY_METHOD_FUNC(_popupmenu),-1);
#endif
#if wxUSE_AUI
	rb_define_method(rb_cWXWindow,"aui",RUBY_METHOD_FUNC(_aui),0);
#endif

	rb_define_module_function(rb_mWX,"mouse_position",RUBY_METHOD_FUNC(_GetMousePosition),0);

	rb_define_method(rb_cWXWindow,"client_to_screen",RUBY_METHOD_FUNC(_ClientToScreen),1);
	rb_define_method(rb_cWXWindow,"screen_to_client",RUBY_METHOD_FUNC(_ScreenToClient),1);

	registerInfo<wxWindow>(rb_cWXWindow);

	registerID("open",wxID_OPEN);
	registerID("close",wxID_CLOSE);
	registerID("new",wxID_NEW);
	registerID("save",wxID_SAVE);
	registerID("save_as",wxID_SAVEAS);
	registerID("revert",wxID_REVERT);
	registerID("exit",wxID_EXIT);
	registerID("undo",wxID_UNDO);
	registerID("redo",wxID_REDO);
	registerID("help",wxID_HELP);
	registerID("print",wxID_PRINT);
	registerID("print_setup",wxID_PRINT_SETUP);
	registerID("page_setup",wxID_PAGE_SETUP);
	registerID("preview",wxID_PREVIEW);
	registerID("about",wxID_ABOUT);
	registerID("help_contents",wxID_HELP_CONTENTS);
	registerID("help_index",wxID_HELP_INDEX);
	registerID("help_search",wxID_HELP_SEARCH);
	registerID("help_commands",wxID_HELP_COMMANDS);
	registerID("help_procedurs",wxID_HELP_PROCEDURES);
	registerID("help_context",wxID_HELP_CONTEXT);
	registerID("close_all",wxID_CLOSE_ALL);
	registerID("preferences",wxID_PREFERENCES);

	registerID("edit",wxID_EDIT);
	registerID("cut",wxID_CUT);
	registerID("copy",wxID_COPY);
	registerID("paste",wxID_PASTE);
	registerID("clear",wxID_CLEAR);
	registerID("find",wxID_FIND);
	registerID("duplicate",wxID_DUPLICATE);
	registerID("select_all",wxID_SELECTALL);
	registerID("delete",wxID_DELETE);
	registerID("replace",wxID_REPLACE);
	registerID("replace_all",wxID_REPLACE_ALL);
	registerID("properties",wxID_PROPERTIES);

	registerID("view_details",wxID_VIEW_DETAILS);
	registerID("view_largeicons",wxID_VIEW_LARGEICONS);
	registerID("view_smallicons",wxID_VIEW_SMALLICONS);
	registerID("view_list",wxID_VIEW_LIST);
	registerID("view_sortdate",wxID_VIEW_SORTDATE);
	registerID("view_sortname",wxID_VIEW_SORTNAME);
	registerID("view_sortsize",wxID_VIEW_SORTSIZE);
	registerID("view_sorttype",wxID_VIEW_SORTTYPE);

	registerID("file",wxID_FILE);
	registerID("file1",wxID_FILE1);
	registerID("file2",wxID_FILE2);
	registerID("file3",wxID_FILE3);
	registerID("file4",wxID_FILE4);
	registerID("file5",wxID_FILE5);
	registerID("file6",wxID_FILE6);
	registerID("file7",wxID_FILE7);
	registerID("file8",wxID_FILE8);
	registerID("file9",wxID_FILE9);

    /*  Standard button and menu IDs */
	registerID("ok",wxID_OK);
	registerID("cancel",wxID_CANCEL);
	registerID("apply",wxID_APPLY);
	registerID("yes",wxID_YES);
	registerID("no",wxID_NO);
	registerID("static",wxID_STATIC);
	registerID("forward",wxID_FORWARD);
	registerID("backward",wxID_BACKWARD);
	registerID("default",wxID_DEFAULT);
	registerID("more",wxID_MORE);
	registerID("setup",wxID_SETUP);
	registerID("reset",wxID_RESET);
	registerID("context_help",wxID_CONTEXT_HELP);
	registerID("yes_to_all",wxID_YESTOALL);
	registerID("no_to_all",wxID_NOTOALL);
	registerID("abort",wxID_ABORT);
	registerID("retry",wxID_RETRY);
	registerID("ignore",wxID_IGNORE);
	registerID("add",wxID_ADD);
	registerID("remove",wxID_REMOVE);

	registerID("up",wxID_UP);
	registerID("down",wxID_DOWN);
	registerID("home",wxID_HOME);
	registerID("refresh",wxID_REFRESH);
	registerID("stop",wxID_STOP);
	registerID("index",wxID_INDEX);

	registerID("bold",wxID_BOLD);
	registerID("italic",wxID_ITALIC);
	registerID("justify_center",wxID_JUSTIFY_CENTER);
	registerID("justify_fill",wxID_JUSTIFY_FILL);
	registerID("justify_right",wxID_JUSTIFY_RIGHT);
	registerID("justify_left",wxID_JUSTIFY_LEFT);
	registerID("underline",wxID_UNDERLINE);
	registerID("indent",wxID_INDENT);
	registerID("unindent",wxID_UNINDENT);
	registerID("zoom_100",wxID_ZOOM_100);
	registerID("zoom_fit",wxID_ZOOM_FIT);
	registerID("zoom_in",wxID_ZOOM_IN);
	registerID("zoom_out",wxID_ZOOM_OUT);
	registerID("undelete",wxID_UNDELETE);
	registerID("revert_to_saved",wxID_REVERT_TO_SAVED);
	registerID("cdrom",wxID_CDROM);
	registerID("convert",wxID_CONVERT);
	registerID("execute",wxID_EXECUTE);
	registerID("floppy",wxID_FLOPPY);
	registerID("harddisk",wxID_HARDDISK);
	registerID("bottom",wxID_BOTTOM);
	registerID("first",wxID_FIRST);
	registerID("last",wxID_LAST);
	registerID("top",wxID_TOP);
	registerID("info",wxID_INFO);
	registerID("jump_to",wxID_JUMP_TO);
	registerID("network",wxID_NETWORK);
	registerID("select_color",wxID_SELECT_COLOR);
	registerID("select_font",wxID_SELECT_FONT);
	registerID("sort_asc",wxID_SORT_ASCENDING);
	registerID("sort_desc",wxID_SORT_DESCENDING);
	registerID("spell_check",wxID_SPELL_CHECK);
	registerID("strikethrough",wxID_STRIKETHROUGH);

    /*  System menu IDs (used by wxUniv): */
	registerID("system_menu",wxID_SYSTEM_MENU);
	registerID("close_frame",wxID_CLOSE_FRAME);
	registerID("move_frame",wxID_MOVE_FRAME);
	registerID("resize_frame",wxID_RESIZE_FRAME);
	registerID("maximize_frame",wxID_MAXIMIZE_FRAME);
	registerID("iconize_frame",wxID_ICONIZE_FRAME);
	registerID("restore_frame",wxID_RESTORE_FRAME);

	registerEventType("paint",wxEVT_PAINT);
}
