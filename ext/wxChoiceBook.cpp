/*
 * wxChoiceBook.cpp
 *
 *  Created on: 15.04.2012
 *      Author: hanmac
 */


#include "wxBookCtrl.hpp"
#include "wxChoiceBook.hpp"

VALUE rb_cWXChoicebook;

#if wxUSE_CHOICEBOOK
#define _self wrap<wxChoicebook*>(self)

namespace RubyWX {
namespace Choicebook {

APP_PROTECT(wxChoicebook)

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

}
}
#endif
void Init_WXChoiceBookCtrl(VALUE rb_mWX)
{
#if wxUSE_CHOICEBOOK
	using namespace RubyWX::Choicebook;
	rb_cWXChoicebook = rb_define_class_under(rb_mWX,"ChoiceBookCtrl",rb_cWXBookCtrlBase);
	rb_define_alloc_func(rb_cWXChoicebook,_alloc);

	rb_define_method(rb_cWXChoicebook,"initialize",RUBY_METHOD_FUNC(_initialize),-1);

	registerInfo<wxChoicebook>(rb_cWXChoicebook);
#endif

}


