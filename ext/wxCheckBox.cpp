/*
 * wxCheckBox.cpp
 *
 *  Created on: 01.05.2012
 *      Author: hanmac
 */


#include "wxControl.hpp"

VALUE rb_cWXCheckBox;

#if wxUSE_CHECKBOX
#define _self wrap<wxCheckBox*>(self)

namespace RubyWX {
namespace CheckBox {

macro_attr(Value,bool)

APP_PROTECT(wxCheckBox)

VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE parent,hash;
	int style = 0;
	rb_scan_args(argc, argv, "11",&parent,&hash);
	if(rb_obj_is_kind_of(hash,rb_cHash))
	{
		VALUE temp;
		if(!NIL_P(temp=rb_hash_aref(hash,ID2SYM(rb_intern("style")))))
			style = NUM2INT(temp);
	}

	_self->Create(wrap<wxWindow*>(parent),wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,style);
	_created = true;
	rb_call_super(argc,argv);
	return self;
}

}
}
#endif
DLL_LOCAL void Init_WXCheckBox(VALUE rb_mWX)
{
#if wxUSE_CHECKBOX
	using namespace RubyWX::CheckBox;
	rb_cWXCheckBox = rb_define_class_under(rb_mWX,"CheckBox",rb_cWXControl);
	rb_define_alloc_func(rb_cWXCheckBox,_alloc);

	rb_define_method(rb_cWXCheckBox,"initialize",RUBY_METHOD_FUNC(_initialize),-1);

	rb_define_attr_method(rb_cWXCheckBox,"value",_getValue,_setValue);

	registerInfo<wxCheckBox>(rb_cWXCheckBox);
#endif

}

