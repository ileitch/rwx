/*
 * wxStaticBox.cpp
 *
 *  Created on: 24.04.2012
 *      Author: hanmac
 */

#include "wxStaticBox.hpp"
#include "wxSizer.hpp"

VALUE rb_cWXStaticBox;

#if wxUSE_STATBOX
#define _self wrap<wxStaticBox*>(self)

namespace RubyWX {
namespace StaticBox {

APP_PROTECT(wxStaticBox)

VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE parent,hash;
	rb_scan_args(argc, argv, "11",&parent,&hash);
	_self->Create(wrap<wxWindow*>(parent),wxID_ANY,wxEmptyString);
	_created = true;
	rb_call_super(argc,argv);
	return self;
}

VALUE _GetContainingSizer(VALUE self)
{
	wxSizer * result = _self->GetContainingSizer();
	if(result)
		return wrap(result);
	else
		return wrap(dynamic_cast<wxBoxSizer*>(new wxStaticBoxSizer(_self,wxHORIZONTAL)));
}

}
}
#endif
void Init_WXStaticBox(VALUE rb_mWX)
{
#if wxUSE_STATBOX
	using namespace RubyWX::StaticBox;
	rb_cWXStaticBox = rb_define_class_under(rb_mWX,"StaticBox",rb_cWXControl);
	rb_define_alloc_func(rb_cWXStaticBox,_alloc);

	rb_define_method(rb_cWXStaticBox,"initialize",RUBY_METHOD_FUNC(_initialize),-1);


	rb_define_method(rb_cWXStaticBox,"containing_sizer",RUBY_METHOD_FUNC(_GetContainingSizer),0);// :nodoc:

	registerInfo<wxStaticBox>(rb_cWXStaticBox);
#endif

}




