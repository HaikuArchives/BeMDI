/***********************************************************************/
/* MDICommon.h                                                         */
/*                                                                     */
/* Common types and definitions.                                       */
/*                                                                     */
/*               Copyright 2000, www.3rd-evolution.de                  */
/*                                                                     */
/* Author : Thomas Krammer                                             */
/*                                                                     */
/* For any comments, bugs or thanks, please email us.                  */
/* Email :   info@3rd-evolution.de                                     */
/*                                                                     */
/***********************************************************************/

#ifndef MDI_COMMON_H
#define MDI_COMMON_H

//! file=MDICommon.h

enum enumMouseAction
{
	MDI_MA_NONE,
	MDI_MA_SIZE,
	MDI_MA_MOVE,
	MDI_MA_CLOSE_BOX_PRESSED,
	MDI_MA_MAXIMIZE_BOX_PRESSED,
};

enum enumNonClientHitTest
{
	MDI_NC_NONE,
	MDI_NC_SIZE_EDGE,
	MDI_NC_BORDER,
	MDI_NC_CLOSE_BOX,
	MDI_NC_MAXIMIZE_BOX,
	MDI_NC_TITLE_TAB,
};

enum enumMDIViewFlags
{
	// View isn't movable.
	MDI_NOT_MOVABLE		= 0x00000001,

	// View isn't closable.
	MDI_NOT_CLOSABLE	= 0x00000002,

	// View isn't resizable.
	MDI_NOT_RESIZABLE	= 0x00000004,

    // View has no title tab.
	MDI_NO_TITLE_TAB	= 0x00000008,

	// Force redraw for views below, whenever this view is moved
	// or resized. Set this flag, if your view has a view color
	// other than TRANSPARENT. You should normally avoid this,
	// because it's a lot slower. (And flickers).
	MDI_REDRAW_BELOW	= 0x00000010,	

    // View isn't minimizable.
	MDI_NOT_MINIMIZABLE = 0x00000020,

    // View isn't maximizable.
	MDI_NOT_MAXIMIZABLE = 0x00000040,
};

//: Message id.
// A message with this 'what' field can be send to a CMDIClientView
// to tile the MDI views horizontally.
const int32 MDI_MSG_TILE_VIEWS_HORIZONTAL	= 'mTVH';

//: Message id.
// A message with this 'what' field can be send to a CMDIClientView
// to tile the MDI views vertically.
const int32 MDI_MSG_TILE_VIEWS_VERTICAL		= 'mTVV';

//: Message id.
// A message with this 'what' field can be send to a CMDIClientView
// to stack the MDI views.
const int32 MDI_MSG_STACK_VIEWS				= 'mSVS';

//: Message id.
// A message with this 'what' field can be send to a CMDIClientView
// to activate a MDI view. Which MDI view is activated is
// specified in the MDI_MSG_DATA_VIEW data field of the message.
const int32 MDI_MSG_ACTIVATE_VIEW			= 'mACT';

//: Message id.
// A message with this 'what' field can be send to a CMDIClientView
// to maximize a MDI view. Which MDI view is maximized is
// specified in the MDI_MSG_DATA_VIEW data field of the message.
const int32 MDI_MSG_MAXIMIZE_VIEW			= 'mMAX';

//: Message id.
// A message with this 'what' field can be send to a CMDIClientView
// to minimize a MDI view. Which MDI view is minimized is
// specified in the MDI_MSG_DATA_VIEW data field of the message.
const int32 MDI_MSG_MINIMIZE_VIEW			= 'mMIN';

//: Message id.
// A message with this 'what' field can be send to a CMDIClientView
// to restore the currently maximized MDI view. If no view
// is maximized this message has no effect.
const int32 MDI_MSG_RESTORE_VIEW			= 'mRES';

//: Message data field id.
// A message data field with this name contains a MDI view pointer.
// The type must be set to B_POINTER_TYPE and the field must
// contain a CMDIView pointer.
extern const char * const MDI_MSG_DATA_VIEW;	

#endif // MDI_COMMON_H