/*
 * wxFileCtrlBase.hpp
 *
 *  Created on: 07.05.2012
 *      Author: hanmac
 */

#ifndef WXFILECTRLBASE_HPP_
#define WXFILECTRLBASE_HPP_

#include "wxControl.hpp"

extern VALUE rb_cWXFileCtrlBase;

void Init_WXFileCtrlBase(VALUE rb_mWX);
#if wxUSE_FILECTRL
#include <wx/filectrl.h>
#endif

#endif /* WXFILECTRLBASE_HPP_ */
