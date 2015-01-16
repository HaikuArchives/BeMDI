/***********************************************************************/
/* MaximizeButtonView.h                                                */
/*                                                                     */
/* The maximize button control.                                        */
/*                                                                     */
/*               Copyright 2000, www.3rd-evolution.de                  */
/*                                                                     */
/* Author : Thomas Krammer                                             */
/*                                                                     */
/* For any comments, bugs or thanks, please email us.                  */
/* Email :   info@3rd-evolution.de                                     */
/*                                                                     */
/***********************************************************************/

#ifndef MAXIMIZE_BUTTON_VIEW_H
#define MAXIMIZE_BUTTON_VIEW_H

//! file=MaximizeButtonView.h

#include <mdi/Decoration.h>

//: Displays a BeOS style maximize button.
// This class is derived from BControl and behaves like any other
// control. It posts a message to its target, when it's activated.
class CMaximizeButtonView : 
	public BControl
{
	public:
	CMaximizeButtonView(BRect frame, const char *name, BMessage *message,
		uint32 resizingMode, uint32 flags=B_WILL_DRAW);

	//: Destructor
	virtual ~CMaximizeButtonView();

	virtual void Draw(BRect updateRect);
	virtual void AttachedToWindow();
	virtual void WindowActivated(bool active);
	virtual void MouseDown(BPoint point);
	virtual void MouseMoved(BPoint point, uint32 transit, const BMessage *message);
	virtual void MouseUp(BPoint point);
	
	protected:
	virtual CColor BackgroundColor();
	virtual BRect MaximizeButtonRect();
	
	//: Maximize button decoration.
	// This attached decoration does all the drawing. It is created
	// throught the global IDecorationFactory object.	
	IButtonDecoration *maximizeButton;
	//: True, if control is in mouse tracking mode.
	bool mouseTracking;
	//: True, if parent window is active.
	bool windowActive;
};

#endif // MAXIMIZE_BUTTON_VIEW_H
