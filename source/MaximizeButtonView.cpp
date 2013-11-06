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
#include "Decoration.h"
#include "MaximizeButtonView.h"

//: Constructor
// All paramters are passed to the BControl constructor.
CMaximizeButtonView::CMaximizeButtonView(
	BRect frame, const char *name, 
	BMessage *message, uint32 resizingMode, uint32 flags) :
	BControl(frame, name, name, message, resizingMode, flags)
{
	mouseTracking  = false;
	windowActive   = true;
	
	maximizeButton = DecorationFactory()->CreateMaximizeButton(this);
}

CMaximizeButtonView::~CMaximizeButtonView()
{
	delete maximizeButton;
}

//: BeOS hook function
// Fills the view with the background color and calls 
// CMaximizeButton::Draw.
void CMaximizeButtonView::Draw(BRect updateRect)
{
	float width  = Bounds().Width();
	float height = Bounds().Height();

	CColor	background	= BackgroundColor();

	CColor light(239, 239, 239);
	CColor shadow(184, 184, 184);
	CColor darkShadow(152, 152, 152);

	SetHighColor(background);
	FillRect(Bounds());
	
	BeginLineArray(5);
	AddLine(BPoint(1,0), BPoint(1, height-1), light);
	AddLine(BPoint(1,0), BPoint(width, 0), light);
	AddLine(BPoint(2,height-1), BPoint(width, height-1), shadow);
	AddLine(BPoint(0,height), BPoint(width, height), darkShadow);
	AddLine(BPoint(0,0), BPoint(0, height-1), shadow);
	EndLineArray();
	
	maximizeButton->SetBackgroundColor(background);
	maximizeButton->SetPosition(MaximizeButtonRect().LeftTop());
	maximizeButton->Draw();
}

//: BeOS hook function
// Updates the member variable 'windowActive'.
void CMaximizeButtonView::WindowActivated(bool active)
{
	if(windowActive != active) {
		windowActive = active;
		Invalidate();
	}
}

//: BeOS hook function
// Sets the view color to transparent.
void CMaximizeButtonView::AttachedToWindow()
{
	SetViewColor(CColor::Transparent);
}

//: Returns the background color of the control
// Returns CColor::BeTitleBarYellow is the parent window is active,
// else CColor::BeBackgroundGray.
CColor CMaximizeButtonView::BackgroundColor()
{
	return windowActive ? CColor::BeTitleBarYellow : CColor::BeBackgroundGray;
}

//: Returns the bounding rectangle of the maximize button.
// The maximize button is centered in the view.
BRect CMaximizeButtonView::MaximizeButtonRect()
{
	float buttonWidth  = maximizeButton->Width();
	float buttonHeight = maximizeButton->Height();

	// center button
	float x = (Bounds().Width() - buttonWidth) / 2 + 1;
	float y = (Bounds().Height() - buttonHeight) / 2 - 1;

	return BRect(x, y, x+buttonWidth, y+buttonHeight);
}

//: BeOS hook function
void CMaximizeButtonView::MouseDown(BPoint point)
{
	if(MaximizeButtonRect().Contains(point)) {
		maximizeButton->SetPressed(true);
		SetMouseEventMask(B_POINTER_EVENTS, B_NO_POINTER_HISTORY);
		
		mouseTracking = true;
	}
}

//: BeOS hook function
void CMaximizeButtonView::MouseMoved(BPoint point, uint32 transit, const BMessage *message)
{
	if(mouseTracking) {
		if(MaximizeButtonRect().Contains(point)) {
			maximizeButton->SetPressed(true);
		} else {
			maximizeButton->SetPressed(false);
		}
	}
}

//: BeOS hook function
void CMaximizeButtonView::MouseUp(BPoint point)
{
	if(MaximizeButtonRect().Contains(point)) {
		Invoke();
	}
	
	maximizeButton->SetPressed(false);
	mouseTracking = false;
}