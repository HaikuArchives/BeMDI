/***********************************************************************/
/* MDIView.h                                                           */
/*                                                                     */
/* Contains the class CMDIView.                                        */
/*                                                                     */
/*               Copyright 2000, www.3rd-evolution.de                  */
/*                                                                     */
/* Author : Thomas Krammer                                             */
/*                                                                     */
/* For any comments, bugs or thanks, please email us.                  */
/* Email :   info@3rd-evolution.de                                     */
/*                                                                     */
/***********************************************************************/

#ifndef MDI_VIEW_H
#define MDI_VIEW_H

//! file=MDIView.h

#include <mdi/ViewAction.h>
#include <mdi/TitledView.h>
#include <mdi/MDICommon.h>

class CMDIClientView;
class CMDIMouseAction;

//: MDI view
// <P>This class works together with CMDIClientView and CMDITitleView. 
// A MDI view must be a direct child of a CMDIClientView. That client
// view manages the MDI views and their z-order. CMDITitleView displays
// a the title of a MDI view. You normally don't create an instance
// of CMDITitleView. The CMDIClientView does that for you, when
// you attach the MDI view to the client view.</P>
// <P>Like any other view a MDI view can contain child views. These
// child views are added to the so called 'client area'. The client area
// is surrounded by a border. You can request the size of the client
// area by calling the ClientRect method.</P>
// <P>To speed up drawing the child views of a MDI view should set their
// view color to B_TRANSPARENT_COLOR and fill the view with the
// background color in their implementation of BView::Draw. If that isn't
// possible (e.g. because you are using a BeOS control) you must set
// the MDI_REDRAW_BELOW flag for the MDI view.</P>
// <P>If your MDI view is maximizeable it should contain only one direct
// child. That child (ChildAt(0)) replaces the CMDIClientView when the
// MDI view is maximized.</P>
class CMDIView :
	public CTitledView, 
	public IHitTest
{
	public:
	CMDIView(BRect frame, const char *name, uint32 mdiFlags=0, uint32 resizingMode=B_FOLLOW_NONE, uint32 flags=0);
	CMDIView(BRect frame, const char *name, BView *client, uint32 mdiFlags=0, bool resizeToClient=true);
	//: Destructor
	virtual ~CMDIView();

	void Init();
	
	virtual void Draw(BRect updateRect);
	virtual void MouseDown(BPoint point);
	virtual void MouseMoved(BPoint point, uint32 transit, const BMessage *message);
	virtual void MouseUp(BPoint point);
	virtual void FrameResized(float width, float height);
	virtual void Activate(bool activate);
	//: Returns true, if this view is the active MDI view.
	virtual bool Active() { return active; }

	//: Called when the view should be closed.
	// When the user presses the close button of a MDI view's title tab,
	// it calls this method. If it returns false the view isn't
	// closed. The default implementation returns true.	
	virtual bool CanClose() { return true; }
	
	virtual BRect ClientRect();

	void SetSizeLimits(float _minWidth, float _maxWidth, float _minHeight, float _maxHeight);
	void GetSizeLimits(float *_minWidth, float *_maxWidth, float *_minHeight, float *_maxHeight) const;

	//: Returns true if the MDI_REDRAW_BELOW flag is set.
	virtual bool RedrawBelow() { return mdiFlags & MDI_REDRAW_BELOW; }

	//: Returns the MDI flags.
	// See constructor for a list of possible flags.
	uint32 MDIFlags() const			{ return mdiFlags; }
	
	protected:
	virtual int32 HitTest(BPoint point);

	virtual BRegion BorderRegion();
	virtual BRegion SizeEdgeRegion(BRegion &borderRegion);
	
	//: Region occupied by the border.
	// This region is only used for hit tests. It isn't used
	// for clipping.
	BRegion borderRegion;

	//: Region occupied by the size edge.
	// This region is only used for hit tests. It isn't used
	// for clipping. This region is even valid if the MDI_NOT_RESIZABLE
	// is set.
	BRegion sizeEdgeRegion;
	
	//: True, if this view is the active view.
	bool active;

	//: Flags
	// See constructor for a list of possible flags.
	uint32 mdiFlags;

	//: Attached mouse action
	// Handles all mouse events for this class.
	CMDIMouseAction *mouseAction;

	//: Minimum width
	float minWidth; 
	//: Maximum width
	float maxWidth;
	//: Minimum height
	float minHeight;
	//: Maximum height
	float maxHeight;
	
	//: Initial value for 'minWidth'
	static const float defaultMinWidth;
	//: Initial value for 'minHeight'
	static const float defaultMinHeight;
	//: Initial value for 'maxWidth'
	static const float defaultMaxWidth;
	//: Initial value for 'maxHeight'
	static const float defaultMaxHeight;

	//: Width of the size edge.	
	static const float sizeEdgeWidth;
	//: Height of the size edge.	
	static const float sizeEdgeHeight;
};

#endif // MDI_VIEW_H
