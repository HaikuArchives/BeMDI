/***********************************************************************/
/* TitledView.h                                                        */
/*                                                                     */
/* Definition for the classes CTitledView and CTitleView.              */
/*                                                                     */
/*               Copyright 2000, www.3rd-evolution.de                  */
/*                                                                     */
/* Author : Thomas Krammer                                             */
/*                                                                     */
/* For any comments, bugs or thanks, please email us.                  */
/* Email :   info@3rd-evolution.de                                     */
/*                                                                     */
/***********************************************************************/

#ifndef TITLED_VIEW_H
#define TITLED_VIEW_H

//! file=TitledView.h

#include <mdi/ZOrderedView.h>

class CTitledView;

//: Base class for title tabs.
// <P>A title view displays the title of a titled view. That titled view
// is called 'target'. The size and position of a title view normally depends
// on the size and position of the target. If the target is moved or
// resize it must notify its title view. Therfore it must be derived
// from CTitledView.</P>
// <P>The title view holds a pointer to its target and vice versa.
// Such a pair should be created in this order:
// <OL>
// <LI>Create the titled view.
// <LI>Create a title view and pass the titled view to its constructor.
// <LI>Call CTitledView::SetTitleView and pass a pointer to the
// title view to it.
// <LI>Add both views to a CZOrderedViewManager using Z_AddChild.
// </OL>
class CTitleView : public CZOrderedView
{
	public:
	//: Constructor
	CTitleView(BRect frame, CTitledView *targetView, uint32 resizingMode, uint32 flags);
	//: Destructor
	virtual ~CTitleView() {}

	virtual void Activate(bool activate);
	virtual void TargetTitleChanged();
	virtual void TargetResized(float width, float height);
	virtual void TargetMoved(BPoint point);

	//: Returns the target.
	CTitledView *Target() const { return target; }
	//: Sets the target.
	void SetTarget(CTitledView *newTarget) { target = newTarget; }
	
	protected:
	//: The target view.
	CTitledView *target;
};

//: View with a title tab.
// See CTitleView for details.
class CTitledView : public CZOrderedView
{
	public:
	CTitledView(BRect frame, const char *name, uint32 resizingMode, uint32 flags=B_FRAME_EVENTS);

	//: Destructor
	virtual ~CTitledView() {}
	
	//: Returns the title of this view.
	// Returns the title which is displayed in the title view.
	// Currently the title is identical to the name of the view.
	virtual const char *Title() { return Name() ? Name() : ""; }

	//: Sets the title of this view.
	// Currently the title is identical to the name of the view.
	virtual void SetTitle(const char *n) { SetName(n); titleView->TargetTitleChanged(); }
	
	//: Sets the title view.
	virtual void SetTitleView(CTitleView *newTitleView) { titleView = newTitleView; }
	//: Returns the title view.
	virtual CTitleView *TitleView() { return titleView; }
	
	virtual void Activate(bool activate);
	virtual void FrameMoved(BPoint point);
	virtual void FrameResized(float width, float height);
	
	protected:
	//: Title view.
	CTitleView *titleView;
};

#endif // TITLED_VIEW_H
