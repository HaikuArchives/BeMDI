/***********************************************************************/
/*                                NOTICE                               */
/*                                ------                               */
/*               Copyright 2000, www.3rd-evolution.de                  */
/*                                                                     */
/*                    This software was developed by                   */
/*                            3rd-Evolution                            */
/*                                                                     */
/* Any reproduction of this software in whole or in part must contain  */
/*                   this notice in its entirety.                      */
/*                                                                     */
/* 3rd-Evolution  is  providing this  software "as is"  and  makes no  */
/* warranty, express or  implied,  as  to  the  accuracy,  capability, */
/* efficiency,  merchantability,  or  functioning  of  this  software  */
/* and/or documentation. In no event will 3rd-evolution be liable for  */
/* any  general,  consequential,   indirect,  incidental,   exemplary, */
/* or special damages, even  if 3rd-evolution has been advised of the  */
/* possibility  of such damages,  irrespective  of  the cause of such  */
/* damages.  For short: 3rd-evolution is impeccable and so any damage  */
/* is your fault.                                                      */
/*                                                                     */
/* Permission  to use, copy, modify, and distribute this software for  */
/* any purpose and without  fee is hereby  granted. For  any comments, */
/* bugs or thanks, please email us: info@3rd-evolution.de              */
/*                                                                     */
/***********************************************************************/

#include "pch.h"
#include "TitledView.h"

//: Constructor
CTitleView::CTitleView(BRect frame, CTitledView *targetView, uint32 resizingMode, uint32 flags) :
	CZOrderedView(frame, "TitleView", resizingMode, flags)
{
	target = targetView;
	target->SetTitleView(this);
	
	BString name="TitleView:";
	
	name += target->Title();
	
	SetName(name.String());
}

//: Called, when this view or its target is activated or deactivated.
// Normally the color of the title tab depends on its activation
// state. So a derived view can overwrite this method to
// invalidate the view, when its activation changes.
// The implemenation of this method is empty.
void CTitleView::Activate(bool activate)
{
}

//: Called, when the title of the target changes.
// The implemenation of this method is empty.
void CTitleView::TargetTitleChanged()
{
}

//: Called, when the target is resized.
// The implemenation of this method is empty.
void CTitleView::TargetResized(float width, float height)
{
}

//: Called, when the target is moved.
// The implemenation of this method is empty.
void CTitleView::TargetMoved(BPoint point)
{
}

// ==== CTitledView ====

//: Constructor
CTitledView::CTitledView(BRect frame, const char *name, uint32 resizingMode, uint32 flags) :
	CZOrderedView(frame, name, resizingMode, flags)
{
	titleView = NULL;
}

//: BeOS hook function
// Notifies the title view.
void CTitledView::FrameMoved(BPoint point)
{
	CZOrderedView::FrameMoved(point);

	if(titleView)
		titleView->TargetMoved(point);
}

//: BeOS hook function
// Notifies the title view.
void CTitledView::FrameResized(float width, float height)
{
	CZOrderedView::FrameResized(width, height);

	if(titleView)
		titleView->TargetResized(width, height);
}

//: Called, when this view is activated or deactivated.
// Notifies the title view.
void CTitledView::Activate(bool activate)
{ 
	if(titleView)
		titleView->Activate(activate);
}
