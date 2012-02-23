/*
 * wxEvtHandler.cpp
 *
 *  Created on: 17.02.2012
 *      Author: hanmac
 */


#include "wxEvtHandler.hpp"
#include "wxEvent.hpp"

#define _self wrap<wxEvtHandler*>(self)

VALUE rb_cWXEvtHandler;

wxEventType unwrapEventType(VALUE type)
{
	if(!SYMBOL_P(type))
		return NUM2INT(type);
	ID id = SYM2ID(type);
	if(id == rb_intern("menu_selected")){
		return wxEVT_COMMAND_MENU_SELECTED;
	}
	if(id==rb_intern("button_clicked"))
		return wxEVT_COMMAND_BUTTON_CLICKED;

	return wxEVT_NULL;
}

class RubyFunctor
#ifndef wxHAS_EVENT_BIND
 : public wxEvtHandler
#endif
{
public:
	RubyFunctor(VALUE obj) : mValue(obj){
	}
	void call( wxEvent & event )
	{
		event.Skip(RTEST(rb_funcall(mValue,rb_intern("call"),1,wrap(event.Clone()))));
	}
	void operator()( wxEvent & event )
	{
		call(event);
	}

private:
	VALUE mValue;
};

namespace RubyWX {
namespace EvtHandler {
VALUE _alloc(VALUE self) {
	return wrap(new wxEvtHandler);
}

VALUE _bind(int argc,VALUE *argv,VALUE self)
{
	VALUE type,id,last,proc;
	rb_scan_args(argc, argv, "12&",&type,&id,&last,&proc);

	int wxid = NIL_P(id) ? wxID_ANY : NUM2INT(id);
	int wxlast = NIL_P(last) ? wxID_ANY : NUM2INT(last);

	if(NIL_P(proc))
		proc = rb_block_proc();
#ifdef wxHAS_EVENT_BIND
	_self->Bind(wxEventTypeTag<wxEvent>(unwrapEventType(type)),RubyFunctor(proc),wxid,wxlast);
#else
	_self->Connect(wxid,wxlast,unwrapEventType(type),(wxObjectEventFunction)&RubyFunctor::call,NULL,new RubyFunctor(proc));
#endif
	return self;
}

VALUE _fire(int argc,VALUE *argv,VALUE self)
{
	VALUE type,id;
	rb_scan_args(argc, argv, "11",&type,&id);
	int wxid;
	if(NIL_P(id))
		wxid = wxID_ANY;
	else
		wxid = NUM2INT(id);

	wxMenuEvent e(unwrapEventType(type),wxid);
	_self->ProcessEvent(e);
	return self;

}
}
}


void Init_WXEvtHandler(VALUE rb_mWX)
{
	using namespace RubyWX::EvtHandler;
	rb_cWXEvtHandler = rb_define_class_under(rb_mWX,"EvtHandler",rb_cObject);
	rb_define_alloc_func(rb_cWXEvtHandler,_alloc);

	rb_define_method(rb_cWXEvtHandler,"bind",RUBY_METHOD_FUNC(_bind),-1);
	rb_define_method(rb_cWXEvtHandler,"call",RUBY_METHOD_FUNC(_fire),-1);
}


