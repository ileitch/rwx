/*
 * wxBookCtrl.cpp
 *
 *  Created on: 26.03.2012
 *      Author: hanmac
 */



#include "wxEvtHandler.hpp"
#include "wxSizer.hpp"

VALUE rb_cWXBookCtrlBase,rb_cWXBookCtrlEvent;

#if wxUSE_BOOKCTRL
#define _self wrap<wxBookCtrlBase*>(self)

namespace RubyWX {
namespace BookCtrl {

macro_attr(ImageList,wxImageList*)
macro_attr(InternalBorder,unsigned int)
macro_attr(ControlMargin,int)
macro_attr(Selection,int)

singlereturn(GetControlSizer)
singlereturn(GetCurrentPage)

VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE parent,hash;
	rb_scan_args(argc, argv, "11",&parent,&hash);
	if(!_created)
	{
		_self->Create(wrap<wxWindow*>(parent),wxID_ANY);
		_created = true;
	}
	rb_call_super(argc,argv);
	return self;
}

VALUE _page(VALUE self,VALUE i)
{
	return wrap(_self->GetPage(NUM2UINT(i)));
}

VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	size_t count = _self->GetPageCount();
	for(size_t i = 0; i < count; ++i)
		rb_yield(wrap(_self->GetPage(i)));
	return self;
}

VALUE _addPage(int argc,VALUE *argv,VALUE self)
{
	VALUE window,text,select,imageid,hash;
	wxWindow *w = NULL;
	bool sel = false;
	int iid = -1;
	rb_scan_args(argc, argv, "23",&window,&text,&select,&imageid,&hash);
	if(rb_obj_is_kind_of(select,rb_cHash))
		hash = select;
	else if(!NIL_P(select))
	{
		sel = RTEST(select);
		if(rb_obj_is_kind_of(imageid,rb_cHash))
			hash = imageid;
		else if(!NIL_P(imageid))
			iid = NUM2INT(imageid);
	}

	if(rb_obj_is_kind_of(window,rb_cClass) && rb_class_inherited(window,rb_cWXWindow)) {
		VALUE argv2[] = {self, hash };
		w = wrap<wxWindow*>(rb_class_new_instance(2,argv2,window));
	}else
	{
		w = wrap<wxWindow*>(window);
//		if(w->GetParent() != _self)
//			rb_raise(rb_eArgError, "%s has wrong parent.",wrap<char*>(window));
	}
	return wrap(_self->AddPage(w,wrap<wxString>(text),sel,iid));
}

VALUE _insertPage(int argc,VALUE *argv,VALUE self)
{
	VALUE n,window,text,select,imageid,hash;
	wxWindow *w = NULL;
	bool sel = false;
	int iid = -1;
	rb_scan_args(argc, argv, "33",&n,&window,&text,&select,&imageid,&hash);
	if(rb_obj_is_kind_of(select,rb_cHash))
		hash = select;
	else if(!NIL_P(select))
		sel = RTEST(select);
	if(rb_obj_is_kind_of(imageid,rb_cHash))
		hash = imageid;
	else if(!NIL_P(select))
		iid = NUM2INT(imageid);

	if(rb_obj_is_kind_of(window,rb_cWXWindow)){
		w = wrap<wxWindow*>(window);
//		if(w->GetParent() != _self)
//			rb_raise(rb_eArgError, "%s has wrong parent.",wrap<char*>(window));
	}else if(rb_obj_is_kind_of(window,rb_cClass) && rb_class_inherited(window,rb_cWXWindow)) {
		VALUE argv2[] = {self, hash };
		w = wrap<wxWindow*>(rb_class_new_instance(2,argv2,window));
	}
	return wrap(_self->InsertPage(NUM2INT(n),w,wrap<wxString>(text),sel,iid));
}

singlefunc(DeleteAllPages)


namespace Event {
#undef _self
#define _self unwrapPtr<wxBookCtrlEvent>(self,rb_cWXBookCtrlEvent)
macro_attr(Selection,int)
macro_attr(OldSelection,int)
}

}
}
#endif
void Init_WXBookCtrl(VALUE rb_mWX)
{
#if wxUSE_BOOKCTRL
	using namespace RubyWX::BookCtrl;
	rb_cWXBookCtrlBase = rb_define_class_under(rb_mWX,"BookCtrl",rb_cWXControl);
	rb_undef_alloc_func(rb_cWXBookCtrlBase);

	rb_define_method(rb_cWXBookCtrlBase,"initialize",RUBY_METHOD_FUNC(_initialize),-1);

	rb_define_method(rb_cWXBookCtrlBase,"add_page",RUBY_METHOD_FUNC(_addPage),-1);
	rb_define_method(rb_cWXBookCtrlBase,"insert_page",RUBY_METHOD_FUNC(_insertPage),-1);

	rb_define_method(rb_cWXBookCtrlBase,"each_page",RUBY_METHOD_FUNC(_each),0);

	rb_define_method(rb_cWXBookCtrlBase,"page",RUBY_METHOD_FUNC(_page),1);

	rb_define_method(rb_cWXBookCtrlBase,"current_page",RUBY_METHOD_FUNC(_GetCurrentPage),0);

	rb_define_method(rb_cWXBookCtrlBase,"delete_all_pages",RUBY_METHOD_FUNC(_DeleteAllPages),0);

	rb_cWXBookCtrlEvent = rb_define_class_under(rb_cWXEvent,"BookCtrl",rb_cWXEvent);

	rb_define_attr_method(rb_cWXBookCtrlEvent,"selection",Event::_getSelection,Event::_setSelection);
	rb_define_attr_method(rb_cWXBookCtrlEvent,"old_selection",Event::_getOldSelection,Event::_setOldSelection);

	registerInfo<wxBookCtrlBase>(rb_cWXBookCtrlBase);
#endif

}



