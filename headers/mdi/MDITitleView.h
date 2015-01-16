/***********************************************************************/
/* MDITitleView.h                                                      */
/*                                                                     */
/* Title tab for a MDI view.                                           */
/*                                                                     */
/*               Copyright 2000, www.3rd-evolution.de                  */
/*                                                                     */
/* Author : Thomas Krammer                                             */
/*                                                                     */
/* For any comments, bugs or thanks, please email us.                  */
/* Email :   info@3rd-evolution.de                                     */
/*                                                                     */
/***********************************************************************/

#ifndef MDI_TITLE_VIEW_H
#define MDI_TITLE_VIEW_H

//! file=MDITitleView.h

#include <mdi/ViewAction.h>
#include <mdi/Decoration.h>
#include <mdi/Color.h>
#include <mdi/TitledView.h>
#include <mdi/MDICommon.h>

class CMDITitleMouseAction;

//: Displays the title of a MDI view.
// <P>This view simulates a BeOS title tab. It contains a close button and
// a maximize button. Both buttons are drawn by a decoration, which is
// attached to this view. Those decorations are created using the
// global decoration factory.</P>
// <P>It works together with the classes CMDIClientView and CMDIView.
// A CMDITitleView object must be connected to a CMDIView during creation.
// See CTitledView for more information on this creation process. A
// CMDITitleView expects to be a direct child of a CMDIClientView.</P>
// <P>Normally you don't need to create a title view. The
// CMDIClientView automatically creates a title view, if you attach
// a MDI view to it.</P>
class CMDITitleView : 
	public CTitleView, 
	public IHitTest
{
	public:
	CMDITitleView(BRect frame, CTitledView *targetView);
	//: Destructor
	virtual ~CMDITitleView();
	
	virtual void Draw(BRect updateRect);
	virtual void MouseDown(BPoint point);
	virtual void MouseMoved(BPoint point, uint32 transit, const BMessage *message);
	virtual void MouseUp(BPoint point);
	
	virtual void GetPreferredSize(float *width, float *height);

	virtual void Activate(bool activate);
	//: Returns true, if the target view is active.
	virtual bool Active() { return active; }
	virtual void TargetTitleChanged();
	virtual void TargetResized(float width, float height);
	virtual void TargetMoved(BPoint point);
	
	//: Returns the state of the close button.
	bool CloseButtonPressed() const { return closeButton->Pressed(); }
	//: Returns the state of the maximize button.
	bool MaximizeButtonPressed() const { return maximizeButton->Pressed(); }

	//: Set the state of the close button.
	// Called by the mouse action to change the state of the button.
	void SetCloseButtonPressed(bool down) { closeButton->SetPressed(down); }
	//: Set the state of the maximize button.
	// Called by the mouse action to change the state of the button.
	void SetMaximizeButtonPressed(bool down) { maximizeButton->SetPressed(down); }
	
	protected:
	virtual int32 HitTest(BPoint point);
	virtual void GetTitleFont(BFont *font);
	virtual void GetTitleWidthAndPos(float &width, BPoint &pos);
	virtual CColor BackgroundColor();

	virtual bool DisplayCloseButton();
	virtual bool DisplayMaximizeButton();	
	
	virtual BRect CloseButtonRect();
	virtual BRect MaximizeButtonRect();
	
	//: True, if the the target view is active.
	// The title tab of the active view is displayed in yellow,
	// the title tab of all other views in light gray.
	bool				active;
	//: Maximize button decoration.
	// Draws the maximize button. This decoration is created
	// throught the global IDecorationFactory object.
	IButtonDecoration    *maximizeButton;
	//: Close button decoration.
	// Draws the close button. This decoration is created
	// throught the global IDecorationFactory object.
	IButtonDecoration    *closeButton;
	//: Attached mouse action.
	// Handles all mouse events for this class.
	CMDITitleMouseAction *mouseAction;

	//: Distance of the title from the close box.
	static const float distFromCloseBox;
	//: Distance of the title form the maximize box.
	static const float distFromMaximizeBox;
	//: Distance of the title from right border.
	static const float distFromRightBorder;
	//: Distance of the close box from left border.
	static const float distFromLeftBorder;
	//: Distance of the close box from top border.
	static const float distFromTopBorder;
	//: Distance of the close box from bottom border.
	static const float distFromBottomBorder;
};

#endif // MDI_TITLE_VIEW_H
