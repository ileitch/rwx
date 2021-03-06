/*
 * wxToolBarBase.cpp
 *
 *  Created on: 30.03.2012
 *      Author: hanmac
 */

#include "wxToolBarBase.hpp"
#include "wxBitmap.hpp"
#include "wxToolBarTool.hpp"
#include "wxControl.hpp"

VALUE rb_cWXToolBarBase;

#define _self unwrapPtr<wxToolBarBase>(self,rb_cWXToolBarBase)

namespace RubyWX {
namespace ToolBarBase {

macro_attr(ToolBitmapSize,wxSize)
macro_attr(Margins,wxSize)

macro_attr(ToolPacking,int)
macro_attr(ToolSeparation,int)

VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE parent,hash;
	rb_scan_args(argc, argv, "11",&parent,&hash);
	rb_call_super(argc,argv);
	return self;
}

VALUE _addNormal(int argc,VALUE *argv,VALUE self)
{
	VALUE id,text,bitmap,bmpDisabled,shorthelp,longhelp,arg;
	wxToolBarToolBase *tool = NULL;
	wxControl *c = NULL;
	rb_scan_args(argc, argv, "11*",&id,&text,&arg);
	if(rb_obj_is_kind_of(id,rb_cWXControl)){
		c = wrap<wxControl*>(id);
		if(c->GetParent() != _self)
			rb_raise(rb_eArgError, "%s has wrong parent.",wrap<char*>(id));
	}else if(rb_obj_is_kind_of(id,rb_cClass) && rb_class_inherited(id,rb_cWXControl)) {
		rb_scan_args(argc, argv, "11",&id,&arg);
		VALUE argv2[] = {self, arg };
		c = wrap<wxControl*>(rb_class_new_instance(2,argv2,id));
	}else {
		rb_scan_args(argc, argv, "24",&id,&text,&bitmap,&bmpDisabled,&shorthelp,&longhelp);
		wxWindowID wxid = unwrapID(id);
		tool = _self->AddTool(wxid, wrap<wxString>(text),
				wrapBitmap(bitmap,wxid,false,wxART_TOOLBAR),
				wrapBitmap(bmpDisabled,wxid,true,wxART_TOOLBAR),wxITEM_NORMAL,
				wrap<wxString>(shorthelp), wrap<wxString>(longhelp));
	}
	if(c)
		tool = _self->AddControl(c,wrap<wxString>(text));

	if(rb_block_given_p() && !c){
		VALUE proc = rb_block_proc();
#ifdef wxHAS_EVENT_BIND
		_self->Bind(wxEVT_COMMAND_MENU_SELECTED,RubyFunctor(proc),tool->GetId());
#else
		_self->Connect(tool->GetId(),wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RubyFunctor::operator()),NULL,new RubyFunctor(proc));
#endif
	}
	return wrap(tool);
}


VALUE _addCheck(int argc,VALUE *argv,VALUE self)
{
	VALUE id,text,bitmap,bmpDisabled,shorthelp,longhelp;
	rb_scan_args(argc, argv, "24",&id,&text,&bitmap,&bmpDisabled,&shorthelp,&longhelp);
	wxWindowID wxid = unwrapID(id);

	wxToolBarToolBase *tool = _self->AddCheckTool(unwrapID(id), wrap<wxString>(text),
				wrapBitmap(bitmap,wxid,false,wxART_TOOLBAR),
				wrapBitmap(bmpDisabled,wxid,true,wxART_TOOLBAR),
				wrap<wxString>(shorthelp), wrap<wxString>(longhelp));

	if(rb_block_given_p()){
		VALUE proc = rb_block_proc();
#ifdef wxHAS_EVENT_BIND
		_self->Bind(wxEVT_COMMAND_MENU_SELECTED,RubyFunctor(proc),tool->GetId());
#else
		_self->Connect(tool->GetId(),wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RubyFunctor::operator()),NULL,new RubyFunctor(proc));
#endif
	}

	return wrap(tool);
}


VALUE _addRadio(int argc,VALUE *argv,VALUE self)
{
	VALUE id,text,bitmap,bmpDisabled,shorthelp,longhelp;
	rb_scan_args(argc, argv, "24",&id,&text,&bitmap,&bmpDisabled,&shorthelp,&longhelp);
	wxWindowID wxid = unwrapID(id);
	wxToolBarToolBase *tool = _self->AddRadioTool(unwrapID(id), wrap<wxString>(text),
			wrapBitmap(bitmap,wxid,false,wxART_TOOLBAR),
			wrapBitmap(bmpDisabled,wxid,true,wxART_TOOLBAR),
			wrap<wxString>(shorthelp), wrap<wxString>(longhelp));

	if(rb_block_given_p()){
		VALUE proc = rb_block_proc();
#ifdef wxHAS_EVENT_BIND
_self->Bind(wxEVT_COMMAND_MENU_SELECTED,RubyFunctor(proc),tool->GetId());
#else
_self->Connect(tool->GetId(),wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RubyFunctor::operator()),NULL,new RubyFunctor(proc));
#endif
	}

	return wrap(tool);
}

VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	size_t count = _self->GetToolsCount();
	for(size_t i = 0; i < count; ++i)
	{
		rb_yield(wrap(const_cast<wxToolBarToolBase*>(_self->GetToolByPos(i))));
	}
	return self;
}


singlereturn(AddSeparator)
singlereturn(AddStretchableSpace)

singlereturn(Realize)

}
}

void Init_WXToolBarBase(VALUE rb_mWX)
{
	using namespace RubyWX::ToolBarBase;
	rb_cWXToolBarBase = rb_define_class_under(rb_mWX,"ToolBarBase",rb_cWXControl);
	rb_undef_alloc_func(rb_cWXToolBarBase);

	rb_define_method(rb_cWXToolBarBase,"initialize",RUBY_METHOD_FUNC(_initialize),-1);

	rb_define_method(rb_cWXToolBarBase,"addNormal",RUBY_METHOD_FUNC(_addNormal),-1);
	rb_define_method(rb_cWXToolBarBase,"addCheck",RUBY_METHOD_FUNC(_addCheck),-1);
	rb_define_method(rb_cWXToolBarBase,"addRadio",RUBY_METHOD_FUNC(_addRadio),-1);

	rb_define_method(rb_cWXToolBarBase,"addSeparator",RUBY_METHOD_FUNC(_AddSeparator),0);
	rb_define_method(rb_cWXToolBarBase,"addStretchableSpace",RUBY_METHOD_FUNC(_AddStretchableSpace),0);

	rb_define_method(rb_cWXToolBarBase,"realize",RUBY_METHOD_FUNC(_Realize),0);


	rb_define_method(rb_cWXToolBarBase,"each_tool",RUBY_METHOD_FUNC(_each),0);

}
