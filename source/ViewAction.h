/***********************************************************************/
/* ViewAction.h                                                        */
/*                                                                     */
/* Classes and interfaces for mouse handling delegation.               */
/*                                                                     */
/*               Copyright 2000, www.3rd-evolution.de                  */
/*                                                                     */
/* Author : Thomas Krammer                                             */
/*                                                                     */
/* For any comments, bugs or thanks, please email us.                  */
/* Email :   info@3rd-evolution.de                                     */
/*                                                                     */
/***********************************************************************/

#ifndef VIEW_ACTION_H
#define VIEW_ACTION_H

//! file=ViewAction.h

//: Interface for classes controled by mouse handlers.
// This interface must be implemented by views passed as controled view
// to CViewMouseAction.
class IHitTest
{
	public:
	//: Returns the area the mouse is over.
	// The returned value totally depends on the implemenation.
	// Normally its some number which uniquely identifies some
	// area of the view.
	virtual int32 HitTest(BPoint point) = 0;
};

//: Interface for mouse handlers.
// See CViewMouseAction for details.
class IMouseAction
{
	public:
	//: Handler for MouseDown.
	// Call this method in your view's implemenation of BView::MouseDown.
	virtual void MouseDown(BPoint point) = 0;
	//: Handler for MouseMoved.
	// Call this method in your view's implemenation of BView::MouseMoved.
	virtual void MouseMoved(BPoint point, uint32 transit) = 0;
	//: Handler for MouseUp.
	// Call this method in your view's implemenation of BView::MouseUp.
	virtual void MouseUp(BPoint point) = 0;
};

//: Base class for mouse handlers.
// <P>A mouse action object does the mouse handling for a view. The view
// calls the according mouse action methods in its implementation of
// the MouseDown, MouseUp and MouseMoved hook functions.</P>
// <P>The mouse action object takes all actions to handle the mouse message
// e.g move the controled view, resize it or call some method of the
// controled view. The action taken normally depends on the area 
// the mouse is over.
// Therefore the controled view must implenent the IHitTest interface.</P>
// <P>This separation of mouse handler and view allows you to create a
// class hierarchy of mouse handles indepentent from view's class
// hierarchy.</P>
class CViewMouseAction : public IMouseAction
{
	public:
	//: Constructor
	CViewMouseAction(BView *controledView) : controled(controledView) {}

	//: Returns the area the mouse is over.
	// Calls the IHitTest::HitTest implementation of the view.
	// Crashes, if the view doesn't support the IHitTest interface.
	virtual int32 HitTest(BPoint point)
	{
		IHitTest *hitTest = dynamic_cast<IHitTest *>(controled);
		return hitTest->HitTest(point);
	}

	//: Moves the controled view.
	// Calls BView::MoveTo.
	virtual void MoveControledTo(float x, float y)
	{
		controled->MoveTo(x, y);
	}
	
	//: Resizes the controled view.
	// Calls BView::ResizeTo.
	virtual void ResizeControledTo(float vert, float horz)
	{
		controled->ResizeTo(vert, horz);
	}
	
	inline  void MoveControledBy(float vert, float horz);
	inline  void MoveControledTo(BPoint point);
	inline  void ResizeControledBy(float vert, float horz);

	//: Returns the controled view.
	inline BView *Controled() { return controled; }
	
	protected:
	//: Controled view.
	BView *controled;
};

//: Moves the controled view.
// Calls MoveControledTo
void CViewMouseAction::MoveControledBy(float horz, float vert)
{
	BPoint leftTop = controled->Frame().LeftTop();

	MoveControledTo(leftTop.x+horz, leftTop.y+vert);
}

//: Moves the controled view.
// Calls MoveControledTo.
void CViewMouseAction::MoveControledTo(BPoint point)
{
	MoveControledTo(point.x, point.y);
}

//: Resizes the controled view.
// Calls ResizeControledTo
void CViewMouseAction::ResizeControledBy(float horz, float vert)
{
	BRect bounds = controled->Bounds();

	ResizeControledTo(bounds.Width()+horz, bounds.Height()+vert);
}

#endif // VIEW_ACTION_H